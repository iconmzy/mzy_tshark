//
// Created by gzj on 2021/9/3.
//

#ifndef WIRESHARK_AUTHORIZE_H
#define WIRESHARK_AUTHORIZE_H

#include "ws_symbol_export.h"

char globalCPUid[256] = {'\0'};

WS_DLL_PUBLIC void verify_identity_one(const char * reg_path);
WS_DLL_PUBLIC void verify_identity_two(const char * reg_path);
WS_DLL_PUBLIC void cpu_id(void);

#endif //WIRESHARK_AUTHORIZE_H
