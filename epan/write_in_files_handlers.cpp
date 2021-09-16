//
// Created by root on 21-6-16.
//

#include "write_in_files_handlers.h"
#include <cstdio>
#include <string>
#include <vector>
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
#include <regex>   // c++   [ c use #include <regex.h> ]
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "curl/curl.h"

/*常用的一些字符串*/
#define str_FILES_RESOURCE "file_path"


extern void fill_label_number(field_info *fi, gchar *label_str, gboolean is_signed);

/*即将写进文件的协议*/
static std::string write_in_files_proto;
/*内容缓存*/
static std::string write_in_files_stream = "";
static cJSON *write_in_files_cJson = cJSON_CreateObject();
static cJSON *pro_cJson = cJSON_CreateObject();
/*缓存会话数据内容*/
static cJSON *write_in_files_conv_cJson = cJSON_CreateObject();
static std::string conv_path_t = "";

static FILE *conversation_Handle_File = nullptr;

char EXPORT_PATH[256] = {0};
char RESULT_PATH[256] = {0};

gboolean WRITE_IN_FILES_CONFIG = 1;
gboolean DISPLAY_PACKET_INFO_FLAG = 0;
gboolean WRITE_IN_CONVERSATIONS_FLAG = 1;
gboolean EDIT_FILES_DISSECT_FLAG = 0;
gboolean file_Name_From_Dir_Flag = 0;

char WRITE_IN_CONVERSATIONS_PATH[256] = {0};
gboolean PACKET_PROTOCOL_FLAG = 0;
char PACKET_PROTOCOL_TYPES[256] = {0};
char PACKET_PROTOCOL_PATH[256] = {0};

int EDIT_FILES_SIZES = 1000;
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
char OFFLINE_LINE_NO_REGEX[256] = {0};  /* 离线接入数据的识别线路号的正则表达式 */
char REGISTRATION_FILE_PATH[256] = {0};  /* 注册文件的路径 */
char OFFLINE_LINE_LINE_NO[256] = {0};

//写入ES数据库相关配置
gboolean WRITE_IN_ES_FLAG = 0;  /* 配置是否写入ElasticSearch数据库 */
char ES_URL[256] = {0};  /* ElasticSearch地址 */

static std::string global_time_str;  // long int types
FILE *fp_result_timestampe = nullptr;

/*最终的初始化互斥变量1代表已经初始化过一次*/
gboolean mutex_final_clean_flag = 0;

/*批量插入的链表*/
struct insertManyProtocolStream {
    struct insertManyProtocolStream *next;
    struct insertManyProtocolStream *pre;
    std::string contents;
    std::string protocol;
    int times;
};
static insertManyProtocolStream *insertmanystream_Head;

//strname的重复次数，头文件times为-1
struct strNameSameLevel {
    std::string str_name;
    struct strNameSameLevel *next;
    u_int times;
};
struct strNameSameLevel *strname_head;

//协议名称与对应的文件打开的指针map
std::map<std::string, FILE *> pFile_map;

//stream handle----------------------------begin 20210909 yy ----------------------------stream handle begin
//rtp stream---------------------- 20210909 yy ----------------------rtp stream begin
const char *rtp_payload_type_to_str[128] = {
        "g711U","fs-1016","g721","GSM","g723","DVI4 8k","DVI4 16k","Exp. from Xerox PARC","g711A","g722","16-bit audio, stereo",\
        "16-bit audio, monaural","Qualcomm","CN","MPEG-I/II Audio","g728","DVI4 11k","DVI4 22k","g729","CN(old)","Unassigned","Unassigned","Unassigned",\
        "Unassigned","Unassigned","CellB","JPEG","Unassigned","NV","Unassigned","Unassigned","h261","MPEG-I/II Video","MPEG-II streams","h263",\
        "Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned",\
        "Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned",\
        "Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned",\
        "Unassigned","Unassigned","Unassigned","Unassigned","Reserved for RTCP conflict avoidance","Reserved for RTCP conflict avoidance","Reserved for RTCP conflict avoidance",\
        "Reserved for RTCP conflict avoidance","Reserved for RTCP conflict avoidance","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned",\
        "Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned","Unassigned",\
        "Unassigned","RTPType-96","RTPType-97","RTPType-98","RTPType-99","RTPType-100","RTPType-101","RTPType-102","RTPType-103","RTPType-104","RTPType-105","RTPType-106",\
        "RTPType-107","RTPType-108","RTPType-109","RTPType-110","RTPType-111","RTPType-112","RTPType-113","RTPType-114","RTPType-115","RTPType-116","RTPType-117",\
        "RTPType-118","RTPType-119","RTPType-120","RTPType-121","RTPType-122","RTPType-123","RTPType-124","RTPType-125","RTPType-126","RTPType-127"
        };
