# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
include dependencies/openal/CMakeFiles/alrecord.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/openal/CMakeFiles/alrecord.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/openal/CMakeFiles/alrecord.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/openal/CMakeFiles/alrecord.dir/flags.make

dependencies/openal/CMakeFiles/alrecord.dir/examples/alrecord.c.o: dependencies/openal/CMakeFiles/alrecord.dir/flags.make
dependencies/openal/CMakeFiles/alrecord.dir/examples/alrecord.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alrecord.c
dependencies/openal/CMakeFiles/alrecord.dir/examples/alrecord.c.o: dependencies/openal/CMakeFiles/alrecord.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/openal/CMakeFiles/alrecord.dir/examples/alrecord.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alrecord.dir/examples/alrecord.c.o -MF CMakeFiles/alrecord.dir/examples/alrecord.c.o.d -o CMakeFiles/alrecord.dir/examples/alrecord.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alrecord.c

dependencies/openal/CMakeFiles/alrecord.dir/examples/alrecord.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/alrecord.dir/examples/alrecord.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alrecord.c > CMakeFiles/alrecord.dir/examples/alrecord.c.i

dependencies/openal/CMakeFiles/alrecord.dir/examples/alrecord.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/alrecord.dir/examples/alrecord.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alrecord.c -o CMakeFiles/alrecord.dir/examples/alrecord.c.s

# Object files for target alrecord
alrecord_OBJECTS = \
"CMakeFiles/alrecord.dir/examples/alrecord.c.o"

# External object files for target alrecord
alrecord_EXTERNAL_OBJECTS =

dependencies/openal/alrecord: dependencies/openal/CMakeFiles/alrecord.dir/examples/alrecord.c.o
dependencies/openal/alrecord: dependencies/openal/CMakeFiles/alrecord.dir/build.make
dependencies/openal/alrecord: dependencies/openal/libal-excommon.a
dependencies/openal/alrecord: dependencies/openal/libopenal.so.1.23.1
dependencies/openal/alrecord: dependencies/openal/CMakeFiles/alrecord.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable alrecord"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alrecord.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/openal/CMakeFiles/alrecord.dir/build: dependencies/openal/alrecord
.PHONY : dependencies/openal/CMakeFiles/alrecord.dir/build

dependencies/openal/CMakeFiles/alrecord.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -P CMakeFiles/alrecord.dir/cmake_clean.cmake
.PHONY : dependencies/openal/CMakeFiles/alrecord.dir/clean

dependencies/openal/CMakeFiles/alrecord.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal/CMakeFiles/alrecord.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/openal/CMakeFiles/alrecord.dir/depend

