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
include writecap/CMakeFiles/writecap.dir/depend.make

# Include the progress variables for this target.
include writecap/CMakeFiles/writecap.dir/progress.make

# Include the compile flags for this target's objects.
include writecap/CMakeFiles/writecap.dir/flags.make

writecap/CMakeFiles/writecap.dir/pcapio.c.o: writecap/CMakeFiles/writecap.dir/flags.make
writecap/CMakeFiles/writecap.dir/pcapio.c.o: ../writecap/pcapio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object writecap/CMakeFiles/writecap.dir/pcapio.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/writecap && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/writecap.dir/pcapio.c.o   -c /root/CLionProjects/tshark_shanghai/writecap/pcapio.c

writecap/CMakeFiles/writecap.dir/pcapio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/writecap.dir/pcapio.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/writecap && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/writecap/pcapio.c > CMakeFiles/writecap.dir/pcapio.c.i

writecap/CMakeFiles/writecap.dir/pcapio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/writecap.dir/pcapio.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/writecap && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/writecap/pcapio.c -o CMakeFiles/writecap.dir/pcapio.c.s

# Object files for target writecap
writecap_OBJECTS = \
"CMakeFiles/writecap.dir/pcapio.c.o"

# External object files for target writecap
writecap_EXTERNAL_OBJECTS =

run/libwritecap.a: writecap/CMakeFiles/writecap.dir/pcapio.c.o
run/libwritecap.a: writecap/CMakeFiles/writecap.dir/build.make
run/libwritecap.a: writecap/CMakeFiles/writecap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library ../run/libwritecap.a"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/writecap && $(CMAKE_COMMAND) -P CMakeFiles/writecap.dir/cmake_clean_target.cmake
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/writecap && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/writecap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
writecap/CMakeFiles/writecap.dir/build: run/libwritecap.a

.PHONY : writecap/CMakeFiles/writecap.dir/build

writecap/CMakeFiles/writecap.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/writecap && $(CMAKE_COMMAND) -P CMakeFiles/writecap.dir/cmake_clean.cmake
.PHONY : writecap/CMakeFiles/writecap.dir/clean

writecap/CMakeFiles/writecap.dir/depend:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/writecap /root/CLionProjects/tshark_shanghai/cmake-build-release /root/CLionProjects/tshark_shanghai/cmake-build-release/writecap /root/CLionProjects/tshark_shanghai/cmake-build-release/writecap/CMakeFiles/writecap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : writecap/CMakeFiles/writecap.dir/depend

