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
include plugins/epan/gryphon/CMakeFiles/gryphon.dir/depend.make

# Include the progress variables for this target.
include plugins/epan/gryphon/CMakeFiles/gryphon.dir/progress.make

# Include the compile flags for this target's objects.
include plugins/epan/gryphon/CMakeFiles/gryphon.dir/flags.make

plugins/epan/gryphon/plugin.c: ../plugins/epan/gryphon/packet-gryphon.c
plugins/epan/gryphon/plugin.c: ../tools/make-plugin-reg.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating plugin.c"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon && /usr/bin/python3.6 /root/CLionProjects/tshark_gongjv/tools/make-plugin-reg.py /root/CLionProjects/tshark_gongjv/plugins/epan/gryphon plugin packet-gryphon.c

plugins/epan/gryphon/CMakeFiles/gryphon.dir/plugin.c.o: plugins/epan/gryphon/CMakeFiles/gryphon.dir/flags.make
plugins/epan/gryphon/CMakeFiles/gryphon.dir/plugin.c.o: plugins/epan/gryphon/plugin.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object plugins/epan/gryphon/CMakeFiles/gryphon.dir/plugin.c.o"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gryphon.dir/plugin.c.o   -c /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon/plugin.c

plugins/epan/gryphon/CMakeFiles/gryphon.dir/plugin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gryphon.dir/plugin.c.i"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon/plugin.c > CMakeFiles/gryphon.dir/plugin.c.i

plugins/epan/gryphon/CMakeFiles/gryphon.dir/plugin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gryphon.dir/plugin.c.s"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon/plugin.c -o CMakeFiles/gryphon.dir/plugin.c.s

plugins/epan/gryphon/CMakeFiles/gryphon.dir/packet-gryphon.c.o: plugins/epan/gryphon/CMakeFiles/gryphon.dir/flags.make
plugins/epan/gryphon/CMakeFiles/gryphon.dir/packet-gryphon.c.o: ../plugins/epan/gryphon/packet-gryphon.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object plugins/epan/gryphon/CMakeFiles/gryphon.dir/packet-gryphon.c.o"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gryphon.dir/packet-gryphon.c.o   -c /root/CLionProjects/tshark_gongjv/plugins/epan/gryphon/packet-gryphon.c

plugins/epan/gryphon/CMakeFiles/gryphon.dir/packet-gryphon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gryphon.dir/packet-gryphon.c.i"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_gongjv/plugins/epan/gryphon/packet-gryphon.c > CMakeFiles/gryphon.dir/packet-gryphon.c.i

plugins/epan/gryphon/CMakeFiles/gryphon.dir/packet-gryphon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gryphon.dir/packet-gryphon.c.s"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_gongjv/plugins/epan/gryphon/packet-gryphon.c -o CMakeFiles/gryphon.dir/packet-gryphon.c.s

# Object files for target gryphon
gryphon_OBJECTS = \
"CMakeFiles/gryphon.dir/plugin.c.o" \
"CMakeFiles/gryphon.dir/packet-gryphon.c.o"

# External object files for target gryphon
gryphon_EXTERNAL_OBJECTS =

run/plugins/3.4/epan/gryphon.so: plugins/epan/gryphon/CMakeFiles/gryphon.dir/plugin.c.o
run/plugins/3.4/epan/gryphon.so: plugins/epan/gryphon/CMakeFiles/gryphon.dir/packet-gryphon.c.o
run/plugins/3.4/epan/gryphon.so: plugins/epan/gryphon/CMakeFiles/gryphon.dir/build.make
run/plugins/3.4/epan/gryphon.so: run/libwireshark.so.14.0.5
run/plugins/3.4/epan/gryphon.so: run/libwiretap.so.11.0.5
run/plugins/3.4/epan/gryphon.so: run/libwsutil.so.12.0.0
run/plugins/3.4/epan/gryphon.so: /usr/lib64/libgmodule-2.0.so
run/plugins/3.4/epan/gryphon.so: /usr/lib64/libgcrypt.so
run/plugins/3.4/epan/gryphon.so: /usr/lib64/libgpg-error.so
run/plugins/3.4/epan/gryphon.so: /usr/lib64/libglib-2.0.so
run/plugins/3.4/epan/gryphon.so: plugins/epan/gryphon/CMakeFiles/gryphon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C shared module ../../../run/plugins/3.4/epan/gryphon.so"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gryphon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plugins/epan/gryphon/CMakeFiles/gryphon.dir/build: run/plugins/3.4/epan/gryphon.so

.PHONY : plugins/epan/gryphon/CMakeFiles/gryphon.dir/build

plugins/epan/gryphon/CMakeFiles/gryphon.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon && $(CMAKE_COMMAND) -P CMakeFiles/gryphon.dir/cmake_clean.cmake
.PHONY : plugins/epan/gryphon/CMakeFiles/gryphon.dir/clean

plugins/epan/gryphon/CMakeFiles/gryphon.dir/depend: plugins/epan/gryphon/plugin.c
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/plugins/epan/gryphon /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/epan/gryphon/CMakeFiles/gryphon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/epan/gryphon/CMakeFiles/gryphon.dir/depend

