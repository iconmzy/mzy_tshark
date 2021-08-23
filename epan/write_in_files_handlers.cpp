//
// Created by root on 21-6-16.
//

#include "write_in_files_handlers.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <exceptions.h>
#include "cJSON.h"
#include "epan_dissect.h"
#include <sys/stat.h>
#include <map>
#include <ctime>
#include <unistd.h>

/*常用的一些字符串*/
#define str_Protocol_in_frame "[Protocols in frame:"
#define str_FILES_RESOURCE "fileResource"

extern void fill_label_number(field_info *fi, gchar *label_str, gboolean is_signed);
 /*即将写进文件的协议*/
static  std::string  write_in_files_proto = "";
 /*内容缓存*/
static std::string write_in_files_stream = "";
static cJSON *write_in_files_cJson = cJSON_CreateObject();
static cJSON *pro_cJson = cJSON_CreateObject();
 /*存放当前数据包的协议栈*/
static std::vector<std::string> proto_array;
/*缓存会话数据内容*/
static cJSON *write_in_files_conv_cJson = cJSON_CreateObject();
static std::string conv_path_t = "";


char EXPORT_PATH[256] = {0};
//char read_File_Path[256];
gboolean WRITE_IN_FILES_CONFIG = 1;
gboolean DISPLAY_PACKET_INFO_FLAG = 0;
gboolean WRITE_IN_CONVERSATIONS_FLAG = 1;
gboolean EDIT_FILES_DISSECT_FLAG = 0;

char WRITE_IN_CONVERSATIONS_PATH[256] = {0};
gboolean PACKET_PROTOCOL_FLAG = 0;
char PACKET_PROTOCOL_TYPES[256] = {0};
char PACKET_PROTOCOL_PATH[256] = {0};
int EDIT_FILES_PROCESS_NUM = 6;

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

static std::string global_time_str;  // long int types

static __u_long Frame_Number= 0;
static __u_char protocol_Content_Level = 0;
static __u_char protocol_Content_Begin_FLag = 0;
/*最终的初始化互斥变量1代表已经初始化过一次*/
static gboolean mutex_final_clean_flag = 0;

typedef enum {
   GOT_NOTHING,
   GOT_FILE_PATH,
   GOT_IP_TYPES,
   GOT_LINK_TYPES
} Stream_Head_Fileds_Content;
Stream_Head_Fileds_Content stream_head_fileds_contents = GOT_NOTHING;

struct pro_Child_Node{
    struct pro_Child_Node * child;
    struct pro_Child_Node * next;
    std::string key;
    std::string value;
    /*type 1表示node节点，0表示数据节点(默认为0),   77表示根结点 根结点的value表示level注意要进行转换*/
    gboolean type;
};
static pro_Child_Node *pro_tree_head;
/*批量插入的链表*/
struct insertManyProtocolStream{
    struct insertManyProtocolStream * next;
    struct insertManyProtocolStream * pre;
    std::string contents;
    std::string protocol;
    int times;
};
static insertManyProtocolStream *insertmanystream_Head;

//strname的重复次数，头文件times为-1
struct strNameSameLevel{
    std::string str_name;
    struct strNameSameLevel *next;
    u_int times;
};
struct strNameSameLevel *strname_head;

void init_Pro_Child_Node(struct pro_Child_Node * temp){
    temp->key = "";
    temp->value = "";
    temp->type = 0;
    temp->child = NULL;
    temp->next = NULL;
}
void init_Str_Name_Node(struct strNameSameLevel * temp){
    temp->next = NULL;
    temp->times = 0;
    temp->str_name = "";
}

std::string ltos(__u_long l);
std::string ltos(u_int l);

/**
 * 将key value插入协议树中
 * @param key
 * @param value
 * @param level
 * @return
 */
gboolean insertProtocolNodeInHead(std::string &key,std::string &value,int &level){
    g_assert(level > std::stoi(pro_tree_head->value));
    struct pro_Child_Node * temp = new pro_Child_Node;
    init_Pro_Child_Node(temp);
    temp->key = key;
    temp->value = value;

    if(pro_tree_head->child == NULL ){
        if(level - std::stoi(pro_tree_head->value) == 1){
        /*第一个孩子*/
        pro_tree_head->child = temp;
        return true;
        } else{
            return false;
        }
    }
    struct pro_Child_Node * pre_index = pro_tree_head;
    struct pro_Child_Node * index = pro_tree_head->child; //index永远指向该层的最右边
    while (index->next != NULL){
        index = index->next;
    }
    for (int i = level - std::stoi(pro_tree_head->value); i >1 ; --i) {
        /*找树的最右节点*/
        while (pre_index->next != NULL){
            pre_index = pre_index->next;
        }
        while (index->next != NULL){
            index = index->next;
        }
        pre_index = index;
         index = index->child;
    }
    if(index == NULL){
        /*对应层数的第一个节点*/
        while (pre_index->next != NULL){
            pre_index = pre_index->next;
        }
        pre_index->child = temp;
        pre_index->type = 1;
        return true;
    } else{
        while (index->next != NULL){
            index = index->next;
        }
        index->next = temp;
        return true;
    }
}

/**
 * 返回字段名称
 * @param strname 字段名称
 * @param level 层次
 * @return
 */
