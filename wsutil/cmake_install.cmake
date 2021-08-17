# Install script for directory: /root/CLionProjects/tshark_test/wsutil

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwsutil.so.12.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwsutil.so.12"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/usr/local/lib64")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/root/CLionProjects/tshark_test/run/libwsutil.so.12.0.0"
    "/root/CLionProjects/tshark_test/run/libwsutil.so.12"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwsutil.so.12.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwsutil.so.12"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "::::::::::::::::"
           NEW_RPATH "/usr/local/lib64")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwsutil.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwsutil.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwsutil.so"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/root/CLionProjects/tshark_test/run/libwsutil.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwsutil.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwsutil.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwsutil.so"
         OLD_RPATH "::::::::::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libwsutil.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/wireshark/wsutil" TYPE FILE FILES
    "/root/CLionProjects/tshark_test/wsutil/adler32.h"
    "/root/CLionProjects/tshark_test/wsutil/base32.h"
    "/root/CLionProjects/tshark_test/wsutil/bits_count_ones.h"
    "/root/CLionProjects/tshark_test/wsutil/bits_ctz.h"
    "/root/CLionProjects/tshark_test/wsutil/bitswap.h"
    "/root/CLionProjects/tshark_test/wsutil/buffer.h"
    "/root/CLionProjects/tshark_test/wsutil/codecs.h"
    "/root/CLionProjects/tshark_test/wsutil/color.h"
    "/root/CLionProjects/tshark_test/wsutil/copyright_info.h"
    "/root/CLionProjects/tshark_test/wsutil/cpu_info.h"
    "/root/CLionProjects/tshark_test/wsutil/crash_info.h"
    "/root/CLionProjects/tshark_test/wsutil/crc5.h"
    "/root/CLionProjects/tshark_test/wsutil/crc6.h"
    "/root/CLionProjects/tshark_test/wsutil/crc7.h"
    "/root/CLionProjects/tshark_test/wsutil/crc8.h"
    "/root/CLionProjects/tshark_test/wsutil/crc10.h"
    "/root/CLionProjects/tshark_test/wsutil/crc11.h"
    "/root/CLionProjects/tshark_test/wsutil/crc16.h"
    "/root/CLionProjects/tshark_test/wsutil/crc16-plain.h"
    "/root/CLionProjects/tshark_test/wsutil/crc32.h"
    "/root/CLionProjects/tshark_test/wsutil/curve25519.h"
    "/root/CLionProjects/tshark_test/wsutil/eax.h"
    "/root/CLionProjects/tshark_test/wsutil/epochs.h"
    "/root/CLionProjects/tshark_test/wsutil/filesystem.h"
    "/root/CLionProjects/tshark_test/wsutil/frequency-utils.h"
    "/root/CLionProjects/tshark_test/wsutil/g711.h"
    "/root/CLionProjects/tshark_test/wsutil/inet_addr.h"
    "/root/CLionProjects/tshark_test/wsutil/inet_ipv4.h"
    "/root/CLionProjects/tshark_test/wsutil/inet_ipv6.h"
    "/root/CLionProjects/tshark_test/wsutil/interface.h"
    "/root/CLionProjects/tshark_test/wsutil/jsmn.h"
    "/root/CLionProjects/tshark_test/wsutil/json_dumper.h"
    "/root/CLionProjects/tshark_test/wsutil/mpeg-audio.h"
    "/root/CLionProjects/tshark_test/wsutil/netlink.h"
    "/root/CLionProjects/tshark_test/wsutil/nstime.h"
    "/root/CLionProjects/tshark_test/wsutil/os_version_info.h"
    "/root/CLionProjects/tshark_test/wsutil/pint.h"
    "/root/CLionProjects/tshark_test/wsutil/please_report_bug.h"
    "/root/CLionProjects/tshark_test/wsutil/plugins.h"
    "/root/CLionProjects/tshark_test/wsutil/pow2.h"
    "/root/CLionProjects/tshark_test/wsutil/privileges.h"
    "/root/CLionProjects/tshark_test/wsutil/processes.h"
    "/root/CLionProjects/tshark_test/wsutil/report_message.h"
    "/root/CLionProjects/tshark_test/wsutil/sign_ext.h"
    "/root/CLionProjects/tshark_test/wsutil/sober128.h"
    "/root/CLionProjects/tshark_test/wsutil/socket.h"
    "/root/CLionProjects/tshark_test/wsutil/str_util.h"
    "/root/CLionProjects/tshark_test/wsutil/strnatcmp.h"
    "/root/CLionProjects/tshark_test/wsutil/strtoi.h"
    "/root/CLionProjects/tshark_test/wsutil/tempfile.h"
    "/root/CLionProjects/tshark_test/wsutil/time_util.h"
    "/root/CLionProjects/tshark_test/wsutil/type_util.h"
    "/root/CLionProjects/tshark_test/wsutil/unicode-utils.h"
    "/root/CLionProjects/tshark_test/wsutil/utf8_entities.h"
    "/root/CLionProjects/tshark_test/wsutil/ws_cpuid.h"
    "/root/CLionProjects/tshark_test/wsutil/ws_mempbrk.h"
    "/root/CLionProjects/tshark_test/wsutil/ws_mempbrk_int.h"
    "/root/CLionProjects/tshark_test/wsutil/ws_pipe.h"
    "/root/CLionProjects/tshark_test/wsutil/ws_printf.h"
    "/root/CLionProjects/tshark_test/wsutil/wsjson.h"
    "/root/CLionProjects/tshark_test/wsutil/xtea.h"
    )
endif()

