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
include plugins/codecs/G711/CMakeFiles/g711.dir/depend.make

# Include the progress variables for this target.
include plugins/codecs/G711/CMakeFiles/g711.dir/progress.make

# Include the compile flags for this target's objects.
include plugins/codecs/G711/CMakeFiles/g711.dir/flags.make

plugins/codecs/G711/plugin.c: ../plugins/codecs/G711/G711decode.c
plugins/codecs/G711/plugin.c: ../tools/make-plugin-reg.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating plugin.c"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711 && /usr/bin/python3.6 /root/CLionProjects/tshark_gongjv/tools/make-plugin-reg.py /root/CLionProjects/tshark_gongjv/plugins/codecs/G711 plugin_codec G711decode.c

plugins/codecs/G711/CMakeFiles/g711.dir/plugin.c.o: plugins/codecs/G711/CMakeFiles/g711.dir/flags.make
plugins/codecs/G711/CMakeFiles/g711.dir/plugin.c.o: plugins/codecs/G711/plugin.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object plugins/codecs/G711/CMakeFiles/g711.dir/plugin.c.o"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/g711.dir/plugin.c.o   -c /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711/plugin.c

plugins/codecs/G711/CMakeFiles/g711.dir/plugin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/g711.dir/plugin.c.i"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711/plugin.c > CMakeFiles/g711.dir/plugin.c.i

plugins/codecs/G711/CMakeFiles/g711.dir/plugin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/g711.dir/plugin.c.s"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711/plugin.c -o CMakeFiles/g711.dir/plugin.c.s

plugins/codecs/G711/CMakeFiles/g711.dir/G711decode.c.o: plugins/codecs/G711/CMakeFiles/g711.dir/flags.make
plugins/codecs/G711/CMakeFiles/g711.dir/G711decode.c.o: ../plugins/codecs/G711/G711decode.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object plugins/codecs/G711/CMakeFiles/g711.dir/G711decode.c.o"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/g711.dir/G711decode.c.o   -c /root/CLionProjects/tshark_gongjv/plugins/codecs/G711/G711decode.c

plugins/codecs/G711/CMakeFiles/g711.dir/G711decode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/g711.dir/G711decode.c.i"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_gongjv/plugins/codecs/G711/G711decode.c > CMakeFiles/g711.dir/G711decode.c.i

plugins/codecs/G711/CMakeFiles/g711.dir/G711decode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/g711.dir/G711decode.c.s"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_gongjv/plugins/codecs/G711/G711decode.c -o CMakeFiles/g711.dir/G711decode.c.s

# Object files for target g711
g711_OBJECTS = \
"CMakeFiles/g711.dir/plugin.c.o" \
"CMakeFiles/g711.dir/G711decode.c.o"

# External object files for target g711
g711_EXTERNAL_OBJECTS =

run/plugins/3.4/codecs/g711.so: plugins/codecs/G711/CMakeFiles/g711.dir/plugin.c.o
run/plugins/3.4/codecs/g711.so: plugins/codecs/G711/CMakeFiles/g711.dir/G711decode.c.o
run/plugins/3.4/codecs/g711.so: plugins/codecs/G711/CMakeFiles/g711.dir/build.make
run/plugins/3.4/codecs/g711.so: run/libwsutil.so.12.0.0
run/plugins/3.4/codecs/g711.so: /usr/lib64/libgmodule-2.0.so
run/plugins/3.4/codecs/g711.so: /usr/lib64/libglib-2.0.so
run/plugins/3.4/codecs/g711.so: /usr/lib64/libgcrypt.so
run/plugins/3.4/codecs/g711.so: /usr/lib64/libgpg-error.so
run/plugins/3.4/codecs/g711.so: plugins/codecs/G711/CMakeFiles/g711.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_gongjv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C shared module ../../../run/plugins/3.4/codecs/g711.so"
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/g711.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plugins/codecs/G711/CMakeFiles/g711.dir/build: run/plugins/3.4/codecs/g711.so

.PHONY : plugins/codecs/G711/CMakeFiles/g711.dir/build

plugins/codecs/G711/CMakeFiles/g711.dir/clean:
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711 && $(CMAKE_COMMAND) -P CMakeFiles/g711.dir/cmake_clean.cmake
.PHONY : plugins/codecs/G711/CMakeFiles/g711.dir/clean

plugins/codecs/G711/CMakeFiles/g711.dir/depend: plugins/codecs/G711/plugin.c
	cd /root/CLionProjects/tshark_gongjv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_gongjv /root/CLionProjects/tshark_gongjv/plugins/codecs/G711 /root/CLionProjects/tshark_gongjv/cmake-build-debug /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711 /root/CLionProjects/tshark_gongjv/cmake-build-debug/plugins/codecs/G711/CMakeFiles/g711.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/codecs/G711/CMakeFiles/g711.dir/depend
