//
// Created by root on 21-6-16.
//

#include "write_in_files_handlers.h"
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <fstream>
#include <sstream>
#include <exceptions.h>
#include "cJSON.h"
#include "epan_dissect.h"
#include <sys/stat.h>
#include <map>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include <epan/ftypes/ftypes.h>
#include "glib.h"
#include "wsutil/pint.h"
#include "epan/rtp_media.h"
#include "wsutil/codecs.h"
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "curl/curl.h"
#define __U__ __attribute__((unused))

/*常用的一些字符串*/
#define str_FILES_RESOURCE "file_path"

/*即将写进文件的协议*/
static std::string write_in_files_proto;
/*内容缓存*/
static std::string write_in_files_stream;
static cJSON *write_in_files_cJson = cJSON_CreateObject();
/*缓存会话数据内容*/
static cJSON *write_in_files_conv_cJson = cJSON_CreateObject();
static std::string conv_path_t;

static FILE *conversation_Handle_File = nullptr;

cJSON *regex_dict = nullptr;
std::map<std::string,std::string> regex_dict_map;

static std::string global_time_str;  // long int types
FILE *fp_result_timestampe = nullptr;

//begin--------------------------------配置文件变量定义--------------------------------begin//
char EXPORT_PATH[256] = {0};
char RESULT_PATH[256] = {0};
gboolean WRITE_IN_FILES_CONFIG = 1;
gboolean DISPLAY_PACKET_INFO_FLAG = 0;
gboolean WRITE_IN_CONVERSATIONS_FLAG = 1;
gboolean PACKET_PROTOCOL_FLAG = 1;
gboolean EDIT_FILES_DISSECT_FLAG = 0;
gboolean file_Name_From_Dir_Flag = 0;
char WRITE_IN_CONVERSATIONS_PATH[256] = {0};
char PACKET_PROTOCOL_TYPES[256] = {"imf,dicom,http,smb,tftp"};
char PACKET_PROTOCOL_PATH[256] = {0};
int EDIT_FILES_SIZES = 1000;
int PER_FILES_MAX_LINES = 10000;
gboolean INSERT_MANY_PROTOCOL_STREAM_FLAG = 1;
int INSERT_MANY_PROTOCOL_STREAM_NUM = 1000;
//数据来源相关配置
gboolean ONLINE_CAPTURE_DATA_FLAG = 0;
char ONLINE_CAPTURE_DATA_DEVICE_NAME[32] = {0};
gboolean READ_PACKET_FROM_FILES_FLAG = 0;
char READ_PACKET_FROM_FILES_PATH[256] = {0};
//是否允许新增协议相关
gboolean JSON_ADD_PROTO = 0;
char JSON_ADD_PROTO_PATH[256] = {0};
//线路号相关配置
char ONLINE_LINE_NO[32] = {0};  /* 实时接入数据的线路号 */
static char OFFLINE_LINE_NO_REGEX[512] = {0};  /* 离线接入数据的识别线路号的正则表达式 */
char REGISTRATION_FILE_PATH[256] = {0};  /* 注册文件的路径 */
char OFFLINE_LINE_LINE_NO[256] = {0};
//写入ES数据库相关配置
gboolean WRITE_IN_ES_FLAG = 0;  /* 配置是否写入ElasticSearch数据库 */
char ES_URL[256] = {0};  /* ElasticSearch地址 */
//end--------------------------------配置文件变量定义--------------------------------end//

/*最终的初始化互斥变量1代表已经初始化过一次*/
gboolean mutex_final_clean_flag = 0;

/*批量插入的链表*/
struct insertManyProtocolStream {
    struct insertManyProtocolStream *next{};
    struct insertManyProtocolStream *pre{};
    std::string contents;
    std::string protocol;
    int times{};
};
static insertManyProtocolStream *insertmanystream_Head;

//strname的重复次数，头文件times为-1
struct strNameSameLevel {
    std::string str_name;
    struct strNameSameLevel *next{};
    u_int times{};
};
struct strNameSameLevel *strname_head;

typedef struct pFile_Info{
    FILE *fp{};
    std::string fileName_ori;//最原始文件名
    std::string fileName_last;//最后/最新文件名
    int lines{};
    int times{};
}pFILE_INFO;
//协议名称与对应的文件打开的指针map
std::map<std::string, pFILE_INFO *> pFile_map;

/**
 * 输入数字，返回对应string
 * @tparam T 泛型名
 * @param l
 * @return
 */
template <typename T>
inline std::string numtos(T l){
    std::ostringstream os;
    os << l;
    std::string result;
    std::istringstream is(os.str());
    is >> result;
    return result;
}

/**
 * 返回该包内重复字段的名称，如A_01,A_02... 现在改为输出数组则用不到 20211011 15:37 yy
 * @param strname 字段名称
 * @return
 */
std::string gotStrNameByStrName(std::string &strname) {
    if (strname_head->next == nullptr) {
        auto *temp = new struct strNameSameLevel;
        temp->next = strname_head->next;
        temp->times = 0;
        temp->str_name = strname;
        strname_head->next = temp;
        return strname;
    } else {
        struct strNameSameLevel *temp = strname_head->next;
        while (temp != nullptr) {
            if (temp->str_name == strname) {
                temp->times++;
                return strname + "_" + numtos(temp->times);
            }
            temp = temp->next;
        }
        //头插法插入名称节点。
        auto *temp_t = new struct strNameSameLevel;
        temp_t->next = strname_head->next;
        temp_t->times = 0;
        temp_t->str_name = strname;
        strname_head->next = temp_t;
        return strname;
    }
}
/**
 * 判断是否重复key_str  重复返回1，非重复返回0
 * @param key_str
 * @return
 */
gboolean judgeDuplicateKeyStr(const std::string &key_str){
    if(strname_head->next == nullptr){
        auto *temp = new struct strNameSameLevel;
        temp->next = strname_head->next;
        temp->times = 0;
        temp->str_name = key_str;
        strname_head->next = temp;
        return false;
    } else{
        struct strNameSameLevel *temp = strname_head->next;
        while (temp != nullptr) {
            if (temp->str_name == key_str) {
                temp->times++;
                return true;
            }
            temp = temp->next;
        }
        //头插法插入名称节点。
        auto *temp_t = new struct strNameSameLevel;
        temp_t->next = strname_head->next;
        temp_t->times = 0;
        temp_t->str_name = key_str;
        strname_head->next = temp_t;
        return false;
    }
}

/**
 * 初始化 strNameSameLevel链表。
 * @param node
 */
