#ifndef JSONOPT_H
#define JSONOPT_H
#include <stdlib.h>
#include <stdio.h>
#include <glib-object.h>
#include <string.h>
#include <json-glib/json-glib.h>
#include <sys/types.h>
#include <dirent.h>

/*enum DataType
{
    ITYPE = 0, //int
    FTYPE,     //float
    CTYPE,     //char
    DTYPE,     //dictory

};*/
struct PartHead;
typedef struct parts
{
    int length;
    char name[20];
    char abbName[20];
    int type;
    struct PartHead *partHead;
} parts;

typedef struct PartHead
{
    int partsNum;
    parts *dataParts;
} PartHead;

typedef struct exProtocol
{
    char protocolName[20];
    char shortName[20];
    char filterName[20];
    int port[10];
    char transportProtocol[10];
    //int totalLength;
    //char feature[100];
    //int feature_offset;
    PartHead *partHead;
} exProtocol;

typedef struct allExProtocols
{
    int exProtocolNum;
    exProtocol *exProto;
} allExProtocols;

int ParseJson(char *filePath, exProtocol *proto);
int ParseAllJson(char *dirPath, allExProtocols *protos);
int CountJsonFile(char *dirPath);
#endif