//rtp 流文件句柄map
static std::map<std::string,FILE*> rtp_stream_pFile_map;
GList *rtp_fields = nullptr;
struct rtp_Content{
    gboolean marker;
    char ssrc[24];
    guint8 payload[2*4000];
    size_t payload_len;
    unsigned int payload_type;
};
gboolean packetProtoAlready = 0;
typedef struct _rtp_decoder_t{
    codec_handle_t handle;
    void *context;
} rtp_decoder_t;
//rtp stream---------------------- 20210909 yy ---------------------- rtp stream end

struct totalParam{
    struct rtp_Content *rtp_content = nullptr;
};
/*流处理函数线程池*/
GThreadPool *handleStreamTpool;
//stream handle----------------------------begin 20210909 yy ----------------------------stream handle end

template <typename T>
std::string numtos(T l){
    std::ostringstream os;
    os << l;
    std::string result;
    std::istringstream is(os.str());
    is >> result;
    return result;
}

/**
 * 返回字段名称
 * @param strname 字段名称
 * @param level 层次
 * @return
 */
std::string gotStrNameByStrName(std::string &strname) {

    if (strname_head->next == NULL) {
        struct strNameSameLevel *temp = new struct strNameSameLevel;
        temp->next = strname_head->next;
        temp->times = 0;
        temp->str_name = strname;
        strname_head->next = temp;
        return strname;
    } else {
        struct strNameSameLevel *temp = strname_head->next;
        while (temp != NULL) {
            if (temp->str_name.compare(strname) == 0) {
                temp->times++;
                return strname + "_" + numtos(temp->times);
            }
            temp = temp->next;
        }
        if (temp == NULL) {
            struct strNameSameLevel *temp_t = new struct strNameSameLevel;
            temp_t->next = strname_head->next;
            temp_t->times = 0;
            temp_t->str_name = strname;
            strname_head->next = temp_t;
            return strname;
        }
    }
    return strname;
}

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
std::vector<std::string> split(const std::string &str, std::string delim) {
    std::vector<std::string> res;
    char *source = new char[str.length() + 1];
    strcpy(source, str.c_str());
    char *p = strtok(source, delim.c_str());
    while (p) {
        res.push_back(p);
        p = strtok(NULL, delim.c_str());
    }
    delete[] source;
    return res;
}

/**
 * filter lastLayerProtocol Name By given chars.
 * @param dst
 * @return
 */
gboolean lastLayerProtocolFilter(const char *dst) {
    if (strcmp(dst, "communityid") == 0) {
        return TRUE;
    }
    if (strcmp(dst, "ftp.current-working-directory") == 0) {
        return TRUE;
    }
    if (strcmp(dst, "xml") == 0) {
        return TRUE;
    }
    if (strcmp(dst, "json") == 0) {
        return TRUE;
    }
    if (strcmp(dst, "_ws.malformed") == 0) {  /* SSHv2协议中多解析出来的信息 */
        return TRUE;
    }
    if (strcmp(dst, "smb2.fsctl.wait.name") == 0) {  /* smb2协议中多解析出来的信息 */
        return TRUE;
    }
    if (strcmp(dst, "mswsp.msg") == 0) {  /* smb2的子协议mswsp中出现的畸形报文信息 */
        return TRUE;
    }
    if (strcmp(dst, "tcp.segments") == 0) {
        return TRUE;
    }
    if (strcmp(dst, "urlencoded-form") == 0) {
        return TRUE;
    }

    return FALSE;
}
/**
 *
 */
gboolean cursionkeyStrFilter(const char *key_str){
    if (strcmp(key_str, "text") == 0) {
        return TRUE;
    }
    return false;
}
/**
 * 匹配返回下标，为找到返回-1
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
 * 最终的数据流写入对应协议文件
 * @param stream
 * @param protocol
 * @return
 */
gboolean write_Files(std::string &stream, std::string &protocol) {

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

    if (pFile_map.size() == 0) {
        /*当前是空map*/
        if (access(fileDirPath_t, 0) != 0) {
            /*当前文件夹不存在*/
            mkdirs(fileDirPath_t);
        }

        FILE *fp = fopen(filepath_t, "a+");
        if (fp == NULL) {
            g_print("open filepath error!\n");
            return false;
        }
        pFile_map.insert(std::pair<std::string, FILE *>(protocol, fp));
        fputs(stream.c_str(), fp);
        fflush(fp);
    } else {
        std::map<std::string, FILE *>::iterator it;
        it = pFile_map.find(protocol);
        if (it != pFile_map.end()) {
            fputs(stream.c_str(), it->second);
            fflush(it->second);
        } else {
//            没有找到对应的文件句柄,接下来新增一个句柄.
            if (access(fileDirPath_t, 0) != 0) {
                /**
                 * 当前协议对应文件夹不存在
                 */
                mkdirs(fileDirPath_t);
            }
            FILE *fp = fopen(filepath_t, "a+");
            if (fp == NULL) {
                g_print("open filepath error!\n");
                return false;
            }
            pFile_map.insert(std::pair<std::string, FILE *>(protocol, fp));
            fputs(stream.c_str(), fp);
            fflush(fp);
        }
    }
    return true;
}
/**
 * 给fp写入rtp可播放流的头部
 * @param fp
 */
