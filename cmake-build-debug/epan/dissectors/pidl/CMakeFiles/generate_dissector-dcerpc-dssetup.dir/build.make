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

# Utility rule file for generate_dissector-dcerpc-dssetup.

# Include the progress variables for this target.
include epan/dissectors/pidl/CMakeFiles/generate_dissector-dcerpc-dssetup.dir/progress.make

epan/dissectors/pidl/CMakeFiles/generate_dissector-dcerpc-dssetup: epan/dissectors/pidl/packet-dcerpc-dssetup-stamp


epan/dissectors/pidl/packet-dcerpc-dssetup-stamp: ../tools/pidl/pidl
epan/dissectors/pidl/packet-dcerpc-dssetup-stamp: ../epan/dissectors/pidl/dssetup/dssetup.idl
epan/dissectors/pidl/packet-dcerpc-dssetup-stamp: ../epan/dissectors/pidl/dssetup/dssetup.cnf
epan/dissectors/pidl/packet-dcerpc-dssetup-stamp: ../epan/dissectors/pidl/misc/misc.idl
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating packet-dcerpc-dssetup-stamp"
	cd /root/CLionProjects/tshark_gongjv/epan/dissectors/pidl/dssetup && /usr/bin/perl /root/CLionProjects/tshark_gongjv/tools/pidl/pidl --ws-parser --outputdir ../.. --includedir .. -- dssetup.idl
	cd /root/CLionProjects/tshark_gongjv/epan/dissectors/pidl/dssetup && /home/mzy/Downloads/clion-2019.3.4/bin/cmake/linux/bin/cmake -E touch /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/pidl/packet-dcerpc-dssetup-stamp

generate_dissector-dcerpc-dssetup: epan/dissectors/pidl/CMakeFiles/generate_dissector-dcerpc-dssetup
generate_dissector-dcerpc-dssetup: epan/dissectors/pidl/packet-dcerpc-dssetup-stamp
generate_dissector-dcerpc-dssetup: epan/dissectors/pidl/CMakeFiles/generate_dissector-dcerpc-dssetup.dir/build.make

.PHONY : generate_dissector-dcerpc-dssetup

# Rule to build all files generated by this target.
epan/dissectors/pidl/CMakeFiles/generate_dissector-dcerpc-dssetup.dir/build: generate_dissector-dcerpc-dssetup

.PHONY : epan/dissectors/pidl/CMakeFiles/generate_dissector-dcerpc-dssetup.dir/build

epan/dissectors/pidl/CMakeFiles/generate_dissector-dcerpc-dssetup.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/pidl && $(CMAKE_COMMAND) -P CMakeFiles/generate_dissector-dcerpc-dssetup.dir/cmake_clean.cmake
.PHONY : epan/dissectors/pidl/CMakeFiles/generate_dissector-dcerpc-dssetup.dir/clean

epan/dissectors/pidl/CMakeFiles/generate_dissector-dcerpc-dssetup.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/epan/dissectors/pidl /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/pidl /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/pidl/CMakeFiles/generate_dissector-dcerpc-dssetup.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/dissectors/pidl/CMakeFiles/generate_dissector-dcerpc-dssetup.dir/depend

