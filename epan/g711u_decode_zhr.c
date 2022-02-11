#include <stdio.h>
#include <stdlib.h>
#include "decode_zhr.h"

int uuu_g711u(unsigned char u_val)
{
	int	t;	
	u_val = ~u_val;	t = ((u_val & 0xf) << 3) + 0x84;
	t <<= ((unsigned)u_val & 0x70) >> 4;
	return ((u_val & 0x80) ? (0x84 - t) : (t - 0x84));
}
int aaa_g711u(unsigned char a_val)
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

void g711u_decode(unsigned char out[], unsigned char in[], int len)
{
	int i, j;
	for(i=0;i<len;i++){ j=uuu_g711u(in[i]); out[2*i]=j>>8&0xff; out[2*i+1]=j&0xff;}
}

void g711u_decode_zhr(char filename1[],  char filename2[])   // 8000  1
{
	int i, m, n ;
	long int ll,len;
	FILE *fp, *fn, * outfile;
	char file[256], outfilename[256];
	unsigned char *in1, *in2, *out1, *out2, *out;
	//unsigned char AU_header[24] = {'.','s','n','d',0,0,0,0x18,0xff,0xff,0xff,0xff,0,0,0,0x03,0,0,0x1f,0x40,0,0,0,0x01 };

	fp = fopen(filename1 , "rb"); 	fn = fopen(filename2 , "rb");
	if(fp==NULL && fn==NULL){printf("no file!\n"); return; }
	if(fp==NULL)
	{
		fseek(fn, 0,SEEK_END); ll=ftell(fn); in2=(unsigned char *)malloc(ll); rewind(fn); fread(in2,sizeof(char),ll,fn);fclose(fn); out2=(unsigned char *)malloc(ll*2);
		//printf("%d %d \n",ll,i);
		n=0; for(i=0; i<ll;)
		{
			m=in2[i+8]+(in2[i+9]<<8)+(in2[i+10]<<16)+(in2[i+11]<<24); i+=12;
			g711u_decode( out2+n, in2+i, m);	 n+=m*2; i+=m;
		}		
		sprintf(file, "%s.single.wav",filename2);
		if((outfile= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }
		pcm_to_wav(out2, n, outfile, 8000, 1);

		fclose(outfile);
		free(in2);
		free(out2);
		sprintf(outfilename, "%s.single.mp3",filename2);
		wav_to_mp3(file, outfilename,8000,1);
		return;
	}
	if(fn==NULL)
	{
		fseek(fp, 0,SEEK_END); ll=ftell(fp); in2=(unsigned char *)malloc(ll); rewind(fp); fread(in2,sizeof(char),ll,fp);fclose(fp); out2=(unsigned char *)malloc(ll*2);
		//printf("%d %d \n",ll,i);
		n=0; for(i=0; i<ll;)
		{
			m=in2[i+8]+(in2[i+9]<<8)+(in2[i+10]<<16)+(in2[i+11]<<24); i+=12;
			g711u_decode( out2+n, in2+i, m);	 n+=m*2; i+=m;
		}
		sprintf(file, "%s.single.wav",filename1);
		if((outfile= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }
		pcm_to_wav(out2, n, outfile, 8000, 1);

		fclose(outfile);
		free(in2);
		free(out2);
		sprintf(outfilename, "%s.single.mp3",filename1);
		wav_to_mp3(file, outfilename,8000,1);
		return;
	}

	fseek(fp, 0,SEEK_END); ll=ftell(fp); in1=(unsigned char *)malloc(ll); rewind(fp); fread(in1,sizeof(char),ll,fp);fclose(fp); out1=(unsigned char *)malloc(ll*2); len=ll;
	//printf("%d %d\n",i,len);
	fseek(fn, 0,SEEK_END); ll=ftell(fn); in2=(unsigned char *)malloc(ll); rewind(fn); fread(in2,sizeof(char),ll,fn);fclose(fn); out2=(unsigned char *)malloc(ll*2);
	//printf("%d %d \n",ll,i);
	//AU_header[23]=2;
	n=0; for(i=0; i<len;)
	{
		m=in1[i+8]+(in1[i+9]<<8)+(in1[i+10]<<16)+(in1[i+11]<<24); i+=12;
		g711u_decode( out1+n, in1+i, m);	 n+=m*2; i+=m;
	}
	len=n;

	n=0; for(i=0; i<ll;)
	{
		m=in2[i+8]+(in2[i+9]<<8)+(in2[i+10]<<16)+(in2[i+11]<<24); i+=12;
		g711u_decode( out2+n, in2+i, m);	 n+=m*2; i+=m;
	}
	ll=n;


	sprintf(file, "%s.paired.wav",filename1);
	if((outfile= fopen(file,"wb"))==NULL){  printf("OPEN FILE %s FAIL\n",file);   return ; }
	//AU_header[23]=2;
	//fwrite(AU_header, 1, 24, fp);

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
	free(out);
	free(in2);
	free(out2);
	sprintf(outfilename, "%s.paired.mp3",filename1);
	wav_to_mp3(file, outfilename,8000,2);

}




int  pcm_to_wav(unsigned char *buf,int ll, FILE *outfile, unsigned int sampleRate, unsigned int channels)
{
	//unsigned char *buf=NULL;
	unsigned char se, wavhead[]={'R', 'I', 'F', 'F',0,0,0,0, 'W','A', 'V', 'E','f', 'm', 't', ' ',16,0,0,0,  1,0,1,0,  0,0,0,0,  0,0,0,0,  2,0,16,0, 'd', 'a', 't', 'a', 0,0,0,0 };
	int i;//, ll;
	//FILE *fp;
	//if((fp=fopen(in_file,"rb"))==NULL){printf("open file err!\n");return -1;}
	//fseek(fp, 0, SEEK_END);ll=ftell(fp); buf = (unsigned char*)malloc(ll); fseek(fp, 0, SEEK_SET); fread(buf,1,ll,fp); fclose(fp);

	ll += 36;
	wavhead[4]=ll>>0&0xff;  wavhead[5]=ll>>8&0xff; wavhead[6]=ll>>16&0xff; wavhead[7]=ll>>24&0xff;
	wavhead[22]=channels;    //channels
	wavhead[24]=sampleRate>>0&0xff; wavhead[25]=sampleRate>>8&0xff; wavhead[26]=sampleRate>>16&0xff; wavhead[27]=sampleRate>>24&0xff; //// 采样率
	wavhead[28]=(sampleRate*16/8)>>0&0xff; wavhead[29]=(sampleRate*16/8)>>8&0xff; wavhead[30]=(sampleRate*16/8)>>16&0xff; wavhead[31]=(sampleRate*16/8)>>24&0xff; //比特率
	wavhead[32]=(16/8)>>0&0xff; wavhead[33]=(16/8)>>8&0xff;// 块对齐
	wavhead[34]=16; wavhead[35]=(16/8)>>8&0xff;// 采样精度
	ll = ll-36;
	wavhead[40]=ll>>0&0xff; wavhead[41]=ll>>8&0xff; wavhead[42]=ll>>16&0xff; wavhead[43]=ll>>24&0xff;
	for(i=0;i<ll;i+=2){se=buf[i];buf[i]=buf[i+1];buf[i+1]=se;}
	//if((fp=fopen(outfile,"wb"))==NULL){printf("open filew err!\n");return -1;}
	fwrite(wavhead, 1,44, outfile);    fwrite(buf, 1, ll, outfile);    //fclose(outfile);  free(buf);
	return 0;
}

void wav_to_mp3(char *in_file, char *outfile, int sampleRate, unsigned int channels)
{
	int i, write;
	size_t read;
	short int     pcm_buffer[8192*2], aaa[8192];
	unsigned char mp3_buffer[8192];
	FILE *wav = fopen(in_file, "rb");
	FILE *mp3 = fopen(outfile, "wb");

	fread(aaa,1,44,wav);
	lame_t lame = lame_init();
	lame_set_in_samplerate(lame, sampleRate);//    lame_set_num_channels(lame, 1);//    lame_set_brate(lame, 64);
	lame_set_VBR(lame, vbr_default);
	lame_init_params(lame);
	do {
		read = fread(aaa,  2, 8192, wav);// read = fread(pcm_buffer, 2*sizeof(short int), 8192, pcm);
		//for(i=0;i<8192;i++)aaa[i]=(aaa[i]>>8&0xff)+(aaa[i]<<8&0xff00);
		if (read == 0) write = lame_encode_flush(lame, mp3_buffer, 8192);
		else
		{
			if(channels==1)for(i=0;i<8192;i++){pcm_buffer[2*i]=aaa[i]; pcm_buffer[2*i+1]=aaa[i];}//channel=1 --> channel=2;
			if(channels==2)
			{
				for(i=0;i<8192;i++)pcm_buffer[i]=aaa[i];
				read = fread(aaa,  2, 8192, wav);
				for(i=0;i<8192;i++)pcm_buffer[i+8192]=aaa[i];//channel=2;
			 }
			write = lame_encode_buffer_interleaved(lame, pcm_buffer, (int)read, mp3_buffer, 8192);
			if(write == -1) return;
		}
		fwrite(mp3_buffer, write, 1, mp3);
	} while (read != 0);

	lame_close(lame);    fclose(mp3);    fclose(wav);
}

