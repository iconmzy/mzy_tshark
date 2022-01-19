#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode_zhr.h"

enum
{
    G722_SAMPLE_RATE_8000 = 0x0001,
    G722_PACKED = 0x0002
};
typedef struct
{    
    int itu_test_mode;    int packed;        int eight_k;        int bits_per_sample;    int x[24];
    struct
    {
        int s;        int sp;        int sz;        int r[3];        int a[3];        int ap[3];        int p[3];
        int d[7];        int b[7];        int bp[7];        int sg[7];        int nb;        int det;
    } band[2];    
    unsigned int in_buffer;    int in_bits;    unsigned int out_buffer;    int out_bits;
} g722_decode_state_t;



static __inline short saturate(int amp)
{
    short amp16;
    amp16 = (short) amp;
    if (amp == amp16)  return amp16;
    if (amp > 32767)  return  32767;//WEBRTC_short_MAX;
    return  -32768;
}

static void block4(g722_decode_state_t *s, int band, int d)
{
    int wd1, wd2, wd3, i;
    
    s->band[band].d[0] = d;
    s->band[band].r[0] = saturate(s->band[band].s + d);    
    s->band[band].p[0] = saturate(s->band[band].sz + d);

    for (i = 0;  i < 3;  i++)  s->band[band].sg[i] = s->band[band].p[i] >> 15;
    wd1 = saturate(s->band[band].a[1] << 2);

    wd2 = (s->band[band].sg[0] == s->band[band].sg[1])  ?  -wd1  :  wd1;
    if (wd2 > 32767)   wd2 = 32767;
    wd3 = (s->band[band].sg[0] == s->band[band].sg[2])  ?  128  :  -128;
    wd3 += (wd2 >> 7);
    wd3 += (s->band[band].a[2]*32512) >> 15;
    if (wd3 > 12288)   wd3 = 12288;
    else if (wd3 < -12288)     wd3 = -12288;
    s->band[band].ap[2] = wd3;

    s->band[band].sg[0] = s->band[band].p[0] >> 15;
    s->band[band].sg[1] = s->band[band].p[1] >> 15;
    wd1 = (s->band[band].sg[0] == s->band[band].sg[1])  ?  192  :  -192;
    wd2 = (s->band[band].a[1]*32640) >> 15;

    s->band[band].ap[1] = saturate(wd1 + wd2);
    wd3 = saturate(15360 - s->band[band].ap[2]);
    if (s->band[band].ap[1] > wd3)   s->band[band].ap[1] = wd3;
    else if (s->band[band].ap[1] < -wd3)   s->band[band].ap[1] = -wd3;
    
    wd1 = (d == 0)  ?  0  :  128;
    s->band[band].sg[0] = d >> 15;
    for (i = 1;  i < 7;  i++)
    {
        s->band[band].sg[i] = s->band[band].d[i] >> 15;
        wd2 = (s->band[band].sg[i] == s->band[band].sg[0])  ?  wd1  :  -wd1;
        wd3 = (s->band[band].b[i]*32640) >> 15;
        s->band[band].bp[i] = saturate(wd2 + wd3);
    }
    
    for (i = 6;  i > 0;  i--)
    {
        s->band[band].d[i] = s->band[band].d[i - 1];
        s->band[band].b[i] = s->band[band].bp[i];
    }
    
    for (i = 2;  i > 0;  i--)
    {
        s->band[band].r[i] = s->band[band].r[i - 1];
        s->band[band].p[i] = s->band[band].p[i - 1];
        s->band[band].a[i] = s->band[band].ap[i];
    }

    /* Block 4, FILTEP */
    wd1 = saturate(s->band[band].r[1] + s->band[band].r[1]);
    wd1 = (s->band[band].a[1]*wd1) >> 15;
    wd2 = saturate(s->band[band].r[2] + s->band[band].r[2]);
    wd2 = (s->band[band].a[2]*wd2) >> 15;
    s->band[band].sp = saturate(wd1 + wd2);

    /* Block 4, FILTEZ */
    s->band[band].sz = 0;
    for (i = 6;  i > 0;  i--)
    {
        wd1 = saturate(s->band[band].d[i] + s->band[band].d[i]);
        s->band[band].sz += (s->band[band].b[i]*wd1) >> 15;
    }
    s->band[band].sz = saturate(s->band[band].sz);
    /* Block 4, PREDIC */
    s->band[band].s = saturate(s->band[band].sp + s->band[band].sz);
}


