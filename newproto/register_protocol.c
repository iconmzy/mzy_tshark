#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "packet-scoreboard.h"
#include "register_protocol.h"

#define SupportJsonNum 10
static int intproto[SupportJsonNum];
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

int GetProtoInfos(struct allExProtocols *exprotocols)
{
    for (int i = 0; i < exprotocols->exProtocolNum; i++)
    {
        //一共有多少列的数据
        allProtoInfo[i].protoNum = exprotocols->exProto[i].partHead->partsNum;
        int num = exprotocols->exProto[i].partHead->partsNum;
        //端口号
        allProtoInfo[i].port = exprotocols->exProto[i].port;
        //获得协议名称
        strcpy(allProtoInfo[i].protoName, exprotocols->exProto[i].protocolName);
        strcpy(allProtoInfo[i].shortName, exprotocols->exProto[i].shortName);
        strcpy(allProtoInfo[i].filterName, exprotocols->exProto[i].filterName);
        strcpy(allProtoInfo[i].transportProto, exprotocols->exProto[i].transportProtocol);
        allProtoInfo[i].column = (struct columnInfo *)malloc(num * sizeof(struct columnInfo));
        for (int j = 0; j < num; j++)
        {
            //对每一列的信息进行赋值
            allProtoInfo[i].column[j].id = -1;
            strcpy(allProtoInfo[i].column[j].name, exprotocols->exProto[i].partHead->dataParts[j].name);
            strcpy(allProtoInfo[i].column[j].abbName, exprotocols->exProto[i].partHead->dataParts[j].name);
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
            hf[i].hfinfo.type = FT_UINT8;
            hf[i].hfinfo.display = BASE_HEX;
            break;
        case (1):
            hf[i].hfinfo.type = FT_FLOAT;
            hf[i].hfinfo.display = BASE_FLOAT;
            break;
        case (2):
            hf[i].hfinfo.type = FT_STRING;
            hf[i].hfinfo.display = STR_UNICODE;
            break;
        default:
            hf[i].hfinfo.type = FT_BYTES;
            hf[i].hfinfo.display = BASE_NONE;
        }

        hf[i].hfinfo.strings = NULL;
        hf[i].hfinfo.bitmask = 0;
        hf[i].hfinfo.blurb = NULL;
        HFILL_INIT(hf[i]);
    }

    gint *ett[] = {
        &ettprotos[j]}; //我们只需要一个子树，显示分值与颜色分量

    intproto[j] = proto_register_protocol(allProtoInfo[j].protoName,
                                          allProtoInfo[j].shortName,
                                          allProtoInfo[j].filterName);
    proto_register_field_array(intproto[j], hf, columNum);
    proto_register_subtree_array(ett, array_length(ett));
}

void proto_reg_handoff_exprotocol(int index)
{
    dissector_handle_t exprotocol_handle;
    exprotocol_handle = create_dissector_handle(functions[index], intproto[index]);
    dissector_add_uint("udp.port", allProtoInfo[index].port, exprotocol_handle);
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
