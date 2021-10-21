#include "write_in_files_handlers.h"
int uuu(unsigned char u_val)
{
	int	t;	
	u_val = ~u_val;	t = ((u_val & 0xf) << 3) + 0x84;
	t <<= ((unsigned)u_val & 0x70) >> 4;
	return ((u_val & 0x80) ? (0x84 - t) : (t - 0x84));
}

int g711u_decode(unsigned char in[], int inlen, unsigned char out[])
{
	int i ,j;
	unsigned char AU_header[24] = {'.','s','n','d',0,0,0,0x18,0xff,0xff,0xff,0xff,0,0,0,0x03,0,0,0x1f,0x40,0,0,0,0x01}; 
	for(i=0;i<24;i++)out[i]=AU_header[i];
	for(i=0; i<inlen; i++){ j=uuu(in[i]); out[2*i+24]=j>>8&0xff; out[2*i+1+24]=j&0xff;}
	return 2*inlen+24;
}


