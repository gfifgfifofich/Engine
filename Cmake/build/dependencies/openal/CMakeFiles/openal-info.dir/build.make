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
include dependencies/openal/CMakeFiles/openal-info.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/openal/CMakeFiles/openal-info.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/openal/CMakeFiles/openal-info.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/openal/CMakeFiles/openal-info.dir/flags.make

dependencies/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o: dependencies/openal/CMakeFiles/openal-info.dir/flags.make
dependencies/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/utils/openal-info.c
dependencies/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o: dependencies/openal/CMakeFiles/openal-info.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o -MF CMakeFiles/openal-info.dir/utils/openal-info.c.o.d -o CMakeFiles/openal-info.dir/utils/openal-info.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/utils/openal-info.c

dependencies/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/openal-info.dir/utils/openal-info.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/utils/openal-info.c > CMakeFiles/openal-info.dir/utils/openal-info.c.i

dependencies/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/openal-info.dir/utils/openal-info.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/utils/openal-info.c -o CMakeFiles/openal-info.dir/utils/openal-info.c.s

# Object files for target openal-info
openal__info_OBJECTS = \
"CMakeFiles/openal-info.dir/utils/openal-info.c.o"

# External object files for target openal-info
openal__info_EXTERNAL_OBJECTS =

dependencies/openal/openal-info: dependencies/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o
dependencies/openal/openal-info: dependencies/openal/CMakeFiles/openal-info.dir/build.make
dependencies/openal/openal-info: dependencies/openal/libopenal.so.1.23.1
dependencies/openal/openal-info: dependencies/openal/CMakeFiles/openal-info.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable openal-info"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/openal-info.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/openal/CMakeFiles/openal-info.dir/build: dependencies/openal/openal-info
.PHONY : dependencies/openal/CMakeFiles/openal-info.dir/build

dependencies/openal/CMakeFiles/openal-info.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -P CMakeFiles/openal-info.dir/cmake_clean.cmake
.PHONY : dependencies/openal/CMakeFiles/openal-info.dir/clean

dependencies/openal/CMakeFiles/openal-info.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal/CMakeFiles/openal-info.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/openal/CMakeFiles/openal-info.dir/depend

