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
include plugins/codecs/G722/CMakeFiles/g722.dir/depend.make

# Include the progress variables for this target.
include plugins/codecs/G722/CMakeFiles/g722.dir/progress.make

# Include the compile flags for this target's objects.
include plugins/codecs/G722/CMakeFiles/g722.dir/flags.make

plugins/codecs/G722/plugin.c: ../plugins/codecs/G722/G722decode.c
plugins/codecs/G722/plugin.c: ../tools/make-plugin-reg.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating plugin.c"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722 && /usr/bin/python3.6 /root/CLionProjects/tshark_shanghai/tools/make-plugin-reg.py /root/CLionProjects/tshark_shanghai/plugins/codecs/G722 plugin_codec G722decode.c

plugins/codecs/G722/CMakeFiles/g722.dir/plugin.c.o: plugins/codecs/G722/CMakeFiles/g722.dir/flags.make
plugins/codecs/G722/CMakeFiles/g722.dir/plugin.c.o: plugins/codecs/G722/plugin.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object plugins/codecs/G722/CMakeFiles/g722.dir/plugin.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/g722.dir/plugin.c.o   -c /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722/plugin.c

plugins/codecs/G722/CMakeFiles/g722.dir/plugin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/g722.dir/plugin.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722/plugin.c > CMakeFiles/g722.dir/plugin.c.i

plugins/codecs/G722/CMakeFiles/g722.dir/plugin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/g722.dir/plugin.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722/plugin.c -o CMakeFiles/g722.dir/plugin.c.s

plugins/codecs/G722/CMakeFiles/g722.dir/G722decode.c.o: plugins/codecs/G722/CMakeFiles/g722.dir/flags.make
plugins/codecs/G722/CMakeFiles/g722.dir/G722decode.c.o: ../plugins/codecs/G722/G722decode.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object plugins/codecs/G722/CMakeFiles/g722.dir/G722decode.c.o"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/g722.dir/G722decode.c.o   -c /root/CLionProjects/tshark_shanghai/plugins/codecs/G722/G722decode.c

plugins/codecs/G722/CMakeFiles/g722.dir/G722decode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/g722.dir/G722decode.c.i"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/tshark_shanghai/plugins/codecs/G722/G722decode.c > CMakeFiles/g722.dir/G722decode.c.i

plugins/codecs/G722/CMakeFiles/g722.dir/G722decode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/g722.dir/G722decode.c.s"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/tshark_shanghai/plugins/codecs/G722/G722decode.c -o CMakeFiles/g722.dir/G722decode.c.s

# Object files for target g722
g722_OBJECTS = \
"CMakeFiles/g722.dir/plugin.c.o" \
"CMakeFiles/g722.dir/G722decode.c.o"

# External object files for target g722
g722_EXTERNAL_OBJECTS =

run/plugins/3.4/codecs/g722.so: plugins/codecs/G722/CMakeFiles/g722.dir/plugin.c.o
run/plugins/3.4/codecs/g722.so: plugins/codecs/G722/CMakeFiles/g722.dir/G722decode.c.o
run/plugins/3.4/codecs/g722.so: plugins/codecs/G722/CMakeFiles/g722.dir/build.make
run/plugins/3.4/codecs/g722.so: run/libwsutil.so.12.0.0
run/plugins/3.4/codecs/g722.so: /lib64/libspandsp.so
run/plugins/3.4/codecs/g722.so: /usr/lib64/libgmodule-2.0.so
run/plugins/3.4/codecs/g722.so: /usr/lib64/libglib-2.0.so
run/plugins/3.4/codecs/g722.so: /usr/lib64/libgcrypt.so
run/plugins/3.4/codecs/g722.so: /usr/lib64/libgpg-error.so
run/plugins/3.4/codecs/g722.so: plugins/codecs/G722/CMakeFiles/g722.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C shared module ../../../run/plugins/3.4/codecs/g722.so"
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/g722.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plugins/codecs/G722/CMakeFiles/g722.dir/build: run/plugins/3.4/codecs/g722.so

.PHONY : plugins/codecs/G722/CMakeFiles/g722.dir/build

plugins/codecs/G722/CMakeFiles/g722.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722 && $(CMAKE_COMMAND) -P CMakeFiles/g722.dir/cmake_clean.cmake
.PHONY : plugins/codecs/G722/CMakeFiles/g722.dir/clean

plugins/codecs/G722/CMakeFiles/g722.dir/depend: plugins/codecs/G722/plugin.c
	cd /root/CLionProjects/tshark_shanghai/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/plugins/codecs/G722 /root/CLionProjects/tshark_shanghai/cmake-build-release /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722 /root/CLionProjects/tshark_shanghai/cmake-build-release/plugins/codecs/G722/CMakeFiles/g722.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/codecs/G722/CMakeFiles/g722.dir/depend

