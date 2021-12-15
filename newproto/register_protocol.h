#ifndef REGISTER_PROTOCOL_H
#define REGISTER_PROTOCOL_H
#include <stdlib.h>
#include <stdio.h>
#include <epan/packet.h>
#include "jsonopt.h"
struct columnInfo
{
    int id;
    char name[20];
    char abbName[20];
    int type;
    int length;
};
struct protoInfo
{
    int protoNum;
    int port[10] ;
    char transportProto[10];
    char protoName[20];
    char shortName[20];
    char filterName[20];
    char feature[100];
    int feature_offset;
    struct columnInfo *column;
};

extern struct protoInfo *allProtoInfo;
void exproto_register(allExProtocols *exprotocols);
#endif