void initStrNameLevelLinkList(struct strNameSameLevel *node) {
    if (node != NULL) {
        initStrNameLevelLinkList(node->next);
        delete (node);
    }
}

/**
 * 切分string类 ,返回vector<string>
 * @param str
 * @param delim
 * @return
 */
std::vector<std::string> split(const std::string &str, const std::string& delim) {
    std::vector<std::string> res;
    char *source = new char[str.length() + 1];
    strcpy(source, str.c_str());
    char *p = strtok(source, delim.c_str());
    while (p) {
        res.emplace_back(p);
        p = strtok(nullptr, delim.c_str());
    }
    delete[] source;
    return res;
}

/**
 * 过滤一些无用的协议。
 * @param dst
 * @return
 */
gboolean lastLayerProtocolFilter(const char *dst) {
    if (strcmp(dst, "communityid") == 0) {
        return TRUE;
    }
    else if (strcmp(dst, "ftp.current-working-directory") == 0) {
        return TRUE;
    }
    else if (strcmp(dst, "xml") == 0) {
        return TRUE;
    }
    else if (strcmp(dst, "json") == 0) {
        return TRUE;
    }
    else if (strcmp(dst, "_ws.malformed") == 0) {  /* SSHv2协议中多解析出来的信息 */
        return TRUE;
    }
    else if (strcmp(dst, "smb2.fsctl.wait.name") == 0) {  /* smb2协议中多解析出来的信息 */
        return TRUE;
    }
    else if (strcmp(dst, "mswsp.msg") == 0) {  /* smb2的子协议mswsp中出现的畸形报文信息 */
        return TRUE;
    }
    else if (strcmp(dst, "tcp.segments") == 0) {
        return TRUE;
    }
    else if (strcmp(dst, "urlencoded-form") == 0) {
        return TRUE;
    }
    else if (strcmp(dst, "data-text-lines") == 0) {
        return TRUE;
    }
    else if (strcmp(dst, "media") == 0) {
        return TRUE;
    }
    return FALSE;
}
/**
 * 递归key的过滤。
 */
gboolean cursionkeyStrFilter(const char *key_str){
    if (strcmp(key_str, "text") == 0) {
        return TRUE;
    }
    return false;
}
/**
 * 快速匹配算法。匹配返回下标，为找到返回-1
 * @param s 匹配串
 * @param t 模式串
 * @return
 */
