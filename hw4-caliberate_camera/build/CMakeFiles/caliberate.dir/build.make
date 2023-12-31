# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xyt/rm_hw/hw4-caliberate_camera

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xyt/rm_hw/hw4-caliberate_camera/build

# Include any dependencies generated for this target.
include CMakeFiles/caliberate.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/caliberate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/caliberate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/caliberate.dir/flags.make

CMakeFiles/caliberate.dir/main.cpp.o: CMakeFiles/caliberate.dir/flags.make
CMakeFiles/caliberate.dir/main.cpp.o: ../main.cpp
CMakeFiles/caliberate.dir/main.cpp.o: CMakeFiles/caliberate.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xyt/rm_hw/hw4-caliberate_camera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/caliberate.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/caliberate.dir/main.cpp.o -MF CMakeFiles/caliberate.dir/main.cpp.o.d -o CMakeFiles/caliberate.dir/main.cpp.o -c /home/xyt/rm_hw/hw4-caliberate_camera/main.cpp

CMakeFiles/caliberate.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/caliberate.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xyt/rm_hw/hw4-caliberate_camera/main.cpp > CMakeFiles/caliberate.dir/main.cpp.i

CMakeFiles/caliberate.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/caliberate.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xyt/rm_hw/hw4-caliberate_camera/main.cpp -o CMakeFiles/caliberate.dir/main.cpp.s

# Object files for target caliberate
caliberate_OBJECTS = \
"CMakeFiles/caliberate.dir/main.cpp.o"

# External object files for target caliberate
caliberate_EXTERNAL_OBJECTS =

caliberate: CMakeFiles/caliberate.dir/main.cpp.o
caliberate: CMakeFiles/caliberate.dir/build.make
caliberate: /usr/local/lib/libopencv_gapi.so.4.8.0
caliberate: /usr/local/lib/libopencv_highgui.so.4.8.0
caliberate: /usr/local/lib/libopencv_ml.so.4.8.0
caliberate: /usr/local/lib/libopencv_objdetect.so.4.8.0
caliberate: /usr/local/lib/libopencv_photo.so.4.8.0
caliberate: /usr/local/lib/libopencv_stitching.so.4.8.0
caliberate: /usr/local/lib/libopencv_video.so.4.8.0
caliberate: /usr/local/lib/libopencv_videoio.so.4.8.0
caliberate: /usr/local/lib/libopencv_imgcodecs.so.4.8.0
caliberate: /usr/local/lib/libopencv_dnn.so.4.8.0
caliberate: /usr/local/lib/libopencv_calib3d.so.4.8.0
caliberate: /usr/local/lib/libopencv_features2d.so.4.8.0
caliberate: /usr/local/lib/libopencv_flann.so.4.8.0
caliberate: /usr/local/lib/libopencv_imgproc.so.4.8.0
caliberate: /usr/local/lib/libopencv_core.so.4.8.0
caliberate: CMakeFiles/caliberate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xyt/rm_hw/hw4-caliberate_camera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable caliberate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/caliberate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/caliberate.dir/build: caliberate
.PHONY : CMakeFiles/caliberate.dir/build

CMakeFiles/caliberate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/caliberate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/caliberate.dir/clean

CMakeFiles/caliberate.dir/depend:
	cd /home/xyt/rm_hw/hw4-caliberate_camera/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xyt/rm_hw/hw4-caliberate_camera /home/xyt/rm_hw/hw4-caliberate_camera /home/xyt/rm_hw/hw4-caliberate_camera/build /home/xyt/rm_hw/hw4-caliberate_camera/build /home/xyt/rm_hw/hw4-caliberate_camera/build/CMakeFiles/caliberate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/caliberate.dir/depend

