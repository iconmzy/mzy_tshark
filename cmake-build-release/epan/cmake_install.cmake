# Install script for directory: /root/CLionProjects/tshark_shanghai/epan

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
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/run/libwireshark.so.14.0.5"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/run/libwireshark.so.14"
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/run/libwireshark.so")
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
    "/root/CLionProjects/tshark_shanghai/epan/addr_and_mask.h"
    "/root/CLionProjects/tshark_shanghai/epan/addr_resolv.h"
    "/root/CLionProjects/tshark_shanghai/epan/address.h"
    "/root/CLionProjects/tshark_shanghai/epan/address_types.h"
    "/root/CLionProjects/tshark_shanghai/epan/afn.h"
    "/root/CLionProjects/tshark_shanghai/epan/aftypes.h"
    "/root/CLionProjects/tshark_shanghai/epan/app_mem_usage.h"
    "/root/CLionProjects/tshark_shanghai/epan/arcnet_pids.h"
    "/root/CLionProjects/tshark_shanghai/epan/arptypes.h"
    "/root/CLionProjects/tshark_shanghai/epan/asn1.h"
    "/root/CLionProjects/tshark_shanghai/epan/ax25_pids.h"
    "/root/CLionProjects/tshark_shanghai/epan/bridged_pids.h"
    "/root/CLionProjects/tshark_shanghai/epan/capture_dissectors.h"
    "/root/CLionProjects/tshark_shanghai/epan/charsets.h"
    "/root/CLionProjects/tshark_shanghai/epan/chdlctypes.h"
    "/root/CLionProjects/tshark_shanghai/epan/cisco_pid.h"
    "/root/CLionProjects/tshark_shanghai/epan/color_filters.h"
    "/root/CLionProjects/tshark_shanghai/epan/column.h"
    "/root/CLionProjects/tshark_shanghai/epan/column-info.h"
    "/root/CLionProjects/tshark_shanghai/epan/column-utils.h"
    "/root/CLionProjects/tshark_shanghai/epan/conversation.h"
    "/root/CLionProjects/tshark_shanghai/epan/conversation_debug.h"
    "/root/CLionProjects/tshark_shanghai/epan/conversation_table.h"
    "/root/CLionProjects/tshark_shanghai/epan/conv_id.h"
    "/root/CLionProjects/tshark_shanghai/epan/crc10-tvb.h"
    "/root/CLionProjects/tshark_shanghai/epan/crc16-tvb.h"
    "/root/CLionProjects/tshark_shanghai/epan/crc32-tvb.h"
    "/root/CLionProjects/tshark_shanghai/epan/crc6-tvb.h"
    "/root/CLionProjects/tshark_shanghai/epan/crc8-tvb.h"
    "/root/CLionProjects/tshark_shanghai/epan/decode_as.h"
    "/root/CLionProjects/tshark_shanghai/epan/diam_dict.h"
    "/root/CLionProjects/tshark_shanghai/epan/disabled_protos.h"
    "/root/CLionProjects/tshark_shanghai/epan/conversation_filter.h"
    "/root/CLionProjects/tshark_shanghai/epan/dtd.h"
    "/root/CLionProjects/tshark_shanghai/epan/dtd_parse.h"
    "/root/CLionProjects/tshark_shanghai/epan/dvb_chartbl.h"
    "/root/CLionProjects/tshark_shanghai/epan/eap.h"
    "/root/CLionProjects/tshark_shanghai/epan/eapol_keydes_types.h"
    "/root/CLionProjects/tshark_shanghai/epan/epan.h"
    "/root/CLionProjects/tshark_shanghai/epan/epan_dissect.h"
    "/root/CLionProjects/tshark_shanghai/epan/etypes.h"
    "/root/CLionProjects/tshark_shanghai/epan/ex-opt.h"
    "/root/CLionProjects/tshark_shanghai/epan/except.h"
    "/root/CLionProjects/tshark_shanghai/epan/exceptions.h"
    "/root/CLionProjects/tshark_shanghai/epan/expert.h"
    "/root/CLionProjects/tshark_shanghai/epan/export_object.h"
    "/root/CLionProjects/tshark_shanghai/epan/exported_pdu.h"
    "/root/CLionProjects/tshark_shanghai/epan/filter_expressions.h"
    "/root/CLionProjects/tshark_shanghai/epan/follow.h"
    "/root/CLionProjects/tshark_shanghai/epan/frame_data.h"
    "/root/CLionProjects/tshark_shanghai/epan/frame_data_sequence.h"
    "/root/CLionProjects/tshark_shanghai/epan/funnel.h"
    "/root/CLionProjects/tshark_shanghai/epan/garrayfix.h"
    "/root/CLionProjects/tshark_shanghai/epan/golay.h"
    "/root/CLionProjects/tshark_shanghai/epan/guid-utils.h"
    "/root/CLionProjects/tshark_shanghai/epan/iana_charsets.h"
    "/root/CLionProjects/tshark_shanghai/epan/iax2_codec_type.h"
    "/root/CLionProjects/tshark_shanghai/epan/in_cksum.h"
    "/root/CLionProjects/tshark_shanghai/epan/ip_opts.h"
    "/root/CLionProjects/tshark_shanghai/epan/ipproto.h"
    "/root/CLionProjects/tshark_shanghai/epan/ipv4.h"
    "/root/CLionProjects/tshark_shanghai/epan/ipv6.h"
    "/root/CLionProjects/tshark_shanghai/epan/lapd_sapi.h"
    "/root/CLionProjects/tshark_shanghai/epan/llcsaps.h"
    "/root/CLionProjects/tshark_shanghai/epan/maxmind_db.h"
    "/root/CLionProjects/tshark_shanghai/epan/media_params.h"
    "/root/CLionProjects/tshark_shanghai/epan/next_tvb.h"
    "/root/CLionProjects/tshark_shanghai/epan/nlpid.h"
    "/root/CLionProjects/tshark_shanghai/epan/oids.h"
    "/root/CLionProjects/tshark_shanghai/epan/osi-utils.h"
    "/root/CLionProjects/tshark_shanghai/epan/oui.h"
    "/root/CLionProjects/tshark_shanghai/epan/packet.h"
    "/root/CLionProjects/tshark_shanghai/epan/packet_info.h"
    "/root/CLionProjects/tshark_shanghai/epan/params.h"
    "/root/CLionProjects/tshark_shanghai/epan/plugin_if.h"
    "/root/CLionProjects/tshark_shanghai/epan/ppptypes.h"
    "/root/CLionProjects/tshark_shanghai/epan/print.h"
    "/root/CLionProjects/tshark_shanghai/epan/print_stream.h"
    "/root/CLionProjects/tshark_shanghai/epan/prefs.h"
    "/root/CLionProjects/tshark_shanghai/epan/prefs-int.h"
    "/root/CLionProjects/tshark_shanghai/epan/proto.h"
    "/root/CLionProjects/tshark_shanghai/epan/proto_data.h"
    "/root/CLionProjects/tshark_shanghai/epan/ps.h"
    "/root/CLionProjects/tshark_shanghai/epan/ptvcursor.h"
    "/root/CLionProjects/tshark_shanghai/epan/range.h"
    "/root/CLionProjects/tshark_shanghai/epan/reassemble.h"
    "/root/CLionProjects/tshark_shanghai/epan/reedsolomon.h"
    "/root/CLionProjects/tshark_shanghai/epan/register.h"
    "/root/CLionProjects/tshark_shanghai/epan/req_resp_hdrs.h"
    "/root/CLionProjects/tshark_shanghai/epan/rtd_table.h"
    "/root/CLionProjects/tshark_shanghai/epan/rtp_pt.h"
    "/root/CLionProjects/tshark_shanghai/epan/sctpppids.h"
    "/root/CLionProjects/tshark_shanghai/epan/secrets.h"
    "/root/CLionProjects/tshark_shanghai/epan/show_exception.h"
    "/root/CLionProjects/tshark_shanghai/epan/slow_protocol_subtypes.h"
    "/root/CLionProjects/tshark_shanghai/epan/sminmpec.h"
    "/root/CLionProjects/tshark_shanghai/epan/srt_table.h"
    "/root/CLionProjects/tshark_shanghai/epan/stat_tap_ui.h"
    "/root/CLionProjects/tshark_shanghai/epan/stat_groups.h"
    "/root/CLionProjects/tshark_shanghai/epan/stats_tree.h"
    "/root/CLionProjects/tshark_shanghai/epan/stats_tree_priv.h"
    "/root/CLionProjects/tshark_shanghai/epan/stream.h"
    "/root/CLionProjects/tshark_shanghai/epan/strutil.h"
    "/root/CLionProjects/tshark_shanghai/epan/t35.h"
    "/root/CLionProjects/tshark_shanghai/epan/tap.h"
    "/root/CLionProjects/tshark_shanghai/epan/tap-voip.h"
    "/root/CLionProjects/tshark_shanghai/epan/timestamp.h"
    "/root/CLionProjects/tshark_shanghai/epan/timestats.h"
    "/root/CLionProjects/tshark_shanghai/epan/tfs.h"
    "/root/CLionProjects/tshark_shanghai/epan/time_fmt.h"
    "/root/CLionProjects/tshark_shanghai/epan/to_str.h"
    "/root/CLionProjects/tshark_shanghai/epan/tvbparse.h"
    "/root/CLionProjects/tshark_shanghai/epan/tvbuff.h"
    "/root/CLionProjects/tshark_shanghai/epan/tvbuff-int.h"
    "/root/CLionProjects/tshark_shanghai/epan/uat.h"
    "/root/CLionProjects/tshark_shanghai/epan/uat-int.h"
    "/root/CLionProjects/tshark_shanghai/epan/unit_strings.h"
    "/root/CLionProjects/tshark_shanghai/epan/value_string.h"
    "/root/CLionProjects/tshark_shanghai/epan/write_in_files_handlers.h"
    "/root/CLionProjects/tshark_shanghai/epan/cJSON.h"
    "/root/CLionProjects/tshark_shanghai/epan/writefile.h"
    "/root/CLionProjects/tshark_shanghai/epan/rtp_media.h"
    "/root/CLionProjects/tshark_shanghai/epan/authorize.h"
    "/root/CLionProjects/tshark_shanghai/epan/x264_prt_id.h"
    "/root/CLionProjects/tshark_shanghai/epan/xdlc.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/epan/crypt/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dfilter/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dissectors/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/epan/ftypes/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/epan/wmem/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/epan/wslua/cmake_install.cmake")

endif()