int kmp(std::string s, std::string t) {
    int i = 0, j = -1;
    int slen = s.length(), tlen = t.length();
    int *next = new int[tlen+1]();
    //首先求出模式串t的next数组
    next[0] = -1;
    while (i < tlen) {
        if (j == -1 || t[i] == t[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else
            j = next[j];
    }
    //接着根据next数组实现KMP算法
    i = 0;
    j = 0;
    while (i < slen && j < tlen) {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else
            j = next[j];
    }
    delete[] next;
    if (j == tlen)
        return i - j;
    else
        return -1;
}
/**
 * 工具：用ts 替换 dstr 中的所有 rs。
 * @param dstr
 * @param rs
 * @param ts
 * @return
 */
inline void stringReplaceByStr(std::string &dstr,std::string const &rs,std::string const &ts){
    int len = rs.length();
    int n_t = kmp(dstr,rs);
    while (n_t != -1){
        dstr.replace(n_t,len,ts);
        n_t = kmp(dstr,rs);
    }
}
/**
 * 返回指向对应协议名的结构体指针 为找到返回NULL
 * @param head  头结点
 * @param protocol 协议名
 * @return
 */
insertManyProtocolStream *insertManyFindProtocol(insertManyProtocolStream *&head, std::string &protocol) {
    insertManyProtocolStream *temp = head->next;
    while (temp != head) {
        if (temp->protocol.compare(protocol) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
/**
 * 创建多层文件夹
 * @param muldir
 */
void mkdirs(const char *muldir) {
    int i, len;
    char str[512];
    strncpy(str, muldir, 512);
    len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == '/') {
            str[i] = '\0';
            if (access(str, 0) != 0) {  // type为0表示判断该路径是否存在
                mkdir(str, 0777);  // mode定义所创建目录的权限，创建结果0表示成功，但是mkdir一次之只能创建一层目录
            }
            str[i] = '/';
        }
    }
    if (len > 0 && access(str, 0) != 0) {
        mkdir(str, 0777);
    }
}
/**
 * 最终的数据流写入对应协议文件，lines为该此写入文件的json行数。除了批量写入，其他单次写入为1
 * @param stream
 * @param protocol
 * @param lines
 * @return
 */
gboolean write_Files(std::string const &stream, std::string const &protocol,int lines) {

    if (access(EXPORT_PATH, 0) != 0) {  // type为0表示判断该路径是否存在
        /*当前协议对应文件夹不存在*/
        mkdirs(EXPORT_PATH);
    }
    std::string filepath__str_t = EXPORT_PATH + protocol + "/" + protocol + "_" + global_time_str + ".writting";
    std::string filedirpath_str_t = EXPORT_PATH + protocol;
    char filepath_t[MAXWRITEFILELENGTH] = {0};
    char fileDirPath_t[MAXWRITEFILELENGTH] = {0};

    strcpy(filepath_t, filepath__str_t.c_str());
    strcpy(fileDirPath_t, filedirpath_str_t.c_str());
    pFILE_INFO *fp_t;

    if (pFile_map.empty()) {
        /*当前是空map*/
        if (access(fileDirPath_t, 0) != 0) {
            /*当前文件夹不存在*/
            mkdirs(fileDirPath_t);
        }
        fp_t = new pFile_Info;
        fp_t->fp = fopen(filepath_t, "a+");
        if (fp_t->fp == NULL) {
            g_print("open filepath error!\n");
            return false;
        }
        fp_t->fileName_ori = filepath_t;
        fp_t->fileName_last = filepath_t;
        fp_t->lines = 0;
        fp_t->times = 1;
        pFile_map.insert(std::pair<std::string, pFILE_INFO*>(protocol, fp_t));
    } else {
        std::map<std::string, pFILE_INFO*>::iterator it;
        it = pFile_map.find(protocol);
        if (it != pFile_map.end()) {
            fp_t = it->second;
        } else {
//            没有找到对应的文件句柄,接下来新增一个句柄.
            if (access(fileDirPath_t, 0) != 0) {
                /**
                 * 当前协议对应文件夹不存在
                 */
                mkdirs(fileDirPath_t);
            }
            fp_t = new pFile_Info;
            fp_t->fp = fopen(filepath_t, "a+");
            if (fp_t->fp == NULL) {
                g_print("open filepath error!\n");
                return false;
            }
            fp_t->fileName_ori = filepath_t;
            fp_t->fileName_last = filepath_t;
            fp_t->lines = 0;
            fp_t->times = 1;
            pFile_map.insert(std::pair<std::string, pFILE_INFO*>(protocol, fp_t));
        }
    }

    fp_t->lines += lines;
    if(fp_t->lines > PER_FILES_MAX_LINES){
        //单个文件行数已经大于配置数
        fclose(fp_t->fp);
        std::string fN_t = fp_t->fileName_last;
        stringReplaceByStr(fN_t,".writting",".txt");
        rename(fp_t->fileName_last.c_str(),fN_t.c_str()); //将writing 写成最终文件。
        std::string tail = "_"+numtos(fp_t->times)+".";
        std::string file_t = fp_t->fileName_ori;
        file_t.replace(file_t.rfind('.'),1,tail);//在原始文件名上更改
        FILE *fp = fopen(file_t.c_str(),"a+");
        if(!fp){
            g_print("%s open error,FUNCTION:%s",file_t.c_str(),__FUNCTION__);
        }
        fp_t->lines = lines;
        fp_t->times++;
        fp_t->fp = fp;
        fp_t->fileName_last = file_t;
    }

    g_assert(fp_t->fp); //这里肯定fp不能为空。否则文件不知道写到那里。
    fputs(stream.c_str(),fp_t->fp);
    fflush(fp_t->fp);
    return true;
}
/**
 * 将会话统计信息写入文件中，文件名固定为conversation.txt
 * @param stream
 * @param protocol
 * @return
 */
gboolean write_Files_conv(std::string &stream) {
    /*这里把json写成一行,且添加换行符 ----begin*/
    int n_t = kmp(stream, "\n");
    while (n_t != -1) {
        stream.replace(n_t, 1, "");
        n_t = kmp(stream, "\n");
    }
    int t_t = kmp(stream, "\t");
    while (t_t != -1) {
        stream.replace(t_t, 1, "");
        t_t = kmp(stream, "\t");
    }
    stream.append("\r\n");
    /*这里把json写成一行,且添加换行符 ----end*/

    if (access(WRITE_IN_CONVERSATIONS_PATH, 0) != 0) {
        /*当前协议对应文件夹不存在*/
        if (mkdir(WRITE_IN_CONVERSATIONS_PATH, 0777) != 0) {
            g_print("%s create error", WRITE_IN_CONVERSATIONS_PATH);
        }
    }
    if (conv_path_t.empty()) {
        conv_path_t = WRITE_IN_CONVERSATIONS_PATH;
        conv_path_t = conv_path_t + "conversation_" + global_time_str + ".txt";
    }
    if (!conversation_Handle_File) {
        conversation_Handle_File = fopen(conv_path_t.c_str(), "a+");
        if (conversation_Handle_File == NULL) {
            g_print("open %s error!\n", conv_path_t.c_str());
            return false;
        }
    }
    try {
        fputs(stream.c_str(), conversation_Handle_File);
        fflush(conversation_Handle_File);
    }catch (std::out_of_range){
        g_print("out of range\n");
        return false;
    }catch (std::overflow_error){
        g_print("overflow_error\n");
        return false;
    }catch (std::runtime_error){
        g_print("runtime_error\n");
        return false;
    }
    return true;
}
size_t noop_cb(void *ptr __U__, size_t size, size_t nmemb, void *data __U__) {
    return size * nmemb;
}
/**
 * 将数据流steam写入ES数据库，protocol协议
 * @param stream
 * @param protocol
 */
void write_into_es(std::string &stream, std::string &protocol) {
    CURL *curl;
    CURLcode res;

    //HTTP报文头
    struct curl_slist *headers = NULL;
    char tmp_str[256] = {0};

    //构建HTTP报文头
    snprintf(tmp_str, sizeof(tmp_str), "content-type: application/json; charset=UTF-8");
    headers = curl_slist_append(headers, tmp_str);
    curl = curl_easy_init();  /* get a curl handle */
    if (curl) {
        std::string url = ES_URL;
        url = ES_URL + protocol + "/_doc";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  //访问的URL
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);  //设置HTTP头
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, stream.c_str());  //post请求传输的数据
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, noop_cb);  //如果不人为设置对返回数据的处理,则会自动在结束的时候在控制台打印
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);  //这个调用用来结束一个会话.与curl_easy_init配合着用
    }
    stream = "";
}
/**
 * 将数据流steam写入文件，protocol为协议
 * @param stream
 * @param protocol
 * @return
 */
gboolean write_All_Temps_Into_Files(std::string &stream, std::string &protocol) {

    /*这里把json写成一行,且添加换行符 ----begin*/
    int n_t = kmp(stream, "\n");
    while (n_t != -1) {
        stream.replace(n_t, 1, "");
        n_t = kmp(stream, "\n");
    }
    int t_t = kmp(stream, "\t");
    while (t_t != -1) {
        stream.replace(t_t, 1, "");
        t_t = kmp(stream, "\t");
    }
    stream.append("\r\n");
    /*这里把json写成一行,且添加换行符 ----end*/

    assert(protocol.compare("") != 0);

    if (INSERT_MANY_PROTOCOL_STREAM_FLAG) {
        /*批量插入标志*/
        insertManyProtocolStream *index_t = insertManyFindProtocol(insertmanystream_Head, protocol);
        if (index_t != NULL) {
            /*NOT null*/
            index_t->contents.append(stream);
            if (++index_t->times >= INSERT_MANY_PROTOCOL_STREAM_NUM) {
                /*批量插入*/
                if (!write_Files(index_t->contents, protocol,INSERT_MANY_PROTOCOL_STREAM_NUM)) {
                    g_print("%s insert error!\n", protocol.c_str());
                }
                /*批量插入成功后对这个缓存节点清空并释放缓存*/
                index_t->contents.clear();
                index_t->times = 0;
                index_t->pre->next = index_t->next;
                index_t->next->pre = index_t->pre;
                delete index_t;
            }
        } else {
            /*NULL 头插法循环双链表*/
            auto *temp = new insertManyProtocolStream;
            temp->protocol = protocol;
            temp->contents.append(stream);
            temp->times = 1;
            temp->next = insertmanystream_Head->next;
            temp->pre = insertmanystream_Head;
            insertmanystream_Head->next = temp;
            temp->next->pre = temp;
        }
    } else {
        if (!write_Files(stream, protocol,1)) {
            g_print("%s insert error !\n", protocol.c_str());
        }
    }

    stream = "";
    return true;
}
/**
 * 每个edt处理完后的，所有参数初始化。初始化较为频繁，尽量防止内存错误。
 * @return
 */
