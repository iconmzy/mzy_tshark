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
CMAKE_BINARY_DIR = /root/CLionProjects/tshark_shanghai/cmake-build-debug

# Include any dependencies generated for this target.
include extcap/CMakeFiles/udpdump.dir/depend.make

# Include the progress variables for this target.
include extcap/CMakeFiles/udpdump.dir/progress.make

# Include the compile flags for this target's objects.
include extcap/CMakeFiles/udpdump.dir/flags.make

extcap/CMakeFiles/udpdump.dir/udpdump.c.o: extcap/CMakeFiles/udpdump.dir/flags.make
extcap/CMakeFiles/udpdump.dir/udpdump.c.o: ../extcap/udpdump.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object extcap/CMakeFiles/udpdump.dir/udpdump.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/extcap && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/udpdump.dir/udpdump.c.o   -c /root/CLionProjects/tshark_shanghai/extcap/udpdump.c

extcap/CMakeFiles/udpdump.dir/udpdump.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/udpdump.dir/udpdump.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/extcap && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/extcap/udpdump.c > CMakeFiles/udpdump.dir/udpdump.c.i

extcap/CMakeFiles/udpdump.dir/udpdump.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/udpdump.dir/udpdump.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/extcap && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/extcap/udpdump.c -o CMakeFiles/udpdump.dir/udpdump.c.s

# Object files for target udpdump
udpdump_OBJECTS = \
"CMakeFiles/udpdump.dir/udpdump.c.o"

# External object files for target udpdump
udpdump_EXTERNAL_OBJECTS = \
"/root/CLionProjects/tshark_shanghai/cmake-build-debug/CMakeFiles/cli_main.dir/cli_main.c.o" \
"/root/CLionProjects/tshark_shanghai/cmake-build-debug/extcap/CMakeFiles/extcap-base.dir/extcap-base.c.o"

run/extcap/udpdump: extcap/CMakeFiles/udpdump.dir/udpdump.c.o
run/extcap/udpdump: CMakeFiles/cli_main.dir/cli_main.c.o
run/extcap/udpdump: extcap/CMakeFiles/extcap-base.dir/extcap-base.c.o
run/extcap/udpdump: extcap/CMakeFiles/udpdump.dir/build.make
run/extcap/udpdump: /usr/lib64/libglib-2.0.so
run/extcap/udpdump: run/libwsutil.so.12.0.0
run/extcap/udpdump: run/libwritecap.a
run/extcap/udpdump: /usr/lib64/libgmodule-2.0.so
run/extcap/udpdump: /usr/lib64/libglib-2.0.so
run/extcap/udpdump: /usr/lib64/libgcrypt.so
run/extcap/udpdump: /usr/lib64/libgpg-error.so
run/extcap/udpdump: extcap/CMakeFiles/udpdump.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../run/extcap/udpdump"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/extcap && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/udpdump.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extcap/CMakeFiles/udpdump.dir/build: run/extcap/udpdump

.PHONY : extcap/CMakeFiles/udpdump.dir/build

extcap/CMakeFiles/udpdump.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/extcap && $(CMAKE_COMMAND) -P CMakeFiles/udpdump.dir/cmake_clean.cmake
.PHONY : extcap/CMakeFiles/udpdump.dir/clean

extcap/CMakeFiles/udpdump.dir/depend:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/extcap /root/CLionProjects/tshark_shanghai/cmake-build-debug /root/CLionProjects/tshark_shanghai/cmake-build-debug/extcap /root/CLionProjects/tshark_shanghai/cmake-build-debug/extcap/CMakeFiles/udpdump.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extcap/CMakeFiles/udpdump.dir/depend

