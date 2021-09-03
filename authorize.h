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


void getMac(char *mac);

char *cpu_id(char *id);

char *calidenty(char *str);

char *halve(char *str);

char *addkey1(char *str);

void usersee(char *str);

void writefile(char *str);

char *addkey2(char *str);

#endif //WIRESHARK_AUTHORIZE_H