gboolean initial_All_para() {
    TRY {
                write_in_files_proto = "";

                /*初始化部分要用到的 json对象 ----begin*/
                cJSON_Delete(write_in_files_cJson);
                write_in_files_cJson = cJSON_CreateObject();
                /*初始化部分要用到的 json对象 ----end*/

                /*需要初始化strname链表*/
                initStrNameLevelLinkList(strname_head);
                strname_head = new struct strNameSameLevel;
                strname_head->next = NULL;
                strname_head->times = 0;
                strname_head->str_name = "";

                return true;
            }
            CATCH(OutOfMemoryError) {
                g_print("initialize error");
                return false;
            }
    ENDTRY;
    return true;
}

/**
 * 处理单个数据节点。针对node
 * @param json_t
 * @param node
 * @param cookie
 * @return
 */
gboolean dissect_Per_Node_No_Cursion(cJSON *&json_t,proto_node *&temp, struct totalParam *cookie __U__){
    if(temp->finfo->length >= 1514 or temp->finfo->length <= 0) return false; //无意义的长值直接跳过

    std::string key_str = temp->finfo->hfinfo->abbrev;
    if(cursionkeyStrFilter(key_str.c_str())) return false; //无意义的字段过滤掉

    //获取value
    auto *value = new gchar[(temp->finfo->length *3 +1)>100?temp->finfo->length *3 +1:100];
    yy_proto_item_fill_label(temp->finfo,value);

    //将key_str 形式“x.ab.c.d” 转换成“x_ab_c_d”
    while (key_str.find('.') != std::string::npos) {  /* 返回string::npos表示未查找到匹配项 */
        key_str.replace(key_str.find('.'), 1, "_");
    }

/*
            //重复字段的数组处理
            if(judgeDuplicateKeyStr(key_str)){
                cJSON *item = cJSON_GetObjectItem(json_t,key_str.c_str());
                if(cJSON_IsArray(item)){
                    //已经是数组
                    cJSON_AddItemToArray(item,cJSON_CreateString(value));
                } else{
                    //第一次重复
                    std::string pre_value = cJSON_GetStringValue(item);
                    cJSON_DeleteItemFromObject(json_t, key_str.c_str());
                    cJSON * temp_array = cJSON_AddArrayToObject(json_t, key_str.c_str());
                    cJSON_AddItemToArray(temp_array,cJSON_CreateString(pre_value.c_str()));
                    cJSON_AddItemToArray(temp_array,cJSON_CreateString(value));
                }
            } else{
                cJSON_AddStringToObject(json_t,key_str.c_str(),value);
            }
*/

    key_str = gotStrNameByStrName(key_str);
    cJSON_AddStringToObject(json_t,key_str.c_str(),value);

    delete []value;
}
/**
 * 非递归处理协议解析树内容，层序遍历，存入json中。
 * @param json_t
 * @param node
 * @param cookie
 * @return
 */
gboolean dissect_edt_Tree_Into_Json_No_Cursion(cJSON *&json_t,proto_node *&node, struct totalParam *cookie __U__){
    std::queue< proto_node* > que;
    while(node != nullptr){
        if(node->first_child == nullptr or node->last_child == nullptr){
            dissect_Per_Node_No_Cursion(json_t,node,cookie);
            node = node->next;
        } else{
            que.push(node);
            node = node->next;
        }
    }
    while (!que.empty()){
        proto_node* temp = que.front();
        que.pop();
        if(temp->first_child == nullptr or temp->last_child == nullptr){
            dissect_Per_Node_No_Cursion(json_t,temp,cookie);
        } else{
            temp = temp->first_child;
            while (temp != nullptr){
                que.push(temp);
                temp = temp->next;
            }
        }
    }
    return true;
}
/**
 * 递归处理协议解析树内容，存入json中。
 * @param json_t
 * @param node
 */
gboolean dissect_edt_Tree_Into_Json(cJSON *&json_t, proto_node *&node,int &cursion_layer,struct totalParam *cookie) {
    /*key的置换和获取*/
    std::string key_str = node->finfo->hfinfo->abbrev;
    if(cursionkeyStrFilter(key_str.c_str())){
        return true;
    }
    if(++cursion_layer > 500 ) return true;

    if (node->first_child == nullptr or node->last_child == nullptr) {
        /*数据节点*/
        if (node->finfo->length > 0 and node->finfo->length <= 1514 ) {
            try {
                gchar value[4542] = {'\0'};
                yy_proto_item_fill_label(node->finfo, value);
//               将key_str 形式“x.ab.c.d” 转换成“x_ab_c_d”
                while (key_str.find('.') != std::string::npos) {  /* 返回string::npos表示未查找到匹配项 */
                    key_str.replace(key_str.find('.'), 1, "_");
                }
//               返回该包内重复字段的名称，如A_01,A_02...
                key_str = gotStrNameByStrName(key_str);
                cJSON_AddStringToObject(json_t, key_str.c_str(), value); //写入JSON
            } catch (std::out_of_range) {
                g_print("out of range\n");
                return false;
            }
            catch (std::length_error) {
                g_print("length_error\n");
                return false;
            }
            catch (std::range_error) {
                g_print("range_error\n");
                return false;
            }
        }
        if (node->next != NULL) {
            proto_node *index = node->next;
            if (!dissect_edt_Tree_Into_Json(json_t, index,cursion_layer,cookie)) {
                g_print("%s dissect_edt_Tree_Into_Json error!\n", key_str.c_str());
                return false;
            }
        }
    }
    else {
        /*还有子节点*/
        dissect_edt_Tree_Into_Json(json_t, node->first_child,cursion_layer,cookie);
        if (node->next != NULL) {
            proto_node *index = node->next;
            dissect_edt_Tree_Into_Json(json_t, index,cursion_layer,cookie);
        }
    }
    return true;
}
/**
 * 匹配线路号
 * @param pattern 匹配模式
 * @param source_str 目标文本串
 * @return
 */
