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

# Utility rule file for checkAPI_g729.

# Include the progress variables for this target.
include plugins/codecs/G729/CMakeFiles/checkAPI_g729.dir/progress.make

plugins/codecs/G729/CMakeFiles/checkAPI_g729:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running checkAPI_g729"
	cd /root/CLionProjects/tshark_gongjv/plugins/codecs/G729 && /usr/bin/perl /root/CLionProjects/tshark_gongjv/tools/checkAPIs.pl -g abort -g termoutput G729decode.c

checkAPI_g729: plugins/codecs/G729/CMakeFiles/checkAPI_g729
checkAPI_g729: plugins/codecs/G729/CMakeFiles/checkAPI_g729.dir/build.make

.PHONY : checkAPI_g729

# Rule to build all files generated by this target.
plugins/codecs/G729/CMakeFiles/checkAPI_g729.dir/build: checkAPI_g729

.PHONY : plugins/codecs/G729/CMakeFiles/checkAPI_g729.dir/build

plugins/codecs/G729/CMakeFiles/checkAPI_g729.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G729 && $(CMAKE_COMMAND) -P CMakeFiles/checkAPI_g729.dir/cmake_clean.cmake
.PHONY : plugins/codecs/G729/CMakeFiles/checkAPI_g729.dir/clean

plugins/codecs/G729/CMakeFiles/checkAPI_g729.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/plugins/codecs/G729 /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G729 /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G729/CMakeFiles/checkAPI_g729.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/codecs/G729/CMakeFiles/checkAPI_g729.dir/depend

