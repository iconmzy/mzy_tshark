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

# Utility rule file for release_notes.

# Include the progress variables for this target.
include docbook/CMakeFiles/release_notes.dir/progress.make

release_notes: docbook/CMakeFiles/release_notes.dir/build.make

.PHONY : release_notes

# Rule to build all files generated by this target.
docbook/CMakeFiles/release_notes.dir/build: release_notes

.PHONY : docbook/CMakeFiles/release_notes.dir/build

docbook/CMakeFiles/release_notes.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/docbook && $(CMAKE_COMMAND) -P CMakeFiles/release_notes.dir/cmake_clean.cmake
.PHONY : docbook/CMakeFiles/release_notes.dir/clean

docbook/CMakeFiles/release_notes.dir/depend:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/docbook /root/CLionProjects/tshark_shanghai/cmake-build-release /root/CLionProjects/tshark_shanghai/cmake-build-release/docbook /root/CLionProjects/tshark_shanghai/cmake-build-release/docbook/CMakeFiles/release_notes.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : docbook/CMakeFiles/release_notes.dir/depend