void writeRTPstreamHead(FILE* fp){
    uint8_t pd[5] = {0};
    phton32(pd,0x2e736e64);
    if(fwrite((const char*)pd, sizeof(uint8_t),4,fp) != 4){
        g_print("%s error",__FUNCTION__);
    }
    phton32(pd,24);
    if(fwrite((const char*)pd, sizeof(uint8_t),4,fp) != 4){
        g_print("%s error",__FUNCTION__);
    }
    phton32(pd,0xffffffff);
    if(fwrite((const char*)pd, sizeof(uint8_t),4,fp) != 4){
        g_print("%s error",__FUNCTION__);
    }
    phton32(pd,3);
    if(fwrite((const char*)pd, sizeof(uint8_t),4,fp) != 4){
        g_print("%s error",__FUNCTION__);
    }
    phton32(pd,8000);
    if(fwrite((const char*)pd, sizeof(uint8_t),4,fp) != 4){
        g_print("%s error",__FUNCTION__);
    }
    //默认不同步的正向音频 或不同步的反转音频
    phton32(pd,1);
    if(fwrite((const char*)pd, sizeof(uint8_t),4,fp) != 4){
        g_print("%s error",__FUNCTION__);
    }
    fflush(fp);
}
/**
 * 将会话统计信息写入文件中
 * @param stream
 * @param protocol
 * @return
 */
gboolean write_Files_conv(std::string &stream) {

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

size_t noop_cb(void *ptr, size_t size, size_t nmemb, void *data) {
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
 * 将数据流steam写入文件，protocol协议
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
                if (!write_Files(index_t->contents, protocol)) {
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
            insertManyProtocolStream *temp = new insertManyProtocolStream;
            temp->protocol = protocol;
            temp->contents.append(stream);
            temp->times = 1;
            temp->next = insertmanystream_Head->next;
            temp->pre = insertmanystream_Head;
            insertmanystream_Head->next = temp;
            temp->next->pre = temp;
        }
    } else {
        if (!write_Files(stream, protocol)) {
            g_print("%s insert error !\n", protocol.c_str());
        }
    }

    stream = "";
    return true;
}

/**
 * 所有参数初始化
 * @return
 */
