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

# Utility rule file for generate_dissector-pkinit.

# Include the progress variables for this target.
include epan/dissectors/asn1/pkinit/CMakeFiles/generate_dissector-pkinit.dir/progress.make

epan/dissectors/asn1/pkinit/CMakeFiles/generate_dissector-pkinit: epan/dissectors/asn1/pkinit/packet-pkinit-stamp


epan/dissectors/asn1/pkinit/packet-pkinit-stamp: ../tools/asn2wrs.py
epan/dissectors/asn1/pkinit/packet-pkinit-stamp: ../epan/dissectors/asn1/pkinit/PKINIT.asn
epan/dissectors/asn1/pkinit/packet-pkinit-stamp: ../epan/dissectors/asn1/pkinit/packet-pkinit-template.c
epan/dissectors/asn1/pkinit/packet-pkinit-stamp: ../epan/dissectors/asn1/pkinit/packet-pkinit-template.h
epan/dissectors/asn1/pkinit/packet-pkinit-stamp: ../epan/dissectors/asn1/pkinit/pkinit.cnf
epan/dissectors/asn1/pkinit/packet-pkinit-stamp: epan/dissectors/asn1/cms/cms-exp.cnf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating packet-pkinit-stamp"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/pkinit && /usr/bin/python3.6 /root/CLionProjects/tshark_gongjv/tools/asn2wrs.py -b -p pkinit -c /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/pkinit/pkinit.cnf -s /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/pkinit/packet-pkinit-template -D /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/pkinit -O /root/CLionProjects/tshark_gongjv/epan/dissectors PKINIT.asn
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/pkinit && /usr/bin/python3.6 -c "import shutil, sys; x,s,d=sys.argv; open(d, 'w'); shutil.copystat(s, d)" /root/CLionProjects/tshark_gongjv/epan/dissectors/packet-pkinit.c packet-pkinit-stamp

generate_dissector-pkinit: epan/dissectors/asn1/pkinit/CMakeFiles/generate_dissector-pkinit
generate_dissector-pkinit: epan/dissectors/asn1/pkinit/packet-pkinit-stamp
generate_dissector-pkinit: epan/dissectors/asn1/pkinit/CMakeFiles/generate_dissector-pkinit.dir/build.make

.PHONY : generate_dissector-pkinit

# Rule to build all files generated by this target.
epan/dissectors/asn1/pkinit/CMakeFiles/generate_dissector-pkinit.dir/build: generate_dissector-pkinit

.PHONY : epan/dissectors/asn1/pkinit/CMakeFiles/generate_dissector-pkinit.dir/build

epan/dissectors/asn1/pkinit/CMakeFiles/generate_dissector-pkinit.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/pkinit && $(CMAKE_COMMAND) -P CMakeFiles/generate_dissector-pkinit.dir/cmake_clean.cmake
.PHONY : epan/dissectors/asn1/pkinit/CMakeFiles/generate_dissector-pkinit.dir/clean

epan/dissectors/asn1/pkinit/CMakeFiles/generate_dissector-pkinit.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/pkinit /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/pkinit /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/pkinit/CMakeFiles/generate_dissector-pkinit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/dissectors/asn1/pkinit/CMakeFiles/generate_dissector-pkinit.dir/depend

