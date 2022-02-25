#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "write_in_files_handlers.h"


#ifndef ACCENCODE_TYPE_H
#define ACCENCODE_TYPE_H
typedef unsigned char   	uint8_t;
typedef short				Int16;
typedef short				int16_t;
typedef int					Int32;
typedef int					int32_t;
typedef unsigned char		UInt8;
typedef unsigned short		UInt16;
typedef unsigned int		UInt32;
#endif //ACCENCODE_TYPE_H

enum
{
    G722_SAMPLE_RATE_8000 = 0x0001,
    G722_PACKED = 0x0002
};
typedef struct
{    
    int itu_test_mode;    
    int packed;    
    int eight_k;    
    int bits_per_sample;
    int x[24];
    struct
    {
        int s;
        int sp;
        int sz;
        int r[3];
        int a[3];
        int ap[3];
        int p[3];
        int d[7];
        int b[7];
        int bp[7];
        int sg[7];
        int nb;
        int det;
    } band[2];
    
    unsigned int in_buffer;
    int in_bits;
    unsigned int out_buffer;
    int out_bits;
} g722_decode_state_t;

static __inline int16_t saturate(int32_t amp)
{
    int16_t amp16;
    amp16 = (int16_t) amp;
    if (amp == amp16)  return amp16;
    if (amp > 32767)  return  32767;//WEBRTC_INT16_MAX;
    return  -32768;
}
/*- End of function --------------------------------------------------------*/


static void block4(g722_decode_state_t *s, int band, int d)
{
    int wd1;
    int wd2;
    int wd3;
    int i;

    /* Block 4, RECONS */
    s->band[band].d[0] = d;
    s->band[band].r[0] = saturate(s->band[band].s + d);

    /* Block 4, PARREC */
    s->band[band].p[0] = saturate(s->band[band].sz + d);

    /* Block 4, UPPOL2 */
    for (i = 0;  i < 3;  i++)
        s->band[band].sg[i] = s->band[band].p[i] >> 15;
    wd1 = saturate(s->band[band].a[1] << 2);

    wd2 = (s->band[band].sg[0] == s->band[band].sg[1])  ?  -wd1  :  wd1;
    if (wd2 > 32767)
        wd2 = 32767;
    wd3 = (s->band[band].sg[0] == s->band[band].sg[2])  ?  128  :  -128;
    wd3 += (wd2 >> 7);
    wd3 += (s->band[band].a[2]*32512) >> 15;
    if (wd3 > 12288)
        wd3 = 12288;
    else if (wd3 < -12288)
        wd3 = -12288;
    s->band[band].ap[2] = wd3;

    /* Block 4, UPPOL1 */
    s->band[band].sg[0] = s->band[band].p[0] >> 15;
    s->band[band].sg[1] = s->band[band].p[1] >> 15;
    wd1 = (s->band[band].sg[0] == s->band[band].sg[1])  ?  192  :  -192;
    wd2 = (s->band[band].a[1]*32640) >> 15;

    s->band[band].ap[1] = saturate(wd1 + wd2);
    wd3 = saturate(15360 - s->band[band].ap[2]);
    if (s->band[band].ap[1] > wd3)
        s->band[band].ap[1] = wd3;
    else if (s->band[band].ap[1] < -wd3)
        s->band[band].ap[1] = -wd3;

    /* Block 4, UPZERO */
    wd1 = (d == 0)  ?  0  :  128;
    s->band[band].sg[0] = d >> 15;
    for (i = 1;  i < 7;  i++)
    {
        s->band[band].sg[i] = s->band[band].d[i] >> 15;
        wd2 = (s->band[band].sg[i] == s->band[band].sg[0])  ?  wd1  :  -wd1;
        wd3 = (s->band[band].b[i]*32640) >> 15;
        s->band[band].bp[i] = saturate(wd2 + wd3);
    }

    /* Block 4, DELAYA */
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
/*- End of function --------------------------------------------------------*/

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
/*- End of function --------------------------------------------------------*/

/*- End of function --------------------------------------------------------*/

int WebRtc_g722_decode(g722_decode_state_t *s, int16_t amp[],  const uint8_t g722_data[], int len)
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
        if (s->itu_test_mode) { amp[outlen++] = (int16_t) (rlow << 1);  amp[outlen++] = (int16_t) (rhigh << 1); }
        else
        {
            if (s->eight_k) { amp[outlen++] = (int16_t) (rlow << 1); }
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

typedef struct WebRtcG722DecInst    G722DecInst;
G722DecInst*  m_pG722Decode = NULL;

int16_t WebRtcG722_CreateDecoder(G722DecInst **G722dec_inst)
{
    *G722dec_inst = (G722DecInst *) malloc(sizeof(g722_decode_state_t));
    if (*G722dec_inst != NULL) return (0); else  return (-1);
}

int16_t WebRtcG722_DecoderInit(G722DecInst *G722dec_inst)
{
    // Create and/or reset the G.722 decoder  // Bitrate 64 kbps and wideband mode (2)
    G722dec_inst = (G722DecInst *) WebRtc_g722_decode_init((g722_decode_state_t *) G722dec_inst, 16000, 2);
    if (G722dec_inst == NULL)  return -1;  else return 0;
}

unsigned char AU_header[24] = {'.','s','n','d',0,0,0,0x18,0xff,0xff,0xff,0xff,0,0,0,0x03,0,0,0x3e,0x80,0,0,0,0x01}; 
int g722decode(unsigned char *data,int len, unsigned char *out)
{
	unsigned char se;
	int i,j,n=0;
	for(j=0;j<len;j+=172)for(i=0;i<160;i++)data[n++]=data[j+i+12];
	printf("%d %d\n",len,n);
	free(m_pG722Decode);
	if (WebRtcG722_CreateDecoder(&m_pG722Decode) != 0)printf("CreateDecoder failed\n");
	if (WebRtcG722_DecoderInit(m_pG722Decode)    != 0)printf("DecoderInit failed\n");		
	Int32 nDecode = WebRtc_g722_decode((g722_decode_state_t *)m_pG722Decode, (Int16*)out+24, data, n);
	j=nDecode * sizeof(Int16);
	for(i=0;i<24;i++)out[i]=AU_header[i];
	for(i=0;i<j;i+=2){se=out[i+24]; out[i+24]=out[i+1+24]; out[i+1+24]=se;};
	return j+24;
}

//void main()
//{
//	int i, ll;
//	FILE *fp;
//	unsigned char *data, *out;
//
//	if((fp= fopen("10_0_2_15_1747210_0_2_20_6000.stream","rb"))==NULL){  printf("OPEN FILE FAIL\n");   return ; }
//	fseek(fp, 0,SEEK_END);  ll = ftell(fp);
//	data = (unsigned char *)malloc(ll);
//    rewind(fp);   i = fread(data,sizeof(char),ll,fp);fclose(fp); //printf("%d %d\n",i, ll);
//	out = (unsigned char *)malloc(ll*4);
//	ll = g722decode(data, ll, out);	//	printf("%d\n",ll);
//	fp = fopen("tmp.au", "wb");
//	fwrite(out, 1, ll, fp);
//	fclose(fp);
//	free(data); free(out);
//	return ;
//}
