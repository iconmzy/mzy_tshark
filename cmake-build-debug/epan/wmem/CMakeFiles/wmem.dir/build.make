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
include epan/wmem/CMakeFiles/wmem.dir/depend.make

# Include the progress variables for this target.
include epan/wmem/CMakeFiles/wmem.dir/progress.make

# Include the compile flags for this target's objects.
include epan/wmem/CMakeFiles/wmem.dir/flags.make

epan/wmem/CMakeFiles/wmem.dir/wmem_array.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_array.c.o: ../epan/wmem/wmem_array.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_array.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_array.c.o -c /home/ymq/tshark/epan/wmem/wmem_array.c

epan/wmem/CMakeFiles/wmem.dir/wmem_array.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_array.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_array.c > CMakeFiles/wmem.dir/wmem_array.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_array.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_array.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_array.c -o CMakeFiles/wmem.dir/wmem_array.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_core.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_core.c.o: ../epan/wmem/wmem_core.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_core.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_core.c.o -c /home/ymq/tshark/epan/wmem/wmem_core.c

epan/wmem/CMakeFiles/wmem.dir/wmem_core.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_core.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_core.c > CMakeFiles/wmem.dir/wmem_core.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_core.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_core.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_core.c -o CMakeFiles/wmem.dir/wmem_core.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block.c.o: ../epan/wmem/wmem_allocator_block.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_allocator_block.c.o -c /home/ymq/tshark/epan/wmem/wmem_allocator_block.c

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_allocator_block.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_allocator_block.c > CMakeFiles/wmem.dir/wmem_allocator_block.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_allocator_block.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_allocator_block.c -o CMakeFiles/wmem.dir/wmem_allocator_block.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.o: ../epan/wmem/wmem_allocator_block_fast.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.o -c /home/ymq/tshark/epan/wmem/wmem_allocator_block_fast.c

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_allocator_block_fast.c > CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_allocator_block_fast.c -o CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_simple.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_simple.c.o: ../epan/wmem/wmem_allocator_simple.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_simple.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_allocator_simple.c.o -c /home/ymq/tshark/epan/wmem/wmem_allocator_simple.c

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_simple.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_allocator_simple.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_allocator_simple.c > CMakeFiles/wmem.dir/wmem_allocator_simple.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_simple.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_allocator_simple.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_allocator_simple.c -o CMakeFiles/wmem.dir/wmem_allocator_simple.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_strict.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_strict.c.o: ../epan/wmem/wmem_allocator_strict.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_strict.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_allocator_strict.c.o -c /home/ymq/tshark/epan/wmem/wmem_allocator_strict.c

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_strict.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_allocator_strict.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_allocator_strict.c > CMakeFiles/wmem.dir/wmem_allocator_strict.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_strict.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_allocator_strict.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_allocator_strict.c -o CMakeFiles/wmem.dir/wmem_allocator_strict.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_interval_tree.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_interval_tree.c.o: ../epan/wmem/wmem_interval_tree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_interval_tree.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_interval_tree.c.o -c /home/ymq/tshark/epan/wmem/wmem_interval_tree.c

epan/wmem/CMakeFiles/wmem.dir/wmem_interval_tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_interval_tree.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_interval_tree.c > CMakeFiles/wmem.dir/wmem_interval_tree.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_interval_tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_interval_tree.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_interval_tree.c -o CMakeFiles/wmem.dir/wmem_interval_tree.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_list.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_list.c.o: ../epan/wmem/wmem_list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_list.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_list.c.o -c /home/ymq/tshark/epan/wmem/wmem_list.c

epan/wmem/CMakeFiles/wmem.dir/wmem_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_list.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_list.c > CMakeFiles/wmem.dir/wmem_list.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_list.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_list.c -o CMakeFiles/wmem.dir/wmem_list.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_map.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_map.c.o: ../epan/wmem/wmem_map.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_map.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_map.c.o -c /home/ymq/tshark/epan/wmem/wmem_map.c

epan/wmem/CMakeFiles/wmem.dir/wmem_map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_map.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_map.c > CMakeFiles/wmem.dir/wmem_map.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_map.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_map.c -o CMakeFiles/wmem.dir/wmem_map.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_miscutl.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_miscutl.c.o: ../epan/wmem/wmem_miscutl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_miscutl.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_miscutl.c.o -c /home/ymq/tshark/epan/wmem/wmem_miscutl.c

epan/wmem/CMakeFiles/wmem.dir/wmem_miscutl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_miscutl.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_miscutl.c > CMakeFiles/wmem.dir/wmem_miscutl.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_miscutl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_miscutl.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_miscutl.c -o CMakeFiles/wmem.dir/wmem_miscutl.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_scopes.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_scopes.c.o: ../epan/wmem/wmem_scopes.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_scopes.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_scopes.c.o -c /home/ymq/tshark/epan/wmem/wmem_scopes.c

