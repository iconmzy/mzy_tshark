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
include CMakeFiles/capture_opts.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/capture_opts.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/capture_opts.dir/flags.make

CMakeFiles/capture_opts.dir/capture_opts.c.o: CMakeFiles/capture_opts.dir/flags.make
CMakeFiles/capture_opts.dir/capture_opts.c.o: ../capture_opts.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/capture_opts.dir/capture_opts.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/capture_opts.dir/capture_opts.c.o   -c /root/CLionProjects/tshark_gongjv/capture_opts.c

CMakeFiles/capture_opts.dir/capture_opts.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/capture_opts.dir/capture_opts.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_gongjv/capture_opts.c > CMakeFiles/capture_opts.dir/capture_opts.c.i

CMakeFiles/capture_opts.dir/capture_opts.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/capture_opts.dir/capture_opts.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_gongjv/capture_opts.c -o CMakeFiles/capture_opts.dir/capture_opts.c.s

capture_opts: CMakeFiles/capture_opts.dir/capture_opts.c.o
capture_opts: CMakeFiles/capture_opts.dir/build.make

.PHONY : capture_opts

# Rule to build all files generated by this target.
CMakeFiles/capture_opts.dir/build: capture_opts

.PHONY : CMakeFiles/capture_opts.dir/build

CMakeFiles/capture_opts.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/capture_opts.dir/cmake_clean.cmake
.PHONY : CMakeFiles/capture_opts.dir/clean

CMakeFiles/capture_opts.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles/capture_opts.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/capture_opts.dir/depend
