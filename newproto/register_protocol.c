#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "packet-scoreboard.h"
#include "register_protocol.h"
#include <stdlib.h>


#define SupportJsonNum 10
static int intproto[SupportJsonNum];
static heur_dissector_list_t heur_subdissector_list;
gint ettprotos[SupportJsonNum];
static const value_string names_cmd[] = {
        {0x00, "request score"},
        {0x01, "set score"},
        {0x80, "response score"},
        {0x10, "request color"},
        {0x11, "set color"},
        {0x90, "response color"},
        {0, NULL}};

static dissector_handle_t exproto_handle;
// static struct protoInfo proto[10];
static int exFunIndex = 0;
static int heur_exFunIndex = 0;
static gint dissect_exproto0(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0; //偏移变量，记录偏移位置
    exFunIndex = 0;
    col_set_str(pinfo->cinfo, COL_PROTOCOL, allProtoInfo[exFunIndex].protoName); //显示协议
    col_clear(pinfo->cinfo, COL_INFO);

    if (tree)
    {
        guint8 cmd_result = 0; //用 于保存获取到的操作类型值
        guint8 id_result = 0;
        proto_item *ti = NULL;                                                   //方便添加结点而定义
        proto_tree *tt = NULL;                                                   //方便添加结点而定义
        ti = proto_tree_add_item(tree, intproto[exFunIndex], tvb, 0, -1, FALSE); //添加结点
        tt = proto_item_add_subtree(ti, ettprotos[exFunIndex]);                  //添加子树， 用以显示数据
        // proto_tree_add_item(tt, hf_scoreboard_id, tvb, offset, 16, FALSE);
        for (int i = 0; i < allProtoInfo[exFunIndex].protoNum; i++)
        {
            proto_tree_add_item(tt, allProtoInfo[exFunIndex].column[i].id, tvb, offset, allProtoInfo[exFunIndex].column[i].length, FALSE);
            offset += allProtoInfo[exFunIndex].column[i].length;
        }
    }
    return tvb_captured_length(tvb);
}

static gint dissect_exproto1(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0;
    exFunIndex = 1;
    col_set_str(pinfo->cinfo, COL_PROTOCOL, allProtoInfo[exFunIndex].protoName); //显示协议
    col_clear(pinfo->cinfo, COL_INFO);

    if (tree)
    {
        // guint8 cmd_result = 0; //用 于保存获取到的操作类型值
        // guint8 id_result = 0;
        proto_item *ti = NULL;                                                   //方便添加结点而定义
        proto_tree *tt = NULL;                                                   //方便添加结点而定义
        ti = proto_tree_add_item(tree, intproto[exFunIndex], tvb, 0, -1, FALSE); //添加结点
        tt = proto_item_add_subtree(ti, ettprotos[exFunIndex]);                  //添加子树， 用以显示数据
        // proto_tree_add_item(tt, hf_scoreboard_id, tvb, offset, 16, FALSE);
        for (int i = 0; i < allProtoInfo[exFunIndex].protoNum; i++)
        {
            proto_tree_add_item(tt, allProtoInfo[exFunIndex].column[i].id, tvb, offset, allProtoInfo[exFunIndex].column[i].length, FALSE);
            offset += allProtoInfo[exFunIndex].column[i].length;
        }
    }
    return tvb_captured_length(tvb);
}

static gint dissect_exproto2(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0;
    exFunIndex = 2;
    col_set_str(pinfo->cinfo, COL_PROTOCOL, allProtoInfo[exFunIndex].protoName); //显示协议
    col_clear(pinfo->cinfo, COL_INFO);

    if (tree)
    {
        // guint8 cmd_result = 0; //用 于保存获取到的操作类型值
        // guint8 id_result = 0;
        proto_item *ti = NULL;                                                   //方便添加结点而定义
        proto_tree *tt = NULL;                                                   //方便添加结点而定义
        ti = proto_tree_add_item(tree, intproto[exFunIndex], tvb, 0, -1, FALSE); //添加结点
        tt = proto_item_add_subtree(ti, ettprotos[exFunIndex]);                  //添加子树， 用以显示数据
        // proto_tree_add_item(tt, hf_scoreboard_id, tvb, offset, 16, FALSE);
        for (int i = 0; i < allProtoInfo[exFunIndex].protoNum; i++)
        {
            proto_tree_add_item(tt, allProtoInfo[exFunIndex].column[i].id, tvb, offset, allProtoInfo[exFunIndex].column[i].length, FALSE);
            offset += allProtoInfo[exFunIndex].column[i].length;
        }
    }
    return tvb_captured_length(tvb);
}

