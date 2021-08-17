# Install script for directory: /root/CLionProjects/tshark_test/epan

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
    "/root/CLionProjects/tshark_test/run/libwireshark.so.14.0.5"
    "/root/CLionProjects/tshark_test/run/libwireshark.so.14"
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/root/CLionProjects/tshark_test/run/libwireshark.so")
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
    "/root/CLionProjects/tshark_test/epan/addr_and_mask.h"
    "/root/CLionProjects/tshark_test/epan/addr_resolv.h"
    "/root/CLionProjects/tshark_test/epan/address.h"
    "/root/CLionProjects/tshark_test/epan/address_types.h"
    "/root/CLionProjects/tshark_test/epan/afn.h"
    "/root/CLionProjects/tshark_test/epan/aftypes.h"
    "/root/CLionProjects/tshark_test/epan/app_mem_usage.h"
    "/root/CLionProjects/tshark_test/epan/arcnet_pids.h"
    "/root/CLionProjects/tshark_test/epan/arptypes.h"
    "/root/CLionProjects/tshark_test/epan/asn1.h"
    "/root/CLionProjects/tshark_test/epan/ax25_pids.h"
    "/root/CLionProjects/tshark_test/epan/bridged_pids.h"
    "/root/CLionProjects/tshark_test/epan/capture_dissectors.h"
    "/root/CLionProjects/tshark_test/epan/charsets.h"
    "/root/CLionProjects/tshark_test/epan/chdlctypes.h"
    "/root/CLionProjects/tshark_test/epan/cisco_pid.h"
    "/root/CLionProjects/tshark_test/epan/color_filters.h"
    "/root/CLionProjects/tshark_test/epan/column.h"
    "/root/CLionProjects/tshark_test/epan/column-info.h"
    "/root/CLionProjects/tshark_test/epan/column-utils.h"
    "/root/CLionProjects/tshark_test/epan/conversation.h"
    "/root/CLionProjects/tshark_test/epan/conversation_debug.h"
    "/root/CLionProjects/tshark_test/epan/conversation_table.h"
    "/root/CLionProjects/tshark_test/epan/conv_id.h"
    "/root/CLionProjects/tshark_test/epan/crc10-tvb.h"
    "/root/CLionProjects/tshark_test/epan/crc16-tvb.h"
    "/root/CLionProjects/tshark_test/epan/crc32-tvb.h"
    "/root/CLionProjects/tshark_test/epan/crc6-tvb.h"
    "/root/CLionProjects/tshark_test/epan/crc8-tvb.h"
    "/root/CLionProjects/tshark_test/epan/decode_as.h"
    "/root/CLionProjects/tshark_test/epan/diam_dict.h"
    "/root/CLionProjects/tshark_test/epan/disabled_protos.h"
    "/root/CLionProjects/tshark_test/epan/conversation_filter.h"
    "/root/CLionProjects/tshark_test/epan/dtd.h"
    "/root/CLionProjects/tshark_test/epan/dtd_parse.h"
    "/root/CLionProjects/tshark_test/epan/dvb_chartbl.h"
    "/root/CLionProjects/tshark_test/epan/eap.h"
    "/root/CLionProjects/tshark_test/epan/eapol_keydes_types.h"
    "/root/CLionProjects/tshark_test/epan/epan.h"
    "/root/CLionProjects/tshark_test/epan/epan_dissect.h"
    "/root/CLionProjects/tshark_test/epan/etypes.h"
    "/root/CLionProjects/tshark_test/epan/ex-opt.h"
    "/root/CLionProjects/tshark_test/epan/except.h"
    "/root/CLionProjects/tshark_test/epan/exceptions.h"
    "/root/CLionProjects/tshark_test/epan/expert.h"
    "/root/CLionProjects/tshark_test/epan/export_object.h"
    "/root/CLionProjects/tshark_test/epan/exported_pdu.h"
    "/root/CLionProjects/tshark_test/epan/filter_expressions.h"
    "/root/CLionProjects/tshark_test/epan/follow.h"
    "/root/CLionProjects/tshark_test/epan/frame_data.h"
    "/root/CLionProjects/tshark_test/epan/frame_data_sequence.h"
    "/root/CLionProjects/tshark_test/epan/funnel.h"
    "/root/CLionProjects/tshark_test/epan/garrayfix.h"
    "/root/CLionProjects/tshark_test/epan/golay.h"
    "/root/CLionProjects/tshark_test/epan/guid-utils.h"
    "/root/CLionProjects/tshark_test/epan/iana_charsets.h"
    "/root/CLionProjects/tshark_test/epan/iax2_codec_type.h"
    "/root/CLionProjects/tshark_test/epan/in_cksum.h"
    "/root/CLionProjects/tshark_test/epan/ip_opts.h"
    "/root/CLionProjects/tshark_test/epan/ipproto.h"
    "/root/CLionProjects/tshark_test/epan/ipv4.h"
    "/root/CLionProjects/tshark_test/epan/ipv6.h"
    "/root/CLionProjects/tshark_test/epan/lapd_sapi.h"
    "/root/CLionProjects/tshark_test/epan/llcsaps.h"
    "/root/CLionProjects/tshark_test/epan/maxmind_db.h"
    "/root/CLionProjects/tshark_test/epan/media_params.h"
    "/root/CLionProjects/tshark_test/epan/next_tvb.h"
    "/root/CLionProjects/tshark_test/epan/nlpid.h"
    "/root/CLionProjects/tshark_test/epan/oids.h"
    "/root/CLionProjects/tshark_test/epan/osi-utils.h"
    "/root/CLionProjects/tshark_test/epan/oui.h"
    "/root/CLionProjects/tshark_test/epan/packet.h"
    "/root/CLionProjects/tshark_test/epan/packet_info.h"
    "/root/CLionProjects/tshark_test/epan/params.h"
    "/root/CLionProjects/tshark_test/epan/plugin_if.h"
    "/root/CLionProjects/tshark_test/epan/ppptypes.h"
    "/root/CLionProjects/tshark_test/epan/print.h"
    "/root/CLionProjects/tshark_test/epan/print_stream.h"
    "/root/CLionProjects/tshark_test/epan/prefs.h"
    "/root/CLionProjects/tshark_test/epan/prefs-int.h"
    "/root/CLionProjects/tshark_test/epan/proto.h"
    "/root/CLionProjects/tshark_test/epan/proto_data.h"
    "/root/CLionProjects/tshark_test/epan/ps.h"
    "/root/CLionProjects/tshark_test/epan/ptvcursor.h"
    "/root/CLionProjects/tshark_test/epan/range.h"
    "/root/CLionProjects/tshark_test/epan/reassemble.h"
    "/root/CLionProjects/tshark_test/epan/reedsolomon.h"
    "/root/CLionProjects/tshark_test/epan/register.h"
    "/root/CLionProjects/tshark_test/epan/req_resp_hdrs.h"
    "/root/CLionProjects/tshark_test/epan/rtd_table.h"
    "/root/CLionProjects/tshark_test/epan/rtp_pt.h"
    "/root/CLionProjects/tshark_test/epan/sctpppids.h"
    "/root/CLionProjects/tshark_test/epan/secrets.h"
    "/root/CLionProjects/tshark_test/epan/show_exception.h"
    "/root/CLionProjects/tshark_test/epan/slow_protocol_subtypes.h"
    "/root/CLionProjects/tshark_test/epan/sminmpec.h"
    "/root/CLionProjects/tshark_test/epan/srt_table.h"
    "/root/CLionProjects/tshark_test/epan/stat_tap_ui.h"
    "/root/CLionProjects/tshark_test/epan/stat_groups.h"
    "/root/CLionProjects/tshark_test/epan/stats_tree.h"
    "/root/CLionProjects/tshark_test/epan/stats_tree_priv.h"
    "/root/CLionProjects/tshark_test/epan/stream.h"
    "/root/CLionProjects/tshark_test/epan/strutil.h"
    "/root/CLionProjects/tshark_test/epan/t35.h"
    "/root/CLionProjects/tshark_test/epan/tap.h"
    "/root/CLionProjects/tshark_test/epan/tap-voip.h"
    "/root/CLionProjects/tshark_test/epan/timestamp.h"
    "/root/CLionProjects/tshark_test/epan/timestats.h"
    "/root/CLionProjects/tshark_test/epan/tfs.h"
    "/root/CLionProjects/tshark_test/epan/time_fmt.h"
    "/root/CLionProjects/tshark_test/epan/to_str.h"
    "/root/CLionProjects/tshark_test/epan/tvbparse.h"
    "/root/CLionProjects/tshark_test/epan/tvbuff.h"
    "/root/CLionProjects/tshark_test/epan/tvbuff-int.h"
    "/root/CLionProjects/tshark_test/epan/uat.h"
    "/root/CLionProjects/tshark_test/epan/uat-int.h"
    "/root/CLionProjects/tshark_test/epan/unit_strings.h"
    "/root/CLionProjects/tshark_test/epan/value_string.h"
    "/root/CLionProjects/tshark_test/epan/write_in_files_handlers.h"
    "/root/CLionProjects/tshark_test/epan/cJSON.h"
    "/root/CLionProjects/tshark_test/epan/writefile.h"
    "/root/CLionProjects/tshark_test/epan/x264_prt_id.h"
    "/root/CLionProjects/tshark_test/epan/xdlc.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/root/CLionProjects/tshark_test/epan/crypt/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/epan/dfilter/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/epan/dissectors/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/epan/ftypes/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/epan/wmem/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/epan/wslua/cmake_install.cmake")

endif()

