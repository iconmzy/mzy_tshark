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

# Include any dependencies generated for this target.
include randpkt_core/CMakeFiles/randpkt_core.dir/depend.make

# Include the progress variables for this target.
include randpkt_core/CMakeFiles/randpkt_core.dir/progress.make

# Include the compile flags for this target's objects.
include randpkt_core/CMakeFiles/randpkt_core.dir/flags.make

randpkt_core/CMakeFiles/randpkt_core.dir/randpkt_core.c.o: randpkt_core/CMakeFiles/randpkt_core.dir/flags.make
randpkt_core/CMakeFiles/randpkt_core.dir/randpkt_core.c.o: randpkt_core/randpkt_core.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object randpkt_core/CMakeFiles/randpkt_core.dir/randpkt_core.c.o"
	cd /root/CLionProjects/tshark_test/randpkt_core && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/randpkt_core.dir/randpkt_core.c.o   -c /root/CLionProjects/tshark_test/randpkt_core/randpkt_core.c

randpkt_core/CMakeFiles/randpkt_core.dir/randpkt_core.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/randpkt_core.dir/randpkt_core.c.i"
	cd /root/CLionProjects/tshark_test/randpkt_core && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_test/randpkt_core/randpkt_core.c > CMakeFiles/randpkt_core.dir/randpkt_core.c.i

randpkt_core/CMakeFiles/randpkt_core.dir/randpkt_core.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/randpkt_core.dir/randpkt_core.c.s"
	cd /root/CLionProjects/tshark_test/randpkt_core && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_test/randpkt_core/randpkt_core.c -o CMakeFiles/randpkt_core.dir/randpkt_core.c.s

# Object files for target randpkt_core
randpkt_core_OBJECTS = \
"CMakeFiles/randpkt_core.dir/randpkt_core.c.o"

# External object files for target randpkt_core
randpkt_core_EXTERNAL_OBJECTS =

run/librandpkt_core.a: randpkt_core/CMakeFiles/randpkt_core.dir/randpkt_core.c.o
run/librandpkt_core.a: randpkt_core/CMakeFiles/randpkt_core.dir/build.make
run/librandpkt_core.a: randpkt_core/CMakeFiles/randpkt_core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library ../run/librandpkt_core.a"
	cd /root/CLionProjects/tshark_test/randpkt_core && $(CMAKE_COMMAND) -P CMakeFiles/randpkt_core.dir/cmake_clean_target.cmake
	cd /root/CLionProjects/tshark_test/randpkt_core && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/randpkt_core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
randpkt_core/CMakeFiles/randpkt_core.dir/build: run/librandpkt_core.a

.PHONY : randpkt_core/CMakeFiles/randpkt_core.dir/build

randpkt_core/CMakeFiles/randpkt_core.dir/clean:
	cd /root/CLionProjects/tshark_test/randpkt_core && $(CMAKE_COMMAND) -P CMakeFiles/randpkt_core.dir/cmake_clean.cmake
.PHONY : randpkt_core/CMakeFiles/randpkt_core.dir/clean

randpkt_core/CMakeFiles/randpkt_core.dir/depend:
	cd /root/CLionProjects/tshark_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_test /root/CLionProjects/tshark_test/randpkt_core /root/CLionProjects/tshark_test /root/CLionProjects/tshark_test/randpkt_core /root/CLionProjects/tshark_test/randpkt_core/CMakeFiles/randpkt_core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : randpkt_core/CMakeFiles/randpkt_core.dir/depend

