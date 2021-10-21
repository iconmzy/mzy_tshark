int aaa(unsigned char a_val)
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


int g711a_decode(unsigned char in[], int inlen, unsigned char out[])
{
	int i ,j;
	unsigned char AU_header[24] = {'.','s','n','d',0,0,0,0x18,0xff,0xff,0xff,0xff,0,0,0,0x03,0,0,0x1f,0x40,0,0,0,0x01}; 
	for(i=0;i<24;i++)out[i]=AU_header[i];
	for(i=0; i<inlen; i++){ j=aaa(in[i]); out[2*i+24]=j>>8&0xff; out[2*i+1+24]=j&0xff;}
	return 2*inlen+24;
}