void match_line_no(char *pattern, char *source_str, char * target) {
    GRegex *regex;   //正则表达式对象
    GMatchInfo *match_info;   //匹配后的集合
    GError *error = NULL;
    regex = g_regex_new(pattern, static_cast<GRegexCompileFlags>(0), static_cast<GRegexMatchFlags>(0),
                        &error);  //创建正则表达式
    g_regex_match(regex, source_str, static_cast<GRegexMatchFlags>(0), &match_info);   //匹配
    while (g_match_info_matches(match_info)) {    //利用g_match_info_fetch把每一项fetch出来
        gint count = g_match_info_get_match_count(match_info);
//        g_print("match count:%d\n", count);

        int i;
        for (i = 0; i < count; i++) {
            gchar *word = g_match_info_fetch(match_info, i);
            strcpy(target, word);
            g_free(word);
        }
        g_match_info_next(match_info, NULL);
        if(strlen(target)>1) break;
    }
    g_match_info_free(match_info);  //释放空间
    g_regex_unref(regex);
}
/**
 * 每解析一个新的文件开始时进行初始化，用OFFLINE_LINE_NO_REGEX对应的value，正则匹配新的文件名称，将该文件名匹配后的结果写入regex_dict_map中。
 * 注意每解析完一个文件后需要对regex_dict_map进行初始化。
 */
void parse_offline_regex_dict(){
    if(regex_dict && regex_dict->child){
        cJSON *temp = regex_dict->child;
        while (temp!=nullptr){
            char value[250] = {0};
            match_line_no(temp->valuestring, FILE_NAME_T, value);
            cJSON_AddStringToObject(write_in_files_cJson, temp->string, value);
            regex_dict_map.insert(std::pair<std::string,std::string>(temp->string,value));
            temp = temp->next;
        }
    }
}

/**
 * 直接解析edt 写入文件缓存中 202107290910
 * @param edt
 * @return
 */
gboolean dissect_edt_into_files(epan_dissect_t *edt) {
    if (edt->tree == nullptr)
        return false;
    proto_node *node = edt->tree->first_child;
    if(node == nullptr)
        return false;

    std::string protocol_stack_t;  // 记录协议栈
    proto_node *stack_node_t = node;

    int stack_node_layer = 0;
    while (stack_node_t != nullptr and ++stack_node_layer < 11) {
        field_info *fi = stack_node_t->finfo;
        if (lastLayerProtocolFilter(fi->hfinfo->abbrev)) {
            stack_node_t = stack_node_t->next;
            continue;
        }
        if (protocol_stack_t.empty() == 1) {
            protocol_stack_t.append(fi->hfinfo->abbrev);
            write_in_files_proto = fi->hfinfo->abbrev;
        }
        else {
            protocol_stack_t.append(",");
            protocol_stack_t.append(fi->hfinfo->abbrev);
            write_in_files_proto = fi->hfinfo->abbrev;
        }
        stack_node_t = stack_node_t->next;
    }
    /*单独的协议过滤*/
    if (kmp("[tcp],[udp]", "[" + write_in_files_proto + "]") != -1) {
        return true;
    }

    /*获取文件来源*/
    if (read_Pcap_From_File_Flag == 1) {
        /* 单个文件 */
        cJSON_AddStringToObject(write_in_files_cJson, str_FILES_RESOURCE, READ_FILE_PATH);
        if(!regex_dict_map.empty()){
            for (auto & i : regex_dict_map) {
                cJSON_AddStringToObject(write_in_files_cJson, i.first.c_str(), i.second.c_str());
            }
        }
    } else {
        cJSON_AddStringToObject(write_in_files_cJson, str_FILES_RESOURCE, "online");
        cJSON_AddStringToObject(write_in_files_cJson, "line_no", ONLINE_LINE_NO);  // 在线实时接入数据的线路号
    }
    /*协议栈*/
    cJSON_AddStringToObject(write_in_files_cJson, "protocols", protocol_stack_t.c_str());
    cJSON_AddStringToObject(write_in_files_cJson, "frame_id", numtos(edt->pi.num).c_str());

    /*帧头每个数据包肯定有帧头*/
    if (strcmp(node->finfo->hfinfo->abbrev, "frame") == 0) {
        proto_node *child = node->first_child; //该层协议的第一个字段
        while (child != nullptr) {
            /*该层协议具有内容*/
            field_info *child_finfo = child->finfo;
            if (strcmp(child_finfo->hfinfo->abbrev, "frame.encap_type") == 0) {
                gchar value[240] = {'\0'};
                yy_proto_item_fill_label(child_finfo, value);
                cJSON_AddStringToObject(write_in_files_cJson, "frame_encap_type", value);
                child = child->next;
                continue;
            }
            if (strcmp(child_finfo->hfinfo->abbrev, "frame.time_epoch") == 0) {
                gchar value[240] = {'\0'};
                yy_proto_item_fill_label(child_finfo, value);
                cJSON_AddStringToObject(write_in_files_cJson, "frame_time_epoch", value);
                child = child->next;
                continue;
            }
            if (strcmp(child_finfo->hfinfo->abbrev, "frame.len") == 0) {
                gchar value[240] = {'\0'};
                yy_proto_item_fill_label(child_finfo, value);
                cJSON_AddStringToObject(write_in_files_cJson, "frame_len", value);
                break; //这里最后一个，提高效率
            }
            child = child->next;
        }
        node = node->next;
    }

    while (node != nullptr) {
        field_info *fi = node->finfo;

        /*eth*/
        if (strcmp(fi->hfinfo->abbrev, "eth") == 0) {
            proto_node *child = node->first_child;
            while (child != nullptr) {
                field_info *child_finfo = child->finfo;
                if (strcmp(child_finfo->hfinfo->abbrev, "eth.dst") == 0) {
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo, value);
                    cJSON_AddStringToObject(write_in_files_cJson, "eth_dst", value);
                    child = child->next;
                    continue;
                }
                else if (strcmp(child_finfo->hfinfo->abbrev, "eth.src") == 0) {
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo, value);
                    cJSON_AddStringToObject(write_in_files_cJson, "eth_src", value);
                    break;//这里最后一个，提高效率
                }
                child = child->next;
            }
            node = node->next;
            continue;
        }
        /*ip ipv6 */
        else if (strcmp(fi->hfinfo->abbrev, "ip") == 0 or strcmp(fi->hfinfo->abbrev, "ipv6") == 0) {
            proto_node *child = node->first_child;
            while (child != nullptr) {
                field_info *child_finfo = child->finfo;
                if (strcmp(child_finfo->hfinfo->abbrev, "ip.src") == 0 or
                    strcmp(child_finfo->hfinfo->abbrev, "ipv6.src") == 0) {
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo, value);
                    cJSON_AddStringToObject(write_in_files_cJson, "src_ip", value);
                    child = child->next;
                    continue;
                }
                else if (strcmp(child_finfo->hfinfo->abbrev, "ip.dst") == 0 or
                    strcmp(child_finfo->hfinfo->abbrev, "ipv6.dst") == 0) {
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo, value);
                    cJSON_AddStringToObject(write_in_files_cJson, "dst_ip", value);
                    break;//这里最后一个，提高效率
                }
                child = child->next;
            }

            node = node->next;
            continue;
        }
        /*tcp udp*/
        else if (strcmp(fi->hfinfo->abbrev, "tcp") == 0 or strcmp(fi->hfinfo->abbrev, "udp") == 0) {
            proto_node *child = node->first_child;
            while (child != nullptr) {
                field_info *child_finfo = child->finfo;
                if (strcmp(child_finfo->hfinfo->abbrev, "tcp.srcport") == 0 or
                    strcmp(child_finfo->hfinfo->abbrev, "udp.srcport") == 0) {
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo, value);
                    cJSON_AddStringToObject(write_in_files_cJson, "src_port", value);
                    child = child->next;
                    continue;
                }
                else if (strcmp(child_finfo->hfinfo->abbrev, "tcp.dstport") == 0 or
                    strcmp(child_finfo->hfinfo->abbrev, "udp.dstport") == 0) {
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo, value);
                    cJSON_AddStringToObject(write_in_files_cJson, "dst_port", value);
                    child = child->next;
                    continue;
                }
                child = child->next;
            }
            node = node->next;
            continue;
        }
        /*未知协议识别规则：最后层协议为data,暂定为未知协议,20211008 yy*/
        else if(strcmp(fi->hfinfo->abbrev,"data") == 0){
            if(node->first_child->first_child != nullptr){
                //当前data并不是最后一个协议，
                continue;
            }
            field_info *fi_data = node->first_child->finfo;
            if(strcmp(fi_data->hfinfo->abbrev,"data.data") == 0){
                auto *value = new gchar[fi_data->length *2 +1];
                yy_proto_item_fill_label(fi_data,value);
                cJSON_AddStringToObject(write_in_files_cJson,"data",value);
                write_in_files_proto = "unknown";
                delete []value;
            }
            //这里直接退出协议数据获取循环。不必进入最后层协议的解析。
            break;
        }
        /*最后层协议的解析*/
        else if (strcmp(fi->hfinfo->abbrev, write_in_files_proto.c_str()) == 0) {
            proto_node *child = node->first_child;
            if (child != nullptr) {
                try {
                    int curlayer = 0;
                    dissect_edt_Tree_Into_Json_No_Cursion(write_in_files_cJson, child, nullptr);
//                    dissect_edt_Tree_Into_Json(write_in_files_cJson,child,curlayer, nullptr);
                }
                catch (std::invalid_argument) {
                    node = node->next;
                    continue;
                }
            }
            break;
        }
        node = node->next;
    }

    write_in_files_stream = cJSON_Print(write_in_files_cJson);
    if (WRITE_IN_ES_FLAG == 1) {
        write_into_es(write_in_files_stream, write_in_files_proto);
    }
    if (WRITE_IN_ES_FLAG != 1 && WRITE_IN_FILES_CONFIG == 1) {
        if (!write_All_Temps_Into_Files(write_in_files_stream, write_in_files_proto)) {
            g_print("write in files error");
            return false;
        }
    }
    if (!initial_All_para()) {
        g_print("initialize error!");
        return false;
    }
    return true;
}

