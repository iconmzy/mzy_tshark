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
CMAKE_SOURCE_DIR = /root/CLionProjects/tshark_shanghai

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/CLionProjects/tshark_shanghai/cmake-build-release

# Utility rule file for checkAPI_transum.

# Include the progress variables for this target.
include plugins/epan/transum/CMakeFiles/checkAPI_transum.dir/progress.make

plugins/epan/transum/CMakeFiles/checkAPI_transum:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running checkAPI_transum"
	cd /root/CLionProjects/tshark_shanghai/plugins/epan/transum && /usr/bin/perl /root/CLionProjects/tshark_shanghai/tools/checkAPIs.pl --group abort --group termoutput:1 --summary-group termoutput packet-transum.c decoders.c extractors.c decoders.h extractors.h packet-transum.h preferences.h

checkAPI_transum: plugins/epan/transum/CMakeFiles/checkAPI_transum
checkAPI_transum: plugins/epan/transum/CMakeFiles/checkAPI_transum.dir/build.make

.PHONY : checkAPI_transum

# Rule to build all files generated by this target.
plugins/epan/transum/CMakeFiles/checkAPI_transum.dir/build: checkAPI_transum

.PHONY : plugins/epan/transum/CMakeFiles/checkAPI_transum.dir/build

plugins/epan/transum/CMakeFiles/checkAPI_transum.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && $(CMAKE_COMMAND) -P CMakeFiles/checkAPI_transum.dir/cmake_clean.cmake
.PHONY : plugins/epan/transum/CMakeFiles/checkAPI_transum.dir/clean

plugins/epan/transum/CMakeFiles/checkAPI_transum.dir/depend:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/plugins/epan/transum /root/CLionProjects/tshark_shanghai/cmake-build-release /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum/CMakeFiles/checkAPI_transum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/epan/transum/CMakeFiles/checkAPI_transum.dir/depend

