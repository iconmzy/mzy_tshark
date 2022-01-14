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
#include <sys/time.h>
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
#include <stdlib.h>
#include <fcntl.h>
#include <mutex>
#include "curl/curl.h"
#include "decode_zhr.h"
#include <epan/export_object.h>



#define __U__ __attribute__((unused))

/*即将写进文件的协议*/
static std::string write_in_files_proto;
/*内容缓存*/
static std::string write_in_files_stream;

/*export溯源内容缓存*/
static std::string write_ex_origin_stream;

static cJSON *write_in_files_cJson = cJSON_CreateObject();

static cJSON *write_export_origin_cJson = cJSON_CreateObject();
static cJSON *pro_cJson = cJSON_CreateObject();
/*缓存会话数据内容*/
static cJSON *write_in_files_conv_cJson = cJSON_CreateObject();
static std::string conv_path_t;

std::list<std::string> special_not_leafNode = {
        "isis_lsp_ip_reachability_ipv4_prefix"
};

typedef struct {
    const char * field_name;
    bool (*special_field_cb)(proto_node *node, char* ret);
} special_field_value;

static bool need_special_field(const char* ,proto_node *, char*);
static bool get_isis_lsp_ip_reachability_ipv4_prefix_mask(proto_node *, char*);
static special_field_value regist_speical_filed[] = {
        {"isis_lsp_ip_reachability_ipv4_prefix", &get_isis_lsp_ip_reachability_ipv4_prefix_mask}
};


static FILE *conversation_Handle_File = nullptr;
std::queue< proto_node* > que; //全局node节点队列
#define VALUE_240_LENGTH 256
gchar* value_240 = nullptr; //240长度是一个协议名最大长度

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
cJSON *regex_dict = nullptr;
std::map<std::string,std::string> regex_dict_map;

//写入ES数据库相关配置
gboolean WRITE_IN_ES_FLAG = 0;  /* 配置是否写入ElasticSearch数据库 */
char ES_URL[256] = {0};  /* ElasticSearch地址 */

gboolean WRITE_IN_KAFKA_CONFIG = 0;
kafka_params kafkaParams_ymq = {{0}, {0},{0},0, KAFKA_NO_RUN};
rd_kafka_t *rk = nullptr;  //producer
rd_kafka_t *rk_con = nullptr; //consumer

static std::string global_time_str;  // long int types
FILE *fp_result_timestampe = nullptr;

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

typedef struct diy_proto_stack{
    std::string pre_potocol;
    std::string next_protocol;
}diy_proto_stack;
std::vector<struct diy_proto_stack> all_diy_protol;



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
std::list<std::string> lastLayerProtocolFilterList = { //最后层协议名称过滤
        "communityid","ftp.current-working-directory","xml","json","_ws.malformed","smb2.fsctl.wait.name", "mswsp.msg"\
        ,"tcp.segments","urlencoded-form","data-text-lines","media","_ws.short","_ws.unreassembled","_ws.short","_ws.unreassembled"\
        ,"ftp-data.current-working-directory","dof.dpp.v2s","dof.oap","wlan.mgt","image-gif","image","ftp-data.command-frame","dcerpc.cn_deseg_req"\
        ,"dcerpc.stub_data","db-lsp-disc","dcerpc.encrypted_stub_data","dcerpc.fragments","snmp.var-bind_str"
};
std::list<std::string> protoKeyFilterList = {"text","useless"}; //协议KEY过滤

//stream handle----------------------------begin 20210909 yy ----------------------------stream handle begin ||||
class gunit8Array
{
public:
    explicit gunit8Array(int s = 0):m_size(s) //构造函数
    {
        if(s == 0)
            m_ptr = nullptr;
        else
            m_ptr = new guint8[s];
    }
    gunit8Array(const gunit8Array &a) //复制构造函数 深拷贝，并非赋指针
    {
        if(a.m_ptr == nullptr)
        {
            m_ptr = nullptr;
            m_size = 0;
        }
        else
        {
            m_ptr = new guint8[a.m_size];
            memcpy(m_ptr, a.m_ptr, sizeof(guint8)*a.m_size); // 拷贝原数组内容
            m_size = a.m_size;
        }
    }
    ~gunit8Array() {
        delete []m_ptr;
    }
    gunit8Array & operator=(const gunit8Array & a)
    {
        if(m_ptr == a.m_ptr)
            return *this;
        if(a.m_ptr == nullptr) {
            delete [] m_ptr;
            m_ptr = nullptr;
            m_size = 0;
            return *this;
        }
        if(m_size < a.m_size)
        {
            delete [] m_ptr;
            m_ptr = new guint8[a.m_size];
        }
        memcpy(m_ptr, a.m_ptr, sizeof(int)*a.m_size); // 拷贝原数组内容
        m_size = a.m_size;
        return *this;
    }
    guint8 & operator[](int i)
    {
        return m_ptr[i];
    }
    void push_back(guint8 *v,int len)
    {
        if(m_ptr) // 如果数组不为空
        {
            auto *tmpPtr = new guint8[m_size + len]; // 重新分配空间
            memcpy(tmpPtr, m_ptr, sizeof(guint8)*m_size); // 拷贝原数组内容
            delete [] m_ptr;
            m_ptr = tmpPtr;
        }
        else
        {
            m_ptr = new guint8[len];
        }
        memcpy(m_ptr+m_size,v,len);
        m_size +=len;
    }
    void push_back(const guint8 &v)
    {
        if(m_ptr) // 如果数组不为空
        {
            auto *tmpPtr = new guint8[m_size + 1]; // 重新分配空间
            memcpy(tmpPtr, m_ptr, sizeof(int)*m_size); // 拷贝原数组内容
            delete [] m_ptr;
            m_ptr = tmpPtr;
        }
        else // 如果数组本来就是空的
        {
            m_ptr = new guint8[1];
        }
        m_ptr[m_size++] = v; //加入新的数组元素
    }
    int length() const {
        return m_size;
    }
    int get_len() const {
        return m_size;
    }
    guint8* get_data(){
        return m_ptr;
    }
    void clear(){
        delete []m_ptr;
        m_ptr = nullptr;
        m_size = 0;
    }
private:
    int  m_size; // 数组元素的个数
    guint8* m_ptr;  // 指向动态分配的数组
};

//h263 stream---------------------- 20210909 yy -----------------------------------begin h263|||
struct comFiveEleContent{ //通信五元组内容及其他信息
    std::string sip;
    std::string dip;
    std::string sport;
    std::string dport;
    std::string protocol;//协议 如rtp
    std::string protocol_suffix;//子协议，如g722,g711
	unsigned int frame_time; // 时间戳整数形式
    unsigned int protocol_suffix_type{}; //子协议号,[0-127]
    int status{};
};
std::vector<struct comFiveEleContent> final_Follow_Write_Need; //存放所有最后需要输出流的通信五元组及其他信息,

//--------------------- 20211228 conversation协议栈缓存五元组 ---------------------------------//
typedef struct comSevenStackContent{ //会话匹配提取文件七元组内容及其他信息
    std::string sip;
    std::string dip;
    std::string sport;
    std::string dport;
    std::string protocol_stack;//协议栈
    std::string line_no;   //文件名
    std::string read_file_path;  //路径
}comSevenStackContent;
std::vector<struct comSevenStackContent> final_conversation_Write_Need; //存放所有包含源目ip/端口的协议栈，供最后组会话筛选//

typedef struct final_Follow_File_Rel{
    std::string streamFileName_t; //缓存followstream文件名，协议+四元组
    FILE *streamFileName_fp = nullptr;  //缓存followstream文件句柄，协议+四元组。
    std::string protocol_suffix;//子协议，如rtp协议承载的g722,g711
    guint8 protocol_suffix_type{}; //对应protocol_suffix 的type number;
    gboolean cache_Flag{}; //是否存放缓存的标志
    std::vector<guchar> content; //存放内容。
    int content_len{};  //内容长度
}*pfinal_Follow_File_Rel;
pfinal_Follow_File_Rel pfinal_follow = nullptr; //存放最后统计流的文件及内容信息