std::string gotStrNameByStrName(std::string &strname){

    if(strname_head->next == NULL){
        struct strNameSameLevel *temp = new struct strNameSameLevel;
        temp->next = strname_head->next;
        temp->times = 0;
        temp->str_name = strname;
        strname_head->next = temp;
        return strname;
    } else{
        struct strNameSameLevel *temp = strname_head->next;
        while(temp!=NULL){
            if(temp->str_name.compare(strname) == 0){
                temp->times++;
                return strname +"_"+ ltos(temp->times);
            }
            temp =temp->next;
        }
        if(temp == NULL){
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

void initStrNameLevelLinkList(struct strNameSameLevel * node){
    if(node != NULL){
        initStrNameLevelLinkList(node->next);
        delete(node);
    }
}

void initProtocolTree(struct pro_Child_Node * node){
    if(node !=NULL){
        initProtocolTree(node->child);
        initProtocolTree(node->next);
        delete(node);
    }
}


/**
 * 会话还原相关变量
 */
//smtp -----------------begin
static u_int conversation_Frame_Number = 0;
typedef enum {
    DEFAULT_CONNECT,
    CLIENT_SEND_SYN,
    CLIENT_RECEV_SYN_ACK,
    CLIENT_SEND_ACK,
    CONNECT_ESTABLISHED,


    CLIENT_RECV_SERVER_CLOSED_1, //Response code 221
    CLIENT_RECV_FIN_ACK_1,
    CLIENT_SEND_FIN_ACK_1,
    CLIEN_RECV_ACK_1,

    CLIENT_ACURIED_CLOSED_2, //客户端主动请求关闭
    CLIENT_SEND_FIN_ACK_2,
    CLIENT_RECV_ACK_2,
    CLIENT_RECV_FIN_ACK_2,
    CLIENT_SEND_ACK_2,

    CONVERSATION_CLOSED,
}CONNECT_STATUS_FLAG;
/*头插法双向链表*/
struct conversation_Connect_Total{
    struct conversation_Connect_Total * next;
    struct conversation_Connect_Total * pre;
    std::string client_ip_cct;
    int client_port_cct;
    std::string server_ip_cct;
    int server_port_cct;
    CONNECT_STATUS_FLAG status_cct;
    FILE * fp;
};
static conversation_Connect_Total *conversation_Head;
static conversation_Connect_Total *conversation_Temp;
static u_char get_Information_status_flag = 0;
//当前包是客户端client 1还是服务端server 0，
static gboolean current_Packet_Conversation_Is_CLient = 1;
static std::string conversation_proto;
static u_char smtp_Response_Level = 1;
static std::string smtp_Response_Code_str = "";
static u_short smtp_Text_Line_Number = 0;
//smtp -----------------end

void deleteConversationNode(struct conversation_Connect_Total *temp){
    if(temp!= NULL){
        if(temp->fp != NULL) fclose(temp->fp);
        temp->next->pre = temp->pre;
        temp->pre = temp->next;
        delete temp;
        return;
    } else
        return;
}
void replace_CR_CF_String(std::string & str){
    /*将末尾"\\r\\n变成\r\n，如果不含有，则添加\r\n"*/
    if(str.length() < 4) return;
    if(str.substr(str.length()-4).compare("\\r\\n") == 0){
        str = str.substr(0,str.length()-4);
        str += "\r\n";
    } else{
        str += "\r\n";
    }
}
/**
 *协议名称与对应的文件打开的指针map
 */
std::map<std::string,FILE*> pFile_map;
/**
 * 切分string类 ,返回vector<string>
 * @param str
 * @param delim
 * @return
 */
std::vector<std::string> split(const std::string &str, std::string delim){
    std::vector<std::string> res;
    char *source = new char[str.length()+1];
    strcpy(source,str.c_str());
    char *p = strtok(source,delim.c_str());
    while(p){
        res.push_back(p);
        p = strtok(NULL,delim.c_str());
    }
    delete[] source;
    return res;
}
std::string ltos(__u_long l)
{
    std::ostringstream os;
    os<<l;
    std::string result;
    std::istringstream is(os.str());
    is>>result;
    return result;
}
std::string ltos(u_int l)
{
    std::ostringstream os;
    os<<l;
    std::string result;
    std::istringstream is(os.str());
    is>>result;
    return result;
}
/**
 * 判断当前的协议子段是否是最后协议栈最后一个协议，如果是，则返回1，否则返回0，如 arp=Address Resolution Protocol 返回1
 * @param s 协议全名
 * @param jstr 进行判断的协议简称
 * @return
 */
gboolean judge_Protocol_by_string(std::string s,std::string jstr){

    g_assert(jstr.length() > 0);
    /**
     * transform to Capitalization
     */
    std::transform(jstr.begin(),jstr.end(),jstr.begin(),::toupper);
    if(s.compare(0,1,jstr,0,1) != 0){
        return 0;
    }

    gboolean flag = 1;
    std::string str = s;
    ushort length = jstr.length();

    std::vector<char > judge_vector_str;
    judge_vector_str.assign(jstr.begin(),jstr.end());

    std::vector<std::string> temp_vector_str = split(str," ");

    int j =0;
    for (auto i = temp_vector_str.begin(); i !=temp_vector_str.end() and j<length ; ++i,++j) {
        if (i->data()[0] != judge_vector_str[j]){
            flag = 0;
        }
    }
    return flag;
}
gboolean JudgeFrameNumber(gchar* label_str,__u_long& FrameNumber){
    std::string str = label_str;
    if(str.length() >= 30){
        std::string substr = str.substr(0,str.find_first_of(":"));
        std::vector<std::string> str_vector_t;
        str_vector_t = split(substr," ");
        if(str_vector_t[0].compare("Frame") == 0){

            if(str_vector_t[1].compare(ltos(FrameNumber)) == 0){
                FrameNumber +=1;
                return true;
            }
        }
    }
    return false;
}
/**
 * 处理字符串前后的空格
 * @param str
 */
void deleteSPACE_before_end(std::string &str){
    if(str.length() == 0) return;
    int left = 0;
    int right = str.length() -1;
    while (str[left] == ' ' and left < right){
        str = str.substr(left+1);
        left++;
    }
    while (str[right] == ' ' and right>left){
        str = str.substr(0,right);
        right++;
    }
    /*去除开头的": "字符串*/
    if(str.compare(0,2,": ") == 0){
        str = str.substr(2);
    }
    return;
}


/**
 * 返回找到的tcp链接四元组结构体指针
 * @param temp 四元组结构体指针
 * @return struct conversation_Connect_Total*
 */
struct conversation_Connect_Total* gotConversationNodeInfo(struct conversation_Connect_Total* &temp,gboolean &flag){
    if(conversation_Head->next == conversation_Head){
        temp->next = conversation_Head->next;
        conversation_Head->next = temp;
        temp->pre = conversation_Head;
        temp->next->pre = temp;
        flag = 1;
        return temp;
    } else{
        struct conversation_Connect_Total* index_t = conversation_Head->next;
        while (index_t != conversation_Head){
            if(index_t->server_port_cct == temp->server_port_cct and index_t->client_port_cct == temp->client_port_cct and \
            index_t->server_ip_cct == temp->server_ip_cct and index_t->client_ip_cct == temp->client_ip_cct){
                flag = 1;
                return index_t;
            }
            if(index_t->client_ip_cct == temp->server_ip_cct and index_t->client_port_cct == temp->server_port_cct and \
            index_t->server_port_cct == temp->client_port_cct and index_t->server_ip_cct == temp->client_ip_cct){
                flag = 0;
                return index_t;
            }
        }
        temp->next = conversation_Head->next;
        conversation_Head->next = temp;
        temp->pre = conversation_Head;
        temp->next->pre = temp;
        flag = 1;
        return temp;
    }

}
void getFileNames(std::string path,std::vector<std::string>& filenames)
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str()))){
        g_print("json Folder doesn't Exist!");
        return;
    }
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0){
            filenames.push_back(ptr->d_name);
        }
    }
    closedir(pDir);
}
/**
 * 匹配返回下标，为找到返回-1
 * @param s 匹配串
 * @param t 模式串
 * @return
 */
