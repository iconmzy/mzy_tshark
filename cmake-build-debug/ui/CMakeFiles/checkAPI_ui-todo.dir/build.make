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

# Utility rule file for checkAPI_ui-todo.

# Include the progress variables for this target.
include ui/CMakeFiles/checkAPI_ui-todo.dir/progress.make

ui/CMakeFiles/checkAPI_ui-todo:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/CLionProjects/tshark_shanghai/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running checkAPI_ui-todo"
	cd /root/CLionProjects/tshark_shanghai/ui && /usr/bin/perl /root/CLionProjects/tshark_shanghai/tools/checkAPIs.pl -M alert_box.c capture.c capture_ui_utils.c clopts_common.c cmdarg_err.c commandline.c console.c decode_as_utils.c dissect_opts.c export_object_ui.c export_pdu_ui_utils.c help_url.c failure_message.c file_dialog.c filter_files.c firewall_rules.c iface_toolbar.c iface_lists.c io_graph_item.c language.c mcast_stream.c packet_list_utils.c packet_range.c persfilepath_opt.c preference_utils.c profile.c proto_hier_stats.c recent.c rtp_media.c rtp_stream.c rtp_stream_id.c service_response_time.c software_update.c ssl_key_export.c summary.c tap_export_pdu.c tap-iax2-analysis.c tap-rtp-analysis.c tap-rtp-common.c tap-sctp-analysis.c tap-rlc-graph.c tap-tcp-stream.c text_import.c time_shift.c traffic_table_ui.c util.c voip_calls.c

checkAPI_ui-todo: ui/CMakeFiles/checkAPI_ui-todo
checkAPI_ui-todo: ui/CMakeFiles/checkAPI_ui-todo.dir/build.make

.PHONY : checkAPI_ui-todo

# Rule to build all files generated by this target.
ui/CMakeFiles/checkAPI_ui-todo.dir/build: checkAPI_ui-todo

.PHONY : ui/CMakeFiles/checkAPI_ui-todo.dir/build

ui/CMakeFiles/checkAPI_ui-todo.dir/clean:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug/ui && $(CMAKE_COMMAND) -P CMakeFiles/checkAPI_ui-todo.dir/cmake_clean.cmake
.PHONY : ui/CMakeFiles/checkAPI_ui-todo.dir/clean

ui/CMakeFiles/checkAPI_ui-todo.dir/depend:
	cd /root/CLionProjects/tshark_shanghai/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/tshark_shanghai /root/CLionProjects/tshark_shanghai/ui /root/CLionProjects/tshark_shanghai/cmake-build-debug /root/CLionProjects/tshark_shanghai/cmake-build-debug/ui /root/CLionProjects/tshark_shanghai/cmake-build-debug/ui/CMakeFiles/checkAPI_ui-todo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ui/CMakeFiles/checkAPI_ui-todo.dir/depend

