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
include dependencies/openal/CMakeFiles/alcommon.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/openal/CMakeFiles/alcommon.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/openal/CMakeFiles/alcommon.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/openal/CMakeFiles/alcommon.dir/flags.make

dependencies/openal/CMakeFiles/alcommon.dir/common/alcomplex.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/flags.make
dependencies/openal/CMakeFiles/alcommon.dir/common/alcomplex.cpp.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alcomplex.cpp
dependencies/openal/CMakeFiles/alcommon.dir/common/alcomplex.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object dependencies/openal/CMakeFiles/alcommon.dir/common/alcomplex.cpp.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alcommon.dir/common/alcomplex.cpp.o -MF CMakeFiles/alcommon.dir/common/alcomplex.cpp.o.d -o CMakeFiles/alcommon.dir/common/alcomplex.cpp.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alcomplex.cpp

dependencies/openal/CMakeFiles/alcommon.dir/common/alcomplex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/alcommon.dir/common/alcomplex.cpp.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alcomplex.cpp > CMakeFiles/alcommon.dir/common/alcomplex.cpp.i

dependencies/openal/CMakeFiles/alcommon.dir/common/alcomplex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/alcommon.dir/common/alcomplex.cpp.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alcomplex.cpp -o CMakeFiles/alcommon.dir/common/alcomplex.cpp.s

dependencies/openal/CMakeFiles/alcommon.dir/common/alsem.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/flags.make
dependencies/openal/CMakeFiles/alcommon.dir/common/alsem.cpp.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alsem.cpp
dependencies/openal/CMakeFiles/alcommon.dir/common/alsem.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object dependencies/openal/CMakeFiles/alcommon.dir/common/alsem.cpp.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alcommon.dir/common/alsem.cpp.o -MF CMakeFiles/alcommon.dir/common/alsem.cpp.o.d -o CMakeFiles/alcommon.dir/common/alsem.cpp.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alsem.cpp

dependencies/openal/CMakeFiles/alcommon.dir/common/alsem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/alcommon.dir/common/alsem.cpp.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alsem.cpp > CMakeFiles/alcommon.dir/common/alsem.cpp.i

dependencies/openal/CMakeFiles/alcommon.dir/common/alsem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/alcommon.dir/common/alsem.cpp.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alsem.cpp -o CMakeFiles/alcommon.dir/common/alsem.cpp.s

dependencies/openal/CMakeFiles/alcommon.dir/common/alstring.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/flags.make
dependencies/openal/CMakeFiles/alcommon.dir/common/alstring.cpp.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alstring.cpp
dependencies/openal/CMakeFiles/alcommon.dir/common/alstring.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object dependencies/openal/CMakeFiles/alcommon.dir/common/alstring.cpp.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alcommon.dir/common/alstring.cpp.o -MF CMakeFiles/alcommon.dir/common/alstring.cpp.o.d -o CMakeFiles/alcommon.dir/common/alstring.cpp.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alstring.cpp

dependencies/openal/CMakeFiles/alcommon.dir/common/alstring.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/alcommon.dir/common/alstring.cpp.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alstring.cpp > CMakeFiles/alcommon.dir/common/alstring.cpp.i

dependencies/openal/CMakeFiles/alcommon.dir/common/alstring.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/alcommon.dir/common/alstring.cpp.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/alstring.cpp -o CMakeFiles/alcommon.dir/common/alstring.cpp.s

dependencies/openal/CMakeFiles/alcommon.dir/common/althrd_setname.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/flags.make
dependencies/openal/CMakeFiles/alcommon.dir/common/althrd_setname.cpp.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/althrd_setname.cpp
dependencies/openal/CMakeFiles/alcommon.dir/common/althrd_setname.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object dependencies/openal/CMakeFiles/alcommon.dir/common/althrd_setname.cpp.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alcommon.dir/common/althrd_setname.cpp.o -MF CMakeFiles/alcommon.dir/common/althrd_setname.cpp.o.d -o CMakeFiles/alcommon.dir/common/althrd_setname.cpp.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/althrd_setname.cpp

