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
include CMakeFiles/cli_main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cli_main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cli_main.dir/flags.make

CMakeFiles/cli_main.dir/cli_main.c.o: CMakeFiles/cli_main.dir/flags.make
CMakeFiles/cli_main.dir/cli_main.c.o: ../cli_main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cli_main.dir/cli_main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cli_main.dir/cli_main.c.o   -c /root/CLionProjects/tshark_gongjv/cli_main.c

CMakeFiles/cli_main.dir/cli_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cli_main.dir/cli_main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_gongjv/cli_main.c > CMakeFiles/cli_main.dir/cli_main.c.i

CMakeFiles/cli_main.dir/cli_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cli_main.dir/cli_main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_gongjv/cli_main.c -o CMakeFiles/cli_main.dir/cli_main.c.s

cli_main: CMakeFiles/cli_main.dir/cli_main.c.o
cli_main: CMakeFiles/cli_main.dir/build.make

.PHONY : cli_main

# Rule to build all files generated by this target.
CMakeFiles/cli_main.dir/build: cli_main

.PHONY : CMakeFiles/cli_main.dir/build

CMakeFiles/cli_main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cli_main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cli_main.dir/clean

CMakeFiles/cli_main.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles/cli_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cli_main.dir/depend

