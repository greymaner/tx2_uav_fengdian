# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/mmc-wy/深圳学习资料/clion/clion-2018.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/mmc-wy/深圳学习资料/clion/clion-2018.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mmc-wy/mmc_onboard

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mmc-wy/mmc_onboard

# Include any dependencies generated for this target.
include modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/depend.make

# Include the progress variables for this target.
include modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/progress.make

# Include the compile flags for this target's objects.
include modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/flags.make

modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.o: modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/flags.make
modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.o: modules/MMC_UAVCAN_spec/libuavcan/libuavcan_drivers/linux/apps/uavcan_monitor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mmc-wy/mmc_onboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.o"
	cd /home/mmc-wy/mmc_onboard/modules/libuavcan/libuavcan_drivers/linux && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.o -c /home/mmc-wy/mmc_onboard/modules/MMC_UAVCAN_spec/libuavcan/libuavcan_drivers/linux/apps/uavcan_monitor.cpp

modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.i"
	cd /home/mmc-wy/mmc_onboard/modules/libuavcan/libuavcan_drivers/linux && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mmc-wy/mmc_onboard/modules/MMC_UAVCAN_spec/libuavcan/libuavcan_drivers/linux/apps/uavcan_monitor.cpp > CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.i

modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.s"
	cd /home/mmc-wy/mmc_onboard/modules/libuavcan/libuavcan_drivers/linux && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mmc-wy/mmc_onboard/modules/MMC_UAVCAN_spec/libuavcan/libuavcan_drivers/linux/apps/uavcan_monitor.cpp -o CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.s

# Object files for target uavcan_monitor
uavcan_monitor_OBJECTS = \
"CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.o"

# External object files for target uavcan_monitor
uavcan_monitor_EXTERNAL_OBJECTS =

modules/libuavcan/libuavcan_drivers/linux/uavcan_monitor: modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/apps/uavcan_monitor.cpp.o
modules/libuavcan/libuavcan_drivers/linux/uavcan_monitor: modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/build.make
modules/libuavcan/libuavcan_drivers/linux/uavcan_monitor: modules/libuavcan/libuavcan/libuavcan.a
modules/libuavcan/libuavcan_drivers/linux/uavcan_monitor: modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mmc-wy/mmc_onboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable uavcan_monitor"
	cd /home/mmc-wy/mmc_onboard/modules/libuavcan/libuavcan_drivers/linux && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uavcan_monitor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/build: modules/libuavcan/libuavcan_drivers/linux/uavcan_monitor

.PHONY : modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/build

modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/clean:
	cd /home/mmc-wy/mmc_onboard/modules/libuavcan/libuavcan_drivers/linux && $(CMAKE_COMMAND) -P CMakeFiles/uavcan_monitor.dir/cmake_clean.cmake
.PHONY : modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/clean

modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/depend:
	cd /home/mmc-wy/mmc_onboard && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mmc-wy/mmc_onboard /home/mmc-wy/mmc_onboard/modules/MMC_UAVCAN_spec/libuavcan/libuavcan_drivers/linux /home/mmc-wy/mmc_onboard /home/mmc-wy/mmc_onboard/modules/libuavcan/libuavcan_drivers/linux /home/mmc-wy/mmc_onboard/modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/libuavcan/libuavcan_drivers/linux/CMakeFiles/uavcan_monitor.dir/depend

