# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/ymq/clion/clion-2021.1.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/ymq/clion/clion-2021.1.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ymq/tshark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ymq/tshark/cmake-build-debug

# Include any dependencies generated for this target.
include epan/wmem/CMakeFiles/wmem_test.dir/depend.make

# Include the progress variables for this target.
include epan/wmem/CMakeFiles/wmem_test.dir/progress.make

# Include the compile flags for this target's objects.
include epan/wmem/CMakeFiles/wmem_test.dir/flags.make

epan/wmem/CMakeFiles/wmem_test.dir/wmem_test.c.o: epan/wmem/CMakeFiles/wmem_test.dir/flags.make
epan/wmem/CMakeFiles/wmem_test.dir/wmem_test.c.o: ../epan/wmem/wmem_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object epan/wmem/CMakeFiles/wmem_test.dir/wmem_test.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem_test.dir/wmem_test.c.o -c /home/ymq/tshark/epan/wmem/wmem_test.c

epan/wmem/CMakeFiles/wmem_test.dir/wmem_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem_test.dir/wmem_test.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_test.c > CMakeFiles/wmem_test.dir/wmem_test.c.i

epan/wmem/CMakeFiles/wmem_test.dir/wmem_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem_test.dir/wmem_test.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_test.c -o CMakeFiles/wmem_test.dir/wmem_test.c.s

# Object files for target wmem_test
wmem_test_OBJECTS = \
"CMakeFiles/wmem_test.dir/wmem_test.c.o"

# External object files for target wmem_test
wmem_test_EXTERNAL_OBJECTS = \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_array.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_core.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_simple.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_strict.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_interval_tree.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_list.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_map.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_miscutl.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_scopes.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_stack.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_strbuf.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_strutl.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_tree.c.o" \
"/home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/wmem_user_cb.c.o"

run/wmem_test: epan/wmem/CMakeFiles/wmem_test.dir/wmem_test.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_array.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_core.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_simple.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_strict.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_interval_tree.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_list.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_map.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_miscutl.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_scopes.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_stack.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_strbuf.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_strutl.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_tree.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem.dir/wmem_user_cb.c.o
run/wmem_test: epan/wmem/CMakeFiles/wmem_test.dir/build.make
run/wmem_test: /usr/lib64/libglib-2.0.so
run/wmem_test: run/libwsutil.so.12.0.0
run/wmem_test: /usr/lib64/libgmodule-2.0.so
run/wmem_test: /usr/lib64/libglib-2.0.so
run/wmem_test: /usr/lib64/libgcrypt.so
run/wmem_test: /usr/lib64/libgpg-error.so
run/wmem_test: epan/wmem/CMakeFiles/wmem_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../run/wmem_test"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wmem_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
epan/wmem/CMakeFiles/wmem_test.dir/build: run/wmem_test

.PHONY : epan/wmem/CMakeFiles/wmem_test.dir/build

epan/wmem/CMakeFiles/wmem_test.dir/clean:
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && $(CMAKE_COMMAND) -P CMakeFiles/wmem_test.dir/cmake_clean.cmake
.PHONY : epan/wmem/CMakeFiles/wmem_test.dir/clean

epan/wmem/CMakeFiles/wmem_test.dir/depend:
	cd /home/ymq/tshark/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ymq/tshark /home/ymq/tshark/epan/wmem /home/ymq/tshark/cmake-build-debug /home/ymq/tshark/cmake-build-debug/epan/wmem /home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/wmem/CMakeFiles/wmem_test.dir/depend