dependencies/openal/CMakeFiles/alcommon.dir/common/althrd_setname.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/alcommon.dir/common/althrd_setname.cpp.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/althrd_setname.cpp > CMakeFiles/alcommon.dir/common/althrd_setname.cpp.i

dependencies/openal/CMakeFiles/alcommon.dir/common/althrd_setname.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/alcommon.dir/common/althrd_setname.cpp.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/althrd_setname.cpp -o CMakeFiles/alcommon.dir/common/althrd_setname.cpp.s

dependencies/openal/CMakeFiles/alcommon.dir/common/dynload.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/flags.make
dependencies/openal/CMakeFiles/alcommon.dir/common/dynload.cpp.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/dynload.cpp
dependencies/openal/CMakeFiles/alcommon.dir/common/dynload.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object dependencies/openal/CMakeFiles/alcommon.dir/common/dynload.cpp.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alcommon.dir/common/dynload.cpp.o -MF CMakeFiles/alcommon.dir/common/dynload.cpp.o.d -o CMakeFiles/alcommon.dir/common/dynload.cpp.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/dynload.cpp

dependencies/openal/CMakeFiles/alcommon.dir/common/dynload.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/alcommon.dir/common/dynload.cpp.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/dynload.cpp > CMakeFiles/alcommon.dir/common/dynload.cpp.i

dependencies/openal/CMakeFiles/alcommon.dir/common/dynload.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/alcommon.dir/common/dynload.cpp.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/dynload.cpp -o CMakeFiles/alcommon.dir/common/dynload.cpp.s

dependencies/openal/CMakeFiles/alcommon.dir/common/pffft.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/flags.make
dependencies/openal/CMakeFiles/alcommon.dir/common/pffft.cpp.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/pffft.cpp
dependencies/openal/CMakeFiles/alcommon.dir/common/pffft.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object dependencies/openal/CMakeFiles/alcommon.dir/common/pffft.cpp.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alcommon.dir/common/pffft.cpp.o -MF CMakeFiles/alcommon.dir/common/pffft.cpp.o.d -o CMakeFiles/alcommon.dir/common/pffft.cpp.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/pffft.cpp

dependencies/openal/CMakeFiles/alcommon.dir/common/pffft.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/alcommon.dir/common/pffft.cpp.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/pffft.cpp > CMakeFiles/alcommon.dir/common/pffft.cpp.i

dependencies/openal/CMakeFiles/alcommon.dir/common/pffft.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/alcommon.dir/common/pffft.cpp.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/pffft.cpp -o CMakeFiles/alcommon.dir/common/pffft.cpp.s

dependencies/openal/CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/flags.make
dependencies/openal/CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/polyphase_resampler.cpp
dependencies/openal/CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object dependencies/openal/CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.o -MF CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.o.d -o CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/polyphase_resampler.cpp

dependencies/openal/CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/polyphase_resampler.cpp > CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.i

dependencies/openal/CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/polyphase_resampler.cpp -o CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.s

dependencies/openal/CMakeFiles/alcommon.dir/common/ringbuffer.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/flags.make
dependencies/openal/CMakeFiles/alcommon.dir/common/ringbuffer.cpp.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/ringbuffer.cpp
dependencies/openal/CMakeFiles/alcommon.dir/common/ringbuffer.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object dependencies/openal/CMakeFiles/alcommon.dir/common/ringbuffer.cpp.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alcommon.dir/common/ringbuffer.cpp.o -MF CMakeFiles/alcommon.dir/common/ringbuffer.cpp.o.d -o CMakeFiles/alcommon.dir/common/ringbuffer.cpp.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/ringbuffer.cpp

dependencies/openal/CMakeFiles/alcommon.dir/common/ringbuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/alcommon.dir/common/ringbuffer.cpp.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/ringbuffer.cpp > CMakeFiles/alcommon.dir/common/ringbuffer.cpp.i

dependencies/openal/CMakeFiles/alcommon.dir/common/ringbuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/alcommon.dir/common/ringbuffer.cpp.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/ringbuffer.cpp -o CMakeFiles/alcommon.dir/common/ringbuffer.cpp.s

