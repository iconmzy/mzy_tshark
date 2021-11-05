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

# Utility rule file for generate_dissector-xnap.

# Include the progress variables for this target.
include epan/dissectors/asn1/xnap/CMakeFiles/generate_dissector-xnap.dir/progress.make

epan/dissectors/asn1/xnap/CMakeFiles/generate_dissector-xnap: epan/dissectors/asn1/xnap/packet-xnap-stamp


epan/dissectors/asn1/xnap/packet-xnap-stamp: ../tools/asn2wrs.py
epan/dissectors/asn1/xnap/packet-xnap-stamp: ../epan/dissectors/asn1/xnap/XnAP-CommonDataTypes.asn
epan/dissectors/asn1/xnap/packet-xnap-stamp: ../epan/dissectors/asn1/xnap/XnAP-Constants.asn
epan/dissectors/asn1/xnap/packet-xnap-stamp: ../epan/dissectors/asn1/xnap/XnAP-Containers.asn
epan/dissectors/asn1/xnap/packet-xnap-stamp: ../epan/dissectors/asn1/xnap/XnAP-IEs.asn
epan/dissectors/asn1/xnap/packet-xnap-stamp: ../epan/dissectors/asn1/xnap/XnAP-PDU-Contents.asn
epan/dissectors/asn1/xnap/packet-xnap-stamp: ../epan/dissectors/asn1/xnap/XnAP-PDU-Descriptions.asn
epan/dissectors/asn1/xnap/packet-xnap-stamp: ../epan/dissectors/asn1/xnap/packet-xnap-template.c
epan/dissectors/asn1/xnap/packet-xnap-stamp: ../epan/dissectors/asn1/xnap/packet-xnap-template.h
epan/dissectors/asn1/xnap/packet-xnap-stamp: ../epan/dissectors/asn1/xnap/xnap.cnf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating packet-xnap-stamp"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/xnap && /usr/bin/python3.6 /root/CLionProjects/tshark_gongjv/tools/asn2wrs.py -p xnap -c /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/xnap/xnap.cnf -s /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/xnap/packet-xnap-template -D /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/xnap -O /root/CLionProjects/tshark_gongjv/epan/dissectors XnAP-CommonDataTypes.asn XnAP-Constants.asn XnAP-Containers.asn XnAP-IEs.asn XnAP-PDU-Contents.asn XnAP-PDU-Descriptions.asn
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/xnap && /usr/bin/python3.6 -c "import shutil, sys; x,s,d=sys.argv; open(d, 'w'); shutil.copystat(s, d)" /root/CLionProjects/tshark_gongjv/epan/dissectors/packet-xnap.c packet-xnap-stamp

generate_dissector-xnap: epan/dissectors/asn1/xnap/CMakeFiles/generate_dissector-xnap
generate_dissector-xnap: epan/dissectors/asn1/xnap/packet-xnap-stamp
generate_dissector-xnap: epan/dissectors/asn1/xnap/CMakeFiles/generate_dissector-xnap.dir/build.make

.PHONY : generate_dissector-xnap

# Rule to build all files generated by this target.
epan/dissectors/asn1/xnap/CMakeFiles/generate_dissector-xnap.dir/build: generate_dissector-xnap

.PHONY : epan/dissectors/asn1/xnap/CMakeFiles/generate_dissector-xnap.dir/build

epan/dissectors/asn1/xnap/CMakeFiles/generate_dissector-xnap.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/xnap && $(CMAKE_COMMAND) -P CMakeFiles/generate_dissector-xnap.dir/cmake_clean.cmake
.PHONY : epan/dissectors/asn1/xnap/CMakeFiles/generate_dissector-xnap.dir/clean

epan/dissectors/asn1/xnap/CMakeFiles/generate_dissector-xnap.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/xnap /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/xnap /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/xnap/CMakeFiles/generate_dissector-xnap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/dissectors/asn1/xnap/CMakeFiles/generate_dissector-xnap.dir/depend

