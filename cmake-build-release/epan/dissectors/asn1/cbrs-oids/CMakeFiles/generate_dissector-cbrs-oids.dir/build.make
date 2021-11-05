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

# Utility rule file for generate_dissector-cbrs-oids.

# Include the progress variables for this target.
include epan/dissectors/asn1/cbrs-oids/CMakeFiles/generate_dissector-cbrs-oids.dir/progress.make

epan/dissectors/asn1/cbrs-oids/CMakeFiles/generate_dissector-cbrs-oids: epan/dissectors/asn1/cbrs-oids/packet-cbrs-oids-stamp


epan/dissectors/asn1/cbrs-oids/packet-cbrs-oids-stamp: ../tools/asn2wrs.py
epan/dissectors/asn1/cbrs-oids/packet-cbrs-oids-stamp: ../epan/dissectors/asn1/cbrs-oids/cbrs-oids.asn
epan/dissectors/asn1/cbrs-oids/packet-cbrs-oids-stamp: ../epan/dissectors/asn1/cbrs-oids/packet-cbrs-oids-template.c
epan/dissectors/asn1/cbrs-oids/packet-cbrs-oids-stamp: ../epan/dissectors/asn1/cbrs-oids/cbrs-oids.cnf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating packet-cbrs-oids-stamp"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dissectors/asn1/cbrs-oids && /usr/bin/python3.6 /root/CLionProjects/tshark_shanghai/tools/asn2wrs.py -b -p cbrs-oids -c /root/CLionProjects/tshark_shanghai/epan/dissectors/asn1/cbrs-oids/cbrs-oids.cnf -s /root/CLionProjects/tshark_shanghai/epan/dissectors/asn1/cbrs-oids/packet-cbrs-oids-template -D /root/CLionProjects/tshark_shanghai/epan/dissectors/asn1/cbrs-oids -O /root/CLionProjects/tshark_shanghai/epan/dissectors cbrs-oids.asn
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dissectors/asn1/cbrs-oids && /usr/bin/python3.6 -c "import shutil, sys; x,s,d=sys.argv; open(d, 'w'); shutil.copystat(s, d)" /root/CLionProjects/tshark_shanghai/epan/dissectors/packet-cbrs-oids.c packet-cbrs-oids-stamp

generate_dissector-cbrs-oids: epan/dissectors/asn1/cbrs-oids/CMakeFiles/generate_dissector-cbrs-oids
generate_dissector-cbrs-oids: epan/dissectors/asn1/cbrs-oids/packet-cbrs-oids-stamp
generate_dissector-cbrs-oids: epan/dissectors/asn1/cbrs-oids/CMakeFiles/generate_dissector-cbrs-oids.dir/build.make

.PHONY : generate_dissector-cbrs-oids

# Rule to build all files generated by this target.
epan/dissectors/asn1/cbrs-oids/CMakeFiles/generate_dissector-cbrs-oids.dir/build: generate_dissector-cbrs-oids

.PHONY : epan/dissectors/asn1/cbrs-oids/CMakeFiles/generate_dissector-cbrs-oids.dir/build

epan/dissectors/asn1/cbrs-oids/CMakeFiles/generate_dissector-cbrs-oids.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dissectors/asn1/cbrs-oids && $(CMAKE_COMMAND) -P CMakeFiles/generate_dissector-cbrs-oids.dir/cmake_clean.cmake
.PHONY : epan/dissectors/asn1/cbrs-oids/CMakeFiles/generate_dissector-cbrs-oids.dir/clean

epan/dissectors/asn1/cbrs-oids/CMakeFiles/generate_dissector-cbrs-oids.dir/depend:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/epan/dissectors/asn1/cbrs-oids /root/CLionProjects/tshark_shanghai/cmake-build-release /root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dissectors/asn1/cbrs-oids /root/CLionProjects/tshark_shanghai/cmake-build-release/epan/dissectors/asn1/cbrs-oids/CMakeFiles/generate_dissector-cbrs-oids.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/dissectors/asn1/cbrs-oids/CMakeFiles/generate_dissector-cbrs-oids.dir/depend