g722_decode_state_t *WebRtc_g722_decode_init(g722_decode_state_t *s, int rate, int options)
{
    if (s == NULL) { if ((s = (g722_decode_state_t *) malloc(sizeof(*s))) == NULL) return NULL;  }
    memset(s, 0, sizeof(*s));
    if (rate == 48000)       s->bits_per_sample = 6;
    else if (rate == 56000)  s->bits_per_sample = 7;  else       s->bits_per_sample = 8;
    if ((options & G722_SAMPLE_RATE_8000))   s->eight_k = 1;
    if ((options & G722_PACKED)  &&  s->bits_per_sample != 8)   s->packed = 1;   else   s->packed = 0;
    s->band[0].det = 32;
    s->band[1].det = 8;
    return s;
}

int WebRtc_g722_decode(g722_decode_state_t *s, short amp[],  const unsigned char g722_data[], int len)
{
    static const int wl[8] = {-60, -30, 58, 172, 334, 538, 1198, 3042 };
    static const int rl42[16] = {0, 7, 6, 5, 4, 3, 2, 1, 7, 6, 5, 4, 3,  2, 1, 0 };
    static const int ilb[32] = {
        2048, 2093, 2139, 2186, 2233, 2282, 2332,  2383, 2435, 2489, 2543, 2599, 2656, 2714, 2774, 2834,
		2896, 2960, 3025, 3091, 3158,  3228, 3298, 3371, 3444, 3520, 3597, 3676, 3756, 3838, 3922, 4008};
    static const int wh[3] = {0, -214, 798};
    static const int rh2[4] = {2, 1, 2, 1};
    static const int qm2[4] = {-7408, -1616,  7408,   1616};
    static const int qm4[16] = { 0, -20456, -12896,  -8968, -6288,  -4240,  -2584,  -1200, 20456,  12896,  8968,  6288, 4240, 2584, 1200, 0 };
    static const int qm5[32] = {
           -280,   -280, -23352, -17560, -14120, -11664,  -9752,  -8184, -6864,  -5712,  -4696,  -3784, -2960,  -2208,  -1520,   -880,
          23352,  17560,  14120,  11664,  9752,   8184,   6864,   5712,  4696,   3784,   2960,   2208,  1520,    880,    280,   -280 };
    static const int qm6[64] = {
           -136,   -136,   -136,   -136, -24808, -21904, -19008, -16704, -14984, -13512, -12280, -11192, -10232,  -9360,  -8576,  -7856,
          -7192,  -6576,  -6000,  -5456,  -4944,  -4464,  -4008,  -3576,  -3168,  -2776,  -2400,  -2032,  -1688,  -1360,  -1040,   -728,
          24808,  21904,  19008,  16704,  14984,  13512,  12280,  11192,  10232,   9360,   8576,   7856,   7192,   6576,   6000,   5456,
           4944,   4464,   4008,   3576,   3168,   2776,   2400,   2032,   1688,   1360,   1040,    728,    432,    136,   -432,   -136  };
    static const int qmf_coeffs[12] = { 3,  -11,   12,   32, -210,  951, 3876, -805,  362, -156,   53,  -11, };
    int dlowt, rlow, ihigh, dhigh, rhigh, xout1, xout2, wd1, wd2, wd3, code, outlen, i, j;
    outlen = 0;  rhigh = 0;
    for (j = 0;  j < len;  )
    {
        if (s->packed)
        {           
            if (s->in_bits < s->bits_per_sample) { s->in_buffer |= (g722_data[j++] << s->in_bits); s->in_bits += 8; }
            code = s->in_buffer & ((1 << s->bits_per_sample) - 1);
            s->in_buffer >>= s->bits_per_sample;      s->in_bits -= s->bits_per_sample;
        }
        else { code = g722_data[j++]; }
        switch (s->bits_per_sample)
        {
        default:
        case 8:
            wd1 = code & 0x3F;
            ihigh = (code >> 6) & 0x03;
            wd2 = qm6[wd1];
            wd1 >>= 2;
            break;
        case 7:
            wd1 = code & 0x1F;
            ihigh = (code >> 5) & 0x03;
            wd2 = qm5[wd1];
            wd1 >>= 1;
            break;
        case 6:
            wd1 = code & 0x0F;
            ihigh = (code >> 4) & 0x03;
            wd2 = qm4[wd1];
            break;
        }       
        wd2 = (s->band[0].det*wd2) >> 15;  rlow = s->band[0].s + wd2;        
        if (rlow > 16383)  rlow = 16383;  else if (rlow < -16384)  rlow = -16384;        
        wd2 = qm4[wd1];   dlowt = (s->band[0].det*wd2) >> 15;        
        wd2 = rl42[wd1];  wd1 = (s->band[0].nb*127) >> 7;  wd1 += wl[wd2];
        if (wd1 < 0) wd1 = 0; else if (wd1 > 18432)  wd1 = 18432;
        s->band[0].nb = wd1;            
        
        wd1 = (s->band[0].nb >> 6) & 31;  wd2 = 8 - (s->band[0].nb >> 11);  wd3 = (wd2 < 0)  ?  (ilb[wd1] << -wd2)  :  (ilb[wd1] >> wd2);
        s->band[0].det = wd3 << 2;
        block4(s, 0, dlowt);
        
        if (!s->eight_k)
        {            
            wd2 = qm2[ihigh];  dhigh = (s->band[1].det*wd2) >> 15; rhigh = dhigh + s->band[1].s;            
            if (rhigh > 16383) rhigh = 16383;  else if (rhigh<-16384) rhigh = -16384;            
            wd2 = rh2[ihigh];  wd1 = (s->band[1].nb*127) >> 7; wd1 += wh[wd2];
            if (wd1 < 0) wd1 = 0; else if (wd1 > 22528) wd1 = 22528;
            s->band[1].nb = wd1; wd1 = (s->band[1].nb >> 6) & 31; wd2 = 10 - (s->band[1].nb >> 11);
            wd3 = (wd2 < 0)  ?  (ilb[wd1] << -wd2)  :  (ilb[wd1] >> wd2);
            s->band[1].det = wd3 << 2;
            block4(s, 1, dhigh);
        }
        if (s->itu_test_mode) { amp[outlen++] = (short) (rlow << 1);  amp[outlen++] = (short) (rhigh << 1); }
        else
        {
            if (s->eight_k) { amp[outlen++] = (short) (rlow << 1); }
            else
            {                
                for (i = 0;  i < 22;  i++) s->x[i] = s->x[i + 2];
                s->x[22] = rlow + rhigh;  s->x[23] = rlow - rhigh;   xout1 = 0;  xout2 = 0;
                for (i = 0;  i < 12;  i++) { xout2 += s->x[2*i]*qmf_coeffs[i]; xout1 += s->x[2*i + 1]*qmf_coeffs[11 - i]; }               
                amp[outlen++] = saturate(xout1 >> 11);  amp[outlen++] = saturate(xout2 >> 11);
            }
        }
    } return outlen;
}




