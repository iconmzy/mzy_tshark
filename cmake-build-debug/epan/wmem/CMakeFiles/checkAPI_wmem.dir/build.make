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

# Utility rule file for checkAPI_wmem.

# Include the progress variables for this target.
include epan/wmem/CMakeFiles/checkAPI_wmem.dir/progress.make

epan/wmem/CMakeFiles/checkAPI_wmem:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running checkAPI_wmem"
	cd /root/CLionProjects/tshark_gongjv/epan/wmem && /usr/bin/perl /root/CLionProjects/tshark_gongjv/tools/checkAPIs.pl --group termoutput:1 --summary-group termoutput wmem_array.c wmem_core.c wmem_allocator_block.c wmem_allocator_block_fast.c wmem_allocator_simple.c wmem_allocator_strict.c wmem_interval_tree.c wmem_list.c wmem_map.c wmem_miscutl.c wmem_scopes.c wmem_stack.c wmem_strbuf.c wmem_strutl.c wmem_tree.c wmem_user_cb.c

checkAPI_wmem: epan/wmem/CMakeFiles/checkAPI_wmem
checkAPI_wmem: epan/wmem/CMakeFiles/checkAPI_wmem.dir/build.make

.PHONY : checkAPI_wmem

# Rule to build all files generated by this target.
epan/wmem/CMakeFiles/checkAPI_wmem.dir/build: checkAPI_wmem

.PHONY : epan/wmem/CMakeFiles/checkAPI_wmem.dir/build

epan/wmem/CMakeFiles/checkAPI_wmem.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/wmem && $(CMAKE_COMMAND) -P CMakeFiles/checkAPI_wmem.dir/cmake_clean.cmake
.PHONY : epan/wmem/CMakeFiles/checkAPI_wmem.dir/clean

epan/wmem/CMakeFiles/checkAPI_wmem.dir/depend:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/epan/wmem /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/wmem /root/CLionProjects/tshark_gongjv/cmake-build-debug/epan/wmem/CMakeFiles/checkAPI_wmem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : epan/wmem/CMakeFiles/checkAPI_wmem.dir/depend

