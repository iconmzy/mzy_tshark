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

# Utility rule file for generate_dissector-t124.

# Include the progress variables for this target.
include epan/dissectors/asn1/t124/CMakeFiles/generate_dissector-t124.dir/progress.make

epan/dissectors/asn1/t124/CMakeFiles/generate_dissector-t124: epan/dissectors/asn1/t124/packet-t124-stamp


epan/dissectors/asn1/t124/packet-t124-stamp: ../tools/asn2wrs.py
epan/dissectors/asn1/t124/packet-t124-stamp: ../epan/dissectors/asn1/t124/GCC-PROTOCOL.asn
epan/dissectors/asn1/t124/packet-t124-stamp: ../epan/dissectors/asn1/t124/packet-t124-template.c
epan/dissectors/asn1/t124/packet-t124-stamp: ../epan/dissectors/asn1/t124/packet-t124-template.h
epan/dissectors/asn1/t124/packet-t124-stamp: ../epan/dissectors/asn1/t124/t124.cnf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating packet-t124-stamp"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dissectors/asn1/t124 && /usr/bin/python3.6 /root/CLionProjects/tshark_shanghai/tools/asn2wrs.py -p t124 -c /root/CLionProjects/tshark_shanghai/epan/dissectors/asn1/t124/t124.cnf -s /root/CLionProjects/tshark_shanghai/epan/dissectors/asn1/t124/packet-t124-template -D /root/CLionProjects/tshark_shanghai/epan/dissectors/asn1/t124 -O /root/CLionProjects/tshark_shanghai/epan/dissectors GCC-PROTOCOL.asn ../t125/MCS-PROTOCOL.asn
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dissectors/asn1/t124 && /usr/bin/python3.6 -c "import shutil, sys; x,s,d=sys.argv; open(d, 'w'); shutil.copystat(s, d)" /root/CLionProjects/tshark_shanghai/epan/dissectors/packet-t124.c packet-t124-stamp

generate_dissector-t124: epan/dissectors/asn1/t124/CMakeFiles/generate_dissector-t124
generate_dissector-t124: epan/dissectors/asn1/t124/packet-t124-stamp
generate_dissector-t124: epan/dissectors/asn1/t124/CMakeFiles/generate_dissector-t124.dir/build.make

.PHONY : generate_dissector-t124

# Rule to build all files generated by this target.
epan/dissectors/asn1/t124/CMakeFiles/generate_dissector-t124.dir/build: generate_dissector-t124

.PHONY : epan/dissectors/asn1/t124/CMakeFiles/generate_dissector-t124.dir/build

epan/dissectors/asn1/t124/CMakeFiles/generate_dissector-t124.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dissectors/asn1/t124 && $(CMAKE_COMMAND) -P CMakeFiles/generate_dissector-t124.dir/cmake_clean.cmake
.PHONY : epan/dissectors/asn1/t124/CMakeFiles/generate_dissector-t124.dir/clean

epan/dissectors/asn1/t124/CMakeFiles/generate_dissector-t124.dir/depend:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/epan/dissectors/asn1/t124 /root/CLionProjects/tshark_shanghai/cmake-build-release /root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dissectors/asn1/t124 /root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dissectors/asn1/t124/CMakeFiles/generate_dissector-t124.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/dissectors/asn1/t124/CMakeFiles/generate_dissector-t124.dir/depend

