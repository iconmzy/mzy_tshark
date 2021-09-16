//
// Created by gzj on 2021/9/3.
//


#include "authorize.h"
#include <string.h>
#include <stdlib.h>

#define MAXINTERFACES 16

void getMac(char *mac) {
    int fd;
//    int interface;
    struct ifreq buf[MAXINTERFACES];
    struct ifconf ifc;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0) {
        int i = 1;
        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t) buf;
        if (!ioctl(fd, SIOCGIFCONF, (char *) &ifc)) {
//            interface = ifc.ifc_len / sizeof(struct ifreq);
            if (!(ioctl(fd, SIOCGIFHWADDR, (char *) &buf[i]))) {
                sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
                        (unsigned char) buf[i].ifr_hwaddr.sa_data[0],
                        (unsigned char) buf[i].ifr_hwaddr.sa_data[1],
                        (unsigned char) buf[i].ifr_hwaddr.sa_data[2],
                        (unsigned char) buf[i].ifr_hwaddr.sa_data[3],
                        (unsigned char) buf[i].ifr_hwaddr.sa_data[4],
                        (unsigned char) buf[i].ifr_hwaddr.sa_data[5]);
            }
        }
    }
}

char *cpu_id(char *id) {
    unsigned long s1, s2;
    asm volatile
    ( "movl $0x01 , %%eax ; \n\t"
      "xorl %%edx , %%edx ;\n\t"
      "cpuid ;\n\t"
      "movl %%edx ,%0 ;\n\t"
      "movl %%eax ,%1 ; \n\t"
    :"=m"(s1), "=m"(s2)
    );
    sprintf(id, "%08X-%08X", s1, s2);
    return id;
}

char *calidenty(char *str) {
    int n = strlen(str);
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] != ':' && str[i] != '-') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
    int j1 = 0;
    for (int i = 0; i < n; i += 2) {
        str[j1++] = str[i];
    }
    str[j1] = '\0';

    return str;

}

char *halve(char *str) {
    int n = strlen(str);
    int j1 = 0;
    for (int i = 0; i < n; i += 2) {
        str[j1++] = str[i];
    }
    str[j1] = '\0';
    return str;
}

char *addkey1(char *str) {
    int idx[] = {4, 3, 5, 2, 0, 1};
    int n = strlen(str);
    int k = n / 6;
    char fenlan[30];
    int p = 0;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < 6; j++) {
            if (i * 6 + idx[j] < n)
                fenlan[p++] = str[i * 6 + idx[j]];
            else
                continue;
        }
    }
    fenlan[p] = '\0';
    int q = 0;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < 6; j++) {
            if (i * 6 + idx[j] < n)
                str[q++] = (char) (fenlan[i * 6 + idx[j]] + i);
            else
                continue;
        }
    }
    str[q] = '\0';
    return str;
}

void usersee(char *machine_id_path, char *str) {
    FILE *fp = fopen(machine_id_path, "w");//添加文件路径
    if (fp == NULL) {
        printf("can't open configure file\n");
        exit(-1);
    }
    fprintf(fp, "%s", str);
    fclose(fp);
}


void writefile(char *regist_path, char *str) {

    FILE *fp = fopen(regist_path, "w");//写入二进制文件,需要添加文件；
    if (fp == NULL) {
        printf("can't open file\n");
        exit(-1);
    }
    fprintf(fp, "%s", str);
    fclose(fp);
}

char *addkey2(char *str) {

    int n = strlen(str);
    int temp[n];
    int add[n];
    for (int i = 0; i < n; i++) {
        temp[i] = i;
    }
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            if (j != i)
                sum += temp[j];

        }
        add[i] = sum;
    }
    int arr[30];
    for (int i = 0; i < n; i++) {
        int a = (str[i] * temp[i] + add[i]) % 126;
        //printf("%d\n",a);
        if (a >= 0 && a <= 9)
            arr[i] = a;
        else if (a >= 10 && a <= 99)
            arr[i] = a % 10;
        else {
            a %= 100;
            if (a >= 10 && a <= 99)
                arr[i] = a % 10;
            else
                arr[i] = a;
        }
    }
    static char cha[30] = {"\0"};
    char cha1[30] = {"\0"};
    for (int i = 0; i < n; i++) {
        sprintf(cha1, "%d", arr[i]);
        strcat(cha, cha1);
    }
    return cha;

}