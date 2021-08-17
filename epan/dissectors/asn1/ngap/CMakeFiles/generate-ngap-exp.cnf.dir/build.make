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

# Utility rule file for generate-ngap-exp.cnf.

# Include the progress variables for this target.
include epan/dissectors/asn1/ngap/CMakeFiles/generate-ngap-exp.cnf.dir/progress.make

epan/dissectors/asn1/ngap/CMakeFiles/generate-ngap-exp.cnf: epan/dissectors/asn1/ngap/ngap-exp.cnf


epan/dissectors/asn1/ngap/ngap-exp.cnf: tools/asn2wrs.py
epan/dissectors/asn1/ngap/ngap-exp.cnf: epan/dissectors/asn1/ngap/NGAP-CommonDataTypes.asn
epan/dissectors/asn1/ngap/ngap-exp.cnf: epan/dissectors/asn1/ngap/NGAP-Constants.asn
epan/dissectors/asn1/ngap/ngap-exp.cnf: epan/dissectors/asn1/ngap/NGAP-Containers.asn
epan/dissectors/asn1/ngap/ngap-exp.cnf: epan/dissectors/asn1/ngap/NGAP-IEs.asn
epan/dissectors/asn1/ngap/ngap-exp.cnf: epan/dissectors/asn1/ngap/NGAP-PDU-Contents.asn
epan/dissectors/asn1/ngap/ngap-exp.cnf: epan/dissectors/asn1/ngap/NGAP-PDU-Descriptions.asn
epan/dissectors/asn1/ngap/ngap-exp.cnf: epan/dissectors/asn1/ngap/packet-ngap-template.c
epan/dissectors/asn1/ngap/ngap-exp.cnf: epan/dissectors/asn1/ngap/packet-ngap-template.h
epan/dissectors/asn1/ngap/ngap-exp.cnf: epan/dissectors/asn1/ngap/ngap.cnf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ngap-exp.cnf"
	cd /root/CLionProjects/tshark_test/epan/dissectors/asn1/ngap && /usr/bin/python3.6 /root/CLionProjects/tshark_test/tools/asn2wrs.py -E -p ngap -c /root/CLionProjects/tshark_test/epan/dissectors/asn1/ngap/ngap.cnf -D /root/CLionProjects/tshark_test/epan/dissectors/asn1/ngap NGAP-CommonDataTypes.asn NGAP-Constants.asn NGAP-Containers.asn NGAP-IEs.asn NGAP-PDU-Contents.asn NGAP-PDU-Descriptions.asn

generate-ngap-exp.cnf: epan/dissectors/asn1/ngap/CMakeFiles/generate-ngap-exp.cnf
generate-ngap-exp.cnf: epan/dissectors/asn1/ngap/ngap-exp.cnf
generate-ngap-exp.cnf: epan/dissectors/asn1/ngap/CMakeFiles/generate-ngap-exp.cnf.dir/build.make

.PHONY : generate-ngap-exp.cnf

# Rule to build all files generated by this target.
epan/dissectors/asn1/ngap/CMakeFiles/generate-ngap-exp.cnf.dir/build: generate-ngap-exp.cnf

.PHONY : epan/dissectors/asn1/ngap/CMakeFiles/generate-ngap-exp.cnf.dir/build

epan/dissectors/asn1/ngap/CMakeFiles/generate-ngap-exp.cnf.dir/clean:
	cd /root/CLionProjects/tshark_test/epan/dissectors/asn1/ngap && $(CMAKE_COMMAND) -P CMakeFiles/generate-ngap-exp.cnf.dir/cmake_clean.cmake
.PHONY : epan/dissectors/asn1/ngap/CMakeFiles/generate-ngap-exp.cnf.dir/clean

epan/dissectors/asn1/ngap/CMakeFiles/generate-ngap-exp.cnf.dir/depend:
	cd /root/CLionProjects/tshark_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_test /root/CLionProjects/tshark_test/epan/dissectors/asn1/ngap /root/CLionProjects/tshark_test /root/CLionProjects/tshark_test/epan/dissectors/asn1/ngap /root/CLionProjects/tshark_test/epan/dissectors/asn1/ngap/CMakeFiles/generate-ngap-exp.cnf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/dissectors/asn1/ngap/CMakeFiles/generate-ngap-exp.cnf.dir/depend