//h263 stream---------------------- 20210909 yy -----------------------------------end h263|||
//rtp stream---------------------- 20210909 yy ----------------------rtp stream begin |||

#define MIN_AUDIO_SIZE 4096  //4kb
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
std::map<std::uint8_t,std::string> rtp_payload_type_To_tail{{0,"au"},{2,"au"},{4,"au"},{8,"au"},{9,"au"},{18,"au"}};//,{32,"mpeg"} key 是rtp_payload_type_to_str的下标，value是该格式对应的输出文件名。
std::array<unsigned int,3> rtp_Head_au_8000_Rate_surport_List{0,2,18};//写8000采样率头部au文件，支持类型列表
typedef struct _rtpTotalBufferContent{ //
    std::string sip;
    std::string dip;
    std::string sport;
    std::string dport;
    std::string ssrc;
    std::string rtpPayloadType;
    unsigned int time_begin{};
    unsigned int time_end{};
    unsigned int last_record_time{0};
    FILE *fp{};
    std::string fp_path{};
    gunit8Array data{};
}rtpTotalBufferContent;

std::map<std::string ,rtpTotalBufferContent> rtpTotalBuffer;
typedef struct _rtpMatchingInfo{
    std::string sip;
    std::string dip;
    std::string sport;
    std::string dport;
    std::string rtpPayloadType;
    unsigned int time_begin{};
    unsigned int time_end{};
    unsigned int last_record_time{0};
    std::string fp_path{};
}rtpMatchingInfo;
std::vector<rtpMatchingInfo> rtpMachingVec{};
std::mutex rtp_mtx;
struct rtpFileRel{ //RTP文件及解码器相关
    FILE * fp;
    struct _GHashTable *decoders_hash;
};
//rtp 流文件句柄map
static std::map<std::string,struct rtpFileRel> rtp_stream_pFile_map;

//rtp字段的双链表
GList *rtp_fields = nullptr;

//对应rtp字段双链表的存储
struct rtp_Content{
    char protocol[32];
    gboolean marker = 0;
    gboolean bye = 0;
    char ssrc[24]{};
    guint8 payload[2*4000]{};
    int payload_len{};
    unsigned int payload_type{};
    char file_name[128]{};
};

typedef struct _rtp_decoder_t{
    codec_handle_t handle;
    void *context;
} rtp_decoder_t;
//写rtp可播放流的头 仅支持8000采样率.
void writeRTPstreamHead(FILE* fp);
//给定rtp的类型，返回组报结果文件名
inline std::string got_rtp_Stream_FileName(unsigned int,const std::string &, const std::string &);

//rtp stream---------------------- 20210909 yy ---------------------- rtp stream end |||

//tls stream---------------------- 20210909 yy ---------------------- tls stream begin |||
GList *tls_fields = nullptr; //tls字段的双链表
enum tls_Status{
    CLIENT_HELLO = 0,
    SERVER_HELLO,
    SERVER_CERTIFICATE,
};
struct tls_Content{
    char        sip[24];
    char        dip[24];
    uint16_t    sport;
    uint16_t    dport;
    uint16_t    handshake_ciphersuite;  //tls.handshake.ciphersuite
    uint8_t     handshake_type; //tls.handshake.type
    char      cer[8000];   //tls.handshake.certificates
};//并发处理tls相关内容

struct tls_Vec{
    std::string sip;
    std::string dip;
    uint16_t    sport;
    uint16_t    dport;
    uint8_t     tls_Status;
};//保存tls所有连接状态
std::vector<struct tls_Vec> tls_Total;
//tls stream---------------------- 20210909 yy ---------------------- tls stream end |||

struct totalParam{ //流组报相关全参数结构体
    struct comFiveEleContent *c5e = nullptr; //通信五元组
    struct rtp_Content *rtp_content = nullptr;
    struct tls_Content *tls_content = nullptr;
};
/*流处理函数线程池*/
GThreadPool *handleStreamTpool;

//当前数据包若为需要组的包则为TRUE，否则为FALSE
gboolean packetProtoAlready = false;


//根据payloadType调用解码器//
void call_decode_by_i(int payloadType_i,char* it_fp_path_t,char* info_fp_path_t);

//并发处理流数据的函数入口。
void do_handle_strem(gpointer str,gpointer data);
//stream handle----------------------------begin 20210909 yy ----------------------------stream handle end ||||

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
                if(temp->times >= 50)
                    return "-1";
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
    if (node != nullptr) {
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
    for (auto &i : lastLayerProtocolFilterList) { //lastLayerProtocolFilterList 列表在上面定义 yy20211026
        if(i == dst){
            return true;
        }
    }
    return false;
}
/**
 * 递归key的过滤。
 */