int kmp(std::string s,std::string t)
{
    int i=0,j=-1;
    int slen=s.length(),tlen=t.length();
    int next[tlen];
    //首先求出模式串t的next数组
    next[0]=-1;
    while(i<tlen){
        if(j==-1 || t[i]==t[j]){
            ++i; ++j;
            next[i]=j;
        }
        else
            j = next[j];
    }
    /*
    //输出next数组
    for(i=0;i<tlen;++i){
        cout<<next[i]<<" ";
    }
    cout<<endl;
    */
    //接着根据next数组实现KMP算法
    i=0; j=0;
    while(i<slen && j<tlen){
        if(j==-1||s[i]==t[j])
        {i++;j++;}
        else
            j = next[j];
    }
    if(j==tlen)
        return i-j;
    else
        return -1;
}
/**
 * 返回指向对应协议名的结构体指针 为找到返回NULL
 * @param head  头结点
 * @param protocol 协议名
 * @return
 */
insertManyProtocolStream* insertManyFindProtocol(insertManyProtocolStream* &head,std::string &protocol){
    insertManyProtocolStream * temp = head->next;
    while (temp != head){
        if(temp->protocol.compare(protocol) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
/**
 * 最终的数据流写入对应协议文件
 * @param stream
 * @param protocol
 * @return
 */
gboolean write_Files(std::string &stream,std::string &protocol){

    if (access(EXPORT_PATH, 0) != 0) {
        /*当前协议对应文件夹不存在*/
        if (mkdir(EXPORT_PATH, 0777) != 0) {
            g_print("%s create error", EXPORT_PATH);
        }
    }
    std::string filepath__str_t = EXPORT_PATH + protocol + "/" + protocol + "_" + global_time_str + ".txt";;
    std::string filedirpath_str_t = EXPORT_PATH + protocol;
    char filepath_t[MAXWRITEFILELENGTH] = {0};
    char fileDirPath_t[MAXWRITEFILELENGTH] = {0};

    strcpy(filepath_t, filepath__str_t.c_str());
    strcpy(fileDirPath_t, filedirpath_str_t.c_str());

    if (pFile_map.size() == 0) {
        /*当前是空map*/
        if (access(fileDirPath_t, 0) != 0) {
            /*当前文件夹不存在*/
            if (mkdir(fileDirPath_t, 0777) != 0) {
                g_print("%s create error", fileDirPath_t);
            }
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
                if (mkdir(fileDirPath_t, 0777) != 0) {
                    g_print("%s create error", fileDirPath_t);
                }
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
 * 将会话统计信息写入文件中
 * @param stream
 * @param protocol
 * @return
 */
gboolean write_Files_conv(std::string &stream){

    int n_t = kmp(stream,"\n");
    while ( n_t != -1){
        stream.replace(n_t,1,"");
        n_t = kmp(stream,"\n");
    }
    int t_t = kmp(stream,"\t");
    while (t_t != -1){
        stream.replace(t_t,1,"");
        t_t = kmp(stream,"\t");
    }
    stream.append("\r\n");
    /*这里把json写成一行,且添加换行符 ----end*/

    if (access(WRITE_IN_CONVERSATIONS_PATH, 0) != 0) {
        /*当前协议对应文件夹不存在*/
        if (mkdir(WRITE_IN_CONVERSATIONS_PATH, 0777) != 0) {
            g_print("%s create error", WRITE_IN_CONVERSATIONS_PATH);
        }
    }
    if(conv_path_t.empty()){
        conv_path_t = WRITE_IN_CONVERSATIONS_PATH;
        conv_path_t = conv_path_t + "conv" + global_time_str + ".txt";
    }

    FILE *fp = fopen(conv_path_t.c_str(), "a+");
    if (fp == NULL) {
        g_print("open %s error!\n",conv_path_t.c_str());
        return false;
    }
    fputs(stream.c_str(), fp);
    fflush(fp);
    return true;
}
/**
 * 将数据流steam写入文件，protocol协议
 * @param stream
 * @param protocol
 * @return
 */
gboolean write_All_Temps_Into_Files(std::string& stream,std::string& protocol){

    /*这里把json写成一行,且添加换行符 ----begin*/
    int n_t = kmp(stream,"\n");
    while ( n_t != -1){
        stream.replace(n_t,1,"");
        n_t = kmp(stream,"\n");
    }
    int t_t = kmp(stream,"\t");
    while (t_t != -1){
        stream.replace(t_t,1,"");
        t_t = kmp(stream,"\t");
    }
    stream.append("\r\n");
    /*这里把json写成一行,且添加换行符 ----end*/

    assert(protocol.compare("") != 0);

    if(INSERT_MANY_PROTOCOL_STREAM_FLAG){
    /*批量插入标志*/
        insertManyProtocolStream *index_t = insertManyFindProtocol(insertmanystream_Head,protocol);
        if( index_t != NULL){
            /*NOT null*/
            index_t->contents.append(stream);
            if(++index_t->times >= INSERT_MANY_PROTOCOL_STREAM_NUM){
                /*批量插入*/
                if(!write_Files(index_t->contents,protocol)){
                    g_print("%s insert error!\n",protocol.c_str());
                }
                /*批量插入成功后对这个缓存节点清空并释放缓存*/
                index_t->contents.clear();
                index_t->times = 0;
                index_t->pre->next = index_t->next;
                index_t->next->pre = index_t->pre;
                delete index_t;
            }
        } else{
            /*NULL 头插法循环双链表*/
            insertManyProtocolStream * temp = new insertManyProtocolStream;
            temp->protocol = protocol;
            temp->contents.append(stream);
            temp->times = 1;
            temp->next = insertmanystream_Head->next;
            temp->pre = insertmanystream_Head;
            insertmanystream_Head->next = temp;
            temp->next->pre = temp;
        }
    }
    else {
       if(!write_Files(stream,protocol)){
            g_print("%s insert error !\n",protocol.c_str());
       }
    }

    stream = "";
    return true;
}

/**
 * 所有参数初始化
 * @return
 */
gboolean initial_All_para(){
    TRY{
//                write_in_files_stream = "";
                write_in_files_proto = "";
                protocol_Content_Level = 0;
                protocol_Content_Begin_FLag = 0;
                stream_head_fileds_contents = GOT_NOTHING;

                /*初始化部分要用到的 json对象 ----begin*/
                cJSON_Delete(write_in_files_cJson);
                cJSON_Delete(pro_cJson);
                write_in_files_cJson = cJSON_CreateObject();
                pro_cJson = cJSON_CreateObject();
                /*初始化部分要用到的 json对象 ----end*/

                /*需要初始化协议树*/
                initProtocolTree(pro_tree_head);
                pro_tree_head = new struct pro_Child_Node;
                pro_tree_head->child = NULL;
                pro_tree_head->type = 77;
                pro_tree_head->value = "";
                pro_tree_head->next = NULL;
                pro_tree_head->key = "";

                /*需要初始化strname链表*/
                initStrNameLevelLinkList(strname_head);
                strname_head = new struct strNameSameLevel;
                strname_head->next = NULL;
                strname_head->times = 0;
                strname_head->str_name = "";
                return true;

    }
    CATCH(OutOfMemoryError){
        g_print("initialize error");
        return false;
    }
    ENDTRY;
    return true;
}
/**
 * 将全局变量协议树的内容写入cJSON中。从根结点的第一个孩子开始递归
 * @param json_t
 * @return
 */
gboolean proTocolTreeDataIntoJson(cJSON* &json_t, struct pro_Child_Node * &tree){
    /*过滤根结点*/
    if(tree->type == 77 and tree->child == NULL) {
        return true;
    }

    struct pro_Child_Node *index = tree;
    if(index->type == 0){
        /*当前是数据节点*/
        if(index->child != NULL) {
            g_print("%s protocol tree node type error!\n ", index->key.c_str());
            return false;
        }

        cJSON_AddStringToObject(json_t,index->key.c_str(),index->value.c_str());
        if (index->next != NULL){
            index = index->next;
            if(!proTocolTreeDataIntoJson(json_t,index)){
                g_print("%s protocol tree node type error!\n",index->next->key.c_str());
                return false;
            }
        }
    } else if (index->type == 1){
        /*当前是node节点，*/
        g_assert(index->child != NULL);
        cJSON * t = cJSON_CreateObject();
        proTocolTreeDataIntoJson(t,index->child);
        cJSON_AddItemToObject(json_t, index->key.c_str(),t);

        if (index->next != NULL){
            index = index->next;
            proTocolTreeDataIntoJson(json_t,index);
        }
        return true;
    }
    return true;
}
/*写文件入口*/
void do_write_in_files_handler(gchar* label_ptr, const gchar* abbrev,const gchar *name,int level){
    if(strcmp(label_ptr,"") == 0){
        return;
    }
    std::string str_abbrev = abbrev;
    std::string abbrev_str_app_t = abbrev_t;
    std::string str = label_ptr;
    std::string str_name = name;
    if(str_abbrev.compare("frame") == 0) {

        if (Frame_Number >= 1) {
//            Frame_Number +=1;
//            if(Frame_Number <= 3) return;
            /*处理协议树的内容入json中 */
            if (pro_tree_head->child != NULL) {
                /*协议树有内容*/
                if (!proTocolTreeDataIntoJson(write_in_files_cJson, pro_tree_head->child)) {
                    g_print("%s protocol tree data into json error!\n", write_in_files_proto.c_str());
                    return;
                }

                write_in_files_stream = cJSON_Print(write_in_files_cJson);
                    if (!write_All_Temps_Into_Files(write_in_files_stream, write_in_files_proto)) {
                        g_print("write in files error");
                        return;
                    }
                if (!initial_All_para()) {
                    g_print("initialize error!");
                    return;
                }
            }
        }
        Frame_Number+=1;
        return;
    }
    /*获取路径来源 */
    if (stream_head_fileds_contents == GOT_NOTHING) {
        if (read_Pcap_From_File_Flag == 1) {
             /*当前是读文件来的，需要一开始就把文件路径写入write_stream里面*/
            if (strlen(read_File_Path) == 0) {
                g_print("read_Pcap_From_File_Flag = 1,but read_File_Path = \"\" ");
            } else {
                std::string str_t = read_File_Path;
                deleteSPACE_before_end(str_t);
                cJSON_AddStringToObject(write_in_files_cJson,str_FILES_RESOURCE,str_t.c_str());
            }
        } else {
            /*否则添加为在线实时获取*/
             cJSON_AddStringToObject(write_in_files_cJson,str_FILES_RESOURCE,"onLine");
        }
        stream_head_fileds_contents = GOT_FILE_PATH;
    }

    /*帧头相关信息*/
    if(str_abbrev.compare("frame.protocols") == 0 and level ==1){
        /*获取当前协议栈*/
        if (!str.compare(0, 20, str_Protocol_in_frame, 0, 20)) {
            proto_array = split(str.substr(21, str.length() - 22), ":");
            /**
             * 确保获取协议栈里面的最后个协议,"data"字符串也除开
             */
            for (int i = proto_array.size() - 1; i >= 0; i--) {
                write_in_files_proto = proto_array[i];
//                这里把协议最后的解析字段去掉
                if (write_in_files_proto.compare("") == 0 or kmp(write_in_files_proto,"data") != -1) {
                    continue;
                } else {
                    break;
                }
            }
            pro_tree_head->key = write_in_files_proto;

            std::string value_t = str.substr(str.find_first_of(":")+2);
            value_t = value_t.substr(0,value_t.length()-1);
            deleteSPACE_before_end(value_t);
            cJSON_AddStringToObject(write_in_files_cJson,"protocols",value_t.c_str());
        }
        return;
    }
    if(str_abbrev.compare("frame.encap_type") == 0 and level == 1){
        std::string value_t = str.substr(str.find_first_of(":") +1);
        deleteSPACE_before_end(value_t);
        cJSON_AddStringToObject(write_in_files_cJson,"frame.encap_type",value_t.c_str());
        return;
    }
    if(str_abbrev.compare("frame.time_epoch") == 0 and level == 1){
        std::string value_t = str.substr(str.find_first_of(":"),str.length()-20);
        deleteSPACE_before_end(value_t);
        cJSON_AddStringToObject(write_in_files_cJson,"frame.time_epoch",value_t.c_str());
        return;
    }
//    frame.len
    if(str_abbrev.compare("frame.len") == 0 and level == 1){
        std::string value_t = str.substr(str.find_first_of(":")+2,kmp(str,"bytes")-14);
        deleteSPACE_before_end(value_t);
        cJSON_AddStringToObject(write_in_files_cJson,"frame.len",value_t.c_str());
        return;
    }

    if(str_abbrev.compare("eth.dst") == 0 and level == 1){
        std::string value_t = str.substr(str.find_first_of(":")+2);
        deleteSPACE_before_end(value_t);
        cJSON_AddStringToObject(write_in_files_cJson,"eth.dst",value_t.c_str());
        return;
    }
    if(str_abbrev.compare("eth.src") == 0 and level == 1){
        std::string value_t = str.substr(str.find_first_of(":")+2);
        deleteSPACE_before_end(value_t);
        cJSON_AddStringToObject(write_in_files_cJson,"eth.src",value_t.c_str());
        return;
    }


    /*拿通信四元组 ----------begin*/
    /*ip.src*/
    if(str_abbrev.compare("ip.src") == 0 or str_abbrev.compare("ipv6.src") == 0){
        std::string value_t = str.substr(str.find_first_of(":")+2);
        deleteSPACE_before_end(value_t);
        cJSON_AddStringToObject(write_in_files_cJson,"ip.src",value_t.c_str());
        return;
    }
    /*ip.dst ipv6.src*/
    if(str_abbrev.compare("ip.dst") == 0 or str_abbrev.compare("ipv6.dst") == 0){
        std::string value_t = str.substr(str.find_first_of(":") +2);
        deleteSPACE_before_end(value_t);
        cJSON_AddStringToObject(write_in_files_cJson,"ip.dst",value_t.c_str());
        return;
    }
    /*tcp.srcport udp.srcport*/
    if(str_abbrev.compare("tcp.srcport") == 0 or str_abbrev.compare("udp.srcport") == 0){
        std::string value_t = str.substr(str.find_first_of(":")+2);
        deleteSPACE_before_end(value_t);
        cJSON_AddStringToObject(write_in_files_cJson,"srcport",value_t.c_str());
    }
    /*tcp.dstport udp.dstport*/
    if(str_abbrev.compare("tcp.dstport") == 0 or str_abbrev.compare("udp.dstport") == 0){
        std::string value_t = str.substr(str.find_first_of(":") +2);
        deleteSPACE_before_end(value_t);
        cJSON_AddStringToObject(write_in_files_cJson,"dstport",value_t.c_str());
    }
    /*拿通信四元组 ----------end*/

    /*拿解析协议内容 --------------begin*/
    if(str_abbrev.compare(write_in_files_proto) == 0){
//        text rip.version rip
        protocol_Content_Begin_FLag = true;
        protocol_Content_Level = level;
        pro_tree_head->value = ltos((u_int)level);
        return;
    }
    if(protocol_Content_Begin_FLag){
        /*生成的字段不统计*/
        if (str.find_first_of('[', 0) == 0 and str.find_last_of("]") == str.length() - 1) return;
        if(level > protocol_Content_Level){
            /*当前是协议的子字段 dns.flags.response*/
//            str_name = gotStrNameByStrName(str_name,level);
            std::string value_t;
            value_t = str.substr(str.find_first_of(":") + 1);
            deleteSPACE_before_end(value_t);
            insertProtocolNodeInHead(str_name,value_t,level);
        }
    }
    /*拿解析协议内容 --------------end*/
}

/**
 * 递归处理协议解析树内容，存入json中。
 * @param json_t
 * @param node
 */
gboolean dissect_edt_Tree_Into_Json(cJSON *&json_t,proto_node *&node){
    /*key的置换和获取*/
    std::string key_str = node->finfo->hfinfo->abbrev;
    while (key_str.find(".") != key_str.npos){
        key_str.replace(key_str.find("."),1,"_");
    }
    key_str = gotStrNameByStrName(key_str);

    if(node->first_child == NULL or node->last_child == NULL){
        /*数据节点*/

        /*以太网MTU最大1500，除开网络层头20，TCP头20字节，1460，udp头8字节，MSS为1472，这里取最大1472+1终止位*/
        gchar value[1473] = {'\0'};
        yy_proto_item_fill_label(node->finfo,value);
        cJSON_AddStringToObject(json_t,key_str.c_str(),value);

        if(node->next !=NULL){
            proto_node* index = node->next;
            if(!dissect_edt_Tree_Into_Json(json_t,index)){
             g_print("%s dissect_edt_Tree_Into_Json error!\n",key_str.c_str());
                return false;
            }
        }
        else{
            return true;
        }
    } else{
        /*还有子节点*/
        cJSON *t = cJSON_CreateObject();
        dissect_edt_Tree_Into_Json(t,node->first_child);
        cJSON_AddItemToObject(json_t,key_str.c_str(),t);

        if(node->next != NULL){
            proto_node* index = node->next;
            dissect_edt_Tree_Into_Json(json_t,index);
        } else{
            return true;
        }
    }
    return true;
}
/**
 * 直接解析edt 写入文件缓存中 202107290910
 * @param edt
 * @return
 */
gboolean dissect_edt_into_files(epan_dissect_t* edt){
    g_assert(edt!= NULL);
    if(edt->tree == NULL)
        return false;
    proto_node *node = edt->tree->first_child;
    std::string protocol_stack_t = "";
    proto_node *stack_node_t = node;
    while (stack_node_t != NULL){
        field_info *fi = stack_node_t->finfo;
        if(strcmp(fi->hfinfo->abbrev,"communityid") == 0) {
            stack_node_t = stack_node_t->next;
            continue;
        }

        if(protocol_stack_t.empty() == 1){
            protocol_stack_t.append(fi->hfinfo->abbrev);
            write_in_files_proto = fi->hfinfo->abbrev;
        } else{
            protocol_stack_t.append(",");
            protocol_stack_t.append(fi->hfinfo->abbrev);
            write_in_files_proto = fi->hfinfo->abbrev;
        }
        stack_node_t = stack_node_t->next;
    }
    /*单独的协议过滤*/
    if(kmp("[tcp],[udp],[data]","["+ write_in_files_proto +"]") != -1){
        return true;
    }


    /*获取文件来源*/
    if(read_Pcap_From_File_Flag == 1){
        if(strlen(file_Name_t) == 0){
            /*存在文件名*/
            strcpy(read_File_Path,file_Name_t);
            cJSON_AddStringToObject(write_in_files_cJson,str_FILES_RESOURCE,read_File_Path);
        } else{
            cJSON_AddStringToObject(write_in_files_cJson,str_FILES_RESOURCE,read_File_Path);
        }
    } else{
        cJSON_AddStringToObject(write_in_files_cJson,str_FILES_RESOURCE,"onLine");
    }
    /*协议栈*/
    cJSON_AddStringToObject(write_in_files_cJson,"protocols",protocol_stack_t.c_str());

    while(node!= NULL){
        field_info *fi = node->finfo;

        /*帧头*/
        if (strcmp(fi->hfinfo->abbrev, "frame") == 0) {
            proto_node *child = node->first_child; //该层协议的第一个字段
            while (child != NULL){
                /*该层协议具有内容*/
                field_info *child_finfo = child->finfo;
                if(strcmp(child_finfo->hfinfo->abbrev,"frame.encap_type") == 0){
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo,value);
                    cJSON_AddStringToObject(write_in_files_cJson,"frame_encap_type",value);
                    child = child->next;
                    continue;
                }
                if(strcmp(child_finfo->hfinfo->abbrev,"frame.time_epoch") == 0){
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo,value);
                    cJSON_AddStringToObject(write_in_files_cJson,"frame_time_epoch",value);
                    child = child->next;
                    continue;
                }
                if(strcmp(child_finfo->hfinfo->abbrev,"frame.len") == 0){
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo,value);
                    cJSON_AddStringToObject(write_in_files_cJson,"frame_len",value);
                    child = child->next;
                    continue;
                }
                child = child->next;
            }
            node = node->next;
            continue;
        }
        /*eth*/
        if(strcmp(fi->hfinfo->abbrev,"eth") == 0){
            proto_node *child = node->first_child;
            while (child != NULL){
                field_info *child_finfo = child->finfo;
                if(strcmp(child_finfo->hfinfo->abbrev,"eth.dst") == 0){
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo,value);
                    cJSON_AddStringToObject(write_in_files_cJson,"eth_dst",value);
                    child = child->next;
                    continue;
                }
                if(strcmp(child_finfo->hfinfo->abbrev,"eth.src") == 0){
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo,value);
                    cJSON_AddStringToObject(write_in_files_cJson,"eth_src",value);
                    child = child->next;
                    continue;
                }
                child = child->next;
            }
            node = node->next;
            continue;
        }
        /*ip ipv6 */
        if(strcmp(fi->hfinfo->abbrev,"ip") == 0 or strcmp(fi->hfinfo->abbrev,"ipv6") == 0){
            proto_node *child = node->first_child;
            while (child != NULL){
                field_info *child_finfo = child->finfo;
                if(strcmp(child_finfo->hfinfo->abbrev,"ip.src") == 0 or strcmp(child_finfo->hfinfo->abbrev,"ipv6.src") == 0){
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo,value);
                    cJSON_AddStringToObject(write_in_files_cJson,"ip_src",value);
                    child = child->next;
                    continue;
                }
                if(strcmp(child_finfo->hfinfo->abbrev,"ip.dst") == 0 or strcmp(child_finfo->hfinfo->abbrev,"ipv6.dst") == 0){
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo,value);
                    cJSON_AddStringToObject(write_in_files_cJson,"ip_dst",value);
                    child = child->next;
                    continue;
                }
                child = child->next;
            }
            node = node->next;
            continue;
        }
        /*tcp udp*/
        if(strcmp(fi->hfinfo->abbrev,"tcp") == 0 or strcmp(fi->hfinfo->abbrev,"udp") == 0){
            proto_node *child = node->first_child;
            while (child != NULL){
                field_info *child_finfo = child->finfo;
                if(strcmp(child_finfo->hfinfo->abbrev,"tcp.srcport") == 0 or strcmp(child_finfo->hfinfo->abbrev,"udp.srcport") == 0){
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo,value);
                    cJSON_AddStringToObject(write_in_files_cJson,"srcport",value);
                    child = child->next;
                    continue;
                }
                if(strcmp(child_finfo->hfinfo->abbrev,"tcp.dstport") == 0 or strcmp(child_finfo->hfinfo->abbrev,"udp.dstport") == 0){
                    gchar value[240] = {'\0'};
                    yy_proto_item_fill_label(child_finfo,value);
                    cJSON_AddStringToObject(write_in_files_cJson,"dstport",value);
                    child = child->next;
                    continue;
                }
                child = child->next;
            }
            node = node->next;
            continue;
        }
        /*最后层协议的解析*/
        if(strcmp(fi->hfinfo->abbrev,write_in_files_proto.c_str()) == 0){
            proto_node *child = node->first_child;
            if(child != NULL){
                try {
                    dissect_edt_Tree_Into_Json(write_in_files_cJson,child);
                }
                catch (std::invalid_argument){
                    node = node->next;
                    continue;
                }
            }
            node = node->next;
            continue;
        }
        node = node->next;
    }

    write_in_files_stream = cJSON_Print(write_in_files_cJson);
    if (!write_All_Temps_Into_Files(write_in_files_stream, write_in_files_proto)) {
        g_print("write in files error");
        return false;
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
void do_write_in_conversation_handler(gchar*key,gchar* value){
    std::string key_str = key;
    std::string value_str = value;
    if(value_str.compare("-1END") == 0){
        /*当前流统计结束*/
        if(write_in_files_conv_cJson->child == NULL)
            return;
        std::string string = cJSON_Print(write_in_files_conv_cJson);
        write_Files_conv(string);
        cJSON_Delete(write_in_files_conv_cJson);
        write_in_files_conv_cJson = cJSON_CreateObject();
    } else{
        cJSON_AddStringToObject(write_in_files_conv_cJson,key_str.c_str(),value_str.c_str());
    }
}
/**
 * 初始化拿json的map数据，正常取值返回1，否则返回0，flag为0表示没有初始化，为1表示已初始化。
 * @param flag
 * @return
 */
gboolean initWriteJsonFiles(char* flag){

//    这里把同级的level的strname初始化
    strname_head = new struct strNameSameLevel;
    strname_head->next = NULL;
    strname_head->str_name  = "";
    strname_head->times = 0;

//    把协议树初始化一下
    pro_tree_head = new struct pro_Child_Node;
    pro_tree_head->child = NULL;
    pro_tree_head->type = 77;
    pro_tree_head->value = "";
    pro_tree_head->next = NULL;
    pro_tree_head->key = "";
//    这里顺便把conversation的也初始化了
    if(WRITE_IN_CONVERSATIONS_FLAG){
        conversation_Head = new  conversation_Connect_Total;
        conversation_Head->next = conversation_Head;
        conversation_Head->pre = conversation_Head;
    }

    /*批量插入初始化头部节点*/
    if(INSERT_MANY_PROTOCOL_STREAM_FLAG == 1){
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
 * 获取读取configfiles的状态.
 * @return
 */
gboolean readConfigFilesStatus(){
    TRY {
                std::string temp_str_json_path;
                std::string temp_str_export_path;
                char *write_in_files_config;
                char *write_in_conversations_flag;
                char *write_in_conversation_path;
                char *packet_protocol_flag;
                char *packet_protocol_types;
                char *packet_protocol_path;
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
                char *edit_files_process_num;
                char *insert_many_protocol_stream_flag;
                char *insert_many_protocol_stream_num;

//WS_DLL_PUBLIC gboolean PACKET_PROTOCOL_FLAG;
//WS_DLL_PUBLIC char PACKET_PROTOCOL_TYPES[256];
//WS_DLL_PUBLIC char PACKET_PROTOCOL_PATH[256];

                /**
                 * 这里需要把当前运行的时间戳定下来
                 */
                std::time_t global_time = std::time(0);
                global_time_str = ltos((u_long)global_time);
                g_print("current files time %s \n",global_time_str.c_str());

                char **fileData = NULL;
                int lines = 0;
                struct ConfigInfo *info = NULL;

                loadFile_ConfigFile(CONFIG_FILES_PATH, &fileData, &lines);
                parseFile_ConfigFile(fileData, lines, &info);

//                packet_protocol_path = getInfo_ConfigFile("PACKET_PROTOCOL_PATH", info, lines);
//                if (packet_protocol_path != NULL) {
//                    strcpy(PACKET_PROTOCOL_PATH,packet_protocol_path);
//                    int len = strlen(PACKET_PROTOCOL_PATH);
//                    if(PACKET_PROTOCOL_PATH[len-1] != '/'){
//                        strcat(PACKET_PROTOCOL_PATH,"/");
//                    }
//                } else {
//                    strcpy(PACKET_PROTOCOL_PATH,"./");
//                }

                packet_protocol_types = getInfo_ConfigFile("PACKET_PROTOCOL_TYPES", info, lines);
                if (packet_protocol_types != NULL) {
                    strcpy(PACKET_PROTOCOL_TYPES,packet_protocol_types);
                } else {
                    strcpy(PACKET_PROTOCOL_TYPES,"./");
                }

                packet_protocol_flag = getInfo_ConfigFile("PACKET_PROTOCOL_FLAG", info, lines);
                if (packet_protocol_flag != NULL) {
                    PACKET_PROTOCOL_FLAG = *packet_protocol_flag - '0';
                } else PACKET_PROTOCOL_FLAG = 0;

                edit_files_process_num = getInfo_ConfigFile("EDIT_FILES_PROCESS_NUM", info, lines);
                if (edit_files_process_num != NULL) {
                    EDIT_FILES_PROCESS_NUM = std::stoi(edit_files_process_num);
                } else EDIT_FILES_PROCESS_NUM = 1000;

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

//                write_in_conversation_path = getInfo_ConfigFile("WRITE_IN_CONVERSATIONS_PATH", info, lines);
//                if (write_in_conversation_path != NULL) {
//                   strcpy(WRITE_IN_CONVERSATIONS_PATH,write_in_conversation_path);
//                    int len = strlen(WRITE_IN_CONVERSATIONS_PATH);
//                    if(WRITE_IN_CONVERSATIONS_PATH[len-1] != '/'){
//                        strcat(WRITE_IN_CONVERSATIONS_PATH,"/");
//                    }
//                } else {
//                    strcpy(WRITE_IN_CONVERSATIONS_PATH,"./");
//                }

                export_path = getInfo_ConfigFile("EXPORT_PATH", info, lines);
                if(export_path != NULL){
                    strcpy(EXPORT_PATH, export_path);
                    int len = strlen(EXPORT_PATH);
                    if(EXPORT_PATH[len-1] != '/'){
                        strcat(EXPORT_PATH,"/");
                    }
                    /*统一将路径全部初始化掉*/
                    strcat(WRITE_IN_CONVERSATIONS_PATH,EXPORT_PATH);
                    strcat(WRITE_IN_CONVERSATIONS_PATH,"conversation/");

                    strcat(PACKET_PROTOCOL_PATH,EXPORT_PATH);
                    strcat(PACKET_PROTOCOL_PATH,"export/");

                    strcat(EXPORT_PATH,"dissectors/");
                } else{
                    strcpy(EXPORT_PATH,"./");
                }

                display_packet_info_flag = getInfo_ConfigFile("DISPLAY_PACKET_INFO_FLAG",info,lines);
                if(display_packet_info_flag != NULL){
                    DISPLAY_PACKET_INFO_FLAG = *display_packet_info_flag - '0';
                } else{
                    DISPLAY_PACKET_INFO_FLAG = 0;
                }

                online_capture_data_flag = getInfo_ConfigFile("ONLINE_CAPTURE_DATA_FLAG",info,lines);
                if(online_capture_data_flag != NULL){
                    ONLINE_CAPTURE_DATA_FLAG = *online_capture_data_flag - '0';
                } else{
                    ONLINE_CAPTURE_DATA_FLAG = 0;
                }

                online_capture_data_device_name = getInfo_ConfigFile("ONLINE_CAPTURE_DATA_DEVICE_NAME", info, lines);
                if(online_capture_data_device_name != NULL){
                    strcpy(ONLINE_CAPTURE_DATA_DEVICE_NAME, online_capture_data_device_name);
                } else{
                    strcpy(ONLINE_CAPTURE_DATA_DEVICE_NAME,"./");
                }

                read_packet_from_files_flag = getInfo_ConfigFile("READ_PACKET_FROM_FILES_FLAG",info,lines);
                if(read_packet_from_files_flag != NULL){
                    READ_PACKET_FROM_FILES_FLAG = *read_packet_from_files_flag - '0';
                } else{
                    READ_PACKET_FROM_FILES_FLAG = 0;
                }

                read_packet_from_files_path = getInfo_ConfigFile("READ_PACKET_FROM_FILES_PATH", info, lines);
                if(read_packet_from_files_path != NULL){
                    strcpy(READ_PACKET_FROM_FILES_PATH, read_packet_from_files_path);
                } else{
                    strcpy(READ_PACKET_FROM_FILES_PATH,"./");
                }

                json_add_proto = getInfo_ConfigFile("JSON_ADD_PROTO",info,lines);
                if(json_add_proto != NULL){
                    JSON_ADD_PROTO = *json_add_proto - '0';
                } else{
                    JSON_ADD_PROTO = 0;
                }

                json_add_proto_path = getInfo_ConfigFile("JSON_ADD_PROTO_PATH", info, lines);
                if(json_add_proto_path != NULL){
                    strcpy(JSON_ADD_PROTO_PATH, json_add_proto_path);
                } else{
                    strcpy(JSON_ADD_PROTO_PATH,"./defaul.json");
                }

                destroInfo_ConfigFile(info);

            };
            CATCH_ALL {
                return false;
            }
    ENDTRY;
    return true;
}

void clean_Temp_Files_All() {
    if (!mutex_final_clean_flag) {
       /* if (pro_tree_head != NULL and pro_tree_head->child != NULL) {
            *//*协议树有内容*//*
            if (!proTocolTreeDataIntoJson(write_in_files_cJson, pro_tree_head->child)) {
                g_print("%s protocol tree data into json error!\n", write_in_files_proto.c_str());
                return;
            }
            write_in_files_stream = cJSON_Print(write_in_files_cJson);
            if (!write_All_Temps_Into_Files(write_in_files_stream, write_in_files_proto)) {
                g_print("write in files error");
                return;
            }
            if (!initial_All_para()) {
                g_print("initialize error!");
                return;
            }
        }*/

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
        if(INSERT_MANY_PROTOCOL_STREAM_FLAG == 1){
            insertmanystream_Head = new struct insertManyProtocolStream;
            insertmanystream_Head->next = insertmanystream_Head;
            insertmanystream_Head->pre = insertmanystream_Head;
            insertmanystream_Head->times = 0;
            insertmanystream_Head->protocol = "";
            insertmanystream_Head->contents = "";
        }
        /*最后内存清空*/
        pFile_map.clear();

        /*最终初始化互斥变量*/
        mutex_final_clean_flag = 1;
    }
}