gboolean initial_All_para() {
    TRY {
                write_in_files_proto = "";

                /*初始化部分要用到的 json对象 ----begin*/
                cJSON_Delete(write_in_files_cJson);
                cJSON_Delete(pro_cJson);
                write_in_files_cJson = cJSON_CreateObject();
                pro_cJson = cJSON_CreateObject();
                /*初始化部分要用到的 json对象 ----end*/

                /*需要初始化strname链表*/
                initStrNameLevelLinkList(strname_head);
                strname_head = new struct strNameSameLevel;
                strname_head->next = NULL;
                strname_head->times = 0;
                strname_head->str_name = "";
                return true;

                packetProtoAlready = false;

            }
            CATCH(OutOfMemoryError) {
                g_print("initialize error");
                return false;
            }
    ENDTRY;
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
        gchar value[4542] = {'\0'};

        if (node->finfo->length != 0 and node->finfo->length < 1514 ) {
            try {
                yy_proto_item_fill_label(node->finfo, value);
                while (key_str.find(".") != key_str.npos) {  /* 返回string::npos表示未查找到匹配项 */
                    key_str.replace(key_str.find("."), 1, "_");
                }
                key_str = gotStrNameByStrName(key_str);
                cJSON_AddStringToObject(json_t, key_str.c_str(), value);
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

        if (PACKET_PROTOCOL_FLAG && packetProtoAlready) {
            //rtp content relative
            g_assert(cookie !=nullptr);
            GList *it = nullptr;
            if ((it = g_list_find_custom(rtp_fields, (gpointer)key_str.c_str(),(GCompareFunc)strcmp))) {
                if(strcmp((char*)it->data,"rtp_marker") == 0){
                    cookie->rtp_content->marker = std::stoi(value);
                }else if(strcmp((char*)it->data,"rtp_ssrc") == 0){
                    strcpy(cookie->rtp_content->ssrc,value);
                } else if(strcmp((char*)it->data,"rtp_payload") == 0){
                    strcpy((char*)cookie->rtp_content->payload,(char*)node->finfo->value.value.bytes->data);
                    cookie->rtp_content->payload_len = node->finfo->value.value.bytes->len;
                } else if(strcmp((char*)it->data,"rtp_p_type") == 0){
                    cookie->rtp_content->payload_type = std::stoi(value);
                }
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
#define GET_FILENAME_FROM_PATH(_ptr_, _filename_) do {  \
	_ptr_ = strrchr(_filename_, '/');  \
	if (_ptr_ == NULL)  _ptr_ = _filename_;  \
	else  _ptr_++;  \
} while (0)

void match_line_no(char *pattern, char *source_str, char * target) {
    try{
        std::regex reg(pattern);  //, std::regex_constants::extended
        //std::string s = source_str;
//        char * ret;
        std::cmatch results;

        /* get filename from path */
        const char *_ptr_ = nullptr;
        GET_FILENAME_FROM_PATH(_ptr_, source_str);
        bool match_bool = std::regex_search(_ptr_, results, reg);

        // g_print("%d", match_bool);
        if(match_bool){
            strcpy(target, results.str().c_str());
        } else{
            strcpy(target, "unknown");
        }
    }
    catch (std::runtime_error){
        g_print("regex grammar format error !");
        strcpy(target, "unknown");
    }
}
/**
 * 直接解析edt 写入文件缓存中 202107290910
 * @param edt
 * @return
 */
gboolean dissect_edt_into_files(epan_dissect_t *edt) {
    g_assert(edt != NULL);
    if (edt->tree == NULL)
        return false;
    proto_node *node = edt->tree->first_child;
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
    if (kmp("[tcp],[udp],[data]", "[" + write_in_files_proto + "]") != -1) {
        return true;
    }

    /*debug test*/
//    if(write_in_files_proto.compare("ftp.current-working-directory") == 0 ){
//        int a=0;
//    }

    if(PACKET_PROTOCOL_FLAG){
        /*判断当前协议是否需要组包*/
        if(g_list_find_custom(rtp_fields,write_in_files_proto.c_str(),(GCompareFunc)strcmp)){
            packetProtoAlready = true;
        }
    }
    /*获取文件来源*/
    if (read_Pcap_From_File_Flag == 1) {
        if (file_Name_From_Dir_Flag) {
            /*当前读取文件夹来*/
            cJSON_AddStringToObject(write_in_files_cJson, str_FILES_RESOURCE, FILE_NAME_T);
            cJSON_AddStringToObject(write_in_files_cJson, "line_no", OFFLINE_LINE_LINE_NO);  /* 离线接入数据的线路号 */
        } else {
            /* 单个文件 */
            cJSON_AddStringToObject(write_in_files_cJson, str_FILES_RESOURCE, READ_FILE_PATH);
            cJSON_AddStringToObject(write_in_files_cJson, "line_no", OFFLINE_LINE_LINE_NO);  /* 离线接入数据的线路号 */
        }
    } else {
        cJSON_AddStringToObject(write_in_files_cJson, str_FILES_RESOURCE, "online");
        cJSON_AddStringToObject(write_in_files_cJson, "line_no", ONLINE_LINE_NO);  // 在线实时接入数据的线路号
    }
    /*协议栈*/
    cJSON_AddStringToObject(write_in_files_cJson, "protocols", protocol_stack_t.c_str());

    while (node != NULL) {
        field_info *fi = node->finfo;

        /*帧头*/
        if (strcmp(fi->hfinfo->abbrev, "frame") == 0) {
            proto_node *child = node->first_child; //该层协议的第一个字段
            while (child != NULL) {
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
                    child = child->next;
                    continue;
                }
                child = child->next;
            }
            node = node->next;
            continue;
        }
        /*eth*/
        if (strcmp(fi->hfinfo->abbrev, "eth") == 0) {
            proto_node *child = node->first_child;
            while (child != NULL) {
                field_info *child_finfo = child->finfo;
                if (strcmp(child_finfo->hfinfo->abbrev, "eth.dst") == 0) {
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo, value);
                    cJSON_AddStringToObject(write_in_files_cJson, "eth_dst", value);
                    child = child->next;
                    continue;
                }
                if (strcmp(child_finfo->hfinfo->abbrev, "eth.src") == 0) {
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo, value);
                    cJSON_AddStringToObject(write_in_files_cJson, "eth_src", value);
                    child = child->next;
                    continue;
                }
                child = child->next;
            }
            node = node->next;
            continue;
        }
        /*ip ipv6 */
        if (strcmp(fi->hfinfo->abbrev, "ip") == 0 or strcmp(fi->hfinfo->abbrev, "ipv6") == 0) {
            proto_node *child = node->first_child;
            while (child != NULL) {
                field_info *child_finfo = child->finfo;
                if (strcmp(child_finfo->hfinfo->abbrev, "ip.src") == 0 or
                    strcmp(child_finfo->hfinfo->abbrev, "ipv6.src") == 0) {
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo, value);
                    cJSON_AddStringToObject(write_in_files_cJson, "src_ip", value);
                    child = child->next;
                    continue;
                }
                if (strcmp(child_finfo->hfinfo->abbrev, "ip.dst") == 0 or
                    strcmp(child_finfo->hfinfo->abbrev, "ipv6.dst") == 0) {
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo, value);
                    cJSON_AddStringToObject(write_in_files_cJson, "dst_ip", value);
                    child = child->next;
                    continue;
                }
                child = child->next;
            }
            node = node->next;
            continue;
        }
        /*tcp udp*/
        if (strcmp(fi->hfinfo->abbrev, "tcp") == 0 or strcmp(fi->hfinfo->abbrev, "udp") == 0) {
            proto_node *child = node->first_child;
            while (child != NULL) {
                field_info *child_finfo = child->finfo;
                if (strcmp(child_finfo->hfinfo->abbrev, "tcp.srcport") == 0 or
                    strcmp(child_finfo->hfinfo->abbrev, "udp.srcport") == 0) {
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo, value);
                    cJSON_AddStringToObject(write_in_files_cJson, "src_port", value);
                    child = child->next;
                    continue;
                }
                if (strcmp(child_finfo->hfinfo->abbrev, "tcp.dstport") == 0 or
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
        /*最后层协议的解析*/
        if (strcmp(fi->hfinfo->abbrev, write_in_files_proto.c_str()) == 0) {
            proto_node *child = node->first_child;
            if (child != NULL) {
                try {
                    int cursion_layer = 0;
                    /*传入递归的参数*/
                    if(PACKET_PROTOCOL_FLAG && packetProtoAlready){
                        struct totalParam *cookie_t = g_new0(totalParam,1);
                        cookie_t->rtp_content = g_new0(rtp_Content,1);
                        dissect_edt_Tree_Into_Json(write_in_files_cJson, child, cursion_layer,cookie_t);
                        g_thread_pool_push(handleStreamTpool,(gpointer)cookie_t, nullptr);
                    } else{
                        dissect_edt_Tree_Into_Json(write_in_files_cJson, child,cursion_layer,NULL);
                    }
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
 * 写会话
 * @param label_str 字段
 * @param level 层级
 */
void do_write_in_conversation_handler(gchar *key, gchar *value) {
    std::string key_str = key;
    std::string value_str = value;
    if (value_str.compare("-1END") == 0) {
        /*获取文件来源，将conversation与源文件进行关联*/
        if (read_Pcap_From_File_Flag == 1) {
            if (file_Name_From_Dir_Flag) {
                /*当前读取文件夹来*/
                cJSON_AddStringToObject(write_in_files_conv_cJson, str_FILES_RESOURCE, FILE_NAME_T);
                cJSON_AddStringToObject(write_in_files_conv_cJson, "line_no", OFFLINE_LINE_LINE_NO); /* 离线接入数据的线路号 */
            } else {
                cJSON_AddStringToObject(write_in_files_conv_cJson, str_FILES_RESOURCE, READ_FILE_PATH);
                cJSON_AddStringToObject(write_in_files_conv_cJson, "line_no", OFFLINE_LINE_LINE_NO);  /* 离线接入数据的线路号 */
            }
        } else {
            cJSON_AddStringToObject(write_in_files_conv_cJson, str_FILES_RESOURCE, "online");
            cJSON_AddStringToObject(write_in_files_conv_cJson, "line_no", ONLINE_LINE_NO);  // 在线实时接入数据的线路号
        }

        /*当前流统计结束*/
        if (write_in_files_conv_cJson->child == NULL)
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
 * decode rtp streams into pd_out
 * @param payload_type_names
 * @param payload_data
 * @param payload_len
 * @param pd_out
 * @param decoders_hash
 * @return
 */
size_t convert_payload_to_samples(unsigned int payload_type,guint8* payload_data,size_t payload_len,uint8_t *pd_out,struct _GHashTable *decoders_hash){
    unsigned int channels = 0;
    unsigned int sample_rate = 0;
    size_t decode_bytes;
    SAMPLE *decode_buff = nullptr;
    size_t decoded_samples;
    const gchar *payload_type_str = nullptr;
    payload_type_str = rtp_payload_type_to_str[payload_type];
    decode_bytes = decode_rtp_packet_payload(payload_type,payload_type_str,payload_data,payload_len,&decode_buff,decoders_hash,&channels,&sample_rate);
    decoded_samples = decode_bytes/2;

    if(decoded_samples > 0){
        if(sample_rate == 8000){
            /* Change byte order to network order */
            for (size_t i= 0; i < decoded_samples; i++) {
                SAMPLE sample;
                uint8_t pd[4];

                sample = decode_buff[i];
                phton16(pd, sample);
                pd_out[2*i] = pd[0];
                pd_out[2*i+1] = pd[1];
            }
        } else{
            g_print("File parsing and saving at this rate is not supported \n%s\n",__FUNCTION__);
            decoded_samples = 0;
        }
    } else{
        g_print("File parsing and saving at this rate is not supported \n%s\n",__FUNCTION__);
        decoded_samples = 0;
    }
    g_free(decode_buff);

    return decoded_samples;
}

/**
 * 并发处理rtp流
 * @param str
 * @param data
 */
void do_handle_strem(gpointer str,gpointer data){
    totalParam *t = (totalParam *) str;
    if(t->rtp_content != nullptr){
        /*存在rtpstream*/
        char file_name_t[256] = {0};
        strcat(file_name_t,PACKET_PROTOCOL_PATH);
        sprintf(file_name_t,"%s%s",PACKET_PROTOCOL_PATH,"rtp/");
        if(access(file_name_t,0)!= 0){
            mkdirs(file_name_t);
        }
        strcat(file_name_t,global_time_str.c_str());
        strcat(file_name_t,t->rtp_content->ssrc);
        strcat(file_name_t,".au");

        FILE* fp;
        if(rtp_stream_pFile_map.size() == 0){
            //空map
            fp = fopen(file_name_t,"a");
            if(!fp){
                g_print("%s open error",file_name_t);
                return;
            }
            writeRTPstreamHead(fp);
            char ssrc_t[24]= {0};
            strcpy(ssrc_t,t->rtp_content->ssrc);
            rtp_stream_pFile_map.insert(std::pair<std::string,FILE*>(ssrc_t,fp));
        } else {
            auto index = rtp_stream_pFile_map.find(t->rtp_content->ssrc);
            if(index != rtp_stream_pFile_map.end()){
                fp = index->second;
            } else{
                fp = fopen(file_name_t,"a");
                if(!fp){
                    g_print("%s open error",file_name_t);
                    return;
                }
                writeRTPstreamHead(fp);
                char ssrc_t[24]= {0};
                strcpy(ssrc_t,t->rtp_content->ssrc);
                rtp_stream_pFile_map.insert(std::pair<std::string,FILE*>(ssrc_t,fp));
            }
        }
        g_assert(fp != nullptr);
        struct _GHashTable *decoders_hash = rtp_decoder_hash_table_new();
        uint8_t pd_out[2*4000];
        size_t sample_count;
        //payload_type_name 暂定
        sample_count = convert_payload_to_samples(t->rtp_content->payload_type,t->rtp_content->payload,t->rtp_content->payload_len,pd_out,decoders_hash);
        if(fwrite(pd_out, sizeof(uint8_t),sample_count,fp) != sample_count){
            g_print("%s sample_count write error !\n",__FUNCTION__);
        }

        g_free(t->rtp_content);
    }
    g_free(t);
}

/**
 * 初始化拿json的map数据，正常取值返回1，否则返回0，flag为0表示没有初始化，为1表示已初始化。
 * @param flag
 * @return
 */
gboolean initWriteJsonFiles(char *flag) {

//    这里把同级的level的strname初始化
    strname_head = new struct strNameSameLevel;
    strname_head->next = NULL;
    strname_head->str_name = "";
    strname_head->times = 0;

    /*批量插入初始化头部节点*/
    if (INSERT_MANY_PROTOCOL_STREAM_FLAG == 1) {
        insertmanystream_Head = new struct insertManyProtocolStream;
        insertmanystream_Head->next = insertmanystream_Head;
        insertmanystream_Head->pre = insertmanystream_Head;
        insertmanystream_Head->times = 0;
        insertmanystream_Head->protocol = "";
        insertmanystream_Head->contents = "";
    }

    /*初始化rtpstream处理函数线程池*/
    handleStreamTpool = g_thread_pool_new(do_handle_strem,NULL,1,FALSE,NULL);
    rtp_fields = g_list_append(rtp_fields, (gpointer) "rtp");
    rtp_fields = g_list_append(rtp_fields, (gpointer) "rtp_marker");
    rtp_fields = g_list_append(rtp_fields, (gpointer) "rtp_ssrc");
    rtp_fields = g_list_append(rtp_fields, (gpointer) "rtp_payload");
    rtp_fields = g_list_append(rtp_fields, (gpointer) "rtp_p_type");

    /*初始化互斥变量*/
    *flag = 1;
    return true;
}

/**
 * 获取读取configfiles的状态.
 * @return
 */
gboolean readConfigFilesStatus() {
    TRY {
                std::string temp_str_json_path;
                std::string temp_str_export_path;
                char *write_in_files_config;
                char *write_in_conversations_flag;
                char *packet_protocol_flag;
                char *packet_protocol_types;
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

                /**
                 * 这里需要把当前运行的时间戳定下来
                 */
                std::time_t global_time = std::time(0);
                global_time_str = numtos((u_long) global_time);
                g_print("current files time %s \n", global_time_str.c_str());

                char **fileData = NULL;
                int lines = 0;
                struct ConfigInfo *info = NULL;

                if (loadFile_ConfigFile(CONFIG_FILES_PATH, &fileData, &lines)) {
                    parseFile_ConfigFile(fileData, lines, &info);
                } else {
                    return false;
                }

                write_in_es_flag = getInfo_ConfigFile("WRITE_IN_ES_FLAG", info, lines);
                if (write_in_es_flag != NULL) {
                    WRITE_IN_ES_FLAG = *write_in_es_flag - '0';
                } else WRITE_IN_ES_FLAG = 0;

                es_url = getInfo_ConfigFile("ES_URL", info, lines);
                if (es_url != NULL) {
                    strcpy(ES_URL, es_url);
                    int len = strlen(ES_URL);
                    if (ES_URL[len - 1] != '/') {
                        strcat(ES_URL, "/");
                    }
                }

                packet_protocol_types = getInfo_ConfigFile("PACKET_PROTOCOL_TYPES", info, lines);
                if (packet_protocol_types != NULL) {
                    strcpy(PACKET_PROTOCOL_TYPES, packet_protocol_types);
                } else {
                    strcpy(PACKET_PROTOCOL_TYPES, "./");
                }

                registration_file_path = getInfo_ConfigFile("REGISTRATION_FILE_PATH", info, lines);
                if (registration_file_path != NULL) {
                    strcpy(REGISTRATION_FILE_PATH, registration_file_path);
                    int len = strlen(REGISTRATION_FILE_PATH);
                    if (REGISTRATION_FILE_PATH[len - 1] != '/') {
                        strcat(REGISTRATION_FILE_PATH, "/");
                    }
                } else {
                    strcpy(REGISTRATION_FILE_PATH, "./");
                }


                packet_protocol_flag = getInfo_ConfigFile("PACKET_PROTOCOL_FLAG", info, lines);
                if (packet_protocol_flag != NULL) {
                    PACKET_PROTOCOL_FLAG = *packet_protocol_flag - '0';
                } else PACKET_PROTOCOL_FLAG = 0;

                insert_many_protocol_stream_flag = getInfo_ConfigFile("INSERT_MANY_PROTOCOL_STREAM_FLAG", info, lines);
                if (insert_many_protocol_stream_flag != NULL) {
                    INSERT_MANY_PROTOCOL_STREAM_FLAG = *insert_many_protocol_stream_flag - '0';
                } else INSERT_MANY_PROTOCOL_STREAM_FLAG = 0;

                insert_many_protocol_stream_num = getInfo_ConfigFile("INSERT_MANY_PROTOCOL_STREAM_NUM", info, lines);
                if (insert_many_protocol_stream_num != NULL) {
                    INSERT_MANY_PROTOCOL_STREAM_NUM = std::stoi(insert_many_protocol_stream_num);
                } else INSERT_MANY_PROTOCOL_STREAM_NUM = 1000;

                edit_files_sizes = getInfo_ConfigFile("EDIT_FILES_SIZES", info, lines);
                if (edit_files_sizes != NULL) {
                    EDIT_FILES_SIZES = std::stoi(edit_files_sizes);
                } else EDIT_FILES_SIZES = 1000;

                edit_files_dissect_flag = getInfo_ConfigFile("EDIT_FILES_DISSECT_FLAG", info, lines);
                if (edit_files_dissect_flag != NULL) {
                    EDIT_FILES_DISSECT_FLAG = *edit_files_dissect_flag - '0';
                } else EDIT_FILES_DISSECT_FLAG = 0;

                write_in_files_config = getInfo_ConfigFile("WRITE_IN_FILES_CONFIG", info, lines);
                if (write_in_files_config != NULL) {
                    WRITE_IN_FILES_CONFIG = *write_in_files_config - '0';
                } else WRITE_IN_FILES_CONFIG = 0;

                write_in_conversations_flag = getInfo_ConfigFile("WRITE_IN_CONVERSATIONS_FLAG", info, lines);
                if (write_in_conversations_flag != NULL) {
                    WRITE_IN_CONVERSATIONS_FLAG = *write_in_conversations_flag - '0';
                } else {
                    WRITE_IN_CONVERSATIONS_FLAG = 0;
                }

                export_path = getInfo_ConfigFile("EXPORT_PATH", info, lines);
                if (export_path != NULL) {
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
                if (display_packet_info_flag != NULL) {
                    DISPLAY_PACKET_INFO_FLAG = *display_packet_info_flag - '0';
                } else {
                    DISPLAY_PACKET_INFO_FLAG = 0;
                }

                online_capture_data_flag = getInfo_ConfigFile("ONLINE_CAPTURE_DATA_FLAG", info, lines);
                if (online_capture_data_flag != NULL) {
                    ONLINE_CAPTURE_DATA_FLAG = *online_capture_data_flag - '0';
                } else {
                    ONLINE_CAPTURE_DATA_FLAG = 0;
                }

                online_capture_data_device_name = getInfo_ConfigFile("ONLINE_CAPTURE_DATA_DEVICE_NAME", info, lines);
                if (online_capture_data_device_name != NULL) {
                    strcpy(ONLINE_CAPTURE_DATA_DEVICE_NAME, online_capture_data_device_name);
                } else {
                    strcpy(ONLINE_CAPTURE_DATA_DEVICE_NAME, "./");
                }

                read_packet_from_files_flag = getInfo_ConfigFile("READ_PACKET_FROM_FILES_FLAG", info, lines);
                if (read_packet_from_files_flag != NULL) {
                    READ_PACKET_FROM_FILES_FLAG = *read_packet_from_files_flag - '0';
                } else {
                    READ_PACKET_FROM_FILES_FLAG = 0;
                }

                read_packet_from_files_path = getInfo_ConfigFile("READ_PACKET_FROM_FILES_PATH", info, lines);
                if (read_packet_from_files_path != NULL) {
                    strcpy(READ_PACKET_FROM_FILES_PATH, read_packet_from_files_path);
                    struct stat st;
                    stat(READ_PACKET_FROM_FILES_PATH, &st);
                    if (S_ISDIR(st.st_mode)) {
                        int len = strlen(READ_PACKET_FROM_FILES_PATH);
                        if (READ_PACKET_FROM_FILES_PATH[len - 1] != '/') {
                            strcat(READ_PACKET_FROM_FILES_PATH, "/");
                        }
                        file_Name_From_Dir_Flag = 1;
                    }
                } else {
                    strcpy(READ_PACKET_FROM_FILES_PATH, "./");
                }

                json_add_proto = getInfo_ConfigFile("JSON_ADD_PROTO", info, lines);
                if (json_add_proto != NULL) {
                    JSON_ADD_PROTO = *json_add_proto - '0';
                } else {
                    JSON_ADD_PROTO = 0;
                }

                json_add_proto_path = getInfo_ConfigFile("JSON_ADD_PROTO_PATH", info, lines);
                if (json_add_proto_path != NULL) {
                    strcpy(JSON_ADD_PROTO_PATH, json_add_proto_path);
                } else {
                    strcpy(JSON_ADD_PROTO_PATH, "./defaul.json");
                }

                online_line_no = getInfo_ConfigFile("ONLINE_LINE_NO", info, lines);
                if (online_line_no != NULL) {
                    strcpy(ONLINE_LINE_NO, online_line_no);  /* TODO: 适配首部有空格的情况 */
                } else {
                    strcpy(ONLINE_LINE_NO, "");
                }

                offline_line_no_regex = getInfo_ConfigFile("OFFLINE_LINE_NO_REGEX", info, lines);
                if (offline_line_no_regex != NULL) {
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

void clean_Temp_Files_All() {
    if (!mutex_final_clean_flag) {
        if (insertmanystream_Head != NULL and insertmanystream_Head->next != insertmanystream_Head) {
            /*批量插入缓存还有内容*/
            insertManyProtocolStream *index_t = insertmanystream_Head->next;
            while (index_t != insertmanystream_Head) {
                write_Files(index_t->contents, index_t->protocol);
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
            std::string oldName_t = EXPORT_PATH + index.first + "/" + index.first + "_" + global_time_str + ".writting";
            std::string newName_t = EXPORT_PATH + index.first + "/" + index.first + "_" + global_time_str + ".txt";
            rename(oldName_t.c_str(), newName_t.c_str());
        }
        pFile_map.clear();

        /*最终初始化互斥变量*/
        mutex_final_clean_flag = 1;
    }
}

void add_record_in_result_file() {
    if (fp_result_timestampe == NULL) {
        std::string filepath_str = RESULT_PATH;
        filepath_str += "result-" + global_time_str + ".writting";
        FILE *fp_result_timestampe = fopen(filepath_str.c_str(), "a+");
        if (file_Name_From_Dir_Flag) {
            fputs(FILE_NAME_T, fp_result_timestampe);
            fputs("\r\n", fp_result_timestampe);
            fflush(fp_result_timestampe);
        } else {
            fputs(READ_FILE_PATH, fp_result_timestampe);
            fputs("\r\n", fp_result_timestampe);
            fflush(fp_result_timestampe);
        }
    } else {
        if (file_Name_From_Dir_Flag) {
            fputs(FILE_NAME_T, fp_result_timestampe);
            fputs("\r\n", fp_result_timestampe);
            fflush(fp_result_timestampe);
        } else {
            fputs(READ_FILE_PATH, fp_result_timestampe);
            fputs("\r\n", fp_result_timestampe);
            fflush(fp_result_timestampe);
        }
    }
}

void change_result_file_name() {
    std::string filepath_str = RESULT_PATH;
    std::string oldName_t = filepath_str + "result-" + global_time_str + ".writting";
    std::string newName_t = filepath_str + "result-" + global_time_str + ".txt";
    rename(oldName_t.c_str(), newName_t.c_str());

    std::time_t end_time = std::time(0);
    g_print("结束时间戳：%s \n", numtos((u_long) end_time).c_str());
    int begin_time = atoi(global_time_str.c_str());
    int cost_time = (int) end_time - begin_time;
    g_print("总计耗时：%d 秒\n", cost_time);

    curl_global_cleanup();  //在结束libcurl使用的时候，用来对curl_global_init做的工作清理。类似于close的函数
}
