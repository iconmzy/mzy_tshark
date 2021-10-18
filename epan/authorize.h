//
// Created by gzj on 2021/9/3.
//

#ifndef WIRESHARK_AUTHORIZE_H
#define WIRESHARK_AUTHORIZE_H

#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "ws_symbol_export.h"

#define XXX1_AU "regist.txt"
#define XXX2_AU "activate.txt"

void getMac(char *mac);

char *cpu_id(char *id);

char *calidenty(char *str);

char *halve(char *str);

char *addkey1(char *str);

void usersee(const char *, char *str);

void writefile(char *regist_path, char *str);

char *addkey2(char *str);

WS_DLL_PUBLIC void verify_identity_one(const char reg_path[]);

WS_DLL_PUBLIC void verify_identity_two(const char * reg_path);

#endif //WIRESHARK_AUTHORIZE_H