static gint dissect_exproto3(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0;
    exFunIndex = 3;
    col_set_str(pinfo->cinfo, COL_PROTOCOL, allProtoInfo[exFunIndex].protoName); //显示协议
    col_clear(pinfo->cinfo, COL_INFO);

    if (tree)
    {
        // guint8 cmd_result = 0; //用 于保存获取到的操作类型值
        // guint8 id_result = 0;
        proto_item *ti = NULL;                                                   //方便添加结点而定义
        proto_tree *tt = NULL;                                                   //方便添加结点而定义
        ti = proto_tree_add_item(tree, intproto[exFunIndex], tvb, 0, -1, FALSE); //添加结点
        tt = proto_item_add_subtree(ti, ettprotos[exFunIndex]);                  //添加子树， 用以显示数据
        // proto_tree_add_item(tt, hf_scoreboard_id, tvb, offset, 16, FALSE);
        for (int i = 0; i < allProtoInfo[exFunIndex].protoNum; i++)
        {
            proto_tree_add_item(tt, allProtoInfo[exFunIndex].column[i].id, tvb, offset, allProtoInfo[exFunIndex].column[i].length, FALSE);
            offset += allProtoInfo[exFunIndex].column[i].length;
        }
    }
    return tvb_captured_length(tvb);
}

static gint dissect_exproto4(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0;
    exFunIndex = 4;
    col_set_str(pinfo->cinfo, COL_PROTOCOL, allProtoInfo[exFunIndex].protoName); //显示协议
    col_clear(pinfo->cinfo, COL_INFO);

    if (tree)
    {
        // guint8 cmd_result = 0; //用 于保存获取到的操作类型值
        // guint8 id_result = 0;
        proto_item *ti = NULL;                                                   //方便添加结点而定义
        proto_tree *tt = NULL;                                                   //方便添加结点而定义
        ti = proto_tree_add_item(tree, intproto[exFunIndex], tvb, 0, -1, FALSE); //添加结点
        tt = proto_item_add_subtree(ti, ettprotos[exFunIndex]);                  //添加子树， 用以显示数据
        // proto_tree_add_item(tt, hf_scoreboard_id, tvb, offset, 16, FALSE);
        for (int i = 0; i < allProtoInfo[exFunIndex].protoNum; i++)
        {
            proto_tree_add_item(tt, allProtoInfo[exFunIndex].column[i].id, tvb, offset, allProtoInfo[exFunIndex].column[i].length, FALSE);
            offset += allProtoInfo[exFunIndex].column[i].length;
        }
    }
    return tvb_captured_length(tvb);
}

static gint dissect_exproto5(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0;
    exFunIndex = 5;
    col_set_str(pinfo->cinfo, COL_PROTOCOL, allProtoInfo[exFunIndex].protoName); //显示协议
    col_clear(pinfo->cinfo, COL_INFO);

    if (tree)
    {
        // guint8 cmd_result = 0; //用 于保存获取到的操作类型值
        // guint8 id_result = 0;
        proto_item *ti = NULL;                                                   //方便添加结点而定义
        proto_tree *tt = NULL;                                                   //方便添加结点而定义
        ti = proto_tree_add_item(tree, intproto[exFunIndex], tvb, 0, -1, FALSE); //添加结点
        tt = proto_item_add_subtree(ti, ettprotos[exFunIndex]);                  //添加子树， 用以显示数据
        // proto_tree_add_item(tt, hf_scoreboard_id, tvb, offset, 16, FALSE);
        for (int i = 0; i < allProtoInfo[exFunIndex].protoNum; i++)
        {
            proto_tree_add_item(tt, allProtoInfo[exFunIndex].column[i].id, tvb, offset, allProtoInfo[exFunIndex].column[i].length, FALSE);
            offset += allProtoInfo[exFunIndex].column[i].length;
        }
    }
    return tvb_captured_length(tvb);
}

