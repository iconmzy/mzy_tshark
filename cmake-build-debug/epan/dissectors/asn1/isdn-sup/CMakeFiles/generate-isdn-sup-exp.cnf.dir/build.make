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

# Utility rule file for generate-isdn-sup-exp.cnf.

# Include the progress variables for this target.
include epan/dissectors/asn1/isdn-sup/CMakeFiles/generate-isdn-sup-exp.cnf.dir/progress.make

epan/dissectors/asn1/isdn-sup/CMakeFiles/generate-isdn-sup-exp.cnf: epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf


epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../tools/asn2wrs.py
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/Addressing-Data-Elements.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/Basic-Service-Elements.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/Embedded-Q931-Types.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/General-Errors.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/Advice-of-Charge-Operations.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/Closed-User-Group-Service-Operations.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/Conference-Add-On-Operations.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/Diversion-Operations.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/MCID-Operations.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/User-To-User-Signalling-Operations.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/Freephone-Operations.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/MLPP-Operations-And-Errors.asn
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/packet-isdn-sup-template.c
epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf: ../epan/dissectors/asn1/isdn-sup/isdn-sup.cnf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating isdn-sup-exp.cnf"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/isdn-sup && /usr/bin/python3.6 /root/CLionProjects/tshark_gongjv/tools/asn2wrs.py -E -b -p isdn-sup -c /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/isdn-sup/isdn-sup.cnf -D /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/isdn-sup Addressing-Data-Elements.asn Basic-Service-Elements.asn Embedded-Q931-Types.asn General-Errors.asn Advice-of-Charge-Operations.asn Closed-User-Group-Service-Operations.asn Conference-Add-On-Operations.asn Diversion-Operations.asn MCID-Operations.asn User-To-User-Signalling-Operations.asn Freephone-Operations.asn MLPP-Operations-And-Errors.asn

generate-isdn-sup-exp.cnf: epan/dissectors/asn1/isdn-sup/CMakeFiles/generate-isdn-sup-exp.cnf
generate-isdn-sup-exp.cnf: epan/dissectors/asn1/isdn-sup/isdn-sup-exp.cnf
generate-isdn-sup-exp.cnf: epan/dissectors/asn1/isdn-sup/CMakeFiles/generate-isdn-sup-exp.cnf.dir/build.make

.PHONY : generate-isdn-sup-exp.cnf

# Rule to build all files generated by this target.
epan/dissectors/asn1/isdn-sup/CMakeFiles/generate-isdn-sup-exp.cnf.dir/build: generate-isdn-sup-exp.cnf

.PHONY : epan/dissectors/asn1/isdn-sup/CMakeFiles/generate-isdn-sup-exp.cnf.dir/build

epan/dissectors/asn1/isdn-sup/CMakeFiles/generate-isdn-sup-exp.cnf.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/isdn-sup && $(CMAKE_COMMAND) -P CMakeFiles/generate-isdn-sup-exp.cnf.dir/cmake_clean.cmake
.PHONY : epan/dissectors/asn1/isdn-sup/CMakeFiles/generate-isdn-sup-exp.cnf.dir/clean

epan/dissectors/asn1/isdn-sup/CMakeFiles/generate-isdn-sup-exp.cnf.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/epan/dissectors/asn1/isdn-sup /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/isdn-sup /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/dissectors/asn1/isdn-sup/CMakeFiles/generate-isdn-sup-exp.cnf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/dissectors/asn1/isdn-sup/CMakeFiles/generate-isdn-sup-exp.cnf.dir/depend

