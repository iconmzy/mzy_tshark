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
include capchild/CMakeFiles/capchild.dir/depend.make

# Include the progress variables for this target.
include capchild/CMakeFiles/capchild.dir/progress.make

# Include the compile flags for this target's objects.
include capchild/CMakeFiles/capchild.dir/flags.make

capchild/CMakeFiles/capchild.dir/capture_ifinfo.c.o: capchild/CMakeFiles/capchild.dir/flags.make
capchild/CMakeFiles/capchild.dir/capture_ifinfo.c.o: ../capchild/capture_ifinfo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object capchild/CMakeFiles/capchild.dir/capture_ifinfo.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/capchild && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/capchild.dir/capture_ifinfo.c.o   -c /root/CLionProjects/tshark_shanghai/capchild/capture_ifinfo.c

capchild/CMakeFiles/capchild.dir/capture_ifinfo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/capchild.dir/capture_ifinfo.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/capchild && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/capchild/capture_ifinfo.c > CMakeFiles/capchild.dir/capture_ifinfo.c.i

capchild/CMakeFiles/capchild.dir/capture_ifinfo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/capchild.dir/capture_ifinfo.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/capchild && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/capchild/capture_ifinfo.c -o CMakeFiles/capchild.dir/capture_ifinfo.c.s

capchild/CMakeFiles/capchild.dir/capture_sync.c.o: capchild/CMakeFiles/capchild.dir/flags.make
capchild/CMakeFiles/capchild.dir/capture_sync.c.o: ../capchild/capture_sync.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object capchild/CMakeFiles/capchild.dir/capture_sync.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/capchild && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/capchild.dir/capture_sync.c.o   -c /root/CLionProjects/tshark_shanghai/capchild/capture_sync.c

capchild/CMakeFiles/capchild.dir/capture_sync.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/capchild.dir/capture_sync.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/capchild && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/capchild/capture_sync.c > CMakeFiles/capchild.dir/capture_sync.c.i

capchild/CMakeFiles/capchild.dir/capture_sync.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/capchild.dir/capture_sync.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/capchild && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/capchild/capture_sync.c -o CMakeFiles/capchild.dir/capture_sync.c.s

# Object files for target capchild
capchild_OBJECTS = \
"CMakeFiles/capchild.dir/capture_ifinfo.c.o" \
"CMakeFiles/capchild.dir/capture_sync.c.o"

# External object files for target capchild
capchild_EXTERNAL_OBJECTS =

run/libcapchild.a: capchild/CMakeFiles/capchild.dir/capture_ifinfo.c.o
run/libcapchild.a: capchild/CMakeFiles/capchild.dir/capture_sync.c.o
run/libcapchild.a: capchild/CMakeFiles/capchild.dir/build.make
run/libcapchild.a: capchild/CMakeFiles/capchild.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library ../run/libcapchild.a"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/capchild && $(CMAKE_COMMAND) -P CMakeFiles/capchild.dir/cmake_clean_target.cmake
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/capchild && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/capchild.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
capchild/CMakeFiles/capchild.dir/build: run/libcapchild.a

.PHONY : capchild/CMakeFiles/capchild.dir/build

capchild/CMakeFiles/capchild.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/capchild && $(CMAKE_COMMAND) -P CMakeFiles/capchild.dir/cmake_clean.cmake
.PHONY : capchild/CMakeFiles/capchild.dir/clean

capchild/CMakeFiles/capchild.dir/depend:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/capchild /root/CLionProjects/tshark_shanghai/cmake-build-debug /root/CLionProjects/tshark_shanghai/cmake-build-debug/capchild /root/CLionProjects/tshark_shanghai/cmake-build-debug/capchild/CMakeFiles/capchild.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : capchild/CMakeFiles/capchild.dir/depend