static gint dissect_exproto6(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0;
    exFunIndex = 6;
    col_set_str(pinfo->cinfo, COL_PROTOCOL, allProtoInfo[exFunIndex].protoName); //显示协议
    col_clear(pinfo->cinfo, COL_INFO);

    if (tree)
    {
        // guint8 cmd_result = 0; //用 于保存获取到的操作类型值
        // guint8 id_result = 0;
        proto_item *ti = NULL;                                                   //方便添加结点而定义
        proto_tree *tt = NULL;                                                   //方便添加结点而定义
        ti = proto_tree_add_item(tree, intproto[exFunIndex], tvb, 0, -1, FALSE); //添加结点
        tt = proto_item_add_subtree(ti, ettprotos[exFunIndex]);                  //添加子树， 用以显示数据
        // proto_tree_add_item(tt, hf_scoreboard_id, tvb, offset, 16, FALSE);
        for (int i = 0; i < allProtoInfo[exFunIndex].protoNum; i++)
        {
            proto_tree_add_item(tt, allProtoInfo[exFunIndex].column[i].id, tvb, offset, allProtoInfo[exFunIndex].column[i].length, FALSE);
            offset += allProtoInfo[exFunIndex].column[i].length;
        }
    }
    return tvb_captured_length(tvb);
}

static gint dissect_exproto7(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0;
    exFunIndex = 7;
    col_set_str(pinfo->cinfo, COL_PROTOCOL, allProtoInfo[exFunIndex].protoName); //显示协议
    col_clear(pinfo->cinfo, COL_INFO);
    if (tree)
    {
        // guint8 cmd_result = 0; //用 于保存获取到的操作类型值
        // guint8 id_result = 0;
        proto_item *ti = NULL;                                                   //方便添加结点而定义
        proto_tree *tt = NULL;                                                   //方便添加结点而定义
        ti = proto_tree_add_item(tree, intproto[exFunIndex], tvb, 0, -1, FALSE); //添加结点
        tt = proto_item_add_subtree(ti, ettprotos[exFunIndex]);                  //添加子树， 用以显示数据
        // proto_tree_add_item(tt, hf_scoreboard_id, tvb, offset, 16, FALSE);
        for (int i = 0; i < allProtoInfo[exFunIndex].protoNum; i++)
        {
            proto_tree_add_item(tt, allProtoInfo[exFunIndex].column[i].id, tvb, offset, allProtoInfo[exFunIndex].column[i].length, FALSE);
            offset += allProtoInfo[exFunIndex].column[i].length;
        }
    }
    return tvb_captured_length(tvb);
}

static gint dissect_exproto8(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0;
    exFunIndex = 8;
    col_set_str(pinfo->cinfo, COL_PROTOCOL, allProtoInfo[exFunIndex].protoName); //显示协议
    col_clear(pinfo->cinfo, COL_INFO);
    if (tree)
    {
        // guint8 cmd_result = 0; //用 于保存获取到的操作类型值
        // guint8 id_result = 0;
        proto_item *ti = NULL;                                                   //方便添加结点而定义
        proto_tree *tt = NULL;                                                   //方便添加结点而定义
        ti = proto_tree_add_item(tree, intproto[exFunIndex], tvb, 0, -1, FALSE); //添加结点
        tt = proto_item_add_subtree(ti, ettprotos[exFunIndex]);                  //添加子树， 用以显示数据
        // proto_tree_add_item(tt, hf_scoreboard_id, tvb, offset, 16, FALSE);
        for (int i = 0; i < allProtoInfo[exFunIndex].protoNum; i++)
        {
            proto_tree_add_item(tt, allProtoInfo[exFunIndex].column[i].id, tvb, offset, allProtoInfo[exFunIndex].column[i].length, FALSE);
            offset += allProtoInfo[exFunIndex].column[i].length;
        }
    }
    return tvb_captured_length(tvb);
}