/**
 * 程序结束后将tap-iousers.c中的统计会话数据conversation写入文件中。
 * @param label_str 字段
 * @param level 层级
 */
void do_write_in_conversation_handler(gchar *key, gchar *value) {
    std::string key_str = key;
    std::string value_str = value;
    if (value_str == "-1END") {
        /*获取文件来源，将conversation与源文件进行关联*/
        if (read_Pcap_From_File_Flag == 1) {
            cJSON_AddStringToObject(write_in_files_conv_cJson, str_FILES_RESOURCE, READ_FILE_PATH);
            cJSON_AddStringToObject(write_in_files_conv_cJson, "line_no", OFFLINE_LINE_LINE_NO);  /* 离线接入数据的线路号 */
        } else {
            cJSON_AddStringToObject(write_in_files_conv_cJson, str_FILES_RESOURCE, "online");
            cJSON_AddStringToObject(write_in_files_conv_cJson, "line_no", ONLINE_LINE_NO);  // 在线实时接入数据的线路号
        }
        /*当前流统计结束*/
        if (write_in_files_conv_cJson->child == nullptr)
            return;
        std::string string = cJSON_Print(write_in_files_conv_cJson);
        write_Files_conv(string);
        cJSON_Delete(write_in_files_conv_cJson);
        write_in_files_conv_cJson = cJSON_CreateObject();
    } else {
        cJSON_AddStringToObject(write_in_files_conv_cJson, key_str.c_str(), value_str.c_str());
    }
}

/**
 * 程序一开始的初始化，初始化write_file_in_files_handlers.cpp的各种变量。
 * 另外需要一开始初始化的对象也在这里初始化 beginInitOnce
 * @param flag
 * @return
 */
gboolean beginInitOnce(char *flag) {

//    这里把同级的level的strname初始化
    strname_head = new struct strNameSameLevel;
    strname_head->next = nullptr;
    strname_head->str_name = "";
    strname_head->times = 0;
    regex_dict = (cJSON *) cJSON_Parse(OFFLINE_LINE_NO_REGEX); //线路号匹配的json初始化
    if (regex_dict == nullptr) {
        g_print("KEY:OFFLINE_LINE_NO_REGEX format error!\n");
        g_print("must be standard JSON format\n");
        g_print("example:{\"KEY1\":\"VALUE1\",\"KEY2\":\"VALUE2\"}\n");
        exit(0);
    }


    /*批量插入初始化头部节点*/
    if (INSERT_MANY_PROTOCOL_STREAM_FLAG == 1) {
        insertmanystream_Head = new struct insertManyProtocolStream;
        insertmanystream_Head->next = insertmanystream_Head;
        insertmanystream_Head->pre = insertmanystream_Head;
        insertmanystream_Head->times = 0;
        insertmanystream_Head->protocol = "";
        insertmanystream_Head->contents = "";
    }

    /*初始化互斥变量*/
    *flag = 1;
    return true;
}

/**
 * 程序一开始读取一次configfiles的内容.
 * @return
 */
