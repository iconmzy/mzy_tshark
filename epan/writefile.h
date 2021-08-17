#ifndef __WRITEFILE_H__
#define __WRITEFILE_H__

#include <stdio.h>

#define max_lots 512
#define max_strlen 64*4
#define min_blockdata 32*2
/*数据写入结构体数据*/
typedef struct
{
    unsigned char SourceAddress[min_blockdata];
    unsigned char DestAddress[min_blockdata];
    unsigned char SrcPort[min_blockdata];
    unsigned char DisPort[min_blockdata];
    unsigned char Proto[min_blockdata];
    unsigned char Data[min_blockdata*64];
    unsigned char FilePath[min_blockdata*2];
    unsigned char TransProto[min_blockdata];
    unsigned char LineData[max_lots][max_strlen];
    int treeLevel;
} writeFile_fields;

#endif