static gint dissect_exproto9(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0;
    exFunIndex = 9;
    col_set_str(pinfo->cinfo, COL_PROTOCOL, allProtoInfo[exFunIndex].protoName); //显示协议
    col_clear(pinfo->cinfo, COL_INFO);
    if (tree)
    {
        // guint8 cmd_result = 0; //用 于保存获取到的操作类型值
        // guint8 id_result = 0;
        proto_item *ti = NULL;                                                   //方便添加结点而定义
        proto_tree *tt = NULL;                                                   //方便添加结点而定义
        ti = proto_tree_add_item(tree, intproto[exFunIndex], tvb, 0, -1, FALSE); //添加结点
        tt = proto_item_add_subtree(ti, ettprotos[exFunIndex]);                  //添加子树， 用以显示数据
        // proto_tree_add_item(tt, hf_scoreboard_id, tvb, offset, 16, FALSE);
        for (int i = 0; i < allProtoInfo[exFunIndex].protoNum; i++)
        {
            proto_tree_add_item(tt, allProtoInfo[exFunIndex].column[i].id, tvb, offset, allProtoInfo[exFunIndex].column[i].length, FALSE);
            offset += allProtoInfo[exFunIndex].column[i].length;
        }
    }
    return tvb_captured_length(tvb);
}

static gint (*functions[SupportJsonNum])(tvbuff_t *, packet_info *, proto_tree *) = {
        dissect_exproto0,
        dissect_exproto1,
        dissect_exproto2,
        dissect_exproto3,
        dissect_exproto4,
        dissect_exproto5,
        dissect_exproto6,
        dissect_exproto7,
        dissect_exproto8,
        dissect_exproto9};

static gboolean
heur_dissect_exproto0(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data){
    heur_exFunIndex = 0;
    int payload_len = 0;
    gint offset = 0, next_offset, linelen;
    char *payload_future_t = allProtoInfo[heur_exFunIndex].feature;
    int future_offset_t = allProtoInfo[heur_exFunIndex].feature_offset;
    int future_len_t = strlen(payload_future_t);
/*    linelen = tvb_find_line_end(tvb, offset, -1, &next_offset, TRUE);
    if((linelen == -1)||(linelen == 8)){
        return FALSE;
    }*/
    if((tvb_strncaseeql(tvb, future_offset_t, payload_future_t, future_len_t) == 0)){

        payload_len = functions[heur_exFunIndex](tvb,pinfo,tree);

        return TRUE;
    }

    return FALSE;
}

static gboolean
heur_dissect_exproto1(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data){
    heur_exFunIndex = 1;
    int payload_len = 0;
    gint offset = 0, next_offset, linelen;
    char *payload_future_t = allProtoInfo[heur_exFunIndex].feature;
    int future_offset_t = allProtoInfo[heur_exFunIndex].feature_offset;
    int future_len_t = strlen(payload_future_t);
//strcat(payload_future_t,'A'+i);

/*    linelen = tvb_find_line_end(tvb, offset, -1, &next_offset, TRUE);
    if((linelen == -1)||(linelen == 8)){
        return FALSE;
    }*/
    if((tvb_strncaseeql(tvb, future_offset_t, payload_future_t, future_len_t) == 0)){

        payload_len = functions[heur_exFunIndex](tvb,pinfo,tree);

        return TRUE;
    }

    return FALSE;
}

static gboolean
heur_dissect_exproto2(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data){
    heur_exFunIndex = 2;
    int payload_len = 0;
    gint offset = 0, next_offset, linelen;
    char *payload_future_t = allProtoInfo[heur_exFunIndex].feature;
    int future_offset_t = allProtoInfo[heur_exFunIndex].feature_offset;
    int future_len_t = strlen(payload_future_t);
//strcat(payload_future_t,'A'+i);

/*    linelen = tvb_find_line_end(tvb, offset, -1, &next_offset, TRUE);
    if((linelen == -1)||(linelen == 8)){
        return FALSE;
    }*/
    if((tvb_strncaseeql(tvb, future_offset_t, payload_future_t, future_len_t) == 0)){

        payload_len = functions[heur_exFunIndex](tvb,pinfo,tree);

        return TRUE;
    }

    return FALSE;
}

