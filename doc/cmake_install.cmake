# Install script for directory: /root/CLionProjects/tshark_test/doc

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES
    "/root/CLionProjects/tshark_test/doc/androiddump.1"
    "/root/CLionProjects/tshark_test/doc/capinfos.1"
    "/root/CLionProjects/tshark_test/doc/captype.1"
    "/root/CLionProjects/tshark_test/doc/ciscodump.1"
    "/root/CLionProjects/tshark_test/doc/ciscodump.1"
    "/root/CLionProjects/tshark_test/doc/dftest.1"
    "/root/CLionProjects/tshark_test/doc/dumpcap.1"
    "/root/CLionProjects/tshark_test/doc/editcap.1"
    "/root/CLionProjects/tshark_test/doc/mergecap.1"
    "/root/CLionProjects/tshark_test/doc/randpkt.1"
    "/root/CLionProjects/tshark_test/doc/randpktdump.1"
    "/root/CLionProjects/tshark_test/doc/rawshark.1"
    "/root/CLionProjects/tshark_test/doc/reordercap.1"
    "/root/CLionProjects/tshark_test/doc/sshdump.1"
    "/root/CLionProjects/tshark_test/doc/text2pcap.1"
    "/root/CLionProjects/tshark_test/doc/tshark.1"
    "/root/CLionProjects/tshark_test/doc/udpdump.1"
    "/root/CLionProjects/tshark_test/doc/wireshark.1"
    "/root/CLionProjects/tshark_test/doc/dpauxmon.1"
    "/root/CLionProjects/tshark_test/doc/sdjournal.1"
    "/root/CLionProjects/tshark_test/doc/mmdbresolve.1"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man4" TYPE FILE FILES
    "/root/CLionProjects/tshark_test/doc/extcap.4"
    "/root/CLionProjects/tshark_test/doc/wireshark-filter.4"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/wireshark" TYPE FILE FILES
    "/root/CLionProjects/tshark_test/doc/androiddump.html"
    "/root/CLionProjects/tshark_test/doc/capinfos.html"
    "/root/CLionProjects/tshark_test/doc/captype.html"
    "/root/CLionProjects/tshark_test/doc/ciscodump.html"
    "/root/CLionProjects/tshark_test/doc/ciscodump.html"
    "/root/CLionProjects/tshark_test/doc/dftest.html"
    "/root/CLionProjects/tshark_test/doc/dumpcap.html"
    "/root/CLionProjects/tshark_test/doc/editcap.html"
    "/root/CLionProjects/tshark_test/doc/extcap.html"
    "/root/CLionProjects/tshark_test/doc/mergecap.html"
    "/root/CLionProjects/tshark_test/doc/randpkt.html"
    "/root/CLionProjects/tshark_test/doc/randpktdump.html"
    "/root/CLionProjects/tshark_test/doc/rawshark.html"
    "/root/CLionProjects/tshark_test/doc/reordercap.html"
    "/root/CLionProjects/tshark_test/doc/sshdump.html"
    "/root/CLionProjects/tshark_test/doc/text2pcap.html"
    "/root/CLionProjects/tshark_test/doc/tshark.html"
    "/root/CLionProjects/tshark_test/doc/udpdump.html"
    "/root/CLionProjects/tshark_test/doc/wireshark-filter.html"
    "/root/CLionProjects/tshark_test/doc/wireshark.html"
    "/root/CLionProjects/tshark_test/doc/dpauxmon.html"
    "/root/CLionProjects/tshark_test/doc/sdjournal.html"
    "/root/CLionProjects/tshark_test/doc/mmdbresolve.html"
    )
endif()

