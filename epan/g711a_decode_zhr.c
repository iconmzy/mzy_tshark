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


void g711a_decode_zhr(char filename1[],  char filename2[])
{
	int i , ll ,len, m, n ;
	FILE *fp, *fn, *outfile;
	char file[256], outfilename[256];
	unsigned char *in1, *in2, *out, *out1, *out2, sf[2];
	unsigned char AU_header[24] = {'.','s','n','d',0,0,0,0x18,0xff,0xff,0xff,0xff,0,0,0,0x03,0,0,0x1f,0x40,0,0,0,0x01 }; 

	fp = fopen(filename1 , "rb"); 	fn = fopen(filename2 , "rb");
	if(fp==NULL && fn==NULL){printf("no file!\n"); return; }
	if(fp==NULL)
	{
		fseek(fn, 0,SEEK_END); ll=ftell(fn); in2=(unsigned char *)malloc(ll); rewind(fn); fread(in2,sizeof(char),ll,fn);fclose(fn); out2=(unsigned char *)malloc(ll*2);
		//printf("%d %d \n",ll,i);
		n=0; for(i=0; i<ll;)
		{
			m=in2[i+8]+(in2[i+9]<<8)+(in2[i+10]<<16)+(in2[i+11]<<24); i+=12;
			g711a_decode( out2+n, in2+i, m);	 n+=m*2; i+=m;
		}		
		sprintf(file, "%s.single.wav",filename2);
		if((fp= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }
		pcm_to_wav(out2, n, fp, 8000, 1);

		//fwrite(AU_header, 1, 24, fp);
		//fwrite(out2, 1, n, fp);
		fclose(fp);	
		free(in2);
		free(out2);

		sprintf(outfilename, "%s.single.mp3",filename2);
		wav_to_mp3(file, outfilename,8000,1);
		return;
	}
	if(fn==NULL)
	{
		fseek(fp, 0,SEEK_END); ll=ftell(fp); in1=(unsigned char *)malloc(ll); rewind(fp); fread(in1,sizeof(char),ll,fp);fclose(fp); out1=(unsigned char *)malloc(ll*2);
		//printf("%d %d\n",i,ll);				
		n=0; for(i=0; i<ll;)
		{
			m=in1[i+8]+(in1[i+9]<<8)+(in1[i+10]<<16)+(in1[i+11]<<24); i+=12;
			g711a_decode( out1+n, in1+i, m);	 n+=m*2; i+=m;
		}

		sprintf(file, "%s.single.wav",filename1);
		if((fp= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }
		pcm_to_wav(out1, n, fp, 8000, 1);

		//fwrite(AU_header, 1, 24, fp);
		//fwrite(out1, 1, n, fp);
		fclose(fp);	
		free(in1);
		free(out1);

		sprintf(outfilename, "%s.single.mp3",filename1);
		wav_to_mp3(file, outfilename,8000,1);
		return;		
	}

	fseek(fp, 0,SEEK_END); ll=ftell(fp); in1=(unsigned char *)malloc(ll); rewind(fp); i=fread(in1,sizeof(char),ll,fp);fclose(fp); out1=(unsigned char *)malloc(ll*2); len=i;
	//printf("%d %d %d\n",i,len,ll*2);
	fseek(fn, 0,SEEK_END); ll=ftell(fn); in2=(unsigned char *)malloc(ll); rewind(fn); fread(in2,sizeof(char),ll,fn);fclose(fn); out2=(unsigned char *)malloc(ll*2);
	//printf("%d %d %d\n",ll,i,ll*2);
	AU_header[23]=2;	
	n=0; for(i=0; i<len;)
	{
		m=in1[i+8]+(in1[i+9]<<8)+(in1[i+10]<<16)+(in1[i+11]<<24); i+=12;
		//for( j=0; j<16;j++)printf("%02x",in1[j]);printf("\n");
		g711a_decode( out1+n, in1+i, m);	 n+=m*2; i+=m;
		//printf("%d %d\n",n,m);
	}
	len=n;
	//printf("%d\n",n);

	n=0; for(i=0; i<ll;)
	{
		m=in2[i+8]+(in2[i+9]<<8)+(in2[i+10]<<16)+(in2[i+11]<<24); i+=12;
		g711a_decode( out2+n, in2+i, m);	 n+=m*2; i+=m;
		//printf("%d %d\n",n,m);
	}
	ll=n;
	//printf("%d\n",n);
	sprintf(file, "%s.paired.wav",filename1);
	//printf("%s\n",file);
	if((outfile= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }

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
		pcm_to_wav(out, len*2, outfile, 8000, 2);
	}
	if(len<ll) {
		out = (unsigned char *) malloc(ll * 2);
		for (i = 0; i < len; i += 2) {out[2 * i] = out1[i];	out[2 * i + 1] = out1[i + 1];out[2 * i + 2] = out2[i];out[2 * i + 3] = out2[i + 1];	}
		for (i = len; i < ll; i += 2) {	out[2 * i] = out1[i];out[2 * i + 1] = out1[i + 1];out[2 * i + 2] = out2[i];	out[2 * i + 3] = out2[i + 1];}
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

}





