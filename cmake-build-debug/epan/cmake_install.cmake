# Install script for directory: /root/CLionProjects/tshark_gongjv/epan

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so.14.0.5"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so.14"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/usr/local/lib64")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/root/CLionProjects/tshark_gongjv/cmake-build-debug/run/libwireshark.so.14.0.5"
    "/root/CLionProjects/tshark_gongjv/cmake-build-debug/run/libwireshark.so.14"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so.14.0.5"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so.14"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "$ORIGIN:::::::::"
           NEW_RPATH "/usr/local/lib64")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/root/CLionProjects/tshark_gongjv/cmake-build-debug/run/libwireshark.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/wireshark/epan" TYPE FILE FILES
    "/root/CLionProjects/tshark_gongjv/epan/addr_and_mask.h"
    "/root/CLionProjects/tshark_gongjv/epan/addr_resolv.h"
    "/root/CLionProjects/tshark_gongjv/epan/address.h"
    "/root/CLionProjects/tshark_gongjv/epan/address_types.h"
    "/root/CLionProjects/tshark_gongjv/epan/afn.h"
    "/root/CLionProjects/tshark_gongjv/epan/aftypes.h"
    "/root/CLionProjects/tshark_gongjv/epan/app_mem_usage.h"
    "/root/CLionProjects/tshark_gongjv/epan/arcnet_pids.h"
    "/root/CLionProjects/tshark_gongjv/epan/arptypes.h"
    "/root/CLionProjects/tshark_gongjv/epan/asn1.h"
    "/root/CLionProjects/tshark_gongjv/epan/ax25_pids.h"
    "/root/CLionProjects/tshark_gongjv/epan/bridged_pids.h"
    "/root/CLionProjects/tshark_gongjv/epan/capture_dissectors.h"
    "/root/CLionProjects/tshark_gongjv/epan/charsets.h"
    "/root/CLionProjects/tshark_gongjv/epan/chdlctypes.h"
    "/root/CLionProjects/tshark_gongjv/epan/cisco_pid.h"
    "/root/CLionProjects/tshark_gongjv/epan/color_filters.h"
    "/root/CLionProjects/tshark_gongjv/epan/column.h"
    "/root/CLionProjects/tshark_gongjv/epan/column-info.h"
    "/root/CLionProjects/tshark_gongjv/epan/column-utils.h"
    "/root/CLionProjects/tshark_gongjv/epan/conversation.h"
    "/root/CLionProjects/tshark_gongjv/epan/conversation_debug.h"
    "/root/CLionProjects/tshark_gongjv/epan/conversation_table.h"
    "/root/CLionProjects/tshark_gongjv/epan/conv_id.h"
    "/root/CLionProjects/tshark_gongjv/epan/crc10-tvb.h"
    "/root/CLionProjects/tshark_gongjv/epan/crc16-tvb.h"
    "/root/CLionProjects/tshark_gongjv/epan/crc32-tvb.h"
    "/root/CLionProjects/tshark_gongjv/epan/crc6-tvb.h"
    "/root/CLionProjects/tshark_gongjv/epan/crc8-tvb.h"
    "/root/CLionProjects/tshark_gongjv/epan/decode_as.h"
    "/root/CLionProjects/tshark_gongjv/epan/diam_dict.h"
    "/root/CLionProjects/tshark_gongjv/epan/disabled_protos.h"
    "/root/CLionProjects/tshark_gongjv/epan/conversation_filter.h"
    "/root/CLionProjects/tshark_gongjv/epan/dtd.h"
    "/root/CLionProjects/tshark_gongjv/epan/dtd_parse.h"
    "/root/CLionProjects/tshark_gongjv/epan/dvb_chartbl.h"
    "/root/CLionProjects/tshark_gongjv/epan/eap.h"
    "/root/CLionProjects/tshark_gongjv/epan/eapol_keydes_types.h"
    "/root/CLionProjects/tshark_gongjv/epan/epan.h"
    "/root/CLionProjects/tshark_gongjv/epan/epan_dissect.h"
    "/root/CLionProjects/tshark_gongjv/epan/etypes.h"
    "/root/CLionProjects/tshark_gongjv/epan/ex-opt.h"
    "/root/CLionProjects/tshark_gongjv/epan/except.h"
    "/root/CLionProjects/tshark_gongjv/epan/exceptions.h"
    "/root/CLionProjects/tshark_gongjv/epan/expert.h"
    "/root/CLionProjects/tshark_gongjv/epan/export_object.h"
    "/root/CLionProjects/tshark_gongjv/epan/exported_pdu.h"
    "/root/CLionProjects/tshark_gongjv/epan/filter_expressions.h"
    "/root/CLionProjects/tshark_gongjv/epan/follow.h"
    "/root/CLionProjects/tshark_gongjv/epan/frame_data.h"
    "/root/CLionProjects/tshark_gongjv/epan/frame_data_sequence.h"
    "/root/CLionProjects/tshark_gongjv/epan/funnel.h"
    "/root/CLionProjects/tshark_gongjv/epan/garrayfix.h"
    "/root/CLionProjects/tshark_gongjv/epan/golay.h"
    "/root/CLionProjects/tshark_gongjv/epan/guid-utils.h"
    "/root/CLionProjects/tshark_gongjv/epan/iana_charsets.h"
    "/root/CLionProjects/tshark_gongjv/epan/iax2_codec_type.h"
    "/root/CLionProjects/tshark_gongjv/epan/in_cksum.h"
    "/root/CLionProjects/tshark_gongjv/epan/ip_opts.h"
    "/root/CLionProjects/tshark_gongjv/epan/ipproto.h"
    "/root/CLionProjects/tshark_gongjv/epan/ipv4.h"
    "/root/CLionProjects/tshark_gongjv/epan/ipv6.h"
    "/root/CLionProjects/tshark_gongjv/epan/lapd_sapi.h"
    "/root/CLionProjects/tshark_gongjv/epan/llcsaps.h"
    "/root/CLionProjects/tshark_gongjv/epan/maxmind_db.h"
    "/root/CLionProjects/tshark_gongjv/epan/media_params.h"
    "/root/CLionProjects/tshark_gongjv/epan/next_tvb.h"
    "/root/CLionProjects/tshark_gongjv/epan/nlpid.h"
    "/root/CLionProjects/tshark_gongjv/epan/oids.h"
    "/root/CLionProjects/tshark_gongjv/epan/osi-utils.h"
    "/root/CLionProjects/tshark_gongjv/epan/oui.h"
    "/root/CLionProjects/tshark_gongjv/epan/packet.h"
    "/root/CLionProjects/tshark_gongjv/epan/packet_info.h"
    "/root/CLionProjects/tshark_gongjv/epan/params.h"
    "/root/CLionProjects/tshark_gongjv/epan/plugin_if.h"
    "/root/CLionProjects/tshark_gongjv/epan/ppptypes.h"
    "/root/CLionProjects/tshark_gongjv/epan/print.h"
    "/root/CLionProjects/tshark_gongjv/epan/print_stream.h"
    "/root/CLionProjects/tshark_gongjv/epan/prefs.h"
    "/root/CLionProjects/tshark_gongjv/epan/prefs-int.h"
    "/root/CLionProjects/tshark_gongjv/epan/proto.h"
    "/root/CLionProjects/tshark_gongjv/epan/proto_data.h"
    "/root/CLionProjects/tshark_gongjv/epan/ps.h"
    "/root/CLionProjects/tshark_gongjv/epan/ptvcursor.h"
    "/root/CLionProjects/tshark_gongjv/epan/range.h"
    "/root/CLionProjects/tshark_gongjv/epan/reassemble.h"
    "/root/CLionProjects/tshark_gongjv/epan/reedsolomon.h"
    "/root/CLionProjects/tshark_gongjv/epan/register.h"
    "/root/CLionProjects/tshark_gongjv/epan/req_resp_hdrs.h"
    "/root/CLionProjects/tshark_gongjv/epan/rtd_table.h"
    "/root/CLionProjects/tshark_gongjv/epan/rtp_pt.h"
    "/root/CLionProjects/tshark_gongjv/epan/sctpppids.h"
    "/root/CLionProjects/tshark_gongjv/epan/secrets.h"
    "/root/CLionProjects/tshark_gongjv/epan/show_exception.h"
    "/root/CLionProjects/tshark_gongjv/epan/slow_protocol_subtypes.h"
    "/root/CLionProjects/tshark_gongjv/epan/sminmpec.h"
    "/root/CLionProjects/tshark_gongjv/epan/srt_table.h"
    "/root/CLionProjects/tshark_gongjv/epan/stat_tap_ui.h"
    "/root/CLionProjects/tshark_gongjv/epan/stat_groups.h"
    "/root/CLionProjects/tshark_gongjv/epan/stats_tree.h"
    "/root/CLionProjects/tshark_gongjv/epan/stats_tree_priv.h"
    "/root/CLionProjects/tshark_gongjv/epan/stream.h"
    "/root/CLionProjects/tshark_gongjv/epan/strutil.h"
    "/root/CLionProjects/tshark_gongjv/epan/t35.h"
    "/root/CLionProjects/tshark_gongjv/epan/tap.h"
    "/root/CLionProjects/tshark_gongjv/epan/tap-voip.h"
    "/root/CLionProjects/tshark_gongjv/epan/timestamp.h"
    "/root/CLionProjects/tshark_gongjv/epan/timestats.h"
    "/root/CLionProjects/tshark_gongjv/epan/tfs.h"
    "/root/CLionProjects/tshark_gongjv/epan/time_fmt.h"
    "/root/CLionProjects/tshark_gongjv/epan/to_str.h"
    "/root/CLionProjects/tshark_gongjv/epan/tvbparse.h"
    "/root/CLionProjects/tshark_gongjv/epan/tvbuff.h"
    "/root/CLionProjects/tshark_gongjv/epan/tvbuff-int.h"
    "/root/CLionProjects/tshark_gongjv/epan/uat.h"
    "/root/CLionProjects/tshark_gongjv/epan/uat-int.h"
    "/root/CLionProjects/tshark_gongjv/epan/unit_strings.h"
    "/root/CLionProjects/tshark_gongjv/epan/value_string.h"
    "/root/CLionProjects/tshark_gongjv/epan/write_in_files_handlers.h"
    "/root/CLionProjects/tshark_gongjv/epan/cJSON.h"
    "/root/CLionProjects/tshark_gongjv/epan/writefile.h"
    "/root/CLionProjects/tshark_gongjv/epan/rtp_media.h"
    "/root/CLionProjects/tshark_gongjv/epan/authorize.h"
    "/root/CLionProjects/tshark_gongjv/epan/x264_prt_id.h"
    "/root/CLionProjects/tshark_gongjv/epan/xdlc.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/crypt/cmake_install.cmake")
  include("/root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dfilter/cmake_install.cmake")
  include("/root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/cmake_install.cmake")
  include("/root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/ftypes/cmake_install.cmake")
  include("/root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/wmem/cmake_install.cmake")
  include("/root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/wslua/cmake_install.cmake")

endif()

