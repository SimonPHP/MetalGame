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
CMAKE_SOURCE_DIR = "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug"

# Include any dependencies generated for this target.
include /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/depend.make

# Include the progress variables for this target.
include /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/progress.make

# Include the compile flags for this target's objects.
include /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/flags.make

/home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/src/SDL.cpp.o: /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/flags.make
/home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/src/SDL.cpp.o: /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/src/SDL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object /home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/src/SDL.cpp.o"
	cd "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sdl_oo.dir/src/SDL.cpp.o -c "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/src/SDL.cpp"

/home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/src/SDL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdl_oo.dir/src/SDL.cpp.i"
	cd "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/src/SDL.cpp" > CMakeFiles/sdl_oo.dir/src/SDL.cpp.i

/home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/src/SDL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdl_oo.dir/src/SDL.cpp.s"
	cd "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/src/SDL.cpp" -o CMakeFiles/sdl_oo.dir/src/SDL.cpp.s

# Object files for target sdl_oo
sdl_oo_OBJECTS = \
"CMakeFiles/sdl_oo.dir/src/SDL.cpp.o"

# External object files for target sdl_oo
sdl_oo_EXTERNAL_OBJECTS =

/home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/libsdl_oo.a: /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/src/SDL.cpp.o
/home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/libsdl_oo.a: /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/build.make
/home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/libsdl_oo.a: /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsdl_oo.a"
	cd "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug" && $(CMAKE_COMMAND) -P CMakeFiles/sdl_oo.dir/cmake_clean_target.cmake
	cd "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sdl_oo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
/home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/build: /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/libsdl_oo.a

.PHONY : /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/build

/home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/clean:
	cd "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug" && $(CMAKE_COMMAND) -P CMakeFiles/sdl_oo.dir/cmake_clean.cmake
.PHONY : /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/clean

/home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/depend:
	cd "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game" "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo" "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug" "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug" "/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : /home/simon/Desktop/Uni\ sortiert/Semester_5/WPP/MetalGame/sdl_oo/cmake-build-debug/CMakeFiles/sdl_oo.dir/depend

