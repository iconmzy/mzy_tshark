# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/mzy/Downloads/clion-2019.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/mzy/Downloads/clion-2019.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/CLionProjects/tshark_gongjv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/CLionProjects/tshark_gongjv/cmake-build-debug

# Utility rule file for checkAPI_opcua.

# Include the progress variables for this target.
include plugins/epan/opcua/CMakeFiles/checkAPI_opcua.dir/progress.make

plugins/epan/opcua/CMakeFiles/checkAPI_opcua:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running checkAPI_opcua"
	cd /root/CLionProjects/tshark_gongjv/plugins/epan/opcua && /usr/bin/perl /root/CLionProjects/tshark_gongjv/tools/checkAPIs.pl -g abort -g termoutput opcua.c opcua_transport_layer.c opcua_security_layer.c opcua_application_layer.c opcua_serviceparser.c opcua_complextypeparser.c opcua_enumparser.c opcua_simpletypes.c opcua_servicetable.c opcua_extensionobjecttable.c opcua_hfindeces.c opcua_statuscode.c opcua_application_layer.h opcua_complextypeparser.h opcua_enumparser.h opcua_extensionobjectids.h opcua_hfindeces.h opcua_identifiers.h opcua_security_layer.h opcua_serviceids.h opcua_serviceparser.h opcua_servicetable.h opcua_simpletypes.h opcua_statuscode.h opcua_transport_layer.h

checkAPI_opcua: plugins/epan/opcua/CMakeFiles/checkAPI_opcua
checkAPI_opcua: plugins/epan/opcua/CMakeFiles/checkAPI_opcua.dir/build.make

.PHONY : checkAPI_opcua

# Rule to build all files generated by this target.
plugins/epan/opcua/CMakeFiles/checkAPI_opcua.dir/build: checkAPI_opcua

.PHONY : plugins/epan/opcua/CMakeFiles/checkAPI_opcua.dir/build

plugins/epan/opcua/CMakeFiles/checkAPI_opcua.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/opcua && $(CMAKE_COMMAND) -P CMakeFiles/checkAPI_opcua.dir/cmake_clean.cmake
.PHONY : plugins/epan/opcua/CMakeFiles/checkAPI_opcua.dir/clean

plugins/epan/opcua/CMakeFiles/checkAPI_opcua.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/plugins/epan/opcua /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/opcua /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/opcua/CMakeFiles/checkAPI_opcua.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/epan/opcua/CMakeFiles/checkAPI_opcua.dir/depend

