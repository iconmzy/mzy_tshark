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

# Include any dependencies generated for this target.
include plugins/epan/transum/CMakeFiles/transum.dir/depend.make

# Include the progress variables for this target.
include plugins/epan/transum/CMakeFiles/transum.dir/progress.make

# Include the compile flags for this target's objects.
include plugins/epan/transum/CMakeFiles/transum.dir/flags.make

plugins/epan/transum/plugin.c: ../plugins/epan/transum/packet-transum.c
plugins/epan/transum/plugin.c: ../plugins/epan/transum/decoders.c
plugins/epan/transum/plugin.c: ../plugins/epan/transum/extractors.c
plugins/epan/transum/plugin.c: ../tools/make-plugin-reg.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating plugin.c"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/python3.6 /root/CLionProjects/tshark_shanghai/tools/make-plugin-reg.py /root/CLionProjects/tshark_shanghai/plugins/epan/transum plugin packet-transum.c decoders.c extractors.c

plugins/epan/transum/CMakeFiles/transum.dir/plugin.c.o: plugins/epan/transum/CMakeFiles/transum.dir/flags.make
plugins/epan/transum/CMakeFiles/transum.dir/plugin.c.o: plugins/epan/transum/plugin.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object plugins/epan/transum/CMakeFiles/transum.dir/plugin.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/transum.dir/plugin.c.o   -c /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum/plugin.c

plugins/epan/transum/CMakeFiles/transum.dir/plugin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/transum.dir/plugin.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum/plugin.c > CMakeFiles/transum.dir/plugin.c.i

plugins/epan/transum/CMakeFiles/transum.dir/plugin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/transum.dir/plugin.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum/plugin.c -o CMakeFiles/transum.dir/plugin.c.s

plugins/epan/transum/CMakeFiles/transum.dir/packet-transum.c.o: plugins/epan/transum/CMakeFiles/transum.dir/flags.make
plugins/epan/transum/CMakeFiles/transum.dir/packet-transum.c.o: ../plugins/epan/transum/packet-transum.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object plugins/epan/transum/CMakeFiles/transum.dir/packet-transum.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/transum.dir/packet-transum.c.o   -c /root/CLionProjects/tshark_shanghai/plugins/epan/transum/packet-transum.c

plugins/epan/transum/CMakeFiles/transum.dir/packet-transum.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/transum.dir/packet-transum.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/plugins/epan/transum/packet-transum.c > CMakeFiles/transum.dir/packet-transum.c.i

plugins/epan/transum/CMakeFiles/transum.dir/packet-transum.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/transum.dir/packet-transum.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/plugins/epan/transum/packet-transum.c -o CMakeFiles/transum.dir/packet-transum.c.s

plugins/epan/transum/CMakeFiles/transum.dir/decoders.c.o: plugins/epan/transum/CMakeFiles/transum.dir/flags.make
plugins/epan/transum/CMakeFiles/transum.dir/decoders.c.o: ../plugins/epan/transum/decoders.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object plugins/epan/transum/CMakeFiles/transum.dir/decoders.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/transum.dir/decoders.c.o   -c /root/CLionProjects/tshark_shanghai/plugins/epan/transum/decoders.c

plugins/epan/transum/CMakeFiles/transum.dir/decoders.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/transum.dir/decoders.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/plugins/epan/transum/decoders.c > CMakeFiles/transum.dir/decoders.c.i

plugins/epan/transum/CMakeFiles/transum.dir/decoders.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/transum.dir/decoders.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/plugins/epan/transum/decoders.c -o CMakeFiles/transum.dir/decoders.c.s

plugins/epan/transum/CMakeFiles/transum.dir/extractors.c.o: plugins/epan/transum/CMakeFiles/transum.dir/flags.make
plugins/epan/transum/CMakeFiles/transum.dir/extractors.c.o: ../plugins/epan/transum/extractors.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object plugins/epan/transum/CMakeFiles/transum.dir/extractors.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/transum.dir/extractors.c.o   -c /root/CLionProjects/tshark_shanghai/plugins/epan/transum/extractors.c

plugins/epan/transum/CMakeFiles/transum.dir/extractors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/transum.dir/extractors.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/plugins/epan/transum/extractors.c > CMakeFiles/transum.dir/extractors.c.i

plugins/epan/transum/CMakeFiles/transum.dir/extractors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/transum.dir/extractors.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/plugins/epan/transum/extractors.c -o CMakeFiles/transum.dir/extractors.c.s

# Object files for target transum
transum_OBJECTS = \
"CMakeFiles/transum.dir/plugin.c.o" \
"CMakeFiles/transum.dir/packet-transum.c.o" \
"CMakeFiles/transum.dir/decoders.c.o" \
"CMakeFiles/transum.dir/extractors.c.o"

# External object files for target transum
transum_EXTERNAL_OBJECTS =

run/plugins/3.4/epan/transum.so: plugins/epan/transum/CMakeFiles/transum.dir/plugin.c.o
run/plugins/3.4/epan/transum.so: plugins/epan/transum/CMakeFiles/transum.dir/packet-transum.c.o
run/plugins/3.4/epan/transum.so: plugins/epan/transum/CMakeFiles/transum.dir/decoders.c.o
run/plugins/3.4/epan/transum.so: plugins/epan/transum/CMakeFiles/transum.dir/extractors.c.o
run/plugins/3.4/epan/transum.so: plugins/epan/transum/CMakeFiles/transum.dir/build.make
run/plugins/3.4/epan/transum.so: run/libwireshark.so.14.0.5
run/plugins/3.4/epan/transum.so: run/libwiretap.so.11.0.5
run/plugins/3.4/epan/transum.so: run/libwsutil.so.12.0.0
run/plugins/3.4/epan/transum.so: /usr/lib64/libgmodule-2.0.so
run/plugins/3.4/epan/transum.so: /usr/lib64/libgcrypt.so
run/plugins/3.4/epan/transum.so: /usr/lib64/libgpg-error.so
run/plugins/3.4/epan/transum.so: /usr/lib64/libglib-2.0.so
run/plugins/3.4/epan/transum.so: plugins/epan/transum/CMakeFiles/transum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C shared module ../../../run/plugins/3.4/epan/transum.so"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/transum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plugins/epan/transum/CMakeFiles/transum.dir/build: run/plugins/3.4/epan/transum.so

.PHONY : plugins/epan/transum/CMakeFiles/transum.dir/build

plugins/epan/transum/CMakeFiles/transum.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum && $(CMAKE_COMMAND) -P CMakeFiles/transum.dir/cmake_clean.cmake
.PHONY : plugins/epan/transum/CMakeFiles/transum.dir/clean

plugins/epan/transum/CMakeFiles/transum.dir/depend: plugins/epan/transum/plugin.c
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/plugins/epan/transum /root/CLionProjects/tshark_shanghai/cmake-build-release /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/epan/transum/CMakeFiles/transum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/epan/transum/CMakeFiles/transum.dir/depend

