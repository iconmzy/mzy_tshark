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

# Utility rule file for generate_dissector-s1ap.

# Include the progress variables for this target.
include epan/dissectors/asn1/s1ap/CMakeFiles/generate_dissector-s1ap.dir/progress.make

epan/dissectors/asn1/s1ap/CMakeFiles/generate_dissector-s1ap: epan/dissectors/asn1/s1ap/packet-s1ap-stamp


epan/dissectors/asn1/s1ap/packet-s1ap-stamp: ../tools/asn2wrs.py
epan/dissectors/asn1/s1ap/packet-s1ap-stamp: ../epan/dissectors/asn1/s1ap/S1AP-CommonDataTypes.asn
epan/dissectors/asn1/s1ap/packet-s1ap-stamp: ../epan/dissectors/asn1/s1ap/S1AP-Constants.asn
epan/dissectors/asn1/s1ap/packet-s1ap-stamp: ../epan/dissectors/asn1/s1ap/S1AP-Containers.asn
epan/dissectors/asn1/s1ap/packet-s1ap-stamp: ../epan/dissectors/asn1/s1ap/S1AP-IEs.asn
epan/dissectors/asn1/s1ap/packet-s1ap-stamp: ../epan/dissectors/asn1/s1ap/S1AP-PDU-Contents.asn
epan/dissectors/asn1/s1ap/packet-s1ap-stamp: ../epan/dissectors/asn1/s1ap/S1AP-PDU-Descriptions.asn
epan/dissectors/asn1/s1ap/packet-s1ap-stamp: ../epan/dissectors/asn1/s1ap/S1AP-SonTransfer-IEs.asn
epan/dissectors/asn1/s1ap/packet-s1ap-stamp: ../epan/dissectors/asn1/s1ap/packet-s1ap-template.c
epan/dissectors/asn1/s1ap/packet-s1ap-stamp: ../epan/dissectors/asn1/s1ap/packet-s1ap-template.h
epan/dissectors/asn1/s1ap/packet-s1ap-stamp: ../epan/dissectors/asn1/s1ap/s1ap.cnf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating packet-s1ap-stamp"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/s1ap && /usr/bin/python3.6 /root/CLionProjects/tshark_gongjv/tools/asn2wrs.py -p s1ap -c /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/s1ap/s1ap.cnf -s /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/s1ap/packet-s1ap-template -D /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/s1ap -O /root/CLionProjects/tshark_gongjv/epan/dissectors S1AP-CommonDataTypes.asn S1AP-Constants.asn S1AP-Containers.asn S1AP-IEs.asn S1AP-PDU-Contents.asn S1AP-PDU-Descriptions.asn S1AP-SonTransfer-IEs.asn
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/s1ap && /usr/bin/python3.6 -c "import shutil, sys; x,s,d=sys.argv; open(d, 'w'); shutil.copystat(s, d)" /root/CLionProjects/tshark_gongjv/epan/dissectors/packet-s1ap.c packet-s1ap-stamp

generate_dissector-s1ap: epan/dissectors/asn1/s1ap/CMakeFiles/generate_dissector-s1ap
generate_dissector-s1ap: epan/dissectors/asn1/s1ap/packet-s1ap-stamp
generate_dissector-s1ap: epan/dissectors/asn1/s1ap/CMakeFiles/generate_dissector-s1ap.dir/build.make

.PHONY : generate_dissector-s1ap

# Rule to build all files generated by this target.
epan/dissectors/asn1/s1ap/CMakeFiles/generate_dissector-s1ap.dir/build: generate_dissector-s1ap

.PHONY : epan/dissectors/asn1/s1ap/CMakeFiles/generate_dissector-s1ap.dir/build

epan/dissectors/asn1/s1ap/CMakeFiles/generate_dissector-s1ap.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/s1ap && $(CMAKE_COMMAND) -P CMakeFiles/generate_dissector-s1ap.dir/cmake_clean.cmake
.PHONY : epan/dissectors/asn1/s1ap/CMakeFiles/generate_dissector-s1ap.dir/clean

epan/dissectors/asn1/s1ap/CMakeFiles/generate_dissector-s1ap.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/s1ap /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/s1ap /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/s1ap/CMakeFiles/generate_dissector-s1ap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/dissectors/asn1/s1ap/CMakeFiles/generate_dissector-s1ap.dir/depend

