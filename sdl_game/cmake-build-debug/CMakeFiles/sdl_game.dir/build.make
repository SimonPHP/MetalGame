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
CMAKE_COMMAND = /home/simon/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4892.24/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/simon/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4892.24/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/sdl_game.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sdl_game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sdl_game.dir/flags.make

CMakeFiles/sdl_game.dir/src/main.cpp.o: CMakeFiles/sdl_game.dir/flags.make
CMakeFiles/sdl_game.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sdl_game.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sdl_game.dir/src/main.cpp.o -c "/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/src/main.cpp"

CMakeFiles/sdl_game.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdl_game.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/src/main.cpp" > CMakeFiles/sdl_game.dir/src/main.cpp.i

CMakeFiles/sdl_game.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdl_game.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/src/main.cpp" -o CMakeFiles/sdl_game.dir/src/main.cpp.s

# Object files for target sdl_game
sdl_game_OBJECTS = \
"CMakeFiles/sdl_game.dir/src/main.cpp.o"

# External object files for target sdl_game
sdl_game_EXTERNAL_OBJECTS =

sdl_game: CMakeFiles/sdl_game.dir/src/main.cpp.o
sdl_game: CMakeFiles/sdl_game.dir/build.make
sdl_game: CMakeFiles/sdl_game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sdl_game"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sdl_game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sdl_game.dir/build: sdl_game

.PHONY : CMakeFiles/sdl_game.dir/build

CMakeFiles/sdl_game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sdl_game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sdl_game.dir/clean

CMakeFiles/sdl_game.dir/depend:
	cd "/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game" "/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game" "/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug" "/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug" "/home/simon/Schreibtisch/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug/CMakeFiles/sdl_game.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/sdl_game.dir/depend