gboolean cursionkeyStrFilter(const char *key_str){
    for (auto &i :protoKeyFilterList) {  //protoKeyFilterList 列表在上面定义20211026 yy
        if(i == key_str)
            return true;
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
    std::string filepath__str_t;
    std::string filedirpath_str_t;
    /* 20211208MZY ISIS的不同类型放到一个文件夹中输出*/
    if(strncasecmp(protocol.c_str(),"isis",4) == 0){
        std::string isis = "isis";
        filepath__str_t = (std::string)EXPORT_PATH  + isis + "/"+  protocol + "/" + protocol + "_" + global_time_str + ".writting";
        filedirpath_str_t = (std::string)EXPORT_PATH + isis + "/"+ protocol;

    }else{
        filepath__str_t = (std::string)EXPORT_PATH + protocol + "/" + protocol + "_" + global_time_str + ".writting";
        filedirpath_str_t = (std::string)EXPORT_PATH + protocol;
    }
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
        if (fp_t->fp == nullptr) {
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
 * 给fp写入rtp可播放流的头部 仅支持8000采样率，目前测试仅支持g711A/U,g729a，采样率为8000的数据。
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
 * 将会话统计信息写入文件中，文件名固定为conversation.txt
 * @param stream
 * @param protocol
 * @return
 */
gboolean write_Files_conv(std::string &stream) {
    /*添加换行符*/
    stream.append("\r\n");

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
        if (conversation_Handle_File == nullptr) {
            g_print("open %s error!\n", conv_path_t.c_str());
            return false;
        }
    }
    if((kafkaParams_ymq.status == KAFKA_PRODUCER || kafkaParams_ymq.status == KAFKA_PRODUCER_CONSUMER) && WRITE_IN_KAFKA_CONFIG == 1){
        std::string conversation_name_t = "conversation";
        const char * data = stream.c_str();
        const char * key = conversation_name_t.c_str();
        au_kafka_producer(rk, &kafkaParams_ymq, key, data);
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
    struct curl_slist *headers = nullptr;
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

    /*添加换行符*/
    stream.append("\r\n");

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
    try {
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
        strname_head->next = nullptr;
        strname_head->times = 0;
        strname_head->str_name = "";

        //数据包处理完组包标志初始化
        packetProtoAlready = false;

        return true;
    }
    catch (std::out_of_range) {
        g_print("initialize error");
        return false;
    }
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

    //此处是为了过滤自定义协议的无意义字段//
    std::string useless_key_str = key_str.substr(0,7);
    if(cursionkeyStrFilter(useless_key_str.c_str())){
        return false;
    }

    //获取value
    int bufferlen = (temp->finfo->length *3 +1)>100?(temp->finfo->length *3 +1):1000;

    auto *value_t = (gchar*)g_malloc_n(sizeof(gchar),bufferlen);
    if(! need_special_field(temp->finfo->hfinfo->abbrev, temp, value_t)){
        yy_proto_item_fill_label(temp->finfo,&value_t,bufferlen);
    }


    //组包相关
    if (PACKET_PROTOCOL_FLAG && packetProtoAlready) {
        //rtp content relative
        g_assert(cookie !=nullptr);
        GList *it = nullptr;
        if ((it = g_list_find_custom(rtp_fields, (gpointer)key_str.c_str(),(GCompareFunc)strcmp))) {
            if(!cookie->rtp_content){ // 首先初始化
                cookie->rtp_content = g_new0(rtp_Content,1);
                if(!cookie->rtp_content){
                    g_print("rtp content init error!\n");
                    return false;
                }
            }
            //赋值开始
            if(strcmp((char*)it->data,"rtp_marker") == 0){
                cookie->rtp_content->marker = std::stoi(value_t);
            }
            else if(strcmp((char*)it->data,"rtp_ssrc") == 0){
                strcpy(cookie->rtp_content->protocol,"rtp");
                strcpy(cookie->rtp_content->ssrc,value_t);
                strcpy(cookie->rtp_content->file_name,FILE_NAME_T);//这里将rtp数据包所属的文件名也传入
            }
            else if(strcmp((char*)it->data,"rtp_payload") == 0){
                for (guint i = 0; i < temp->finfo->value.value.bytes->len ;++i) {
                    cookie->rtp_content->payload[i] = temp->finfo->value.value.bytes->data[i];
                }
                cookie->rtp_content->payload_len = temp->finfo->value.value.bytes->len;
            }
            else if(strcmp((char*)it->data,"rtp_p_type") == 0){
                cookie->rtp_content->payload_type = std::stoi(value_t);
            }
            else if(strcmp((char*)it->data,"sip_Method") == 0){
                strcpy(cookie->rtp_content->protocol,"sip");
                if(strcmp(value_t,"BYE") == 0){
                    cookie->rtp_content->bye = true;
                }
            }
        }
        else if((it = g_list_find_custom(tls_fields, (gpointer)key_str.c_str(),(GCompareFunc)strcmp))){
            if(!cookie->tls_content){
                cookie->tls_content = g_new0(tls_Content,1);
                if(!cookie->tls_content){
                    g_print("tls content init error!\n");
                    return false;
                }
            }
            //赋值
        }
    }

    //将key_str 形式“x.ab.c.d” 转换成“x_ab_c_d”

/*    while (key_str.find('.') != std::string::npos) {  *//* 返回string::npos表示未查找到匹配项 *//*
        key_str.replace(key_str.find('.'), 1, "_");
    }*/

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
                    cJSON_AddItemToArray(temp_array,cJSON_CreateString(value_t));
                }
            } else{
                cJSON_AddStringToObject(json_t,key_str.c_str(),value_t);
            }
*/

    key_str = gotStrNameByStrName(key_str);
    if(key_str == "-1"){
        return false;
    }
    cJSON_AddStringToObject(json_t,key_str.c_str(),value_t);

    g_free(value_t);
    return true;
}

/**
 * 非递归处理协议解析树内容，层序遍历，存入json中。
 * @param json_t
 * @param node
 * @param cookie
 * @return
 */
gboolean dissect_edt_Tree_Into_Json_No_Cursion(cJSON *&json_t,proto_node *&node, struct totalParam *cookie __U__){
    while(node != nullptr){
        if(node->first_child == nullptr or node->last_child == nullptr or (is_special_not_leafNode(node->finfo->hfinfo->abbrev))){
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

        if(temp->first_child == nullptr or temp->last_child == nullptr or (is_special_not_leafNode(temp->finfo->hfinfo->abbrev))){
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
        auto iter = regex_dict_map.find("line_no");
        if (iter != regex_dict_map.end())
        {
            // 找到了本地文件匹配的线路号
            strcpy(OFFLINE_LINE_LINE_NO,iter->second.c_str());
        }
    }

}

/**
 * 直接解析edt 写入文件缓存中 202107290910
 * @param edt
 * @return
 */
gboolean dissect_edt_into_files(epan_dissect_t *edt) {
    g_assert(edt != nullptr);
    if (edt->tree == nullptr)
        return false;
    proto_node *node = edt->tree->first_child;
    std::string protocol_stack_t;  // 记录协议栈
    proto_node *stack_node_t = node;
    auto *c5e = new comFiveEleContent(); //存放通信五元组
    comSevenStackContent s7e;// 会话七元组

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
        c5e->protocol = write_in_files_proto; //通信五元组协议
        if(stack_node_t->next){
            char pre_proto_t[40] = {};
            char next_proto_t[40] = {};
            strcpy(pre_proto_t,stack_node_t->finfo->hfinfo->abbrev);
            strcpy(next_proto_t,stack_node_t->next->finfo->hfinfo->abbrev);
            if(match_all_diy_proto(pre_proto_t,next_proto_t)){
                dissect_edt_Tree_Into_Json_No_Cursion(write_in_files_cJson,stack_node_t->first_child,nullptr);
            }
        }
        stack_node_t = stack_node_t->next;
    }
    s7e.protocol_stack = protocol_stack_t;
    s7e.line_no = OFFLINE_LINE_LINE_NO;
    s7e.read_file_path = READ_FILE_PATH;




    if(PACKET_PROTOCOL_FLAG){
        /*判断当前协议是否需要组包*/
        if(g_list_find_custom(rtp_fields, write_in_files_proto.c_str(), (GCompareFunc)strcmp)){
            packetProtoAlready = true;
        }
    }
    /*获取文件来源*/
    if (read_Pcap_From_File_Flag == 1) {
        /* 单个文件 */
        cJSON_AddStringToObject(write_in_files_cJson, "file_path", READ_FILE_PATH);
        if(!regex_dict_map.empty()){
            for (auto & i : regex_dict_map) {
                cJSON_AddStringToObject(write_in_files_cJson, i.first.c_str(), i.second.c_str());
            }
        }
    } else {
        cJSON_AddStringToObject(write_in_files_cJson, "file_path", "online");
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
            if (strcmp(child_finfo->hfinfo->abbrev, "frame_encap_type") == 0) {
                yy_proto_item_fill_label(child_finfo, &value_240,240);
                cJSON_AddStringToObject(write_in_files_cJson, "frame_encap_type", value_240);
                child = child->next;
                continue;
            }
            else if (strcmp(child_finfo->hfinfo->abbrev, "frame_time_epoch") == 0) {
                yy_proto_item_fill_label(child_finfo, &value_240,240);
                cJSON_AddStringToObject(write_in_files_cJson, "frame_time_epoch", value_240);
                c5e->frame_time = std::stol(value_240);              // maybe 'std::out_of_range' error (ieee802154-association-data.pcap)
                child = child->next;
                continue;
            }
            else if (strcmp(child_finfo->hfinfo->abbrev, "frame_len") == 0) {
                yy_proto_item_fill_label(child_finfo, &value_240,240);
                cJSON_AddStringToObject(write_in_files_cJson, "frame_len", value_240);
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
                if (strcmp(child_finfo->hfinfo->abbrev, "eth_dst") == 0) {
                    yy_proto_item_fill_label(child_finfo, &value_240,240);
                    cJSON_AddStringToObject(write_in_files_cJson, "eth_dst", value_240);
                    child = child->next;
                    continue;
                }
                else if (strcmp(child_finfo->hfinfo->abbrev, "eth_src") == 0) {
                    yy_proto_item_fill_label(child_finfo, &value_240,240);
                    cJSON_AddStringToObject(write_in_files_cJson, "eth_src", value_240);
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
                if (strcmp(child_finfo->hfinfo->abbrev, "ip_src") == 0 or
                    strcmp(child_finfo->hfinfo->abbrev, "ipv6_src") == 0) {
                    yy_proto_item_fill_label(child_finfo, &value_240,240);
                    cJSON_AddStringToObject(write_in_files_cJson, "src_ip", value_240);
                    c5e->sip = value_240;
                    s7e.sip = value_240;
                    child = child->next;
                    continue;
                }
                else if (strcmp(child_finfo->hfinfo->abbrev, "ip_dst") == 0 or
                         strcmp(child_finfo->hfinfo->abbrev, "ipv6_dst") == 0) {
                    yy_proto_item_fill_label(child_finfo, &value_240,240);
                    cJSON_AddStringToObject(write_in_files_cJson, "dst_ip", value_240);
                    c5e->dip = value_240;
                    s7e.dip = value_240;
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
                if (strcmp(child_finfo->hfinfo->abbrev, "tcp_srcport") == 0 or
                    strcmp(child_finfo->hfinfo->abbrev, "udp_srcport") == 0) {
                    yy_proto_item_fill_label(child_finfo, &value_240,240);
                    cJSON_AddStringToObject(write_in_files_cJson, "src_port", value_240);
                    c5e->sport = value_240;
                    s7e.sport = value_240;
                    child = child->next;
                    continue;
                }
                else if (strcmp(child_finfo->hfinfo->abbrev, "tcp_dstport") == 0 or
                         strcmp(child_finfo->hfinfo->abbrev, "udp_dstport") == 0) {
                    yy_proto_item_fill_label(child_finfo, &value_240,240);
                    cJSON_AddStringToObject(write_in_files_cJson, "dst_port", value_240);
                    c5e->dport = value_240;
                    s7e.dport = value_240;
                    child = child->next;
                    if(s7e.sport == "" || s7e.dport == "" || s7e.sip == "" || s7e.dip == "" ||s7e.protocol_stack == ""){
                        //memset(&s7e,0,sizeof(comSevenStackContent));//不存在会话，直接释放。
                    } else{
                        if(final_conversation_Write_Need.empty()){
                            final_conversation_Write_Need.push_back(s7e);
                        }else{
                            bool exist = FALSE;
                            for (auto &i : final_conversation_Write_Need){
                                if(strcmp(s7e.sip.c_str(),i.sip.c_str()) == 0 && strcmp(s7e.dip.c_str(),i.dip.c_str()) == 0 && i.sport == numtos(s7e.sport) && i.dport == numtos(s7e.dport) &&  strcmp(s7e.protocol_stack.c_str(),i.protocol_stack.c_str()) == 0){
                                    exist = TRUE;
                                    break;
                                }
                            }
                            if(!exist){
                                //避免重复缓存
                                final_conversation_Write_Need.push_back(s7e);
                            }
                        }
                    }
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
            if(strcmp(fi_data->hfinfo->abbrev,"data_data") == 0){
                auto *value = (gchar*)g_malloc_n(sizeof(gchar),fi_data->length *2 +1);
                yy_proto_item_fill_label(fi_data,&value,fi_data->length *2 +1);
                cJSON_AddStringToObject(write_in_files_cJson,"data",value);
                g_free(value);
                write_in_files_proto = "unknown";
            }
            //这里直接退出协议数据获取循环。不必进入最后层协议的解析。
            break;
        }

        /*最后层协议的解析*/
        else if (strcmp(fi->hfinfo->abbrev, write_in_files_proto.c_str()) == 0) {
            proto_node *child = node->first_child;
            if (child != nullptr) {
                try {
                    if(PACKET_PROTOCOL_FLAG && packetProtoAlready){
                        //要组报
                        struct totalParam *cookie_t = g_new0(totalParam,1);
                        //通信五元组赋值
                        cookie_t->c5e = c5e; //这里释放在rtp流处理函数后释放
                        dissect_edt_Tree_Into_Json_No_Cursion(write_in_files_cJson,child, cookie_t);

                        if(cookie_t->rtp_content != nullptr){
                            auto rtp_index = rtp_payload_type_To_tail.find(cookie_t->rtp_content->payload_type);
                            if(strcmp(cookie_t->rtp_content->protocol, "sip")==0 || rtp_index != rtp_payload_type_To_tail.end()){
                                g_thread_pool_push(handleStreamTpool,(gpointer)cookie_t, nullptr);
                            }
                        }
                    }
                    else{
                        dissect_edt_Tree_Into_Json_No_Cursion(write_in_files_cJson,child,nullptr);
                        delete(c5e); //未使用通信五元组，直接释放。
                        c5e = nullptr;
                    }
                }
                catch (std::invalid_argument) {
                    node = node->next;
                    continue;
                }
            }
            //可能存在多个相同协议，如tls,tls;
            break;
        }
        node = node->next;
    }

    /*单独的协议过滤*/
    if (kmp("[tcp],[udp]", "[" + write_in_files_proto + "]") != -1) {
        /*初始化部分要用到的 json对象 ----begin*/
        cJSON_Delete(write_in_files_cJson);
        write_in_files_cJson = cJSON_CreateObject();
        /*初始化部分要用到的 json对象 ----end*/
        return true;
    }

    write_in_files_stream = cJSON_Print(write_in_files_cJson);
    if((kafkaParams_ymq.status == KAFKA_PRODUCER || kafkaParams_ymq.status == KAFKA_PRODUCER_CONSUMER) && WRITE_IN_KAFKA_CONFIG == 1){
        const char * data = cJSON_Print(write_in_files_cJson);
        const char * key = write_in_files_proto.c_str();
        au_kafka_producer(rk, &kafkaParams_ymq, key, data);
    }
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
 * 将export信息与来源pcap写入文件中，文件名固定为export_result_时间戳.txt

 * @return
 */
gboolean write_Export_result(char* ex_name,char * pcap_name ,char* result_path, export_object_entry_t *entry){

    char ex_resulty_filepath_t[MAXWRITEFILELENGTH] = {0};
    std::string export_path_t = result_path;

    //此处截断后七个字符在去除/export，在上一级输出//
    std::string export_result_path_t = export_path_t.substr(0,export_path_t.length()-7);
    std::string filepath_t_str =  export_result_path_t + "export-result_" + global_time_str +".txt";

    //global_time_str
    strcpy(ex_resulty_filepath_t,filepath_t_str.c_str());
    pFILE_INFO *fp_t;
    fp_t = new pFile_Info;
    fp_t->fp = fopen(ex_resulty_filepath_t, "a+");
    if (fp_t->fp == NULL) {
        g_print("open filepath error!\n");
        return false;
    }

    cJSON_AddStringToObject(write_export_origin_cJson, "origin_file_path", pcap_name);
    cJSON_AddStringToObject(write_export_origin_cJson, "export_file_path", ex_name);
    cJSON_AddNumberToObject(write_export_origin_cJson, "pkt_num", entry->pkt_num);
    cJSON_AddStringToObject(write_export_origin_cJson, "hostname", entry->hostname ? entry->hostname : "");
    cJSON_AddStringToObject(write_export_origin_cJson, "content_type", entry->content_type ? entry->content_type : "");
    cJSON_AddStringToObject(write_export_origin_cJson, "filename", entry->filename);
    cJSON_AddNumberToObject(write_export_origin_cJson, "filesize", entry->payload_len);


    write_ex_origin_stream = cJSON_Print(write_export_origin_cJson);

    if((kafkaParams_ymq.status == KAFKA_PRODUCER || kafkaParams_ymq.status == KAFKA_PRODUCER_CONSUMER) && WRITE_IN_KAFKA_CONFIG == 1){
        const char * data = cJSON_Print(write_export_origin_cJson);
        const char * key = "export_result";
        au_kafka_producer(rk, &kafkaParams_ymq, key, data);
    }

    g_assert(fp_t->fp); //这里肯定fp不能为空。否则文件不知道写到那里。
    fputs(write_ex_origin_stream.c_str(),fp_t->fp);
    fprintf(fp_t->fp,"\n");
    fflush(fp_t->fp);

    /*初始化部分要用到的 json对象 ----begin*/
    cJSON_Delete(write_export_origin_cJson);
    write_export_origin_cJson = cJSON_CreateObject();
    /*初始化部分要用到的 json对象 ----end*/

/*    fprintf(fp_t->fp,"%s\t",ex_name);
    fprintf(fp_t->fp,"%s\n",pcap_name);*/
    fclose(fp_t->fp);
    return true;
}

/**
 *  将开始和结束位置写入文件缓存中 20211214MZY
 * @param
 * @return
 */
gboolean write_range_into_write_in_files_cJson(gint64 begin, gint64 end){

    cJSON_AddStringToObject(write_in_files_cJson, "start_position", numtos(begin).c_str());
    cJSON_AddStringToObject(write_in_files_cJson, "end_position", numtos(end).c_str());
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
        //获取文件来源，将conversation与源文件进行关联
/*        if (read_Pcap_From_File_Flag == 1) {
            cJSON_AddStringToObject(write_in_files_conv_cJson, str_FILES_RESOURCE, READ_FILE_PATH);
            cJSON_AddStringToObject(write_in_files_conv_cJson, "line_no", OFFLINE_LINE_LINE_NO);  *//* 离线接入数据的线路号 *//*
        } else {
            cJSON_AddStringToObject(write_in_files_conv_cJson, str_FILES_RESOURCE, "online");
            cJSON_AddStringToObject(write_in_files_conv_cJson, "line_no", ONLINE_LINE_NO);  // 在线实时接入数据的线路号
        }*/
        /*当前流统计结束*/
        if (write_in_files_conv_cJson->child == nullptr)
            return;

        if(key_str == READ_FILE_PATH){
            std::string string = cJSON_Print(write_in_files_conv_cJson);
            write_Files_conv(string);
        }

        cJSON_Delete(write_in_files_conv_cJson);
        write_in_files_conv_cJson = cJSON_CreateObject();
    } else {
        cJSON_AddStringToObject(write_in_files_conv_cJson, key_str.c_str(), value_str.c_str());
    }
}
/**
 * decode rtp streams into pd_out 主要g711A/U g729a的解码器。
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
//            g_print("File parsing and saving at this rate is not supported,8000 rate only \n%s\n",__FUNCTION__);
            decoded_samples = 0;
        }
    } else{
//        g_print("File parsing and saving at this rate is not supported \n%s\n",__FUNCTION__);
        decoded_samples = 0;
    }

    g_free(decode_buff);

    return decoded_samples;
}

/**
 * 判断是否需要配对
 * @param info
 * @return
 */
void rtpVoiceMatching(rtpTotalBufferContent &info){
    std::vector<rtpMatchingInfo>::iterator it;
    for (it = rtpMachingVec.begin();it != rtpMachingVec.end(); it++ ) {
        unsigned int tm_gap = info.time_begin > it->time_begin ? \
                              info.time_begin - it->time_begin : it->time_begin - info.time_begin;
        if (it->sip == info.dip and it->dip == info.sip and it->sport == info.dport and it->dport == info.sport \
        and (tm_gap < 3000) and \
            it->rtpPayloadType == info.rtpPayloadType) { //这里不加结束时间的原因是程序最后的清空有可能没来得及给结束时间赋值，使用time_end可能会报错
            //匹配info.rtpPayloadType
            int payloadType_i = -1;
            for (int i = 0;i < 128;i++){
                if(strcmp(info.rtpPayloadType.c_str(),rtp_payload_type_to_str[i]) == 0){
                    payloadType_i = i;
                    break;
                }
            }
            char info_fp_path_t[256];
            char it_fp_path_t[256];
            strcpy(it_fp_path_t,it->fp_path.c_str());
            strcpy(info_fp_path_t,info.fp_path.c_str());
            call_decode_by_i(payloadType_i,it_fp_path_t,info_fp_path_t);
            //找到对家的两个文件进行合并解码后，在vector缓存区中删除该对家//
            rtpMachingVec.erase(it);
            return;
        }
    }
    //没有找到对家的数据放入缓存区//
    rtpMatchingInfo temp;
    temp.fp_path = info.fp_path;
    temp.time_begin = info.time_begin;
    temp.time_end = info.time_end;
    temp.last_record_time = info.last_record_time;
    temp.dport = info.dport;
    temp.sport = info.sport;
    temp.sip = info.sip;
    temp.dip = info.dip;
    temp.rtpPayloadType = info.rtpPayloadType;
    rtpMachingVec.push_back(temp);
}

/**
 * 根据patloadType调用相应call_zhr_handler。
 * @param i
 * @param it_fp_path_t info_fp_path_t
 */
void call_decode_by_i(int payloadType_i,char* it_fp_path_t,char* info_fp_path_t){
    switch (payloadType_i){
        //根据patloadType调用相应call_zhr_handler//
        case 0:
            g711u_decode_zhr(it_fp_path_t,info_fp_path_t);
            break;

        case 8:
            g711a_decode_zhr(it_fp_path_t,info_fp_path_t);
            break;
        case 9:
            g722_decode_zhr(it_fp_path_t,info_fp_path_t);
            break;
        case 18:
            g729a_decode_zhr(it_fp_path_t,info_fp_path_t);
            break;
        default:
            break;

    }
}

void do_audio_paired(const std::string& index_str, unsigned int end_t, bool mutex){
    auto it = rtpTotalBuffer.find(index_str);
    if (it != rtpTotalBuffer.end()) {
        //find
        it->second.time_end = end_t;
        unsigned long len = it->second.data.get_len();
        if(len>MIN_AUDIO_SIZE){
            if (fwrite(it->second.data.get_data(), sizeof(guint8), len, it->second.fp) != len) {
                g_print("rtp write error ! -> %s\n", index_str.c_str());
            }
            it->second.data.clear();
            fclose(it->second.fp); // 写完就关闭掉
            //判断话音是否要配对
            rtpVoiceMatching(it->second);
        } else{
            if (mutex){
                fclose(it->second.fp);
                if(!it->second.fp_path.empty()) remove(it->second.fp_path.c_str());
            }
        }
        if (mutex){
            rtp_mtx.lock();
            rtpTotalBuffer.erase(it);
            rtp_mtx.unlock();
        } else rtpTotalBuffer.erase(it);
    }
}

/**
 * 并发处理流数据函数;处理cookie_t的内容。
 * @param str
 * @param data
 */
void do_handle_strem(gpointer str,gpointer data __U__){
    auto *t = (totalParam *) str;

    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    std::time_t global_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    std::string global_time_str_tt = numtos((u_long) global_time);

    if(t->rtp_content != nullptr){
//        并发处理rtp流。目前仅支持g711A/U,g729a,g722。
        if (strcmp(t->rtp_content->protocol,"sip") == 0) {
            if (t->rtp_content->bye) {
                //sip发的BYE包
                //当前ssrc通话结束
                std::string index_str = t->c5e->sip + ":" + t->c5e->sport + ":" + t->c5e->dip + ":" + t->c5e->dport + \
                ":" + t->rtp_content->ssrc;
                do_audio_paired(index_str, t->c5e->frame_time, FALSE);
            }
        }
        else if(strlen(t->rtp_content->ssrc) != 0){
            std::string index_str = t->c5e->sip + ":" + t->c5e->sport + ":" + t->c5e->dip + ":" + t->c5e->dport + \
                ":" + t->rtp_content->ssrc;
            auto it = rtpTotalBuffer.find(index_str);
            if(it == rtpTotalBuffer.end()){
                //no find or null
                rtpTotalBufferContent temp{};
                temp.sip = t->c5e->sip;
                temp.dip = t->c5e->dip;
                temp.sport = t->c5e->sport;
                temp.dport = t->c5e->dport;
                temp.time_begin = t->c5e->frame_time; //开始时间戳
                temp.ssrc = t->rtp_content->ssrc;
                temp.rtpPayloadType = rtp_payload_type_to_str[t->rtp_content->payload_type];
                //确定rtp 输出的文件名 begin
                char file_name_t[270] = {0};
                strcat(file_name_t, PACKET_PROTOCOL_PATH);
                sprintf(file_name_t, "%s%s", PACKET_PROTOCOL_PATH, "rtp/");
                if (access(file_name_t, 0) != 0) {
                    mkdirs(file_name_t);
                }
                std::string fn_str_t = got_rtp_Stream_FileName(t->rtp_content->payload_type, global_time_str_tt,
                                                               t->rtp_content->ssrc);
                strcat(file_name_t, fn_str_t.c_str());
                temp.fp = fopen(file_name_t, "a+");
                if (!temp.fp) {
                    g_print("%s open error", file_name_t);
                    return;
                }
                temp.fp_path = file_name_t;
                temp.last_record_time = time_now.tv_sec;
                //确定rtp 输出的文件名 end
                temp.data.push_back((guint8 *)&t->c5e->frame_time,8);
                temp.data.push_back((guint8 *)&t->rtp_content->payload_len,4);
                temp.data.push_back(t->rtp_content->payload, t->rtp_content->payload_len);
                rtpTotalBuffer.insert(std::pair<std::string,rtpTotalBufferContent>(index_str,temp));

            } else{
                //find
                it->second.time_end = t->c5e->frame_time;
                it->second.last_record_time = time_now.tv_sec;
                it->second.data.push_back((guint8 *)&t->c5e->frame_time,8);
                it->second.data.push_back((guint8 *)&t->rtp_content->payload_len,4);
                it->second.data.push_back(t->rtp_content->payload,t->rtp_content->payload_len);
            }
        }
        else{
            //不明格式的rtp数据包。
        }
        /*char file_name_t[270] = {0};
        //确定rtp 输出的文件名
        strcat(file_name_t, PACKET_PROTOCOL_PATH);
        sprintf(file_name_t, "%s%s", PACKET_PROTOCOL_PATH, "rtp/");
        if (access(file_name_t, 0) != 0) {
            mkdirs(file_name_t);
        }
        std::string fn_str_t = got_rtp_Stream_FileName(t->rtp_content->payload_type, global_time_str,
                                                       t->rtp_content->ssrc);
        strcat(file_name_t, fn_str_t.c_str());

        FILE *fp = nullptr;
        struct _GHashTable *decoders_hash = nullptr;
        if (rtp_stream_pFile_map.empty()) {
            //空map
            fp = fopen(file_name_t, "a+");
            if (!fp) {
                g_print("%s open error", file_name_t);
                return;
            }
            if(std::find(rtp_Head_au_8000_Rate_surport_List.begin(),rtp_Head_au_8000_Rate_surport_List.end(),t->rtp_content->payload_type) != rtp_Head_au_8000_Rate_surport_List.end()){
                //按需写入头部
                writeRTPstreamHead(fp);
            }
            struct rtpFileRel temprtpFIleRel{};
            temprtpFIleRel.decoders_hash = rtp_decoder_hash_table_new();
            decoders_hash = temprtpFIleRel.decoders_hash;
            temprtpFIleRel.fp = fp;
            std::string ssrc_t = t->rtp_content->ssrc;
            ssrc_t += rtp_payload_type_to_str[t->rtp_content->payload_type];
            rtp_stream_pFile_map.insert(std::pair<std::string, struct rtpFileRel>(ssrc_t, temprtpFIleRel));
        }
        else {
            std::string ssrc_t = t->rtp_content->ssrc;
            ssrc_t += rtp_payload_type_to_str[t->rtp_content->payload_type];
            auto index = rtp_stream_pFile_map.find(ssrc_t);
            if (index != rtp_stream_pFile_map.end()) {
                fp = index->second.fp;
                decoders_hash = index->second.decoders_hash;
                //这里解码器初始化
                if (t->rtp_content->marker) {
                    if (decoders_hash) {
                        g_hash_table_destroy(decoders_hash);//这里得释放掉。
                    }
                    index->second.decoders_hash = nullptr;
                    decoders_hash = nullptr;
                }
            } else {
                fp = fopen(file_name_t, "a+");
                if (!fp) {
                    g_print("%s open error", file_name_t);
                    return;
                }
                if(std::find(rtp_Head_au_8000_Rate_surport_List.begin(),rtp_Head_au_8000_Rate_surport_List.end(),t->rtp_content->payload_type) != rtp_Head_au_8000_Rate_surport_List.end()){
                    //按需写入头部
                    writeRTPstreamHead(fp);
                }
                struct rtpFileRel temprtpFileRel{};
                temprtpFileRel.decoders_hash = rtp_decoder_hash_table_new();
                decoders_hash = temprtpFileRel.decoders_hash;
                temprtpFileRel.fp = fp;
                rtp_stream_pFile_map.insert(std::pair<std::string, struct rtpFileRel>(ssrc_t, temprtpFileRel));
            }
        }
        g_assert(fp != nullptr);
        size_t sample_count = 0;
        uint8_t pd_out[2 * 4000];

        if(strcmp(rtp_payload_type_to_str[t->rtp_content->payload_type],"g722") == 0){
            //g722
            sample_count = g722_single_frame_decode(t->rtp_content->payload,t->rtp_content->payload_len,t->rtp_content->marker,pd_out);
        } else{
            sample_count = convert_payload_to_samples(t->rtp_content->payload_type, t->rtp_content->payload,
                                                      t->rtp_content->payload_len, pd_out, decoders_hash);
            sample_count *=2; //8000采样率，写入数据内容乘2。
        }

        if (sample_count != 0) {
            if (fwrite(pd_out, sizeof(uint8_t), sample_count, fp) != sample_count) {
                g_print("%s sample_count write error !\n", __FUNCTION__);
            }
        } else {
            g_print(" rtp %s decode error! ->payload len:%zu ->ssrc:%s\n ",rtp_payload_type_to_str[t->rtp_content->payload_type],t->rtp_content->payload_len,t->rtp_content->ssrc);
        }
//        }*/

        std::vector<std::string> tmp_keys{};
        for(auto &it: rtpTotalBuffer){
            if(std::abs(time_now.tv_sec - it.second.last_record_time) > 300)   //wait 300s
                tmp_keys.push_back(it.first);
        }
        for(auto &k: tmp_keys){
            do_audio_paired(k, time_now.tv_sec, TRUE);
        }
        if(t->rtp_content) g_free(t->rtp_content);
    }
    if(t->tls_content != nullptr){
        //tls
    }
    //最后才释放通信五元组内容。
    if(t->c5e) delete(t->c5e);
    //传入的参数空间释放。
    if(t) g_free(t);

}
/**
 * 根据final_Follow_Write_Need内容，判断tap-follow.c中的统计流是否输出
 * @param sip client ip
 * @param sport client port
 * @param dip server ip
 * @param dport server port
 * @return
 */

gboolean JudgeStreamPrint(gchar* sip,guint sport,gchar *dip,guint dport){
    for (auto &i : final_Follow_Write_Need) {
        if(strcmp(sip,i.sip.c_str()) == 0 and strcmp(dip,i.dip.c_str()) == 0 and i.sport == numtos(sport) and i.dport == numtos(dport)){
            if(pfinal_follow != nullptr){
                //应该为空，若不是空指针肯定是那里出了问题。
                return false;
            }

            pfinal_follow = new final_Follow_File_Rel{};
            pfinal_follow->streamFileName_t += i.protocol + "/" + i.protocol_suffix +"_";
            std::string sip_r = i.sip;
            stringReplaceByStr(sip_r,".","_");
            pfinal_follow->streamFileName_t +=sip_r +"_" + i.sport+"_";
            sip_r = i.dip;
            stringReplaceByStr(sip_r,".","_");
            pfinal_follow->streamFileName_t += sip_r +"_" + i.dport;
            pfinal_follow->content.clear();
            pfinal_follow->streamFileName_fp = nullptr;
            pfinal_follow->cache_Flag = false;
            pfinal_follow->protocol_suffix = i.protocol_suffix;
            pfinal_follow->content_len = 0;

            //g722单独处理交给g722处理接口 protocol_suffix 是协议的后层协议，后缀协议
            /*if(i.protocol_suffix == "g722"){
                pfinal_follow->cache_Flag = true;
                pfinal_follow->protocol_suffix_type = 9; //g722 type
            }*/

            //这里就直接把路径建好 后续followstream就不用再重复建造路径
            std::string path_t = PACKET_PROTOCOL_PATH;
            path_t += i.protocol;
            if(access(path_t.c_str(), 0) != 0){
                mkdirs(path_t.c_str());
            }
            return true;
        }
    }
    return false;
}

/**
 * 程序结束后，将tap-follow.c中的统计流数据全部写入文件。
 * @param data
 * @param len
 * @return
 */
gboolean streamFollowIntoFiles(guint8 *data,guint len){
    if(len == 0) return true;
    if(strcmp((char *)data,"-1END") == 0){
        //一个流结束

        /*if(pfinal_follow->cache_Flag){
            //特殊的部分流处理交给指定的接口处理
            if(pfinal_follow->protocol_suffix == "g722"){
                guchar *out = g_new0(guchar, pfinal_follow->content_len * 4);
                int t = g722decode(pfinal_follow->content.data(), pfinal_follow->content_len, out);
                fwrite(out, sizeof(guchar), t, pfinal_follow->streamFileName_fp);
            }
        }*/

        fclose(pfinal_follow->streamFileName_fp);
        pfinal_follow->streamFileName_fp = nullptr;
        pfinal_follow->streamFileName_t.clear();
        pfinal_follow->protocol_suffix.clear();
        pfinal_follow->content.clear();
        free(pfinal_follow);
        pfinal_follow = nullptr;
        return true;
    } else {
        if (!pfinal_follow->streamFileName_fp) {
            std::string fpath_t = PACKET_PROTOCOL_PATH;

            //获取尾名，文件格式名
            /* std::string tail_t;
             auto index_t = rtp_payload_type_To_tail.find(pfinal_follow->protocol_suffix_type);
             if (index_t == rtp_payload_type_To_tail.end()) {
                 tail_t = ".stream";
             } else {
                 tail_t = index_t->second;
             }
             fpath_t += pfinal_follow->streamFileName_t + tail_t;*/

            fpath_t += pfinal_follow->streamFileName_t + ".stream";

            assert(!pfinal_follow->streamFileName_t.empty());//名称肯定不能为空
            pfinal_follow->streamFileName_fp = fopen(fpath_t.c_str(), "a+");
            if (!pfinal_follow->streamFileName_fp) {
                g_print("stream follow fp open error!\n");
                return false;
            }
        }
//        if (!pfinal_follow->cache_Flag) {
        fwrite(data, sizeof(uint8_t), len, pfinal_follow->streamFileName_fp);
        /*  } else {
              //缓存内容
              pfinal_follow->content.reserve(len);
              for (guint i = 0; i < len; ++i) {
                  pfinal_follow->content.push_back(data[i]);
              }

              pfinal_follow->content_len += len;
          }*/
        return true;
    }
}

/**
 * 给定rtp的类型，全局时间戳，ssrc；返回组报结果文件名 [rtpstring]+[global_time_str]+[ssrc]+[tail_t]
 * @param type rtptype（下标0-127）
 * @param s global_time_str
 * @param p ssrc
 * @return
 */
std::string got_rtp_Stream_FileName(unsigned int type,const std::string &s,const std::string &p){
    std::string file_t;
//    std::string tail_t;
//    auto index_t = rtp_payload_type_To_tail.find(type);
//    if(index_t == rtp_payload_type_To_tail.end()){
//        tail_t = "unknownType";
//    } else{
//        tail_t = index_t->second;
//    }

    file_t += rtp_payload_type_to_str[type];
    stringReplaceByStr(file_t, "-", " ");
    stringReplaceByStr(file_t, "-", "/");
//    return file_t += "_" + s +"_"+ p +"."+ tail_t;
    return file_t += "_" + s +"_"+ p;
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
        g_print("\tKEY:OFFLINE_LINE_NO_REGEX format error!\n");
        g_print("\tmust be standard JSON format\n");
        g_print("\texample:{\"KEY1\":\"VALUE1\",\"KEY2\":\"VALUE2\"}\n\n");
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

    /*初始化rtpstream处理函数线程池 ,最大1个线程并发处理流数据*/
    handleStreamTpool = g_thread_pool_new(do_handle_strem,nullptr,1,FALSE,nullptr);
    //rtp
    rtp_fields = g_list_append(rtp_fields, (gpointer) "rtp");
    rtp_fields = g_list_append(rtp_fields, (gpointer) "sip");
    rtp_fields = g_list_append(rtp_fields, (gpointer) "rtp_marker");
    rtp_fields = g_list_append(rtp_fields, (gpointer) "rtp_ssrc");
    rtp_fields = g_list_append(rtp_fields, (gpointer) "rtp_payload");
    rtp_fields = g_list_append(rtp_fields, (gpointer) "rtp_p_type");
    rtp_fields = g_list_append(rtp_fields, (gpointer) "sip_Method");
    //tls
    tls_fields = g_list_append(tls_fields, (gpointer) "tls");
    tls_fields = g_list_append(tls_fields, (gpointer) "tls_handshake_type");
    tls_fields = g_list_append(tls_fields, (gpointer) "tls_handshake_ciphersuite");
    tls_fields = g_list_append(tls_fields, (gpointer) "tls_handshake_certificates");
    //存放240字节的value内存空间
    value_240 = (gchar *) g_malloc_n(sizeof(gchar), VALUE_240_LENGTH);

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
                char *per_files_max_linex;
                char *write_in_kafka_config;

                /**
                 * 这里需要把当前运行的时间戳定下来
                 */
                struct timeval time_now{};
                gettimeofday(&time_now, nullptr);
                std::time_t global_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
                //std::time_t global_time = std::time(nullptr);
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
                // kafka parameters
                char * kafka_status = getInfo_ConfigFile("KAFKA_STATUS", info, lines);
                if (kafka_status != nullptr) {
                    kafkaParams_ymq.status = (kafka_status_t)(*kafka_status - '0');
                } else kafkaParams_ymq.status = KAFKA_NO_RUN;

                char * kafka_broker = getInfo_ConfigFile("KAFKA_BROKER", info, lines);
                if (kafka_broker != nullptr) { strcpy(kafkaParams_ymq.brokers, kafka_broker); }
                char * kafka_topic = getInfo_ConfigFile("KAFKA_TOPIC", info, lines);
                if (kafka_topic != nullptr) { strcpy(kafkaParams_ymq.topic, kafka_topic); }

                write_in_kafka_config = getInfo_ConfigFile("WRITE_IN_KAFKA_CONFIG", info, lines);
                if(write_in_kafka_config != nullptr){
                    WRITE_IN_KAFKA_CONFIG = *write_in_kafka_config - '0';
                }else{
                    WRITE_IN_KAFKA_CONFIG == 0;
                }
                // for consumer
                char * kafka_groupid = getInfo_ConfigFile("KAFKA_GROUPID", info, lines);
                if (kafka_groupid != nullptr) { strcpy(kafkaParams_ymq.groupid, kafka_groupid); }
                char * kafka_topic_cnt = getInfo_ConfigFile("KAFKA_TOPIC_CNT", info, lines);
                if (kafka_topic_cnt != nullptr) { kafkaParams_ymq.topic_cnt = *kafka_topic_cnt - '0'; }

                switch (kafkaParams_ymq.status) {
                    case KAFKA_PRODUCER:
                        rk = init_producer(&kafkaParams_ymq);
                        break;
                    case KAFKA_CONSUMER:
                        rk_con = init_consumer(&kafkaParams_ymq);
                        break;
                    case KAFKA_PRODUCER_CONSUMER:
                        rk = init_producer(&kafkaParams_ymq);
                        rk_con = init_consumer(&kafkaParams_ymq);
                        break;
                    default:
                        kafkaParams_ymq.status = KAFKA_NO_RUN;
                        break;
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

                packet_protocol_types = getInfo_ConfigFile("PACKET_PROTOCOL_TYPES", info, lines);
                if (packet_protocol_types != nullptr) {
                    strcpy(PACKET_PROTOCOL_TYPES, packet_protocol_types);
                } else {
                    strcpy(PACKET_PROTOCOL_TYPES, "./");
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


                packet_protocol_flag = getInfo_ConfigFile("PACKET_PROTOCOL_FLAG", info, lines);
                if (packet_protocol_flag != nullptr) {
                    PACKET_PROTOCOL_FLAG = *packet_protocol_flag - '0';
                } else PACKET_PROTOCOL_FLAG = 0;

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
                    struct stat st{};
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
 * 单个文件结束，进行初始化操作函数 适用于文件夹解析
 */
void single_File_End_Init(){
    regex_dict_map.clear(); //每个文件的线路号清空
}
//尽可能短地计算处理时间，并根据时间控制打印格式//
int calculate_cost_time(char* end_time_t,char* begin_time_t){
    int cut_length = 20;
    for(int i = 0; i <= 20; i++){
        if(end_time_t[i] != begin_time_t[i]){
            cut_length = i;
            break;
        }
    }
    std::string end = end_time_t;
    std::string begin = begin_time_t;
    std::string end_ms= end.substr(cut_length);
    std::string begin_ms= begin.substr(cut_length);

    return  strtol(end_ms.c_str(), nullptr,10) - strtol(begin_ms.c_str(), nullptr,10);

}

/**
 * 程序结束的最后操作。01
 */
void change_result_file_name() {
    std::string filepath_str = RESULT_PATH;
    std::string oldName_t = filepath_str + "result-" + global_time_str + ".writting";
    std::string newName_t = filepath_str + "result-" + global_time_str + ".txt";
    rename(oldName_t.c_str(), newName_t.c_str());

    //std::time_t end_time = std::time(nullptr);
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    std::time_t end_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    std::string end_time_str = numtos((u_long) end_time);
    char begin_time_t[20];
    char end_time_t[20];
    strcpy(end_time_t,end_time_str.c_str());
    g_print("结束时间戳：%s \n", end_time_t);
    strcpy(begin_time_t,global_time_str.c_str());
    //int begin_time = (int)strtol(global_time_str.c_str(), nullptr,0);
    long int cost_time = calculate_cost_time(end_time_t,begin_time_t);
    if(cost_time >= 1000){
        int ms = cost_time %1000;
        g_print("总计耗时：%ld s %d ms\n", cost_time/1000,ms);
    }else{
        g_print("总计耗时：%ld ms\n", cost_time);
    }
    curl_global_cleanup();  //在结束libcurl使用的时候，用来对curl_global_init做的工作清理。类似于close的函数
}


/**
 * 程序结束的最后操作。02 释放一些数据结构，仅释放一次。
 */
void clean_Temp_Files_All() {
    if (!mutex_final_clean_flag) {
        if(!rtp_stream_pFile_map.empty()){
            //rtp map not null
            for (auto &i :rtp_stream_pFile_map) {
                g_hash_table_destroy(i.second.decoders_hash);//这里得释放掉。
                fclose(i.second.fp);//关闭打开的文件句柄
            }
        }
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

        //释放240字节的value内存空间
        g_free(value_240);

        pFile_map.clear();
        /*最终初始化互斥变量*/
        mutex_final_clean_flag = 1;
    }
}

/**
 *程序快结束后，流信息清空（如h263）。在流统计输出初始化之后初始化。
 */
void followConnectFiveEleClear(){
    g_thread_pool_free(handleStreamTpool, false, true); //主线程等待线程池任务全部执行完毕后再退出。

    //程序退出时的rtp缓存的清空和配对
    for (auto &it : rtpTotalBuffer) {
        unsigned long len = it.second.data.get_len();
        if(len>MIN_AUDIO_SIZE){
            if (fwrite(it.second.data.get_data(), sizeof(guint8), len, it.second.fp) != len) {
                g_print("rtp write error ! -> %s\n", it.second.fp_path.c_str());
            }
            it.second.data.clear();
            fclose(it.second.fp); // 写完就关闭掉
            rtpVoiceMatching(it.second);//判断话音是否要配对
        }
        else{
            fclose(it.second.fp);
            if(!it.second.fp_path.empty()) remove(it.second.fp_path.c_str());
        }
    }
    rtpTotalBuffer.clear();//rtp配对清空
    std::vector<rtpMatchingInfo>::iterator it;
    for (it = rtpMachingVec.begin();it != rtpMachingVec.end(); it++ ){

        int payloadType_i = -1;
        for (int i = 0;i < 128;i++){
            if(strcmp(it->rtpPayloadType.c_str(),rtp_payload_type_to_str[i]) == 0){
                payloadType_i = i;
                break;
            }
        }
        char single_fp_path_t[256];
        strcpy(single_fp_path_t,it->fp_path.c_str());
        call_decode_by_i(payloadType_i,single_fp_path_t,nullptr);//对没有对家的文件进行解码//
    }
    rtpMachingVec.clear();

    final_Follow_Write_Need.clear();
}

/**
 *  用于输出一些特殊的非叶子结点
 * @param fieldName 字段名称

 * @return true/false
 */

gboolean is_special_not_leafNode(const char *fieldName){
    for (auto &i :special_not_leafNode) {  //special_not_leafNode 列表在上面定义20211217 MZY
        if(i == fieldName)
            return true;
    }
    return false;
}

bool need_special_field(const char* field, proto_node *node, char* ret){
    for(auto & i : regist_speical_filed){
        if (strcmp(field, i.field_name) == 0){
            i.special_field_cb(node, ret);
            return true;
        }
    }
    return false;
}
static bool get_isis_lsp_ip_reachability_ipv4_prefix_mask(proto_node *node, char* ret){
    /* field: isis_lsp_ip_reachability_ipv4_prefix
     * example rep : IPv4 prefix: 10.0.10.0/30
     * */

    if (node->finfo && node->finfo->rep){
        char *cc_ptr = strrchr(reinterpret_cast<char *>(node->finfo->rep->representation), ':');
        if(strlen(cc_ptr)>1){
            strcpy(ret, cc_ptr+2);
            return true;
        }
    }
    return false;
}
//清空当前关于conversation协议栈的缓存，每处理完一个文件后执行
void final_conversation_Write_Need_clear(){
    final_conversation_Write_Need.clear();

    return;
}
//在conversation协议栈的缓存vector中匹配协议栈，写入conversation
gboolean add_protocolStack_to_conversation(char *src_ip,char *dst_ip, char *src_port,char *dst_port){
    std::string proto_stack_t;

    for (auto &i : final_conversation_Write_Need){
        if(strcmp(src_ip,i.sip.c_str()) == 0 and strcmp(dst_ip,i.dip.c_str()) == 0 and strcmp(src_port,i.sport.c_str()) == 0 and strcmp(dst_port,i.dport.c_str()) == 0 ){
            proto_stack_t = i.protocol_stack;


        }
    }
    cJSON_AddStringToObject(write_in_files_conv_cJson, "protocol_stack", proto_stack_t.c_str());
    return true;
}

char* add_line_no_to_conversation (char *src_ip,char *dst_ip, char *src_port,char *dst_port){
    char return_path[256] = {};
    std::string line_no_t;
    std::string read_file_path_t;
    for (auto &i : final_conversation_Write_Need){
        if(strcmp(src_ip,i.sip.c_str()) == 0 and strcmp(dst_ip,i.dip.c_str()) == 0 and strcmp(src_port,i.sport.c_str()) == 0 and strcmp(dst_port,i.dport.c_str()) == 0){
            line_no_t = i.line_no;
            read_file_path_t = i.read_file_path;
            break;

        }
    }
    cJSON_AddStringToObject(write_in_files_conv_cJson, "line_no", line_no_t.c_str());
    cJSON_AddStringToObject(write_in_files_conv_cJson, "file_path", read_file_path_t.c_str());
    strcpy(return_path,read_file_path_t.c_str());
    return return_path;
}

void  clear_conversation_CJSN(){
    cJSON_Delete(write_in_files_conv_cJson);
    write_in_files_conv_cJson = cJSON_CreateObject();
}

void write_into_all_diy_proto(char* pre_proto,char* next_proto){
    if(*next_proto){
        diy_proto_stack diyproto_t;
        diyproto_t.pre_potocol = pre_proto;
        diyproto_t.next_protocol = next_proto;
        all_diy_protol.push_back(diyproto_t);
    }
}

gboolean match_all_diy_proto(char* pre_proto,char* next_proto){
    for (auto &i:all_diy_protol){
        if(strcmp(pre_proto,i.pre_potocol.c_str())==0 and strcmp(next_proto,i.next_protocol.c_str())==0){
            return true;
        }
    }
    return false;
};


