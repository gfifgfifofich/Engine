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
include dependencies/openal/CMakeFiles/alffplay.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/openal/CMakeFiles/alffplay.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/openal/CMakeFiles/alffplay.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/openal/CMakeFiles/alffplay.dir/flags.make

dependencies/openal/CMakeFiles/alffplay.dir/examples/alffplay.cpp.o: dependencies/openal/CMakeFiles/alffplay.dir/flags.make
dependencies/openal/CMakeFiles/alffplay.dir/examples/alffplay.cpp.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alffplay.cpp
dependencies/openal/CMakeFiles/alffplay.dir/examples/alffplay.cpp.o: dependencies/openal/CMakeFiles/alffplay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object dependencies/openal/CMakeFiles/alffplay.dir/examples/alffplay.cpp.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alffplay.dir/examples/alffplay.cpp.o -MF CMakeFiles/alffplay.dir/examples/alffplay.cpp.o.d -o CMakeFiles/alffplay.dir/examples/alffplay.cpp.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alffplay.cpp

dependencies/openal/CMakeFiles/alffplay.dir/examples/alffplay.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/alffplay.dir/examples/alffplay.cpp.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alffplay.cpp > CMakeFiles/alffplay.dir/examples/alffplay.cpp.i

dependencies/openal/CMakeFiles/alffplay.dir/examples/alffplay.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/alffplay.dir/examples/alffplay.cpp.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/examples/alffplay.cpp -o CMakeFiles/alffplay.dir/examples/alffplay.cpp.s

# Object files for target alffplay
alffplay_OBJECTS = \
"CMakeFiles/alffplay.dir/examples/alffplay.cpp.o"

# External object files for target alffplay
alffplay_EXTERNAL_OBJECTS =

dependencies/openal/alffplay: dependencies/openal/CMakeFiles/alffplay.dir/examples/alffplay.cpp.o
dependencies/openal/alffplay: dependencies/openal/CMakeFiles/alffplay.dir/build.make
dependencies/openal/alffplay: /usr/lib/libSDL2-2.0.so.0.3000.2
dependencies/openal/alffplay: /usr/lib/libavformat.so
dependencies/openal/alffplay: /usr/lib/libavcodec.so
dependencies/openal/alffplay: /usr/lib/libavutil.so
dependencies/openal/alffplay: /usr/lib/libswscale.so
dependencies/openal/alffplay: /usr/lib/libswresample.so
dependencies/openal/alffplay: /usr/lib/libz.so
dependencies/openal/alffplay: dependencies/openal/libal-excommon.a
dependencies/openal/alffplay: dependencies/openal/libopenal.so.1.23.1
dependencies/openal/alffplay: dependencies/openal/CMakeFiles/alffplay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable alffplay"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alffplay.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/openal/CMakeFiles/alffplay.dir/build: dependencies/openal/alffplay
.PHONY : dependencies/openal/CMakeFiles/alffplay.dir/build

dependencies/openal/CMakeFiles/alffplay.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -P CMakeFiles/alffplay.dir/cmake_clean.cmake
.PHONY : dependencies/openal/CMakeFiles/alffplay.dir/clean

dependencies/openal/CMakeFiles/alffplay.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal/CMakeFiles/alffplay.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/openal/CMakeFiles/alffplay.dir/depend

