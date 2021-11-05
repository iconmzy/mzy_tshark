/*
 * Do not modify this file. Changes will be overwritten.
 *
 * Generated automatically from /root/CLionProjects/tshark_test/tools/make-plugin-reg.py.
 */

#include "config.h"

#include <gmodule.h>

/* plugins are DLLs */
#define WS_BUILD_DLL
#include "ws_symbol_export.h"

#include "epan/proto.h"

void proto_register_mate(void);
void proto_reg_handoff_mate(void);

WS_DLL_PUBLIC_DEF const gchar plugin_version[] = PLUGIN_VERSION;
WS_DLL_PUBLIC_DEF const int plugin_want_major = VERSION_MAJOR;
WS_DLL_PUBLIC_DEF const int plugin_want_minor = VERSION_MINOR;

WS_DLL_PUBLIC void plugin_register(void);

void plugin_register(void)
{
    static proto_plugin plug_mate;

    plug_mate.register_protoinfo = proto_register_mate;
    plug_mate.register_handoff = proto_reg_handoff_mate;
    proto_register_plugin(&plug_mate);
}