dependencies/openal/CMakeFiles/alcommon.dir/common/strutils.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/flags.make
dependencies/openal/CMakeFiles/alcommon.dir/common/strutils.cpp.o: /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/strutils.cpp
dependencies/openal/CMakeFiles/alcommon.dir/common/strutils.cpp.o: dependencies/openal/CMakeFiles/alcommon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object dependencies/openal/CMakeFiles/alcommon.dir/common/strutils.cpp.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dependencies/openal/CMakeFiles/alcommon.dir/common/strutils.cpp.o -MF CMakeFiles/alcommon.dir/common/strutils.cpp.o.d -o CMakeFiles/alcommon.dir/common/strutils.cpp.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/strutils.cpp

dependencies/openal/CMakeFiles/alcommon.dir/common/strutils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/alcommon.dir/common/strutils.cpp.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/strutils.cpp > CMakeFiles/alcommon.dir/common/strutils.cpp.i

dependencies/openal/CMakeFiles/alcommon.dir/common/strutils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/alcommon.dir/common/strutils.cpp.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal/common/strutils.cpp -o CMakeFiles/alcommon.dir/common/strutils.cpp.s

# Object files for target alcommon
alcommon_OBJECTS = \
"CMakeFiles/alcommon.dir/common/alcomplex.cpp.o" \
"CMakeFiles/alcommon.dir/common/alsem.cpp.o" \
"CMakeFiles/alcommon.dir/common/alstring.cpp.o" \
"CMakeFiles/alcommon.dir/common/althrd_setname.cpp.o" \
"CMakeFiles/alcommon.dir/common/dynload.cpp.o" \
"CMakeFiles/alcommon.dir/common/pffft.cpp.o" \
"CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.o" \
"CMakeFiles/alcommon.dir/common/ringbuffer.cpp.o" \
"CMakeFiles/alcommon.dir/common/strutils.cpp.o"

# External object files for target alcommon
alcommon_EXTERNAL_OBJECTS =

dependencies/openal/libalcommon.a: dependencies/openal/CMakeFiles/alcommon.dir/common/alcomplex.cpp.o
dependencies/openal/libalcommon.a: dependencies/openal/CMakeFiles/alcommon.dir/common/alsem.cpp.o
dependencies/openal/libalcommon.a: dependencies/openal/CMakeFiles/alcommon.dir/common/alstring.cpp.o
dependencies/openal/libalcommon.a: dependencies/openal/CMakeFiles/alcommon.dir/common/althrd_setname.cpp.o
dependencies/openal/libalcommon.a: dependencies/openal/CMakeFiles/alcommon.dir/common/dynload.cpp.o
dependencies/openal/libalcommon.a: dependencies/openal/CMakeFiles/alcommon.dir/common/pffft.cpp.o
dependencies/openal/libalcommon.a: dependencies/openal/CMakeFiles/alcommon.dir/common/polyphase_resampler.cpp.o
dependencies/openal/libalcommon.a: dependencies/openal/CMakeFiles/alcommon.dir/common/ringbuffer.cpp.o
dependencies/openal/libalcommon.a: dependencies/openal/CMakeFiles/alcommon.dir/common/strutils.cpp.o
dependencies/openal/libalcommon.a: dependencies/openal/CMakeFiles/alcommon.dir/build.make
dependencies/openal/libalcommon.a: dependencies/openal/CMakeFiles/alcommon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libalcommon.a"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -P CMakeFiles/alcommon.dir/cmake_clean_target.cmake
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alcommon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/openal/CMakeFiles/alcommon.dir/build: dependencies/openal/libalcommon.a
.PHONY : dependencies/openal/CMakeFiles/alcommon.dir/build

dependencies/openal/CMakeFiles/alcommon.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -P CMakeFiles/alcommon.dir/cmake_clean.cmake
.PHONY : dependencies/openal/CMakeFiles/alcommon.dir/clean

dependencies/openal/CMakeFiles/alcommon.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine/Cmake/build/dependencies/openal/CMakeFiles/alcommon.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/openal/CMakeFiles/alcommon.dir/depend

