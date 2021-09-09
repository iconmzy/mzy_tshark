//
// Created by yy on 21-6-16.
//

#ifndef WIRESHARK_WRITE_IN_FILES_HANDLERS_H
#define WIRESHARK_WRITE_IN_FILES_HANDLERS_H

#include <glib.h>
#include "ws_symbol_export.h"
#include <stdio.h>
#include "epan.h"
#include "proto.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ConfigInfo {
    char key[64];
    char val[128];
};
WS_DLL_PUBLIC char CONFIG_FILES_PATH[128];

WS_DLL_PUBLIC gboolean WRITE_IN_FILES_CONFIG;
WS_DLL_PUBLIC char EXPORT_PATH[256];

WS_DLL_PUBLIC gboolean WRITE_IN_CONVERSATIONS_FLAG;
WS_DLL_PUBLIC char WRITE_IN_CONVERSATIONS_PATH[256];

WS_DLL_PUBLIC gboolean PACKET_PROTOCOL_FLAG;
WS_DLL_PUBLIC char PACKET_PROTOCOL_TYPES[256];
WS_DLL_PUBLIC char PACKET_PROTOCOL_PATH[256];

WS_DLL_PUBLIC gboolean INSERT_MANY_PROTOCOL_STREAM_FLAG;  // 是否批量写入
WS_DLL_PUBLIC int EDIT_FILES_SIZES;
WS_DLL_PUBLIC int INSERT_MANY_PROTOCOL_STREAM_NUM;  // 每次每个协议批量写入行数
WS_DLL_PUBLIC int EDIT_FILES_PROCESS_NUM;  // 并发进程数目 暂时未用
WS_DLL_PUBLIC gboolean DISPLAY_PACKET_INFO_FLAG;
WS_DLL_PUBLIC gboolean EDIT_FILES_DISSECT_FLAG;

WS_DLL_PUBLIC char READ_FILE_PATH[256];
WS_DLL_PUBLIC char FILE_NAME_T[128];
WS_DLL_PUBLIC gboolean file_Name_From_Dir_Flag;
WS_DLL_PUBLIC gboolean read_Pcap_From_File_Flag;
WS_DLL_PUBLIC gboolean mutex_final_clean_flag;
WS_DLL_PUBLIC char write_Json_Files_Init_Status;

WS_DLL_PUBLIC char *my_itoa(long int n);

WS_DLL_PUBLIC void float2char(float slope, char *buffer, int n);
//存储当前label的字段名称
WS_DLL_PUBLIC char abbrev_t[40];
//是否允许新增协议相关
WS_DLL_PUBLIC gboolean JSON_ADD_PROTO;
WS_DLL_PUBLIC char JSON_ADD_PROTO_PATH[256];
//数据来源相关配置
WS_DLL_PUBLIC gboolean ONLINE_CAPTURE_DATA_FLAG;
WS_DLL_PUBLIC char ONLINE_CAPTURE_DATA_DEVICE_NAME[32];
WS_DLL_PUBLIC gboolean READ_PACKET_FROM_FILES_FLAG;
WS_DLL_PUBLIC char READ_PACKET_FROM_FILES_PATH[256];
//线路号相关配置
WS_DLL_PUBLIC char ONLINE_LINE_NO[32];  /* 实时接入数据的线路号 */
WS_DLL_PUBLIC char OFFLINE_LINE_NO_REGEX[256];  /* 离线接入数据的识别线路号的正则表达式 */
//WS_DLL_PUBLIC char *OFFLINE_LINE_LINE_NO;  /* 离线接入数据通过正则表达式提取出来的线路号 */
WS_DLL_PUBLIC char REGISTRATION_FILE_PATH[256];  /* 注册文件的路径 */
WS_DLL_PUBLIC char OFFLINE_LINE_LINE_NO[256];  /* 离线接入数据通过正则表达式提取出来的线路号 */

#define MAXFILELENGTH 50
#define MAXWRITEFILELENGTH 128


WS_DLL_PUBLIC void do_write_in_files_handler(gchar *label_str, const gchar *abbrev, const gchar *name, int level);

WS_DLL_PUBLIC void do_write_in_conversation_handler(gchar *key, gchar *value);

WS_DLL_PUBLIC gboolean initWriteJsonFiles(char *);

WS_DLL_PUBLIC gboolean readConfigFilesStatus();

WS_DLL_PUBLIC void clean_Temp_Files_All();

WS_DLL_PUBLIC void add_record_in_result_file();

WS_DLL_PUBLIC void change_result_file_name();

WS_DLL_PUBLIC gboolean dissect_edt_into_files(epan_dissect_t *);

//WS_DLL_PUBLIC char *match_line_no(char *, char *);  /* 匹配线路号 */
WS_DLL_PUBLIC void match_line_no(char *, char *, char *);  /* 匹配线路号 */

/**
 * 下面是读取配置文件相关函数
 * @param file
 * @return
 */
//获得文件有效行数
WS_DLL_PUBLIC int getLines_ConfigFile(FILE *file);
//加载配置文件
WS_DLL_PUBLIC gboolean loadFile_ConfigFile(const char *filePath, char ***fileData, int *lines);
//解析配置文件
WS_DLL_PUBLIC void parseFile_ConfigFile(char **fileData, int lines, struct ConfigInfo **info);
//获得指定配置信息
WS_DLL_PUBLIC char *getInfo_ConfigFile(const char *key, struct ConfigInfo *info, int line);
//释放配置文件信息
WS_DLL_PUBLIC void destroInfo_ConfigFile(struct ConfigInfo *info);
//判断当前行是否有效
WS_DLL_PUBLIC int isValid_ConfigFile(const char *buf);


#ifdef __cplusplus
}
#endif


#endif //WIRESHARK_WRITE_IN_FILES_HANDLERS_H
