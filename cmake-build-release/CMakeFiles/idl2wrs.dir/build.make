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
include CMakeFiles/idl2wrs.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/idl2wrs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/idl2wrs.dir/flags.make

CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.o: CMakeFiles/idl2wrs.dir/flags.make
CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.o: ../epan/dissectors/dcerpc/idl2wrs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.o   -c /root/CLionProjects/tshark_shanghai/epan/dissectors/dcerpc/idl2wrs.c

CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/epan/dissectors/dcerpc/idl2wrs.c > CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.i

CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/epan/dissectors/dcerpc/idl2wrs.c -o CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.s

# Object files for target idl2wrs
idl2wrs_OBJECTS = \
"CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.o"

# External object files for target idl2wrs
idl2wrs_EXTERNAL_OBJECTS =

run/idl2wrs: CMakeFiles/idl2wrs.dir/epan/dissectors/dcerpc/idl2wrs.c.o
run/idl2wrs: CMakeFiles/idl2wrs.dir/build.make
run/idl2wrs: /usr/lib64/libglib-2.0.so
run/idl2wrs: run/libwsutil.so.12.0.0
run/idl2wrs: /usr/lib64/libgmodule-2.0.so
run/idl2wrs: /usr/lib64/libglib-2.0.so
run/idl2wrs: /usr/lib64/libgcrypt.so
run/idl2wrs: /usr/lib64/libgpg-error.so
run/idl2wrs: CMakeFiles/idl2wrs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable run/idl2wrs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/idl2wrs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/idl2wrs.dir/build: run/idl2wrs

.PHONY : CMakeFiles/idl2wrs.dir/build

CMakeFiles/idl2wrs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/idl2wrs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/idl2wrs.dir/clean

CMakeFiles/idl2wrs.dir/depend:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/cmake-build-release /root/CLionProjects/tshark_shanghai/cmake-build-release /root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles/idl2wrs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/idl2wrs.dir/depend
