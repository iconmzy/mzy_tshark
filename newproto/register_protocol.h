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
    enum DataType type;
    int length;
};
struct protoInfo
{
    int protoNum;
    int port;
    char transportProto[10];
    char protoName[20];
    char shortName[20];
    char filterName[20];
    struct columnInfo *column;
};

extern struct protoInfo *allProtoInfo;
void exproto_register(allExProtocols *exprotocols);
#endif
