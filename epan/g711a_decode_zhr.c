#include <stdio.h>
#include <stdlib.h>
#include "decode_zhr.h"

int uuu_g711a(unsigned char u_val)
{
	int	t;	
	u_val = ~u_val;	t = ((u_val & 0xf) << 3) + 0x84;
	t <<= ((unsigned)u_val & 0x70) >> 4;
	return ((u_val & 0x80) ? (0x84 - t) : (t - 0x84));
}

int aaa_g711a(unsigned char a_val)
{
	int	t,	seg;
	a_val ^= 0x55;	t = (a_val & 0xf) << 4;	seg = ((unsigned)a_val & 0x70) >> 4;
	switch (seg) {
	case 0:
		t += 8;	break;
	case 1:
		t += 0x108;	break;
	default:
		t += 0x108;	t <<= seg - 1;
	}
	return ((a_val & 0x80) ? t : -t);
}

void g711a_decode(unsigned char out[], unsigned char in[], int len)
{
	int i, j;
	for(i=0;i<len;i++){ j=aaa_g711a(in[i]); out[2*i]=j>>8&0xff; out[2*i+1]=j&0xff;}
	return;
}


void g711a_decode_zhr(char filename1[],  char filename2[], rtp_voice_match_e* voice_e)
{
	int i , ll ,len, m, n ;
	FILE *fp, *fn, *outfile;
	char file[256], outfilename[256];
	unsigned char *in1, *in2, *out, *out1, *out2;

	fp = fopen(filename1 , "rb"); 	fn = fopen(filename2 , "rb");
	if(fp==NULL && fn==NULL){printf("no file!\n"); return; }
	if(fp==NULL)
	{
		fseek(fn, 0,SEEK_END); ll=ftell(fn); in2=(unsigned char *)malloc(ll); rewind(fn); fread(in2,sizeof(char),ll,fn);fclose(fn); out2=(unsigned char *)malloc(ll*2);
		n=0; for(i=0; i<ll;)
		{
			m=in2[i+8]+(in2[i+9]<<8)+(in2[i+10]<<16)+(in2[i+11]<<24); i+=12;
			g711a_decode( out2+n, in2+i, m);	 n+=m*2; i+=m;
		}		
		sprintf(file, "%s.single.wav",filename2);
		if((outfile= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }
		pcm_to_wav(out2, n, outfile, 8000, 1);
        fclose(outfile);

		free(in2);
		free(out2);
		sprintf(outfilename, "%s.single.mp3",filename2);
		wav_to_mp3(file, outfilename,8000,1);

		voice_e->paired = 0;
		strcpy(voice_e->one_part, filename2);
		strcpy(voice_e->mp3_name, outfilename);
		strcpy(voice_e->wav_name, file);

		return;
	}
	if(fn==NULL)
	{
		fseek(fp, 0,SEEK_END); ll=ftell(fp); in1=(unsigned char *)malloc(ll); rewind(fp); fread(in1,sizeof(char),ll,fp);fclose(fp); out1=(unsigned char *)malloc(ll*2);
		n=0; for(i=0; i<ll;)
		{
			m=in1[i+8]+(in1[i+9]<<8)+(in1[i+10]<<16)+(in1[i+11]<<24); i+=12;
			g711a_decode( out1+n, in1+i, m);	 n+=m*2; i+=m;
		}
		sprintf(file, "%s.single.wav",filename1);
		if((outfile= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }
		pcm_to_wav(out1, n, outfile, 8000, 1);
        fclose(outfile);
		free(in1);
		free(out1);
		sprintf(outfilename, "%s.single.mp3",filename1);
		wav_to_mp3(file, outfilename,8000,1);

		voice_e->paired = 0;
		strcpy(voice_e->one_part, filename1);
		strcpy(voice_e->mp3_name, outfilename);
		strcpy(voice_e->wav_name, file);

		return;		
	}

	fseek(fp, 0,SEEK_END); ll=ftell(fp); in1=(unsigned char *)malloc(ll); rewind(fp); i=fread(in1,sizeof(char),ll,fp);fclose(fp); out1=(unsigned char *)malloc(ll*2); len=i;
	fseek(fn, 0,SEEK_END); ll=ftell(fn); in2=(unsigned char *)malloc(ll); rewind(fn); fread(in2,sizeof(char),ll,fn);  fclose(fn); out2=(unsigned char *)malloc(ll*2);
	n=0; for(i=0; i<len;)
	{
		m=in1[i+8]+(in1[i+9]<<8)+(in1[i+10]<<16)+(in1[i+11]<<24); i+=12;
		g711a_decode( out1+n, in1+i, m);	 n+=m*2; i+=m;
	}
	len=n;
	n=0; for(i=0; i<ll;)
	{
		m=in2[i+8]+(in2[i+9]<<8)+(in2[i+10]<<16)+(in2[i+11]<<24); i+=12;
		g711a_decode( out2+n, in2+i, m);	 n+=m*2; i+=m;
	}
	ll=n;

	sprintf(file, "%s.paired.wav",filename1);
	if((outfile= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }
	if(len>=ll)
	{
		out=(unsigned char *)malloc(len*2);
		for(i=0; i<ll; i+=2){	out[2*i]=out1[i]; out[2*i+1]=out1[i+1]; out[2*i+2]=out2[i]; out[2*i+3]=out2[i+1];}
        for(i=ll;i<len;i+=2){	out[2*i]=out1[i]; out[2*i+1]=out1[i+1]; out[2*i+2]=0; out[2*i+3]=0;}
		pcm_to_wav(out, len*2, outfile, 8000, 2);
	}
	if(len<ll) {
		out = (unsigned char *) malloc(ll * 2);
		for (i=0;  i<len;i+=2) {out[2*i]=out1[i]; out[2*i+1]=out1[i+1];out[2*i+2]=out2[i]; out[2*i+3]=out2[i+1];}
        for (i=len;i<ll; i+=2) {out[2*i]=0;       out[2*i+1]=0;        out[2*i+2]=out2[i]; out[2*i+3]=out2[i+1];}
		pcm_to_wav(out, ll*2, outfile, 8000, 2);
	}

	fclose(outfile);
	free(in1);
	free(out1);
	free(in2);
	free(out2);
	free(out);

	sprintf(outfilename, "%s.paired.mp3",filename1);
	wav_to_mp3(file, outfilename,8000,2);

	voice_e->paired = 1;
	strcpy(voice_e->one_part, filename1);
	strcpy(voice_e->opposite_part, filename2);
	strcpy(voice_e->mp3_name, outfilename);
	strcpy(voice_e->wav_name, file);

}





