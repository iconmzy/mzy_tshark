# Install script for directory: /root/CLionProjects/tshark_shanghai

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/aurora" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/aurora")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/aurora"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/run/aurora")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/aurora" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/aurora")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/aurora"
         OLD_RPATH "$ORIGIN:::::::::"
         NEW_RPATH "/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/aurora")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/run/randpkt")
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/reordercap" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/reordercap")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/reordercap"
         RPATH "/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/run/reordercap")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/run/capinfos")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/run/captype")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/run/editcap")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/run/dumpcap")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/run/idl2wrs")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/wireshark" TYPE FILE PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ FILES
    "/root/CLionProjects/tshark_shanghai/cfilters"
    "/root/CLionProjects/tshark_shanghai/colorfilters"
    "/root/CLionProjects/tshark_shanghai/dfilters"
    "/root/CLionProjects/tshark_shanghai/dfilter_macros"
    "/root/CLionProjects/tshark_shanghai/enterprises.tsv"
    "/root/CLionProjects/tshark_shanghai/ipmap.html"
    "/root/CLionProjects/tshark_shanghai/manuf"
    "/root/CLionProjects/tshark_shanghai/pdml2html.xsl"
    "/root/CLionProjects/tshark_shanghai/services"
    "/root/CLionProjects/tshark_shanghai/smi_modules"
    "/root/CLionProjects/tshark_shanghai/wka"
    "/root/CLionProjects/tshark_shanghai/docbook/ws.css"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/AUTHORS-SHORT"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/androiddump.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/udpdump.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/capinfos.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/captype.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/ciscodump.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/dftest.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/dumpcap.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/editcap.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/extcap.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/mergecap.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/randpkt.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/randpktdump.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/rawshark.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/reordercap.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/sshdump.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/text2pcap.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/tshark.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/wireshark.html"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/wireshark-filter.html"
    "/root/CLionProjects/tshark_shanghai/COPYING"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/wireshark" TYPE FILE FILES
    "/root/CLionProjects/tshark_shanghai/cfile.h"
    "/root/CLionProjects/tshark_shanghai/cli_main.h"
    "/root/CLionProjects/tshark_shanghai/file.h"
    "/root/CLionProjects/tshark_shanghai/globals.h"
    "/root/CLionProjects/tshark_shanghai/log.h"
    "/root/CLionProjects/tshark_shanghai/ws_attributes.h"
    "/root/CLionProjects/tshark_shanghai/ws_compiler_tests.h"
    "/root/CLionProjects/tshark_shanghai/ws_diag_control.h"
    "/root/CLionProjects/tshark_shanghai/ws_symbol_export.h"
    "/root/CLionProjects/tshark_shanghai/version_info.h"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/ws_version.h"
    "/root/CLionProjects/tshark_shanghai/epan/write_in_files_handlers.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/pkgconfig" TYPE FILE FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/wireshark.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/wireshark" TYPE DIRECTORY PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ DIR_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ FILES
    "/root/CLionProjects/tshark_shanghai/diameter"
    "/root/CLionProjects/tshark_shanghai/dtds"
    "/root/CLionProjects/tshark_shanghai/profiles"
    "/root/CLionProjects/tshark_shanghai/radius"
    "/root/CLionProjects/tshark_shanghai/tpncp"
    "/root/CLionProjects/tshark_shanghai/wimaxasncp"
    REGEX "/\\.git$" EXCLUDE REGEX "/\\.svn$" EXCLUDE REGEX "/Makefile\\.[^/]*$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake" TYPE FILE FILES
    "/root/CLionProjects/tshark_shanghai/cmake/modules/FindGLIB2.cmake"
    "/root/CLionProjects/tshark_shanghai/cmake/modules/FindWSLibrary.cmake"
    "/root/CLionProjects/tshark_shanghai/cmake/modules/FindWSWinLibs.cmake"
    "/root/CLionProjects/tshark_shanghai/cmake/modules/UseAsn2Wrs.cmake"
    "/root/CLionProjects/tshark_shanghai/cmake/modules/LocatePythonModule.cmake"
    "/root/CLionProjects/tshark_shanghai/cmake/modules/UseMakePluginReg.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake" TYPE FILE FILES
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/WiresharkConfig.cmake"
    "/root/CLionProjects/tshark_shanghai/cmake-build-release/WiresharkConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake/WiresharkTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake/WiresharkTargets.cmake"
         "/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles/Export/lib64/wireshark/cmake/WiresharkTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake/WiresharkTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake/WiresharkTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake" TYPE FILE FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles/Export/lib64/wireshark/cmake/WiresharkTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/wireshark/cmake" TYPE FILE FILES "/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles/Export/lib64/wireshark/cmake/WiresharkTargets-release.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/capchild/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/caputils/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/doc/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/epan/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/extcap/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/randpkt_core/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/tools/lemon/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/ui/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/wiretap/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/writecap/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/wsutil/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/ethercat/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/gryphon/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/irda/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/mate/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/opcua/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/profinet/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/stats_tree/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/unistim/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/wimax/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/wimaxasncp/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/wimaxmacphy/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/wiretap/usbdump/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G711/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/l16_mono/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G726/cmake_install.cmake")
  include("/root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G729/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/root/CLionProjects/tshark_shanghai/cmake-build-release/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
