# Install script for directory: /home/ymq/tshark/epan

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

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
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
    "/home/ymq/tshark/cmake-build-debug/run/libwireshark.so.14.0.5"
    "/home/ymq/tshark/cmake-build-debug/run/libwireshark.so.14"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so.14.0.5"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so.14"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "\$ORIGIN:::::::::"
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/ymq/tshark/cmake-build-debug/run/libwireshark.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so"
         OLD_RPATH "\$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwireshark.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/wireshark/epan" TYPE FILE FILES
    "/home/ymq/tshark/epan/addr_and_mask.h"
    "/home/ymq/tshark/epan/addr_resolv.h"
    "/home/ymq/tshark/epan/address.h"
    "/home/ymq/tshark/epan/address_types.h"
    "/home/ymq/tshark/epan/afn.h"
    "/home/ymq/tshark/epan/aftypes.h"
    "/home/ymq/tshark/epan/app_mem_usage.h"
    "/home/ymq/tshark/epan/arcnet_pids.h"
    "/home/ymq/tshark/epan/arptypes.h"
    "/home/ymq/tshark/epan/asn1.h"
    "/home/ymq/tshark/epan/ax25_pids.h"
    "/home/ymq/tshark/epan/bridged_pids.h"
    "/home/ymq/tshark/epan/capture_dissectors.h"
    "/home/ymq/tshark/epan/charsets.h"
    "/home/ymq/tshark/epan/chdlctypes.h"
    "/home/ymq/tshark/epan/cisco_pid.h"
    "/home/ymq/tshark/epan/color_filters.h"
    "/home/ymq/tshark/epan/column.h"
    "/home/ymq/tshark/epan/column-info.h"
    "/home/ymq/tshark/epan/column-utils.h"
    "/home/ymq/tshark/epan/conversation.h"
    "/home/ymq/tshark/epan/conversation_debug.h"
    "/home/ymq/tshark/epan/conversation_table.h"
    "/home/ymq/tshark/epan/conv_id.h"
    "/home/ymq/tshark/epan/crc10-tvb.h"
    "/home/ymq/tshark/epan/crc16-tvb.h"
    "/home/ymq/tshark/epan/crc32-tvb.h"
    "/home/ymq/tshark/epan/crc6-tvb.h"
    "/home/ymq/tshark/epan/crc8-tvb.h"
    "/home/ymq/tshark/epan/decode_as.h"
    "/home/ymq/tshark/epan/diam_dict.h"
    "/home/ymq/tshark/epan/disabled_protos.h"
    "/home/ymq/tshark/epan/conversation_filter.h"
    "/home/ymq/tshark/epan/dtd.h"
    "/home/ymq/tshark/epan/dtd_parse.h"
    "/home/ymq/tshark/epan/dvb_chartbl.h"
    "/home/ymq/tshark/epan/eap.h"
    "/home/ymq/tshark/epan/eapol_keydes_types.h"
    "/home/ymq/tshark/epan/epan.h"
    "/home/ymq/tshark/epan/epan_dissect.h"
    "/home/ymq/tshark/epan/etypes.h"
    "/home/ymq/tshark/epan/ex-opt.h"
    "/home/ymq/tshark/epan/except.h"
    "/home/ymq/tshark/epan/exceptions.h"
    "/home/ymq/tshark/epan/expert.h"
    "/home/ymq/tshark/epan/export_object.h"
    "/home/ymq/tshark/epan/exported_pdu.h"
    "/home/ymq/tshark/epan/filter_expressions.h"
    "/home/ymq/tshark/epan/follow.h"
    "/home/ymq/tshark/epan/frame_data.h"
    "/home/ymq/tshark/epan/frame_data_sequence.h"
    "/home/ymq/tshark/epan/funnel.h"
    "/home/ymq/tshark/epan/garrayfix.h"
    "/home/ymq/tshark/epan/golay.h"
    "/home/ymq/tshark/epan/guid-utils.h"
    "/home/ymq/tshark/epan/iana_charsets.h"
    "/home/ymq/tshark/epan/iax2_codec_type.h"
    "/home/ymq/tshark/epan/in_cksum.h"
    "/home/ymq/tshark/epan/ip_opts.h"
    "/home/ymq/tshark/epan/ipproto.h"
    "/home/ymq/tshark/epan/ipv4.h"
    "/home/ymq/tshark/epan/ipv6.h"
    "/home/ymq/tshark/epan/lapd_sapi.h"
    "/home/ymq/tshark/epan/llcsaps.h"
    "/home/ymq/tshark/epan/maxmind_db.h"
    "/home/ymq/tshark/epan/media_params.h"
    "/home/ymq/tshark/epan/next_tvb.h"
    "/home/ymq/tshark/epan/nlpid.h"
    "/home/ymq/tshark/epan/oids.h"
    "/home/ymq/tshark/epan/osi-utils.h"
    "/home/ymq/tshark/epan/oui.h"
    "/home/ymq/tshark/epan/packet.h"
    "/home/ymq/tshark/epan/packet_info.h"
    "/home/ymq/tshark/epan/params.h"
    "/home/ymq/tshark/epan/plugin_if.h"
    "/home/ymq/tshark/epan/ppptypes.h"
    "/home/ymq/tshark/epan/print.h"
    "/home/ymq/tshark/epan/print_stream.h"
    "/home/ymq/tshark/epan/prefs.h"
    "/home/ymq/tshark/epan/prefs-int.h"
    "/home/ymq/tshark/epan/proto.h"
    "/home/ymq/tshark/epan/proto_data.h"
    "/home/ymq/tshark/epan/ps.h"
    "/home/ymq/tshark/epan/ptvcursor.h"
    "/home/ymq/tshark/epan/range.h"
    "/home/ymq/tshark/epan/reassemble.h"
    "/home/ymq/tshark/epan/reedsolomon.h"
    "/home/ymq/tshark/epan/register.h"
    "/home/ymq/tshark/epan/req_resp_hdrs.h"
    "/home/ymq/tshark/epan/rtd_table.h"
    "/home/ymq/tshark/epan/rtp_pt.h"
    "/home/ymq/tshark/epan/sctpppids.h"
    "/home/ymq/tshark/epan/secrets.h"
    "/home/ymq/tshark/epan/show_exception.h"
    "/home/ymq/tshark/epan/slow_protocol_subtypes.h"
    "/home/ymq/tshark/epan/sminmpec.h"
    "/home/ymq/tshark/epan/srt_table.h"
    "/home/ymq/tshark/epan/stat_tap_ui.h"
    "/home/ymq/tshark/epan/stat_groups.h"
    "/home/ymq/tshark/epan/stats_tree.h"
    "/home/ymq/tshark/epan/stats_tree_priv.h"
    "/home/ymq/tshark/epan/stream.h"
    "/home/ymq/tshark/epan/strutil.h"
    "/home/ymq/tshark/epan/t35.h"
    "/home/ymq/tshark/epan/tap.h"
    "/home/ymq/tshark/epan/tap-voip.h"
    "/home/ymq/tshark/epan/timestamp.h"
    "/home/ymq/tshark/epan/timestats.h"
    "/home/ymq/tshark/epan/tfs.h"
    "/home/ymq/tshark/epan/time_fmt.h"
    "/home/ymq/tshark/epan/to_str.h"
    "/home/ymq/tshark/epan/tvbparse.h"
    "/home/ymq/tshark/epan/tvbuff.h"
    "/home/ymq/tshark/epan/tvbuff-int.h"
    "/home/ymq/tshark/epan/uat.h"
    "/home/ymq/tshark/epan/uat-int.h"
    "/home/ymq/tshark/epan/unit_strings.h"
    "/home/ymq/tshark/epan/value_string.h"
    "/home/ymq/tshark/epan/write_in_files_handlers.h"
    "/home/ymq/tshark/epan/cJSON.h"
    "/home/ymq/tshark/epan/writefile.h"
    "/home/ymq/tshark/epan/x264_prt_id.h"
    "/home/ymq/tshark/epan/xdlc.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ymq/tshark/cmake-build-debug/epan/crypt/cmake_install.cmake")
  include("/home/ymq/tshark/cmake-build-debug/epan/dfilter/cmake_install.cmake")
  include("/home/ymq/tshark/cmake-build-debug/epan/dissectors/cmake_install.cmake")
  include("/home/ymq/tshark/cmake-build-debug/epan/ftypes/cmake_install.cmake")
  include("/home/ymq/tshark/cmake-build-debug/epan/wmem/cmake_install.cmake")
  include("/home/ymq/tshark/cmake-build-debug/epan/wslua/cmake_install.cmake")

endif()

