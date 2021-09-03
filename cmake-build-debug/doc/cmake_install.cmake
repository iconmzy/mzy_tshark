# Install script for directory: /home/ymq/tshark/doc

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES
    "/home/ymq/tshark/cmake-build-debug/doc/androiddump.1"
    "/home/ymq/tshark/cmake-build-debug/doc/capinfos.1"
    "/home/ymq/tshark/cmake-build-debug/doc/captype.1"
    "/home/ymq/tshark/cmake-build-debug/doc/ciscodump.1"
    "/home/ymq/tshark/cmake-build-debug/doc/ciscodump.1"
    "/home/ymq/tshark/cmake-build-debug/doc/dftest.1"
    "/home/ymq/tshark/cmake-build-debug/doc/dumpcap.1"
    "/home/ymq/tshark/cmake-build-debug/doc/editcap.1"
    "/home/ymq/tshark/cmake-build-debug/doc/mergecap.1"
    "/home/ymq/tshark/cmake-build-debug/doc/randpkt.1"
    "/home/ymq/tshark/cmake-build-debug/doc/randpktdump.1"
    "/home/ymq/tshark/cmake-build-debug/doc/rawshark.1"
    "/home/ymq/tshark/cmake-build-debug/doc/reordercap.1"
    "/home/ymq/tshark/cmake-build-debug/doc/sshdump.1"
    "/home/ymq/tshark/cmake-build-debug/doc/text2pcap.1"
    "/home/ymq/tshark/cmake-build-debug/doc/tshark.1"
    "/home/ymq/tshark/cmake-build-debug/doc/udpdump.1"
    "/home/ymq/tshark/cmake-build-debug/doc/wireshark.1"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man4" TYPE FILE FILES
    "/home/ymq/tshark/cmake-build-debug/doc/extcap.4"
    "/home/ymq/tshark/cmake-build-debug/doc/wireshark-filter.4"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/wireshark" TYPE FILE FILES
    "/home/ymq/tshark/cmake-build-debug/doc/androiddump.html"
    "/home/ymq/tshark/cmake-build-debug/doc/capinfos.html"
    "/home/ymq/tshark/cmake-build-debug/doc/captype.html"
    "/home/ymq/tshark/cmake-build-debug/doc/ciscodump.html"
    "/home/ymq/tshark/cmake-build-debug/doc/ciscodump.html"
    "/home/ymq/tshark/cmake-build-debug/doc/dftest.html"
    "/home/ymq/tshark/cmake-build-debug/doc/dumpcap.html"
    "/home/ymq/tshark/cmake-build-debug/doc/editcap.html"
    "/home/ymq/tshark/cmake-build-debug/doc/extcap.html"
    "/home/ymq/tshark/cmake-build-debug/doc/mergecap.html"
    "/home/ymq/tshark/cmake-build-debug/doc/randpkt.html"
    "/home/ymq/tshark/cmake-build-debug/doc/randpktdump.html"
    "/home/ymq/tshark/cmake-build-debug/doc/rawshark.html"
    "/home/ymq/tshark/cmake-build-debug/doc/reordercap.html"
    "/home/ymq/tshark/cmake-build-debug/doc/sshdump.html"
    "/home/ymq/tshark/cmake-build-debug/doc/text2pcap.html"
    "/home/ymq/tshark/cmake-build-debug/doc/tshark.html"
    "/home/ymq/tshark/cmake-build-debug/doc/udpdump.html"
    "/home/ymq/tshark/cmake-build-debug/doc/wireshark-filter.html"
    "/home/ymq/tshark/cmake-build-debug/doc/wireshark.html"
    )
endif()