epan/wmem/CMakeFiles/wmem.dir/wmem_scopes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_scopes.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_scopes.c > CMakeFiles/wmem.dir/wmem_scopes.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_scopes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_scopes.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_scopes.c -o CMakeFiles/wmem.dir/wmem_scopes.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_stack.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_stack.c.o: ../epan/wmem/wmem_stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_stack.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_stack.c.o -c /home/ymq/tshark/epan/wmem/wmem_stack.c

epan/wmem/CMakeFiles/wmem.dir/wmem_stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_stack.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_stack.c > CMakeFiles/wmem.dir/wmem_stack.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_stack.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_stack.c -o CMakeFiles/wmem.dir/wmem_stack.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_strbuf.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_strbuf.c.o: ../epan/wmem/wmem_strbuf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_strbuf.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_strbuf.c.o -c /home/ymq/tshark/epan/wmem/wmem_strbuf.c

epan/wmem/CMakeFiles/wmem.dir/wmem_strbuf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_strbuf.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_strbuf.c > CMakeFiles/wmem.dir/wmem_strbuf.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_strbuf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_strbuf.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_strbuf.c -o CMakeFiles/wmem.dir/wmem_strbuf.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_strutl.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_strutl.c.o: ../epan/wmem/wmem_strutl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_strutl.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_strutl.c.o -c /home/ymq/tshark/epan/wmem/wmem_strutl.c

epan/wmem/CMakeFiles/wmem.dir/wmem_strutl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_strutl.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_strutl.c > CMakeFiles/wmem.dir/wmem_strutl.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_strutl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_strutl.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_strutl.c -o CMakeFiles/wmem.dir/wmem_strutl.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_tree.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_tree.c.o: ../epan/wmem/wmem_tree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_tree.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_tree.c.o -c /home/ymq/tshark/epan/wmem/wmem_tree.c

epan/wmem/CMakeFiles/wmem.dir/wmem_tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_tree.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_tree.c > CMakeFiles/wmem.dir/wmem_tree.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_tree.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_tree.c -o CMakeFiles/wmem.dir/wmem_tree.c.s

epan/wmem/CMakeFiles/wmem.dir/wmem_user_cb.c.o: epan/wmem/CMakeFiles/wmem.dir/flags.make
epan/wmem/CMakeFiles/wmem.dir/wmem_user_cb.c.o: ../epan/wmem/wmem_user_cb.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymq/tshark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building C object epan/wmem/CMakeFiles/wmem.dir/wmem_user_cb.c.o"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wmem.dir/wmem_user_cb.c.o -c /home/ymq/tshark/epan/wmem/wmem_user_cb.c

epan/wmem/CMakeFiles/wmem.dir/wmem_user_cb.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wmem.dir/wmem_user_cb.c.i"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ymq/tshark/epan/wmem/wmem_user_cb.c > CMakeFiles/wmem.dir/wmem_user_cb.c.i

epan/wmem/CMakeFiles/wmem.dir/wmem_user_cb.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wmem.dir/wmem_user_cb.c.s"
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ymq/tshark/epan/wmem/wmem_user_cb.c -o CMakeFiles/wmem.dir/wmem_user_cb.c.s

wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_array.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_core.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_block_fast.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_simple.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_allocator_strict.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_interval_tree.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_list.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_map.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_miscutl.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_scopes.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_stack.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_strbuf.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_strutl.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_tree.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/wmem_user_cb.c.o
wmem: epan/wmem/CMakeFiles/wmem.dir/build.make

.PHONY : wmem

# Rule to build all files generated by this target.
epan/wmem/CMakeFiles/wmem.dir/build: wmem

.PHONY : epan/wmem/CMakeFiles/wmem.dir/build

epan/wmem/CMakeFiles/wmem.dir/clean:
	cd /home/ymq/tshark/cmake-build-debug/epan/wmem && $(CMAKE_COMMAND) -P CMakeFiles/wmem.dir/cmake_clean.cmake
.PHONY : epan/wmem/CMakeFiles/wmem.dir/clean

epan/wmem/CMakeFiles/wmem.dir/depend:
	cd /home/ymq/tshark/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ymq/tshark /home/ymq/tshark/epan/wmem /home/ymq/tshark/cmake-build-debug /home/ymq/tshark/cmake-build-debug/epan/wmem /home/ymq/tshark/cmake-build-debug/epan/wmem/CMakeFiles/wmem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/wmem/CMakeFiles/wmem.dir/depend

