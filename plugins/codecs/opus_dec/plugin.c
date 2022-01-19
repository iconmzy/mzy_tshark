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

#include "wsutil/codecs.h"

void codec_register_opus(void);

WS_DLL_PUBLIC_DEF const gchar plugin_version[] = PLUGIN_VERSION;
WS_DLL_PUBLIC_DEF const int plugin_want_major = VERSION_MAJOR;
WS_DLL_PUBLIC_DEF const int plugin_want_minor = VERSION_MINOR;

WS_DLL_PUBLIC void plugin_register(void);

void plugin_register(void)
{
    static codecs_plugin plug_opus;

    plug_opus.register_codec_module = codec_register_opus;
    codecs_register_plugin(&plug_opus);
}