/*
unsigned char AU_header[24] = {'.','s','n','d',0,0,0,0x18,0xff,0xff,0xff,0xff,0,0,0,0x03,0,0,0x3e,0x80,0,0,0,0x02}; //0x803e0000, 0x401f0000; //16000 or 8000
void main()
{	
	int i, j, ll, len;
	//unsigned int t1,t2,t3,t4;
	FILE *fp;	
	unsigned char *sc, *sd, *out1, *out2;
	unsigned char se, sf[2];
	g722_decode_state_t *m_pG722Decode = NULL;
	g722_decode_state_t *n_pG722Decode = NULL;

    if((fp= fopen("c0a80040_c0a80078_1ba6_1ba6.g722","rb"))==NULL){  printf("OPEN FILE FAIL\n");   return ; }
	fseek(fp, 0,SEEK_END);  ll = ftell(fp);  sc = (unsigned char *)malloc(ll);   rewind(fp);   i = fread(sc,sizeof(char),ll,fp);fclose(fp);	len=ll;

	if((fp= fopen("c0a80078_c0a80040_1ba6_1ba6.g722","rb"))==NULL){  printf("OPEN FILE FAIL\n");   return ; }
	fseek(fp, 0,SEEK_END);  ll = ftell(fp);  sd = (unsigned char *)malloc(ll);   rewind(fp);   i = fread(sd,sizeof(char),ll,fp);fclose(fp);	

	out1  = (unsigned char*)malloc(2000);	out2  = (unsigned char*)malloc(2000);	
	if((fp= fopen("tmp_g722.au","wb"))==NULL){  printf("OPEN FILE FAIL\n");   return ; }
	fwrite(AU_header, 1, 24, fp);

	m_pG722Decode= (g722_decode_state_t *) malloc(sizeof(g722_decode_state_t));	
	n_pG722Decode= (g722_decode_state_t *) malloc(sizeof(g722_decode_state_t));	
	WebRtc_g722_decode_init((g722_decode_state_t *)m_pG722Decode, 16000, 2);
	WebRtc_g722_decode_init((g722_decode_state_t *)n_pG722Decode, 16000, 2);

	if(len>=ll)
	{
		for(i=0;i<ll;i+=172)
		{
			
			WebRtc_g722_decode((g722_decode_state_t *)m_pG722Decode, (short*)out1, sc+i+12, 160);			
			WebRtc_g722_decode((g722_decode_state_t *)n_pG722Decode, (short*)out2, sd+i+12, 160);
			for(j=0;j<640;j+=2)
			{
				se=out1[j]; out1[j]=out1[j+1]; out1[j+1]=se; fwrite(out1+j,1,2,fp);
				se=out2[j]; out2[j]=out2[j+1]; out2[j+1]=se; fwrite(out2+j,1,2,fp);
			}
		}
		for(i=ll;i<len;i+=172)
		{			
			WebRtc_g722_decode((g722_decode_state_t *)m_pG722Decode, (short*)out1, sc+i+12, 160);
			//WebRtc_g722_decode((g722_decode_state_t *)n_pG722Decode, (short*)out2, sd+i+12, 160);						
			sf[0]=0; sf[1]=0;
			for(j=0;j<640;j+=2){ se=out1[j]; out1[j]=out1[j+1]; out1[j+1]=se; fwrite(out1+j,1,2,fp);	fwrite(sf,1,2,fp);	}			
		}

	}
	if(len<ll)
	{
		for(i=0;i<len;i+=172)
		{
			
			WebRtc_g722_decode((g722_decode_state_t *)m_pG722Decode, (short*)out1, sc+i+12, 160);			
			WebRtc_g722_decode((g722_decode_state_t *)n_pG722Decode, (short*)out2, sd+i+12, 160);
			for(j=0;j<640;j+=2)
			{
				se=out1[j]; out1[j]=out1[j+1]; out1[j+1]=se; fwrite(out1+j,1,2,fp);
				se=out2[j]; out2[j]=out2[j+1]; out2[j+1]=se; fwrite(out2+j,1,2,fp);
			}			
		}
		for(i=len;i<ll;i+=172)
		{			
			//WebRtc_g722_decode((g722_decode_state_t *)m_pG722Decode, (short*)out1, sc+i+12, 160);
			WebRtc_g722_decode((g722_decode_state_t *)n_pG722Decode, (short*)out2, sd+i+12, 160);
			sf[0]=0; sf[1]=0;
			for(j=0;j<640;j+=2){ fwrite(sf,1,2,fp);	 se=out2[j]; out2[j]=out2[j+1]; out2[j+1]=se; fwrite(out2+j,1,2,fp);	}			
		}
	}
	fclose(fp);
	free(sc); free(sd); free(out1); free(out2);
	return ;
}

*/

