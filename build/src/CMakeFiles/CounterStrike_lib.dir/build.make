# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/oem/Taller/TPfinal/CounterStrike

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oem/Taller/TPfinal/CounterStrike/build

# Include any dependencies generated for this target.
include src/CMakeFiles/CounterStrike_lib.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/CounterStrike_lib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/CounterStrike_lib.dir/flags.make

src/CMakeFiles/CounterStrike_lib.dir/main.cpp.o: src/CMakeFiles/CounterStrike_lib.dir/flags.make
src/CMakeFiles/CounterStrike_lib.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oem/Taller/TPfinal/CounterStrike/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/CounterStrike_lib.dir/main.cpp.o"
	cd /home/oem/Taller/TPfinal/CounterStrike/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CounterStrike_lib.dir/main.cpp.o -c /home/oem/Taller/TPfinal/CounterStrike/src/main.cpp

src/CMakeFiles/CounterStrike_lib.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CounterStrike_lib.dir/main.cpp.i"
	cd /home/oem/Taller/TPfinal/CounterStrike/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oem/Taller/TPfinal/CounterStrike/src/main.cpp > CMakeFiles/CounterStrike_lib.dir/main.cpp.i

src/CMakeFiles/CounterStrike_lib.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CounterStrike_lib.dir/main.cpp.s"
	cd /home/oem/Taller/TPfinal/CounterStrike/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oem/Taller/TPfinal/CounterStrike/src/main.cpp -o CMakeFiles/CounterStrike_lib.dir/main.cpp.s

src/CMakeFiles/CounterStrike_lib.dir/prueba.cpp.o: src/CMakeFiles/CounterStrike_lib.dir/flags.make
src/CMakeFiles/CounterStrike_lib.dir/prueba.cpp.o: ../src/prueba.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oem/Taller/TPfinal/CounterStrike/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/CounterStrike_lib.dir/prueba.cpp.o"
	cd /home/oem/Taller/TPfinal/CounterStrike/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CounterStrike_lib.dir/prueba.cpp.o -c /home/oem/Taller/TPfinal/CounterStrike/src/prueba.cpp

src/CMakeFiles/CounterStrike_lib.dir/prueba.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CounterStrike_lib.dir/prueba.cpp.i"
	cd /home/oem/Taller/TPfinal/CounterStrike/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oem/Taller/TPfinal/CounterStrike/src/prueba.cpp > CMakeFiles/CounterStrike_lib.dir/prueba.cpp.i

src/CMakeFiles/CounterStrike_lib.dir/prueba.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CounterStrike_lib.dir/prueba.cpp.s"
	cd /home/oem/Taller/TPfinal/CounterStrike/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oem/Taller/TPfinal/CounterStrike/src/prueba.cpp -o CMakeFiles/CounterStrike_lib.dir/prueba.cpp.s

# Object files for target CounterStrike_lib
CounterStrike_lib_OBJECTS = \
"CMakeFiles/CounterStrike_lib.dir/main.cpp.o" \
"CMakeFiles/CounterStrike_lib.dir/prueba.cpp.o"

# External object files for target CounterStrike_lib
CounterStrike_lib_EXTERNAL_OBJECTS =

src/libCounterStrike_lib.a: src/CMakeFiles/CounterStrike_lib.dir/main.cpp.o
src/libCounterStrike_lib.a: src/CMakeFiles/CounterStrike_lib.dir/prueba.cpp.o
src/libCounterStrike_lib.a: src/CMakeFiles/CounterStrike_lib.dir/build.make
src/libCounterStrike_lib.a: src/CMakeFiles/CounterStrike_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oem/Taller/TPfinal/CounterStrike/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libCounterStrike_lib.a"
	cd /home/oem/Taller/TPfinal/CounterStrike/build/src && $(CMAKE_COMMAND) -P CMakeFiles/CounterStrike_lib.dir/cmake_clean_target.cmake
	cd /home/oem/Taller/TPfinal/CounterStrike/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CounterStrike_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/CounterStrike_lib.dir/build: src/libCounterStrike_lib.a

.PHONY : src/CMakeFiles/CounterStrike_lib.dir/build

src/CMakeFiles/CounterStrike_lib.dir/clean:
	cd /home/oem/Taller/TPfinal/CounterStrike/build/src && $(CMAKE_COMMAND) -P CMakeFiles/CounterStrike_lib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/CounterStrike_lib.dir/clean

src/CMakeFiles/CounterStrike_lib.dir/depend:
	cd /home/oem/Taller/TPfinal/CounterStrike/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oem/Taller/TPfinal/CounterStrike /home/oem/Taller/TPfinal/CounterStrike/src /home/oem/Taller/TPfinal/CounterStrike/build /home/oem/Taller/TPfinal/CounterStrike/build/src /home/oem/Taller/TPfinal/CounterStrike/build/src/CMakeFiles/CounterStrike_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/CounterStrike_lib.dir/depend

