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
include CMakeFiles/test_gst_opencv.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_gst_opencv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_gst_opencv.dir/flags.make

CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.o: CMakeFiles/test_gst_opencv.dir/flags.make
CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.o: test_gst_opencv.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mmc-wy/mmc_onboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.o -c /home/mmc-wy/mmc_onboard/test_gst_opencv.cpp

CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mmc-wy/mmc_onboard/test_gst_opencv.cpp > CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.i

CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mmc-wy/mmc_onboard/test_gst_opencv.cpp -o CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.s

# Object files for target test_gst_opencv
test_gst_opencv_OBJECTS = \
"CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.o"

# External object files for target test_gst_opencv
test_gst_opencv_EXTERNAL_OBJECTS =

test_gst_opencv: CMakeFiles/test_gst_opencv.dir/test_gst_opencv.cpp.o
test_gst_opencv: CMakeFiles/test_gst_opencv.dir/build.make
test_gst_opencv: /usr/local/lib/libopencv_objdetect.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_videostab.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_dnn.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_shape.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_superres.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_ml.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_stitching.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_video.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_photo.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_calib3d.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_features2d.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_flann.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_highgui.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_videoio.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_imgcodecs.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_imgproc.so.3.4.3
test_gst_opencv: /usr/local/lib/libopencv_core.so.3.4.3
test_gst_opencv: CMakeFiles/test_gst_opencv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mmc-wy/mmc_onboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_gst_opencv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_gst_opencv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_gst_opencv.dir/build: test_gst_opencv

.PHONY : CMakeFiles/test_gst_opencv.dir/build

CMakeFiles/test_gst_opencv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_gst_opencv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_gst_opencv.dir/clean

CMakeFiles/test_gst_opencv.dir/depend:
	cd /home/mmc-wy/mmc_onboard && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mmc-wy/mmc_onboard /home/mmc-wy/mmc_onboard /home/mmc-wy/mmc_onboard /home/mmc-wy/mmc_onboard /home/mmc-wy/mmc_onboard/CMakeFiles/test_gst_opencv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_gst_opencv.dir/depend

