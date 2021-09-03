# Install script for directory: /home/ymq/tshark/wsutil

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
    "/home/ymq/tshark/cmake-build-debug/run/libwsutil.so.12.0.0"
    "/home/ymq/tshark/cmake-build-debug/run/libwsutil.so.12"
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/ymq/tshark/cmake-build-debug/run/libwsutil.so")
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
    "/home/ymq/tshark/wsutil/adler32.h"
    "/home/ymq/tshark/wsutil/base32.h"
    "/home/ymq/tshark/wsutil/bits_count_ones.h"
    "/home/ymq/tshark/wsutil/bits_ctz.h"
    "/home/ymq/tshark/wsutil/bitswap.h"
    "/home/ymq/tshark/wsutil/buffer.h"
    "/home/ymq/tshark/wsutil/codecs.h"
    "/home/ymq/tshark/wsutil/color.h"
    "/home/ymq/tshark/wsutil/copyright_info.h"
    "/home/ymq/tshark/wsutil/cpu_info.h"
    "/home/ymq/tshark/wsutil/crash_info.h"
    "/home/ymq/tshark/wsutil/crc5.h"
    "/home/ymq/tshark/wsutil/crc6.h"
    "/home/ymq/tshark/wsutil/crc7.h"
    "/home/ymq/tshark/wsutil/crc8.h"
    "/home/ymq/tshark/wsutil/crc10.h"
    "/home/ymq/tshark/wsutil/crc11.h"
    "/home/ymq/tshark/wsutil/crc16.h"
    "/home/ymq/tshark/wsutil/crc16-plain.h"
    "/home/ymq/tshark/wsutil/crc32.h"
    "/home/ymq/tshark/wsutil/curve25519.h"
    "/home/ymq/tshark/wsutil/eax.h"
    "/home/ymq/tshark/wsutil/epochs.h"
    "/home/ymq/tshark/wsutil/filesystem.h"
    "/home/ymq/tshark/wsutil/frequency-utils.h"
    "/home/ymq/tshark/wsutil/g711.h"
    "/home/ymq/tshark/wsutil/inet_addr.h"
    "/home/ymq/tshark/wsutil/inet_ipv4.h"
    "/home/ymq/tshark/wsutil/inet_ipv6.h"
    "/home/ymq/tshark/wsutil/interface.h"
    "/home/ymq/tshark/wsutil/jsmn.h"
    "/home/ymq/tshark/wsutil/json_dumper.h"
    "/home/ymq/tshark/wsutil/mpeg-audio.h"
    "/home/ymq/tshark/wsutil/netlink.h"
    "/home/ymq/tshark/wsutil/nstime.h"
    "/home/ymq/tshark/wsutil/os_version_info.h"
    "/home/ymq/tshark/wsutil/pint.h"
    "/home/ymq/tshark/wsutil/please_report_bug.h"
    "/home/ymq/tshark/wsutil/plugins.h"
    "/home/ymq/tshark/wsutil/pow2.h"
    "/home/ymq/tshark/wsutil/privileges.h"
    "/home/ymq/tshark/wsutil/processes.h"
    "/home/ymq/tshark/wsutil/report_message.h"
    "/home/ymq/tshark/wsutil/sign_ext.h"
    "/home/ymq/tshark/wsutil/sober128.h"
    "/home/ymq/tshark/wsutil/socket.h"
    "/home/ymq/tshark/wsutil/str_util.h"
    "/home/ymq/tshark/wsutil/strnatcmp.h"
    "/home/ymq/tshark/wsutil/strtoi.h"
    "/home/ymq/tshark/wsutil/tempfile.h"
    "/home/ymq/tshark/wsutil/time_util.h"
    "/home/ymq/tshark/wsutil/type_util.h"
    "/home/ymq/tshark/wsutil/unicode-utils.h"
    "/home/ymq/tshark/wsutil/utf8_entities.h"
    "/home/ymq/tshark/wsutil/ws_cpuid.h"
    "/home/ymq/tshark/wsutil/ws_mempbrk.h"
    "/home/ymq/tshark/wsutil/ws_mempbrk_int.h"
    "/home/ymq/tshark/wsutil/ws_pipe.h"
    "/home/ymq/tshark/wsutil/ws_printf.h"
    "/home/ymq/tshark/wsutil/wsjson.h"
    "/home/ymq/tshark/wsutil/xtea.h"
    )
endif()

