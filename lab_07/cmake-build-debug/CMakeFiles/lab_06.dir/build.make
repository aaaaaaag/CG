# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/denis/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/denis/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/denis/CG/lab_07

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/denis/CG/lab_07/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab_06.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab_06.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab_06.dir/flags.make

CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.o: CMakeFiles/lab_06.dir/flags.make
CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.o: ../src/MyMainWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/denis/CG/lab_07/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.o -c /home/denis/CG/lab_07/src/MyMainWindow.cpp

CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/denis/CG/lab_07/src/MyMainWindow.cpp > CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.i

CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/denis/CG/lab_07/src/MyMainWindow.cpp -o CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.s

CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.o: CMakeFiles/lab_06.dir/flags.make
CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.o: ../src/CanvasPolygon.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/denis/CG/lab_07/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.o -c /home/denis/CG/lab_07/src/CanvasPolygon.cpp

CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/denis/CG/lab_07/src/CanvasPolygon.cpp > CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.i

CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/denis/CG/lab_07/src/CanvasPolygon.cpp -o CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.s

# Object files for target lab_06
lab_06_OBJECTS = \
"CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.o" \
"CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.o"

# External object files for target lab_06
lab_06_EXTERNAL_OBJECTS =

liblab_06.a: CMakeFiles/lab_06.dir/src/MyMainWindow.cpp.o
liblab_06.a: CMakeFiles/lab_06.dir/src/CanvasPolygon.cpp.o
liblab_06.a: CMakeFiles/lab_06.dir/build.make
liblab_06.a: CMakeFiles/lab_06.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/denis/CG/lab_07/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library liblab_06.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lab_06.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab_06.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab_06.dir/build: liblab_06.a

.PHONY : CMakeFiles/lab_06.dir/build

CMakeFiles/lab_06.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab_06.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab_06.dir/clean

CMakeFiles/lab_06.dir/depend:
	cd /home/denis/CG/lab_07/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/denis/CG/lab_07 /home/denis/CG/lab_07 /home/denis/CG/lab_07/cmake-build-debug /home/denis/CG/lab_07/cmake-build-debug /home/denis/CG/lab_07/cmake-build-debug/CMakeFiles/lab_06.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab_06.dir/depend

