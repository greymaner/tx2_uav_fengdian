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
include modules/embed-resource/CMakeFiles/embed-resource.dir/depend.make

# Include the progress variables for this target.
include modules/embed-resource/CMakeFiles/embed-resource.dir/progress.make

# Include the compile flags for this target's objects.
include modules/embed-resource/CMakeFiles/embed-resource.dir/flags.make

modules/embed-resource/CMakeFiles/embed-resource.dir/embedresource.cpp.o: modules/embed-resource/CMakeFiles/embed-resource.dir/flags.make
modules/embed-resource/CMakeFiles/embed-resource.dir/embedresource.cpp.o: modules/embed-resource/embedresource.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mmc-wy/mmc_onboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object modules/embed-resource/CMakeFiles/embed-resource.dir/embedresource.cpp.o"
	cd /home/mmc-wy/mmc_onboard/modules/embed-resource && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/embed-resource.dir/embedresource.cpp.o -c /home/mmc-wy/mmc_onboard/modules/embed-resource/embedresource.cpp

modules/embed-resource/CMakeFiles/embed-resource.dir/embedresource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/embed-resource.dir/embedresource.cpp.i"
	cd /home/mmc-wy/mmc_onboard/modules/embed-resource && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mmc-wy/mmc_onboard/modules/embed-resource/embedresource.cpp > CMakeFiles/embed-resource.dir/embedresource.cpp.i

modules/embed-resource/CMakeFiles/embed-resource.dir/embedresource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/embed-resource.dir/embedresource.cpp.s"
	cd /home/mmc-wy/mmc_onboard/modules/embed-resource && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mmc-wy/mmc_onboard/modules/embed-resource/embedresource.cpp -o CMakeFiles/embed-resource.dir/embedresource.cpp.s

# Object files for target embed-resource
embed__resource_OBJECTS = \
"CMakeFiles/embed-resource.dir/embedresource.cpp.o"

# External object files for target embed-resource
embed__resource_EXTERNAL_OBJECTS =

modules/embed-resource/embed-resource: modules/embed-resource/CMakeFiles/embed-resource.dir/embedresource.cpp.o
modules/embed-resource/embed-resource: modules/embed-resource/CMakeFiles/embed-resource.dir/build.make
modules/embed-resource/embed-resource: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
modules/embed-resource/embed-resource: /usr/lib/x86_64-linux-gnu/libboost_system.so
modules/embed-resource/embed-resource: modules/embed-resource/CMakeFiles/embed-resource.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mmc-wy/mmc_onboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable embed-resource"
	cd /home/mmc-wy/mmc_onboard/modules/embed-resource && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/embed-resource.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/embed-resource/CMakeFiles/embed-resource.dir/build: modules/embed-resource/embed-resource

.PHONY : modules/embed-resource/CMakeFiles/embed-resource.dir/build

modules/embed-resource/CMakeFiles/embed-resource.dir/clean:
	cd /home/mmc-wy/mmc_onboard/modules/embed-resource && $(CMAKE_COMMAND) -P CMakeFiles/embed-resource.dir/cmake_clean.cmake
.PHONY : modules/embed-resource/CMakeFiles/embed-resource.dir/clean

modules/embed-resource/CMakeFiles/embed-resource.dir/depend:
	cd /home/mmc-wy/mmc_onboard && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mmc-wy/mmc_onboard /home/mmc-wy/mmc_onboard/modules/embed-resource /home/mmc-wy/mmc_onboard /home/mmc-wy/mmc_onboard/modules/embed-resource /home/mmc-wy/mmc_onboard/modules/embed-resource/CMakeFiles/embed-resource.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/embed-resource/CMakeFiles/embed-resource.dir/depend

