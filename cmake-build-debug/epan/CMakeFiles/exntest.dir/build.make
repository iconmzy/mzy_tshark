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

# Include any dependencies generated for this target.
include epan/CMakeFiles/exntest.dir/depend.make

# Include the progress variables for this target.
include epan/CMakeFiles/exntest.dir/progress.make

# Include the compile flags for this target's objects.
include epan/CMakeFiles/exntest.dir/flags.make

epan/CMakeFiles/exntest.dir/exntest.c.o: epan/CMakeFiles/exntest.dir/flags.make
epan/CMakeFiles/exntest.dir/exntest.c.o: ../epan/exntest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object epan/CMakeFiles/exntest.dir/exntest.c.o"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/exntest.dir/exntest.c.o   -c /root/CLionProjects/tshark_gongjv/epan/exntest.c

epan/CMakeFiles/exntest.dir/exntest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/exntest.dir/exntest.c.i"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_gongjv/epan/exntest.c > CMakeFiles/exntest.dir/exntest.c.i

epan/CMakeFiles/exntest.dir/exntest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/exntest.dir/exntest.c.s"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_gongjv/epan/exntest.c -o CMakeFiles/exntest.dir/exntest.c.s

epan/CMakeFiles/exntest.dir/except.c.o: epan/CMakeFiles/exntest.dir/flags.make
epan/CMakeFiles/exntest.dir/except.c.o: ../epan/except.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object epan/CMakeFiles/exntest.dir/except.c.o"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/exntest.dir/except.c.o   -c /root/CLionProjects/tshark_gongjv/epan/except.c

epan/CMakeFiles/exntest.dir/except.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/exntest.dir/except.c.i"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_gongjv/epan/except.c > CMakeFiles/exntest.dir/except.c.i

epan/CMakeFiles/exntest.dir/except.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/exntest.dir/except.c.s"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_gongjv/epan/except.c -o CMakeFiles/exntest.dir/except.c.s

# Object files for target exntest
exntest_OBJECTS = \
"CMakeFiles/exntest.dir/exntest.c.o" \
"CMakeFiles/exntest.dir/except.c.o"

# External object files for target exntest
exntest_EXTERNAL_OBJECTS =

run/exntest: epan/CMakeFiles/exntest.dir/exntest.c.o
run/exntest: epan/CMakeFiles/exntest.dir/except.c.o
run/exntest: epan/CMakeFiles/exntest.dir/build.make
run/exntest: /usr/lib64/libglib-2.0.so
run/exntest: epan/CMakeFiles/exntest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ../run/exntest"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exntest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
epan/CMakeFiles/exntest.dir/build: run/exntest

.PHONY : epan/CMakeFiles/exntest.dir/build

epan/CMakeFiles/exntest.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan && $(CMAKE_COMMAND) -P CMakeFiles/exntest.dir/cmake_clean.cmake
.PHONY : epan/CMakeFiles/exntest.dir/clean

epan/CMakeFiles/exntest.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/epan /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/CMakeFiles/exntest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/CMakeFiles/exntest.dir/depend