gboolean readConfigFilesStatus() {
    TRY {
                std::string temp_str_json_path;
                std::string temp_str_export_path;
                char *write_in_files_config;
                char *write_in_conversations_flag;
                char *export_path;
                char *display_packet_info_flag;
                char *online_capture_data_flag;
                char *online_capture_data_device_name;
                char *read_packet_from_files_flag;
                char *read_packet_from_files_path;
                char *json_add_proto;
                char *json_add_proto_path;
                char *edit_files_dissect_flag;
                char *edit_files_sizes;
                char *insert_many_protocol_stream_flag;
                char *insert_many_protocol_stream_num;
                char *online_line_no;
                char *offline_line_no_regex;
                char *registration_file_path;
                char *write_in_es_flag;
                char *es_url;
                char *per_files_max_linex;

                /**
                 * 这里需要把当前运行的时间戳定下来
                 */
                std::time_t global_time = std::time(nullptr);
                global_time_str = numtos((u_long) global_time);
                g_print("current files time %s \n", global_time_str.c_str());

                char **fileData = nullptr;
                int lines = 0;
                struct ConfigInfo *info = nullptr;

                if (loadFile_ConfigFile(CONFIG_FILES_PATH, &fileData, &lines)) {
                    parseFile_ConfigFile(fileData, lines, &info);
                } else {
                    return false;
                }

                write_in_es_flag = getInfo_ConfigFile("WRITE_IN_ES_FLAG", info, lines);
                if (write_in_es_flag != nullptr) {
                    WRITE_IN_ES_FLAG = *write_in_es_flag - '0';
                } else WRITE_IN_ES_FLAG = 0;

                es_url = getInfo_ConfigFile("ES_URL", info, lines);
                if (es_url != nullptr) {
                    strcpy(ES_URL, es_url);
                    int len = strlen(ES_URL);
                    if (ES_URL[len - 1] != '/') {
                        strcat(ES_URL, "/");
                    }
                }

                registration_file_path = getInfo_ConfigFile("REGISTRATION_FILE_PATH", info, lines);
                if (registration_file_path != nullptr) {
                    strcpy(REGISTRATION_FILE_PATH, registration_file_path);
                    int len = strlen(REGISTRATION_FILE_PATH);
                    if (REGISTRATION_FILE_PATH[len - 1] != '/') {
                        strcat(REGISTRATION_FILE_PATH, "/");
                    }
                } else {
                    strcpy(REGISTRATION_FILE_PATH, "./");
                }

                insert_many_protocol_stream_flag = getInfo_ConfigFile("INSERT_MANY_PROTOCOL_STREAM_FLAG", info, lines);
                if (insert_many_protocol_stream_flag != nullptr) {
                    INSERT_MANY_PROTOCOL_STREAM_FLAG = *insert_many_protocol_stream_flag - '0';
                } else INSERT_MANY_PROTOCOL_STREAM_FLAG = 0;

                insert_many_protocol_stream_num = getInfo_ConfigFile("INSERT_MANY_PROTOCOL_STREAM_NUM", info, lines);
                if (insert_many_protocol_stream_num != nullptr) {
                    INSERT_MANY_PROTOCOL_STREAM_NUM = std::stoi(insert_many_protocol_stream_num);
                } else INSERT_MANY_PROTOCOL_STREAM_NUM = 1000;

                edit_files_sizes = getInfo_ConfigFile("EDIT_FILES_SIZES", info, lines);
                if (edit_files_sizes != nullptr) {
                    EDIT_FILES_SIZES = std::stoi(edit_files_sizes);
                } else EDIT_FILES_SIZES = 1000;

                per_files_max_linex = getInfo_ConfigFile("PER_FILES_MAX_LINES", info, lines);
                if (per_files_max_linex != nullptr) {
                    PER_FILES_MAX_LINES = std::stoi(per_files_max_linex);
                } else PER_FILES_MAX_LINES = 10000;

                edit_files_dissect_flag = getInfo_ConfigFile("EDIT_FILES_DISSECT_FLAG", info, lines);
                if (edit_files_dissect_flag != nullptr) {
                    EDIT_FILES_DISSECT_FLAG = *edit_files_dissect_flag - '0';
                } else EDIT_FILES_DISSECT_FLAG = 0;

                write_in_files_config = getInfo_ConfigFile("WRITE_IN_FILES_CONFIG", info, lines);
                if (write_in_files_config != nullptr) {
                    WRITE_IN_FILES_CONFIG = *write_in_files_config - '0';
                } else WRITE_IN_FILES_CONFIG = 0;

                write_in_conversations_flag = getInfo_ConfigFile("WRITE_IN_CONVERSATIONS_FLAG", info, lines);
                if (write_in_conversations_flag != nullptr) {
                    WRITE_IN_CONVERSATIONS_FLAG = *write_in_conversations_flag - '0';
                } else {
                    WRITE_IN_CONVERSATIONS_FLAG = 0;
                }

                export_path = getInfo_ConfigFile("EXPORT_PATH", info, lines);
                if (export_path != nullptr) {
                    strcpy(EXPORT_PATH, export_path);
                    int len = strlen(EXPORT_PATH);
                    if (EXPORT_PATH[len - 1] != '/') {
                        strcat(EXPORT_PATH, "/");
                    }
                    /*统一将路径全部初始化掉*/
                    strcat(RESULT_PATH, EXPORT_PATH);
                    strcat(WRITE_IN_CONVERSATIONS_PATH, EXPORT_PATH);
                    strcat(WRITE_IN_CONVERSATIONS_PATH, "conversation/");

                    strcat(PACKET_PROTOCOL_PATH, EXPORT_PATH);
                    strcat(PACKET_PROTOCOL_PATH, "export/");

                    strcat(EXPORT_PATH, "dissectors/");  // TODO: 其实不太合理
                } else {
                    strcpy(EXPORT_PATH, "./");
                }

                display_packet_info_flag = getInfo_ConfigFile("DISPLAY_PACKET_INFO_FLAG", info, lines);
                if (display_packet_info_flag != nullptr) {
                    DISPLAY_PACKET_INFO_FLAG = *display_packet_info_flag - '0';
                } else {
                    DISPLAY_PACKET_INFO_FLAG = 0;
                }

                online_capture_data_flag = getInfo_ConfigFile("ONLINE_CAPTURE_DATA_FLAG", info, lines);
                if (online_capture_data_flag != nullptr) {
                    ONLINE_CAPTURE_DATA_FLAG = *online_capture_data_flag - '0';
                } else {
                    ONLINE_CAPTURE_DATA_FLAG = 0;
                }

                online_capture_data_device_name = getInfo_ConfigFile("ONLINE_CAPTURE_DATA_DEVICE_NAME", info, lines);
                if (online_capture_data_device_name != nullptr) {
                    strcpy(ONLINE_CAPTURE_DATA_DEVICE_NAME, online_capture_data_device_name);
                } else {
                    strcpy(ONLINE_CAPTURE_DATA_DEVICE_NAME, "./");
                }

                read_packet_from_files_flag = getInfo_ConfigFile("READ_PACKET_FROM_FILES_FLAG", info, lines);
                if (read_packet_from_files_flag != nullptr) {
                    READ_PACKET_FROM_FILES_FLAG = *read_packet_from_files_flag - '0';
                } else {
                    READ_PACKET_FROM_FILES_FLAG = 0;
                }

                read_packet_from_files_path = getInfo_ConfigFile("READ_PACKET_FROM_FILES_PATH", info, lines);
                if (read_packet_from_files_path != nullptr) {
                    strcpy(READ_PACKET_FROM_FILES_PATH, read_packet_from_files_path);
                    auto *st = new struct stat;
                    stat(READ_PACKET_FROM_FILES_PATH, st);
                    if (S_ISDIR(st->st_mode)) {
                        int len = strlen(READ_PACKET_FROM_FILES_PATH);
                        if (READ_PACKET_FROM_FILES_PATH[len - 1] != '/') {
                            strcat(READ_PACKET_FROM_FILES_PATH, "/");
                        }
                        file_Name_From_Dir_Flag = 1;
                    }
                    free(st);
                } else {
                    strcpy(READ_PACKET_FROM_FILES_PATH, "./");
                }

                json_add_proto = getInfo_ConfigFile("JSON_ADD_PROTO", info, lines);
                if (json_add_proto != nullptr) {
                    JSON_ADD_PROTO = *json_add_proto - '0';
                } else {
                    JSON_ADD_PROTO = 0;
                }

                json_add_proto_path = getInfo_ConfigFile("JSON_ADD_PROTO_PATH", info, lines);
                if (json_add_proto_path != nullptr) {
                    strcpy(JSON_ADD_PROTO_PATH, json_add_proto_path);
                } else {
                    strcpy(JSON_ADD_PROTO_PATH, "./defaul.json");
                }

                online_line_no = getInfo_ConfigFile("ONLINE_LINE_NO", info, lines);
                if (online_line_no != nullptr) {
                    strcpy(ONLINE_LINE_NO, online_line_no);  /* TODO: 适配首部有空格的情况 */
                } else {
                    strcpy(ONLINE_LINE_NO, "");
                }

                offline_line_no_regex = getInfo_ConfigFile("OFFLINE_LINE_NO_REGEX", info, lines);
                if (offline_line_no_regex != nullptr) {
                    strcpy(OFFLINE_LINE_NO_REGEX, offline_line_no_regex);
                } else {
                    strcpy(OFFLINE_LINE_NO_REGEX, "");
                }

                destroInfo_ConfigFile(info);
            };
            CATCH_ALL {
                return false;
            }
    ENDTRY;
    curl_global_init(CURL_GLOBAL_ALL);
    return true;
}

