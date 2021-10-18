#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include "authorize.h"

void getMac(char *mac) {
    int fd, i;

    struct ifreq buf[16];
    struct ifconf ifc;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0) {
        i = 1;
        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t) buf;
        if (!ioctl(fd, SIOCGIFCONF, (char *) &ifc)) {
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
    return;
}

void cpu_id(char *id) {
    unsigned int s1, s2;
    asm volatile
    ( "movl $0x01 , %%eax ; \n\t"
      "xorl %%edx , %%edx ;\n\t"
      "cpuid ;\n\t"
      "movl %%edx ,%0 ;\n\t"
      "movl %%eax ,%1 ; \n\t"
    :"=m"(s1), "=m"(s2)
    );
    sprintf(id, "%08X-%08X", s1, s2);
    return;
}


/*添加注册码功能*/
void verify_identity_one(const char * reg_path){
    char mac[256], id[256], file[256], cha[256];
    int i, j, n, k, p, q,  sum, a, temp[256], add[256], arr[256], idx[6] = {4, 3, 5, 2, 0, 1};
    FILE *fp;

    getMac(mac);  cpu_id(id);   strcat(id, mac);
    n = strlen(id); j = 0;
    for ( i = 0; i < n; i++) if (id[i] != ':' && id[i] != '-') id[j++] = id[i];
    id[j] = 0;  n=j;
    j = 0; for (i= 0;i<n;i+=2) id[j++] = id[i]; id[j] = 0;

    n = j;   k = n / 6;   p = 0;
    for ( i = 0; i <= k; i++) {
        for ( j = 0; j < 6; j++) { if (i * 6 + idx[j] < n) cha[p++] = id[i * 6 + idx[j]];  else  continue; }
    }
    cha[p] = 0;    q = 0;
    for(i=0;i<=k;i++){for(j=0;j<6;j++){ if (i * 6 + idx[j] < n)id[q++] = (char)(cha[i*6+idx[j]]+i); else continue;}}
    id[q] = 0;
    printf("The machine id: %s\n", id);
    for(i=0;i<256;i++)file[i]=0; strcpy(file, reg_path);  strcat(file, "activecode.txt");
    if ((fp = fopen(file, "w")) == NULL) {  printf("openfile Err!\n");  exit(0); }  fprintf(fp, "%s", id);  fclose(fp);

    n = strlen(id);
    for ( i = 0; i < n; i++) temp[i] = i;
    for (i = 0; i < n; i++) { sum = 0;  for (j = 0; j < n; j++) if (j != i) sum += temp[j];   add[i] = sum;    }

    for ( i = 0; i < n; i++) {
        a = (id[i] * temp[i] + add[i]) % 126;
        if (a >= 0 && a <= 9)  arr[i] = a;
        else if (a >= 10 && a <= 99)  arr[i] = a % 10;
        else { a %= 100;       if (a >= 10 && a <= 99)  arr[i] = a % 10;  else  arr[i] = a; }
    }
    for ( i = 0; i < 30; i++)cha[i]=0;
    id[0]=0;  for ( i = 0; i < n; i++) {  sprintf(cha, "%d", arr[i]);    strcat(id, cha);  }


    for(i=0;i<256;i++) file[i] = 0;  strcpy(file, reg_path);    strcat(file, "regist.txt");
    if ((fp = fopen(file, "r")) == NULL){printf("未激活，请激活！\n"); exit(0);}
    fread(cha,1,14,fp);   fclose(fp);
    if (strcmp(id, cha) != 0) {printf("未激活，请激活！%s %s\n",id, cha);
        exit(0);}
    printf("该设备已激活！\n");    /*注册码功能结束*/
}

void verify_identity_two(const char * reg_path){
    char mac[256], id[256], file[256], cha[256];
    int i, j, n, k, p, q,  sum, a, temp[256], add[256], arr[256], idx[6] = {4, 3, 5, 2, 0, 1};
    FILE *fp;

    getMac(mac);  cpu_id(id);   strcat(id, mac);
    n = strlen(id); j = 0;
    for ( i = 0; i < n; i++) if (id[i] != ':' && id[i] != '-') id[j++] = id[i];
    id[j] = 0;  n=j;
    j = 0; for (i= 0;i<n;i+=2) id[j++] = id[i]; id[j] = 0;

    n = j;   k = n / 6;   p = 0;
    for ( i = 0; i <= k; i++) {
        for ( j = 0; j < 6; j++) { if (i * 6 + idx[j] < n) cha[p++] = id[i * 6 + idx[j]];  else  continue;  }
    }
    cha[p] = 0;   q = 0;
    for(i=0;i<=k;i++){for(j=0;j<6;j++){ if (i * 6 + idx[j] < n)id[q++] = (char)(cha[i*6+idx[j]]+i); else continue;}}
    id[q] = 0;
    for(i=0;i<256;i++)file[i]=0; strcpy(file, reg_path);  strcat(file, "activecode.txt");
    if ((fp = fopen(file, "w")) == NULL) {  printf("openfile Err!\n");
        exit(0); }  fprintf(fp, "%s", id);  fclose(fp);

    n = strlen(id);
    for ( i = 0; i < n; i++) temp[i] = i;
    for (i = 0; i < n; i++) { sum = 0;  for (j = 0; j < n; j++) if (j != i) sum += temp[j];   add[i] = sum;    }

    for ( i = 0; i < n; i++) {
        a = (id[i] * temp[i] + add[i]) % 126;
        if (a >= 0 && a <= 9)  arr[i] = a;
        else if (a >= 10 && a <= 99)  arr[i] = a % 10;
        else { a %= 100;       if (a >= 10 && a <= 99)  arr[i] = a % 10;  else  arr[i] = a; }
    }
    for ( i = 0; i < 30; i++)cha[i]=0;
    id[0]=0;  for ( i = 0; i < n; i++) {  sprintf(cha, "%d", arr[i]);    strcat(id, cha);  }

    for(i=0;i<256;i++) file[i] = 0;  strcpy(file, reg_path);    strcat(file, "regist.txt");
    if ((fp = fopen(file, "r")) == NULL){printf("未激活，请激活！\n"); exit(0);}
    fread(cha,1,14,fp);   fclose(fp);
    if (strcmp(id, cha) != 0) {printf("未激活，请激活！%s %s\n",id, cha);exit(0);}
    //printf("该设备已激活！\n");
    /*注册码功能结束*/
}


