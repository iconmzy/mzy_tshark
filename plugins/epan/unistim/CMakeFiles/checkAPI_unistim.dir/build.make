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
CMAKE_COMMAND = /opt/clion-2019.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/CLionProjects/tshark_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/CLionProjects/tshark_test

# Utility rule file for checkAPI_unistim.

# Include the progress variables for this target.
include plugins/epan/unistim/CMakeFiles/checkAPI_unistim.dir/progress.make

plugins/epan/unistim/CMakeFiles/checkAPI_unistim:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running checkAPI_unistim"
	cd /root/CLionProjects/tshark_test/plugins/epan/unistim && /usr/bin/perl /root/CLionProjects/tshark_test/tools/checkAPIs.pl -g abort -g termoutput packet-unistim.c audio.h basic.h broadcast.h defines.h display.h expansion.h key.h network.h packet-unistim.h uftp.h

checkAPI_unistim: plugins/epan/unistim/CMakeFiles/checkAPI_unistim
checkAPI_unistim: plugins/epan/unistim/CMakeFiles/checkAPI_unistim.dir/build.make

.PHONY : checkAPI_unistim

# Rule to build all files generated by this target.
plugins/epan/unistim/CMakeFiles/checkAPI_unistim.dir/build: checkAPI_unistim

.PHONY : plugins/epan/unistim/CMakeFiles/checkAPI_unistim.dir/build

plugins/epan/unistim/CMakeFiles/checkAPI_unistim.dir/clean:
	cd /root/CLionProjects/tshark_test/plugins/epan/unistim && $(CMAKE_COMMAND) -P CMakeFiles/checkAPI_unistim.dir/cmake_clean.cmake
.PHONY : plugins/epan/unistim/CMakeFiles/checkAPI_unistim.dir/clean

plugins/epan/unistim/CMakeFiles/checkAPI_unistim.dir/depend:
	cd /root/CLionProjects/tshark_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_test /root/CLionProjects/tshark_test/plugins/epan/unistim /root/CLionProjects/tshark_test /root/CLionProjects/tshark_test/plugins/epan/unistim /root/CLionProjects/tshark_test/plugins/epan/unistim/CMakeFiles/checkAPI_unistim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/epan/unistim/CMakeFiles/checkAPI_unistim.dir/depend