static gboolean
heur_dissect_exproto3(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data){
    heur_exFunIndex = 3;
    int payload_len = 0;
    gint offset = 0, next_offset, linelen;
    char *payload_future_t = allProtoInfo[heur_exFunIndex].feature;
    int future_offset_t = allProtoInfo[heur_exFunIndex].feature_offset;
    int future_len_t = strlen(payload_future_t);
//strcat(payload_future_t,'A'+i);

/*    linelen = tvb_find_line_end(tvb, offset, -1, &next_offset, TRUE);
    if((linelen == -1)||(linelen == 8)){
        return FALSE;
    }*/
    if((tvb_strncaseeql(tvb, future_offset_t, payload_future_t, future_len_t) == 0)){

        payload_len = functions[heur_exFunIndex](tvb,pinfo,tree);

        return TRUE;
    }

    return FALSE;
}

static gboolean
heur_dissect_exproto4(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data){
    heur_exFunIndex = 4;
    int payload_len = 0;
    gint offset = 0, next_offset, linelen;
    char *payload_future_t = allProtoInfo[heur_exFunIndex].feature;
    int future_offset_t = allProtoInfo[heur_exFunIndex].feature_offset;
    int future_len_t = strlen(payload_future_t);



    if((tvb_strncaseeql(tvb, future_offset_t, payload_future_t, future_len_t) == 0)){

        payload_len = functions[heur_exFunIndex](tvb,pinfo,tree);

        return TRUE;
    }

    return FALSE;
}

static gboolean
heur_dissect_exproto5(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data){
    heur_exFunIndex = 5;
    int payload_len = 0;
    gint offset = 0, next_offset, linelen;
    char *payload_future_t = allProtoInfo[heur_exFunIndex].feature;
    int future_offset_t = allProtoInfo[heur_exFunIndex].feature_offset;
    int future_len_t = strlen(payload_future_t);



    if((tvb_strncaseeql(tvb, future_offset_t, payload_future_t, future_len_t) == 0)){

        payload_len = functions[heur_exFunIndex](tvb,pinfo,tree);

        return TRUE;
    }

    return FALSE;
}

static gboolean
heur_dissect_exproto6(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data){
    heur_exFunIndex = 6;
    int payload_len = 0;
    gint offset = 0, next_offset, linelen;
    char *payload_future_t = allProtoInfo[heur_exFunIndex].feature;
    int future_offset_t = allProtoInfo[heur_exFunIndex].feature_offset;
    int future_len_t = strlen(payload_future_t);
    if((tvb_strncaseeql(tvb, future_offset_t, payload_future_t, future_len_t) == 0)){

        payload_len = functions[heur_exFunIndex](tvb,pinfo,tree);

        return TRUE;
    }

    return FALSE;
}

static gboolean
heur_dissect_exproto7(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data){
    heur_exFunIndex = 7;
    int payload_len = 0;
    gint offset = 0, next_offset, linelen;
    char *payload_future_t = allProtoInfo[heur_exFunIndex].feature;
    int future_offset_t = allProtoInfo[heur_exFunIndex].feature_offset;
    int future_len_t = strlen(payload_future_t);
    if((tvb_strncaseeql(tvb, future_offset_t, payload_future_t, future_len_t) == 0)){

        payload_len = functions[heur_exFunIndex](tvb,pinfo,tree);

        return TRUE;
    }

    return FALSE;
}

static gboolean
heur_dissect_exproto8(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data){
    heur_exFunIndex = 8;
    int payload_len = 0;
    gint offset = 0, next_offset, linelen;
    char *payload_future_t = allProtoInfo[heur_exFunIndex].feature;
    int future_offset_t = allProtoInfo[heur_exFunIndex].feature_offset;
    int future_len_t = strlen(payload_future_t);
    if((tvb_strncaseeql(tvb, future_offset_t, payload_future_t, future_len_t) == 0)){

        payload_len = functions[heur_exFunIndex](tvb,pinfo,tree);

        return TRUE;
    }

    return FALSE;
}

static gboolean
heur_dissect_exproto9(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data){
    heur_exFunIndex = 9;
    int payload_len = 0;
    gint offset = 0, next_offset, linelen;
    char *payload_future_t = allProtoInfo[heur_exFunIndex].feature;
    int future_offset_t = allProtoInfo[heur_exFunIndex].feature_offset;
    int future_len_t = strlen(payload_future_t);
    if((tvb_strncaseeql(tvb, future_offset_t, payload_future_t, future_len_t) == 0)){

        payload_len = functions[heur_exFunIndex](tvb,pinfo,tree);

        return TRUE;
    }

    return FALSE;
}

