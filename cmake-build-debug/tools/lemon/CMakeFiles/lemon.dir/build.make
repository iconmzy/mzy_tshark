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
include tools/lemon/CMakeFiles/lemon.dir/depend.make

# Include the progress variables for this target.
include tools/lemon/CMakeFiles/lemon.dir/progress.make

# Include the compile flags for this target's objects.
include tools/lemon/CMakeFiles/lemon.dir/flags.make

tools/lemon/CMakeFiles/lemon.dir/lemon.c.o: tools/lemon/CMakeFiles/lemon.dir/flags.make
tools/lemon/CMakeFiles/lemon.dir/lemon.c.o: ../tools/lemon/lemon.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tools/lemon/CMakeFiles/lemon.dir/lemon.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/tools/lemon && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lemon.dir/lemon.c.o   -c /root/CLionProjects/tshark_shanghai/tools/lemon/lemon.c

tools/lemon/CMakeFiles/lemon.dir/lemon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lemon.dir/lemon.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/tools/lemon && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/tools/lemon/lemon.c > CMakeFiles/lemon.dir/lemon.c.i

tools/lemon/CMakeFiles/lemon.dir/lemon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lemon.dir/lemon.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/tools/lemon && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/tools/lemon/lemon.c -o CMakeFiles/lemon.dir/lemon.c.s

# Object files for target lemon
lemon_OBJECTS = \
"CMakeFiles/lemon.dir/lemon.c.o"

# External object files for target lemon
lemon_EXTERNAL_OBJECTS =

run/lemon: tools/lemon/CMakeFiles/lemon.dir/lemon.c.o
run/lemon: tools/lemon/CMakeFiles/lemon.dir/build.make
run/lemon: tools/lemon/CMakeFiles/lemon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../run/lemon"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/tools/lemon && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lemon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/lemon/CMakeFiles/lemon.dir/build: run/lemon

.PHONY : tools/lemon/CMakeFiles/lemon.dir/build

tools/lemon/CMakeFiles/lemon.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/tools/lemon && $(CMAKE_COMMAND) -P CMakeFiles/lemon.dir/cmake_clean.cmake
.PHONY : tools/lemon/CMakeFiles/lemon.dir/clean

tools/lemon/CMakeFiles/lemon.dir/depend:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/tools/lemon /root/CLionProjects/tshark_shanghai/cmake-build-debug /root/CLionProjects/tshark_shanghai/cmake-build-debug/tools/lemon /root/CLionProjects/tshark_shanghai/cmake-build-debug/tools/lemon/CMakeFiles/lemon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/lemon/CMakeFiles/lemon.dir/depend

