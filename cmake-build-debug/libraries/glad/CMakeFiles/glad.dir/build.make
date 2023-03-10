# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug"

# Include any dependencies generated for this target.
include libraries/glad/CMakeFiles/glad.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include libraries/glad/CMakeFiles/glad.dir/compiler_depend.make

# Include the progress variables for this target.
include libraries/glad/CMakeFiles/glad.dir/progress.make

# Include the compile flags for this target's objects.
include libraries/glad/CMakeFiles/glad.dir/flags.make

libraries/glad/CMakeFiles/glad.dir/src/glad.c.o: libraries/glad/CMakeFiles/glad.dir/flags.make
libraries/glad/CMakeFiles/glad.dir/src/glad.c.o: ../libraries/glad/src/glad.c
libraries/glad/CMakeFiles/glad.dir/src/glad.c.o: libraries/glad/CMakeFiles/glad.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object libraries/glad/CMakeFiles/glad.dir/src/glad.c.o"
	cd "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug/libraries/glad" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT libraries/glad/CMakeFiles/glad.dir/src/glad.c.o -MF CMakeFiles/glad.dir/src/glad.c.o.d -o CMakeFiles/glad.dir/src/glad.c.o -c "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/libraries/glad/src/glad.c"

libraries/glad/CMakeFiles/glad.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.dir/src/glad.c.i"
	cd "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug/libraries/glad" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/libraries/glad/src/glad.c" > CMakeFiles/glad.dir/src/glad.c.i

libraries/glad/CMakeFiles/glad.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.dir/src/glad.c.s"
	cd "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug/libraries/glad" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/libraries/glad/src/glad.c" -o CMakeFiles/glad.dir/src/glad.c.s

# Object files for target glad
glad_OBJECTS = \
"CMakeFiles/glad.dir/src/glad.c.o"

# External object files for target glad
glad_EXTERNAL_OBJECTS =

libraries/glad/libglad.a: libraries/glad/CMakeFiles/glad.dir/src/glad.c.o
libraries/glad/libglad.a: libraries/glad/CMakeFiles/glad.dir/build.make
libraries/glad/libglad.a: libraries/glad/CMakeFiles/glad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libglad.a"
	cd "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug/libraries/glad" && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean_target.cmake
	cd "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug/libraries/glad" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libraries/glad/CMakeFiles/glad.dir/build: libraries/glad/libglad.a
.PHONY : libraries/glad/CMakeFiles/glad.dir/build

libraries/glad/CMakeFiles/glad.dir/clean:
	cd "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug/libraries/glad" && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean.cmake
.PHONY : libraries/glad/CMakeFiles/glad.dir/clean

libraries/glad/CMakeFiles/glad.dir/depend:
	cd "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023" "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/libraries/glad" "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug" "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug/libraries/glad" "/Users/giorgioperri/Desktop/ITU/S2/Graphics Programming/graphics-programming-2023/cmake-build-debug/libraries/glad/CMakeFiles/glad.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : libraries/glad/CMakeFiles/glad.dir/depend