static gint (*heur_functions[SupportJsonNum])(tvbuff_t *, packet_info *, proto_tree *,void *) = {
        heur_dissect_exproto0,
        heur_dissect_exproto1,
        heur_dissect_exproto2,
        heur_dissect_exproto3,
        heur_dissect_exproto4,
        heur_dissect_exproto5,
        heur_dissect_exproto6,
        heur_dissect_exproto7,
        heur_dissect_exproto8,
        heur_dissect_exproto9};

int GetProtoInfos(struct allExProtocols *exprotocols)
{
    for (int i = 0; i < exprotocols->exProtocolNum; i++)
    {
        for (int j = 0; j < 10; j++){
            allProtoInfo[i].port[j] = 0;
        }
        //一共有多少列的数据
        allProtoInfo[i].protoNum = exprotocols->exProto[i].partHead->partsNum;
        int num = exprotocols->exProto[i].partHead->partsNum;
        int port_i = 0;
        //端口号
        while(exprotocols->exProto[i].port[port_i] != 0 && port_i < 10){
            allProtoInfo[i].port[port_i] = exprotocols->exProto[i].port[port_i];
            port_i++;
        }


        //获得协议名称
        strcpy(allProtoInfo[i].protoName, exprotocols->exProto[i].protocolName);
        strcpy(allProtoInfo[i].shortName, exprotocols->exProto[i].shortName);
        strcpy(allProtoInfo[i].filterName, exprotocols->exProto[i].filterName);
        strcpy(allProtoInfo[i].transportProto, exprotocols->exProto[i].transportProtocol);
        strcpy(allProtoInfo[i].feature, exprotocols->exProto[i].feature);
        allProtoInfo[i].feature_offset = exprotocols->exProto[i].feature_offset;

        allProtoInfo[i].column = (struct columnInfo *)malloc(num * sizeof(struct columnInfo));
        for (int j = 0; j < num; j++)
        {
            //对每一列的信息进行赋值
            allProtoInfo[i].column[j].id = -1;
            strcpy(allProtoInfo[i].column[j].name, exprotocols->exProto[i].partHead->dataParts[j].name);
            strcpy(allProtoInfo[i].column[j].abbName, exprotocols->exProto[i].partHead->dataParts[j].abbName);
            allProtoInfo[i].column[j].type = exprotocols->exProto[i].partHead->dataParts[j].type;
            allProtoInfo[i].column[j].length = exprotocols->exProto[i].partHead->dataParts[j].length;
        }
    }

    return 1;
}