void g722_decode_zhr(char filename1[],  char filename2[])
{
	int i, j , ll ,len, m, n ;
	FILE *fp, *fn;
	char file[256], outfilename[256];
	unsigned char *in1, *in2, *out, *out1, *out2, sf[2];
	//unsigned char AU_header[24] = {'.','s','n','d',0,0,0,0x18,0xff,0xff,0xff,0xff,0,0,0,0x03,0,0,0x3e,0x80,0,0,0,0x01 };
	g722_decode_state_t *m_pG722Decode = NULL;
	g722_decode_state_t *n_pG722Decode = NULL;    

	m_pG722Decode= (g722_decode_state_t *) malloc(sizeof(g722_decode_state_t));	
	n_pG722Decode= (g722_decode_state_t *) malloc(sizeof(g722_decode_state_t));	
	WebRtc_g722_decode_init((g722_decode_state_t *)m_pG722Decode, 16000, 2);
	WebRtc_g722_decode_init((g722_decode_state_t *)n_pG722Decode, 16000, 2);



	fp = fopen(filename1 , "rb"); 	fn = fopen(filename2 , "rb");
	if(fp==NULL && fn==NULL){printf("no file!\n"); return; }
	if(fp==NULL)
	{		
		fseek(fn, 0,SEEK_END); ll=ftell(fn); in2=(unsigned char *)malloc(ll); rewind(fn); fread(in2,sizeof(char),ll,fn);fclose(fn); out2=(unsigned char *)malloc(ll*4);
		//printf("%d %d \n",ll,i);
		n=0; for(i=0; i<ll;)
		{
			m=in2[i+8]+(in2[i+9]<<8)+(in2[i+10]<<16)+(in2[i+11]<<24); i+=12;
			WebRtc_g722_decode((g722_decode_state_t *)m_pG722Decode, (short*)(out2+n), in2+i, m);
			//printf("%d %d %d %d %d %d\n",j,n,ll*4,ll,i,m);
			n+=m*4; i+=m;
		}
		for(j=0;j<n;j+=2){sf[0] = out2[j]; out2[j] = out2[j+1]; out2[j+1] = sf[0];}
		//printf("%d %d %d\n",j,n,ll*4);
		sprintf(file, "%s.single.wav",filename2);
		//printf("%s\n",file);
		if((fp= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }

		//fwrite(AU_header, 1, 24, fp);
		//fwrite(out2, 1, n, fp);
		pcm_to_wav(out2, n, fp, 16000, 1);

		fclose(fp);	
		free(in2);
		free(out2);
		free(m_pG722Decode);
		free(n_pG722Decode);

		sprintf(outfilename, "%s.single.mp3",filename2);
		wav_to_mp3(file, outfilename,16000,1);

		return;
	}
	if(fn==NULL)
	{
		fseek(fp, 0,SEEK_END); ll=ftell(fp); in1=(unsigned char *)malloc(ll); rewind(fp); fread(in1,sizeof(char),ll,fp);fclose(fp); out1=(unsigned char *)malloc(ll*4);
		//printf("%d %d\n",i,ll);
		//printf("%s\n",file);
		n=0; for(i=0; i<ll;)
		{
			m=in1[i+8]+(in1[i+9]<<8)+(in1[i+10]<<16)+(in1[i+11]<<24); i+=12;
			WebRtc_g722_decode((g722_decode_state_t *)n_pG722Decode, (short*)(out1+n), in1+i, m);
			n+=m*4; i+=m;
		}
		for(j=0;j<n;j+=2){sf[0] = out1[j]; out1[j] = out1[j+1]; out1[j+1] = sf[0];}
		sprintf(file, "%s.single.wav",filename1);
		if((fp= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }
		//fwrite(AU_header, 1, 24, fp);
		//fwrite(out1, 1, n, fp);
		pcm_to_wav(out1, n, fp, 16000, 1);
		fclose(fp);	
		free(in1);
		free(out1);
		free(m_pG722Decode);
		free(n_pG722Decode);

		sprintf(outfilename, "%s.single.mp3", filename1);
		wav_to_mp3(file, outfilename,16000,1);
		return;		
	}

	fseek(fp, 0,SEEK_END); ll=ftell(fp); in1=(unsigned char *)malloc(ll); rewind(fp); i=fread(in1,sizeof(char),ll,fp);fclose(fp); out1=(unsigned char *)malloc(ll*4); len=i;
	//printf("%d %d\n",i,len);
	fseek(fn, 0,SEEK_END); ll=ftell(fn); in2=(unsigned char *)malloc(ll); rewind(fn); fread(in2,sizeof(char),ll,fn);fclose(fn); out2=(unsigned char *)malloc(ll*4);
	//printf("%d %d \n",ll,i);
	
	n=0; for(i=0; i<len;)
	{
		m=in1[i+8]+(in1[i+9]<<8)+(in1[i+10]<<16)+(in1[i+11]<<24); i+=12;
		WebRtc_g722_decode((g722_decode_state_t *)n_pG722Decode, (short*)(out1+n), in1+i, m);
		n+=m*4; i+=m;
	}
	for(j=0;j<n;j+=2){sf[0] = out1[j]; out1[j] = out1[j+1]; out1[j+1] = sf[0];}
	len=n;

	n=0; for(i=0; i<ll;)
	{
		m=in2[i+8]+(in2[i+9]<<8)+(in2[i+10]<<16)+(in2[i+11]<<24); i+=12;
		WebRtc_g722_decode((g722_decode_state_t *)m_pG722Decode, (short*)(out2+n), in2+i, m);
		n+=m*4; i+=m;
	}
	for(j=0;j<n;j+=2){sf[0] = out2[j]; out2[j] = out2[j+1]; out2[j+1] = sf[0];}
	ll=n;
	sprintf(file, "%s.paired.wav",filename1);
	if((fp= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }

	/*
	AU_header[23]=2;
	fwrite(AU_header, 1, 24, fp);
	if(len>=ll)
	{
		for(i=0;i<ll;i+=2){	fwrite(out1+i,1,2,fp);	fwrite(out2+i,1,2,fp);	}
		for(i=ll;i<len;i+=2){ sf[0]=0; sf[1]=0;		fwrite(out1+i,1,2,fp);	fwrite(sf,1,2,fp);}
	}
	if(len<ll)
	{
		for(i=0;  i<len;i+=2){ fwrite(out1+i,1,2,fp);	fwrite(out2+i,1,2,fp);}		
		for(i=len;i<ll; i+=2){ sf[0]=0; sf[1]=0;		fwrite(sf,1,2,fp);	fwrite(out2+i,1,2,fp);}		
	}
	 */
	if(len>=ll)
	{
		out=(unsigned char *)malloc(len*2);
		for(i=0;i<ll;i+=2){	out[2*i]=out1[i]; out[2*i+1]=out1[i+1]; out[2*i+2]=out2[i]; out[2*i+3]=out2[i+1];}
		for(i=ll;i<len;i+=2){	out[2*i]=out1[i]; out[2*i+1]=out1[i+1]; out[2*i+2]=out2[i]; out[2*i+3]=out2[i+1];}
		pcm_to_wav(out, len*2, fp, 16000, 2);
	}
	if(len<ll) {
		out = (unsigned char *) malloc(ll * 2);
		for (i = 0; i < len; i += 2) {out[2 * i] = out1[i];	out[2 * i + 1] = out1[i + 1];out[2 * i + 2] = out2[i];out[2 * i + 3] = out2[i + 1];	}
		for (i = len; i < ll; i += 2) {	out[2 * i] = out1[i];out[2 * i + 1] = out1[i + 1];out[2 * i + 2] = out2[i];	out[2 * i + 3] = out2[i + 1];}
		pcm_to_wav(out, ll*2, fp, 16000, 2);
	}

	fclose(fp);			
	free(in1);
	free(out1);
	free(out);
	free(in2);
	free(out2);
	free(m_pG722Decode);
	free(n_pG722Decode);

	sprintf(outfilename, "%s.paired.mp3",filename1);
	wav_to_mp3(file, outfilename,16000,2);

}

