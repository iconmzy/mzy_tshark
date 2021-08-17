# Install script for directory: /root/CLionProjects/tshark_test

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tshark" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tshark")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tshark"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_test/run/tshark")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tshark" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tshark")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tshark"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tshark")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/sharkd" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/sharkd")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/sharkd"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_test/run/sharkd")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/sharkd" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/sharkd")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/sharkd"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/sharkd")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/randpkt" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/randpkt")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/randpkt"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_test/run/randpkt")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/randpkt" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/randpkt")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/randpkt"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/randpkt")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/text2pcap" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/text2pcap")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/text2pcap"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_test/run/text2pcap")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/text2pcap" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/text2pcap")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/text2pcap"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/text2pcap")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mergecap" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mergecap")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mergecap"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_test/run/mergecap")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mergecap" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mergecap")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mergecap"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mergecap")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/reordercap" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/reordercap")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/reordercap"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_test/run/reordercap")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/reordercap" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/reordercap")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/reordercap"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/reordercap")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/capinfos" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/capinfos")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/capinfos"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_test/run/capinfos")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/capinfos" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/capinfos")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/capinfos"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/capinfos")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/captype" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/captype")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/captype"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_test/run/captype")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/captype" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/captype")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/captype"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/captype")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/editcap" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/editcap")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/editcap"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_test/run/editcap")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/editcap" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/editcap")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/editcap"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/editcap")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/dumpcap" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/dumpcap")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/dumpcap"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "/root/CLionProjects/tshark_test/run/dumpcap")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/dumpcap" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/dumpcap")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/dumpcap"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/dumpcap")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/idl2wrs" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/idl2wrs")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/idl2wrs"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_test/run/idl2wrs")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/idl2wrs" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/idl2wrs")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/idl2wrs"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/idl2wrs")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mmdbresolve" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mmdbresolve")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mmdbresolve"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_test/run/mmdbresolve")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mmdbresolve" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mmdbresolve")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mmdbresolve"
         OLD_RPATH "::::::::::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mmdbresolve")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/wireshark" TYPE FILE PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ FILES
    "/root/CLionProjects/tshark_test/cfilters"
    "/root/CLionProjects/tshark_test/colorfilters"
    "/root/CLionProjects/tshark_test/dfilters"
    "/root/CLionProjects/tshark_test/dfilter_macros"
    "/root/CLionProjects/tshark_test/enterprises.tsv"
    "/root/CLionProjects/tshark_test/ipmap.html"
    "/root/CLionProjects/tshark_test/manuf"
    "/root/CLionProjects/tshark_test/pdml2html.xsl"
    "/root/CLionProjects/tshark_test/services"
    "/root/CLionProjects/tshark_test/smi_modules"
    "/root/CLionProjects/tshark_test/wka"
    "/root/CLionProjects/tshark_test/docbook/ws.css"
    "/root/CLionProjects/tshark_test/doc/AUTHORS-SHORT"
    "/root/CLionProjects/tshark_test/doc/androiddump.html"
    "/root/CLionProjects/tshark_test/doc/udpdump.html"
    "/root/CLionProjects/tshark_test/doc/capinfos.html"
    "/root/CLionProjects/tshark_test/doc/captype.html"
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
    "/root/CLionProjects/tshark_test/doc/wireshark.html"
    "/root/CLionProjects/tshark_test/doc/wireshark-filter.html"
    "/root/CLionProjects/tshark_test/doc/mmdbresolve.html"
    "/root/CLionProjects/tshark_test/COPYING"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/wireshark" TYPE FILE FILES
    "/root/CLionProjects/tshark_test/cfile.h"
    "/root/CLionProjects/tshark_test/cli_main.h"
    "/root/CLionProjects/tshark_test/file.h"
    "/root/CLionProjects/tshark_test/globals.h"
    "/root/CLionProjects/tshark_test/log.h"
    "/root/CLionProjects/tshark_test/ws_attributes.h"
    "/root/CLionProjects/tshark_test/ws_compiler_tests.h"
    "/root/CLionProjects/tshark_test/ws_diag_control.h"
    "/root/CLionProjects/tshark_test/ws_symbol_export.h"
    "/root/CLionProjects/tshark_test/version_info.h"
    "/root/CLionProjects/tshark_test/ws_version.h"
    "/root/CLionProjects/tshark_test/epan/write_in_files_handlers.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/pkgconfig" TYPE FILE FILES "/root/CLionProjects/tshark_test/wireshark.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/wireshark" TYPE DIRECTORY PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ DIR_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ FILES
    "/root/CLionProjects/tshark_test/diameter"
    "/root/CLionProjects/tshark_test/dtds"
    "/root/CLionProjects/tshark_test/profiles"
    "/root/CLionProjects/tshark_test/radius"
    "/root/CLionProjects/tshark_test/tpncp"
    "/root/CLionProjects/tshark_test/wimaxasncp"
    REGEX "/\\.git$" EXCLUDE REGEX "/\\.svn$" EXCLUDE REGEX "/Makefile\\.[^/]*$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake" TYPE FILE FILES
    "/root/CLionProjects/tshark_test/cmake/modules/FindGLIB2.cmake"
    "/root/CLionProjects/tshark_test/cmake/modules/FindWSLibrary.cmake"
    "/root/CLionProjects/tshark_test/cmake/modules/FindWSWinLibs.cmake"
    "/root/CLionProjects/tshark_test/cmake/modules/UseAsn2Wrs.cmake"
    "/root/CLionProjects/tshark_test/cmake/modules/LocatePythonModule.cmake"
    "/root/CLionProjects/tshark_test/cmake/modules/UseMakePluginReg.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake" TYPE FILE FILES
    "/root/CLionProjects/tshark_test/WiresharkConfig.cmake"
    "/root/CLionProjects/tshark_test/WiresharkConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake/WiresharkTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake/WiresharkTargets.cmake"
         "/root/CLionProjects/tshark_test/CMakeFiles/Export/lib64/wireshark/cmake/WiresharkTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake/WiresharkTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake/WiresharkTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake" TYPE FILE FILES "/root/CLionProjects/tshark_test/CMakeFiles/Export/lib64/wireshark/cmake/WiresharkTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake" TYPE FILE FILES "/root/CLionProjects/tshark_test/CMakeFiles/Export/lib64/wireshark/cmake/WiresharkTargets-debug.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/root/CLionProjects/tshark_test/capchild/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/caputils/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/doc/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/epan/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/extcap/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/randpkt_core/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/tools/lemon/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/ui/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/wiretap/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/writecap/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/wsutil/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/ethercat/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/gryphon/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/irda/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/mate/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/opcua/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/profinet/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/stats_tree/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/transum/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/unistim/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/wimax/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/wimaxasncp/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/epan/wimaxmacphy/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/wiretap/usbdump/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/codecs/G711/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/codecs/l16_mono/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/codecs/G722/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/codecs/G726/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/codecs/iLBC/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/codecs/opus_dec/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/plugins/codecs/sbc/cmake_install.cmake")
  include("/root/CLionProjects/tshark_test/fuzz/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/root/CLionProjects/tshark_test/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