void proto_register_exprotocol(int j)
{
    int columNum = allProtoInfo[j].protoNum;
    hf_register_info *hf = (hf_register_info *)malloc(sizeof(hf_register_info) * columNum);
    // hf[0].p_id = &hf_scoreboard_id;
    for (int i = 0; i < columNum; i++)
    {
        hf[i].p_id = &(allProtoInfo[j].column[i].id);
        hf[i].hfinfo.name = allProtoInfo[j].column[i].name;
        hf[i].hfinfo.abbrev = allProtoInfo[j].column[i].abbName;

        switch (allProtoInfo[j].column[i].type)
        {
            case (0):
                hf[i].hfinfo.type = FT_BOOLEAN;
                hf[i].hfinfo.display = BASE_NONE;
                hf[i].hfinfo.strings = NULL;
                hf[i].hfinfo.bitmask = 0x01;
                hf[i].hfinfo.blurb = NULL;
                break;
            case (1):
                hf[i].hfinfo.type = FT_IPv4;
                hf[i].hfinfo.display = BASE_NONE;
                hf[i].hfinfo.strings = NULL;
                hf[i].hfinfo.bitmask = 0;
                hf[i].hfinfo.blurb = NULL;
                break;
            case (2):
                hf[i].hfinfo.type = FT_IPv6;
                hf[i].hfinfo.display = BASE_NONE;
                hf[i].hfinfo.strings = NULL;
                hf[i].hfinfo.bitmask = 0;
                hf[i].hfinfo.blurb = NULL;
                break;
            case (3):
                hf[i].hfinfo.type = FT_ABSOLUTE_TIME;
                hf[i].hfinfo.display = ABSOLUTE_TIME_LOCAL;
                hf[i].hfinfo.strings = NULL;
                hf[i].hfinfo.bitmask = 0;
                hf[i].hfinfo.blurb = NULL;
                break;
            case (4):
                hf[i].hfinfo.type = FT_INT64;
                hf[i].hfinfo.display = BASE_CUSTOM ;
                hf[i].hfinfo.strings = NULL;
                hf[i].hfinfo.bitmask = 0;
                hf[i].hfinfo.blurb = NULL;
                break;
            case (5):
                hf[i].hfinfo.type = FT_FLOAT;
                hf[i].hfinfo.display = BASE_FLOAT;
                hf[i].hfinfo.strings = NULL;
                hf[i].hfinfo.bitmask = 0;
                hf[i].hfinfo.blurb = NULL;
                break;
            case (6):
                hf[i].hfinfo.type = FT_STRING;
                hf[i].hfinfo.display = STR_UNICODE;
                hf[i].hfinfo.strings = NULL;
                hf[i].hfinfo.bitmask = 0;
                hf[i].hfinfo.blurb = NULL;
                break;
/*        case (99):
                proto_register_exprotocol(i);
                break;*/
            default:
                hf[i].hfinfo.type = FT_BYTES;
                hf[i].hfinfo.display = BASE_NONE;
        }

        HFILL_INIT(hf[i]);

    }

    gint *ett[] = {
            &ettprotos[j]}; //我们只需要一个子树，显示分值与颜色分量

    intproto[j] = proto_register_protocol(allProtoInfo[j].protoName,
                                          allProtoInfo[j].shortName,
                                          allProtoInfo[j].filterName);
    //用于注册hf数组，第一个参数用于将hf数组和这个协议建立联系//
    proto_register_field_array(intproto[j], hf, columNum);
    //注册ett数组，用于展示数据//
    proto_register_subtree_array(ett, array_length(ett));
    //以下是注册启发队列相关的操作//
    heur_subdissector_list = register_heur_dissector_list(allProtoInfo[j].filterName, intproto[j]);
}






void proto_reg_handoff_exprotocol(int index)
{
    int port_i = 0;
    char *transProto_t;
    char *display_name_t;
    char *internal_name_t;
    dissector_handle_t exprotocol_handle;
    exprotocol_handle = create_dissector_handle(functions[index], intproto[index]);
    transProto_t = allProtoInfo[index].transportProto;
    display_name_t = allProtoInfo[index].shortName;
    internal_name_t = allProtoInfo[index].filterName;
    if(strcmp(transProto_t,"udp") == 0){
        strcat(display_name_t," over UDP");

        while(allProtoInfo[index].port[port_i] != 0 && port_i < 10){
            dissector_add_uint("udp.port", allProtoInfo[index].port[port_i], exprotocol_handle);
            port_i++;
        }
        heur_dissector_add("udp", heur_functions[index], display_name_t, internal_name_t, intproto[index], HEURISTIC_ENABLE);

    } else if(strcmp(transProto_t,"tcp") == 0){
        strcat(display_name_t," over TCP");
        heur_dissector_add("tcp", heur_functions[index], display_name_t, internal_name_t, intproto[index], HEURISTIC_ENABLE);
        while(allProtoInfo[index].port[port_i] != 0 && port_i < 10){
            dissector_add_uint("tcp.port", allProtoInfo[index].port[port_i], exprotocol_handle);
            port_i++;
        }

    }

}
void exproto_register(allExProtocols *exprotocols)
{
    int jsonNum = exprotocols->exProtocolNum;
    if (jsonNum > SupportJsonNum)
    {
        printf("Too many json files\n");
    }
    for (int i = 0; i < jsonNum; i++)
    {
        intproto[i] = -1;
        ettprotos[i] = -1;
    }
    GetProtoInfos(exprotocols);
    for (int i = 0; i < jsonNum; i++)
    {
        proto_register_exprotocol(i);
        proto_reg_handoff_exprotocol(i);
    }

    // scoreboard_register();
}
