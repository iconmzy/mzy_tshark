
#ifndef __DECODE_ZHR_H__
#define __DECODE_ZHR_H_

#include<stdio.h>
#include<stdlib.h>
#include "lame/lame.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
void g711a_decode_zhr(char filename1[],  char filename2[]);
void g711u_decode_zhr(char filename1[],  char filename2[]);
void g722_decode_zhr(char filename1[],  char filename2[]);
void g729a_decode_zhr(char filename1[],char filename2[]);

void wav_to_mp3(char *in_file, char *outfile, int sampleRate, unsigned int channels);
int pcm_to_wav(unsigned char *buf,int ll, FILE *outfile, unsigned int sampleRate, unsigned int channels);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DECODE_ZHR_H__ */




