# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_SOURCE_DIR = /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build

# Include any dependencies generated for this target.
include dependencies/openal/CMakeFiles/alconvolve.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/openal/CMakeFiles/alconvolve.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/openal/CMakeFiles/alconvolve.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/openal/CMakeFiles/alconvolve.dir/flags.make

dependencies/openal/CMakeFiles/alconvolve.dir/examples/alconvolve.c.o: dependencies/openal/CMakeFiles/alconvolve.dir/flags.make
dependencies/openal/CMakeFiles/alconvolve.dir/examples/alconvolve.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alconvolve.c
dependencies/openal/CMakeFiles/alconvolve.dir/examples/alconvolve.c.o: dependencies/openal/CMakeFiles/alconvolve.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/openal/CMakeFiles/alconvolve.dir/examples/alconvolve.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alconvolve.dir/examples/alconvolve.c.o -MF CMakeFiles/alconvolve.dir/examples/alconvolve.c.o.d -o CMakeFiles/alconvolve.dir/examples/alconvolve.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alconvolve.c

dependencies/openal/CMakeFiles/alconvolve.dir/examples/alconvolve.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/alconvolve.dir/examples/alconvolve.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alconvolve.c > CMakeFiles/alconvolve.dir/examples/alconvolve.c.i

dependencies/openal/CMakeFiles/alconvolve.dir/examples/alconvolve.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/alconvolve.dir/examples/alconvolve.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alconvolve.c -o CMakeFiles/alconvolve.dir/examples/alconvolve.c.s

# Object files for target alconvolve
alconvolve_OBJECTS = \
"CMakeFiles/alconvolve.dir/examples/alconvolve.c.o"

# External object files for target alconvolve
alconvolve_EXTERNAL_OBJECTS =

dependencies/openal/alconvolve: dependencies/openal/CMakeFiles/alconvolve.dir/examples/alconvolve.c.o
dependencies/openal/alconvolve: dependencies/openal/CMakeFiles/alconvolve.dir/build.make
dependencies/openal/alconvolve: dependencies/openal/libalcommon.a
dependencies/openal/alconvolve: /usr/lib/libsndfile.so
dependencies/openal/alconvolve: dependencies/openal/libal-excommon.a
dependencies/openal/alconvolve: dependencies/openal/libopenal.so.1.23.1
dependencies/openal/alconvolve: dependencies/openal/CMakeFiles/alconvolve.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable alconvolve"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alconvolve.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/openal/CMakeFiles/alconvolve.dir/build: dependencies/openal/alconvolve
.PHONY : dependencies/openal/CMakeFiles/alconvolve.dir/build

dependencies/openal/CMakeFiles/alconvolve.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -P CMakeFiles/alconvolve.dir/cmake_clean.cmake
.PHONY : dependencies/openal/CMakeFiles/alconvolve.dir/clean

dependencies/openal/CMakeFiles/alconvolve.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal/CMakeFiles/alconvolve.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/openal/CMakeFiles/alconvolve.dir/depend

