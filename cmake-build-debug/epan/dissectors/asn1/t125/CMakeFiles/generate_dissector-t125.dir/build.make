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

# Utility rule file for generate_dissector-t125.

# Include the progress variables for this target.
include epan/dissectors/asn1/t125/CMakeFiles/generate_dissector-t125.dir/progress.make

epan/dissectors/asn1/t125/CMakeFiles/generate_dissector-t125: epan/dissectors/asn1/t125/packet-t125-stamp


epan/dissectors/asn1/t125/packet-t125-stamp: ../tools/asn2wrs.py
epan/dissectors/asn1/t125/packet-t125-stamp: ../epan/dissectors/asn1/t125/MCS-PROTOCOL.asn
epan/dissectors/asn1/t125/packet-t125-stamp: ../epan/dissectors/asn1/t125/packet-t125-template.c
epan/dissectors/asn1/t125/packet-t125-stamp: ../epan/dissectors/asn1/t125/t125.cnf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating packet-t125-stamp"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/t125 && /usr/bin/python3.6 /root/CLionProjects/tshark_gongjv/tools/asn2wrs.py -b -p t125 -c /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/t125/t125.cnf -s /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/t125/packet-t125-template -D /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/t125 -O /root/CLionProjects/tshark_gongjv/epan/dissectors MCS-PROTOCOL.asn
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/t125 && /usr/bin/python3.6 -c "import shutil, sys; x,s,d=sys.argv; open(d, 'w'); shutil.copystat(s, d)" /root/CLionProjects/tshark_gongjv/epan/dissectors/packet-t125.c packet-t125-stamp

generate_dissector-t125: epan/dissectors/asn1/t125/CMakeFiles/generate_dissector-t125
generate_dissector-t125: epan/dissectors/asn1/t125/packet-t125-stamp
generate_dissector-t125: epan/dissectors/asn1/t125/CMakeFiles/generate_dissector-t125.dir/build.make

.PHONY : generate_dissector-t125

# Rule to build all files generated by this target.
epan/dissectors/asn1/t125/CMakeFiles/generate_dissector-t125.dir/build: generate_dissector-t125

.PHONY : epan/dissectors/asn1/t125/CMakeFiles/generate_dissector-t125.dir/build

epan/dissectors/asn1/t125/CMakeFiles/generate_dissector-t125.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/t125 && $(CMAKE_COMMAND) -P CMakeFiles/generate_dissector-t125.dir/cmake_clean.cmake
.PHONY : epan/dissectors/asn1/t125/CMakeFiles/generate_dissector-t125.dir/clean

epan/dissectors/asn1/t125/CMakeFiles/generate_dissector-t125.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/t125 /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/t125 /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/t125/CMakeFiles/generate_dissector-t125.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/dissectors/asn1/t125/CMakeFiles/generate_dissector-t125.dir/depend

