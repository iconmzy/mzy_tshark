#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "packet-scoreboard.h"
#include <epan/packet.h>

static int proto_scoreboard = -1;
static int hf_scoreboard_id = -1;
static int hf_scoreboard_cmd = -1;
static int hf_scoreboard_score_left = -1;
static int hf_scoreboard_score_right = -1;
static int hf_scoreboard_color_red = -1;
static int hf_scoreboard_color_green = -1;
static int hf_scoreboard_color_blue = -1;
static gint ett_scoreboard = -1;
static const value_string names_cmd[] = {
    {0x00, "request score"},
    {0x01, "set score"},
    {0x80, "response score"},
    {0x10, "request color"},
    {0x11, "set color"},
    {0x90, "response color"},
    {0, NULL}};

static dissector_handle_t scoreboard_handle;

static gint dissect_scoreboard(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0;                                        //偏移变量，记录偏移位置
    col_set_str(pinfo->cinfo, COL_PROTOCOL, "ScoreBoard"); //显示协议
    col_clear(pinfo->cinfo, COL_INFO);

    if (tree)
    {
        guint8 cmd_result = 0; //用 于保存获取到的操作类型值
        guint8 id_result = 0;
        proto_item *ti = NULL;                                               //方便添加结点而定义
        proto_tree *tt = NULL;                                               //方便添加结点而定义
        ti = proto_tree_add_item(tree, proto_scoreboard, tvb, 0, -1, FALSE); //添加结点
        tt = proto_item_add_subtree(ti, ett_scoreboard);                     //添加子树， 用以显示数据
                                                                             // proto_tree_add_item( tt,hf_scoreboard_id,tvb,offset, 16,FALSE);offset+=16;
        proto_tree_add_item(tt, hf_scoreboard_id, tvb, offset, 16, FALSE);

        id_result = tvb_get_guint8(tvb, offset + 1);
        offset += 16;
        switch (id_result)
        {
        case 0xcb:
            break;
        default:
            return;
        }
        proto_tree_add_item(tt, hf_scoreboard_cmd, tvb, offset, 1, FALSE);
        cmd_result = tvb_get_guint8(tvb, offset);
        offset += 1; //获取操作类型
        switch (cmd_result)
        {
        case 0x00:
            break;
        case 0x01:
            //添加左边比分结点
            proto_tree_add_item(tt, hf_scoreboard_score_left, tvb, offset, 4, FALSE);
            offset += 4;
            //添加右边比分结点
            proto_tree_add_item(tt, hf_scoreboard_score_right, tvb, offset, 4, FALSE);
            offset += 4;
            break;
        case 0x80:
            proto_tree_add_item(tt, hf_scoreboard_score_left, tvb, offset, 4, FALSE);
            offset += 4;
            proto_tree_add_item(tt, hf_scoreboard_score_right, tvb, offset, 4, FALSE);
            offset += 4;
            break;
        case 0x10:
            break;
        case 0x11:
            //添加颜色分量结点
            proto_tree_add_item(tt, hf_scoreboard_color_red, tvb, offset, 1, FALSE);
            offset += 1;
            proto_tree_add_item(tt, hf_scoreboard_color_green, tvb, offset, 1, FALSE);
            offset += 1;
            proto_tree_add_item(tt, hf_scoreboard_color_blue, tvb, offset, 1, FALSE);
            offset += 1;
            break;
        case 0x90:
            proto_tree_add_item(tt, hf_scoreboard_color_red, tvb, offset, 1, FALSE);
            offset += 1;
            proto_tree_add_item(tt, hf_scoreboard_color_green, tvb, offset, 1, FALSE);
            offset += 1;
            proto_tree_add_item(tt, hf_scoreboard_color_blue, tvb, offset, 1, FALSE);
            offset += 1;
            break;
        default:
            break;
        }
    }
}

void proto_register_scoreboard(void)
{
    static hf_register_info hf[] = {
        //FT BYTES仅能为BASE NONE方式，显示
        {&hf_scoreboard_id, {"ScoreBoard ID", "scoreboard.id", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL}},
        //VALS0宏，仅进行类型转换
        {&hf_scoreboard_cmd, {"Command", "scoreboard.cmd", FT_UINT8, BASE_HEX, VALS(names_cmd), 0, NULL, HFILL}},

        {&hf_scoreboard_score_left, {"Score Lef", "scoreboard.sleft", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL}},
        {&hf_scoreboard_score_right, {"Score Right", "scoreboard.sright", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL}},
        {&hf_scoreboard_color_red, {"Color Red", "scoreboard.r", FT_UINT8, BASE_HEX, NULL, 0, NULL, HFILL}},
        {&hf_scoreboard_color_green, {"Color Green", "scoreboard.g", FT_UINT8, BASE_HEX, NULL, 0, NULL, HFILL}},
        {&hf_scoreboard_color_blue, {"Color Blue", "scoreboard.b", FT_UINT8, BASE_HEX, NULL, 0, NULL, HFILL}},
    };
    static gint *ett[] = {
        &ett_scoreboard}; //我们只需要一个子树，显示分值与颜色分量

    proto_scoreboard = proto_register_protocol("Score Board Protocol",
                                               "ScoreBoard",
                                               "scoreboard");
    proto_register_field_array(proto_scoreboard, hf, array_length(hf));
    proto_register_subtree_array(ett, array_length(ett));
}

void proto_reg_handoff_scoreboard(void)
{
    dissector_handle_t scoreboard_handle;
    scoreboard_handle = create_dissector_handle(dissect_scoreboard, proto_scoreboard);
    dissector_add_uint("udp.port", 1127, scoreboard_handle);
}

void scoreboard_register(void)
{
    proto_register_scoreboard();
    proto_reg_handoff_scoreboard();
}