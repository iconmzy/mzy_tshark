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
include epan/CMakeFiles/tvbtest.dir/depend.make

# Include the progress variables for this target.
include epan/CMakeFiles/tvbtest.dir/progress.make

# Include the compile flags for this target's objects.
include epan/CMakeFiles/tvbtest.dir/flags.make

epan/CMakeFiles/tvbtest.dir/tvbtest.c.o: epan/CMakeFiles/tvbtest.dir/flags.make
epan/CMakeFiles/tvbtest.dir/tvbtest.c.o: ../epan/tvbtest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object epan/CMakeFiles/tvbtest.dir/tvbtest.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/epan && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tvbtest.dir/tvbtest.c.o   -c /root/CLionProjects/tshark_shanghai/epan/tvbtest.c

epan/CMakeFiles/tvbtest.dir/tvbtest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tvbtest.dir/tvbtest.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/epan && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/epan/tvbtest.c > CMakeFiles/tvbtest.dir/tvbtest.c.i

epan/CMakeFiles/tvbtest.dir/tvbtest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tvbtest.dir/tvbtest.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/epan && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/epan/tvbtest.c -o CMakeFiles/tvbtest.dir/tvbtest.c.s

# Object files for target tvbtest
tvbtest_OBJECTS = \
"CMakeFiles/tvbtest.dir/tvbtest.c.o"

# External object files for target tvbtest
tvbtest_EXTERNAL_OBJECTS =

run/tvbtest: epan/CMakeFiles/tvbtest.dir/tvbtest.c.o
run/tvbtest: epan/CMakeFiles/tvbtest.dir/build.make
run/tvbtest: run/libwireshark.so.14.0.5
run/tvbtest: run/libwiretap.so.11.0.5
run/tvbtest: run/libwsutil.so.12.0.0
run/tvbtest: /usr/lib64/libgmodule-2.0.so
run/tvbtest: /usr/lib64/libgcrypt.so
run/tvbtest: /usr/lib64/libgpg-error.so
run/tvbtest: /usr/lib64/libglib-2.0.so
run/tvbtest: epan/CMakeFiles/tvbtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../run/tvbtest"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/epan && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tvbtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
epan/CMakeFiles/tvbtest.dir/build: run/tvbtest

.PHONY : epan/CMakeFiles/tvbtest.dir/build

epan/CMakeFiles/tvbtest.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/epan && $(CMAKE_COMMAND) -P CMakeFiles/tvbtest.dir/cmake_clean.cmake
.PHONY : epan/CMakeFiles/tvbtest.dir/clean

epan/CMakeFiles/tvbtest.dir/depend:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/epan /root/CLionProjects/tshark_shanghai/cmake-build-release /root/CLionProjects/tshark_shanghai/cmake-build-release/epan /root/CLionProjects/tshark_shanghai/cmake-build-release/epan/CMakeFiles/tvbtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/CMakeFiles/tvbtest.dir/depend