/**
 * 程序结束的最后操作。02 释放一些数据结构，仅释放一次。
 */
void clean_Temp_Files_All() {
    if (!mutex_final_clean_flag) {
        if (insertmanystream_Head != nullptr and insertmanystream_Head->next != insertmanystream_Head) {
            /*批量插入缓存还有内容*/
            insertManyProtocolStream *index_t = insertmanystream_Head->next;
            while (index_t != insertmanystream_Head) {
                write_Files(index_t->contents, index_t->protocol,1);//最后的清理工作，默认当作1条数据，会导致一个文件行数目可能会大于PER_FILES_MAX_LINES。
                insertManyProtocolStream *t = index_t;
                index_t = index_t->next;
                delete t;
            }
        }
        if (INSERT_MANY_PROTOCOL_STREAM_FLAG == 1) {
            insertmanystream_Head = new struct insertManyProtocolStream;
            insertmanystream_Head->next = insertmanystream_Head;
            insertmanystream_Head->pre = insertmanystream_Head;
            insertmanystream_Head->times = 0;
            insertmanystream_Head->protocol = "";
            insertmanystream_Head->contents = "";
        }
        /*最后内存清空,modify files name, .writting -> .txt*/
        for (const auto& index : pFile_map) {
            std::string oldName_t = index.second->fileName_last;
            std::string newName_t = index.second->fileName_last;
            stringReplaceByStr(newName_t,".writting",".txt");
            rename(oldName_t.c_str(), newName_t.c_str());
            fclose(index.second->fp);
        }

        //delete regex_dict cJson
        cJSON_Delete(regex_dict);

        pFile_map.clear();
        /*最终初始化互斥变量*/
        mutex_final_clean_flag = 1;
    }
}

/**
 * 将处理完的文件名称写入结果文件 result+global_time_str.writting
 * READ_FILE_PATH 全局存放文件名（含路径）
 */
void add_record_in_result_file() {
    if (fp_result_timestampe == nullptr) {
        std::string filepath_str = RESULT_PATH;
        filepath_str += "result-" + global_time_str + ".writting";
        fp_result_timestampe = fopen(filepath_str.c_str(), "a+");
        fputs(READ_FILE_PATH, fp_result_timestampe);
        fputs("\r\n", fp_result_timestampe);
        fflush(fp_result_timestampe);
    } else {
        fputs(READ_FILE_PATH, fp_result_timestampe);
        fputs("\r\n", fp_result_timestampe);
        fflush(fp_result_timestampe);
    }
}

/**
 * 单个文件结束，进行初始化操作函数
 */
void single_File_End_Init(){
    regex_dict_map.clear(); //每个文件的线路号清空
}

/**
 * 程序结束的最后操作。01
 */
void change_result_file_name() {
    std::string filepath_str = RESULT_PATH;
    std::string oldName_t = filepath_str + "result-" + global_time_str + ".writting";
    std::string newName_t = filepath_str + "result-" + global_time_str + ".txt";
    rename(oldName_t.c_str(), newName_t.c_str());

    std::time_t end_time = std::time(nullptr);
    g_print("结束时间戳：%s \n", numtos((u_long) end_time).c_str());
    int begin_time = (int)strtol(global_time_str.c_str(), nullptr,10);
    int cost_time = (int) end_time - begin_time;
    g_print("总计耗时：%d 秒\n", cost_time);

    curl_global_cleanup();  //在结束libcurl使用的时候，用来对curl_global_init做的工作清理。类似于close的函数
}

