# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /Users/batuhanyigit/Documents/C++/OpenGL/particle-game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/particle_game.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/particle_game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/particle_game.dir/flags.make

CMakeFiles/particle_game.dir/main.cpp.o: CMakeFiles/particle_game.dir/flags.make
CMakeFiles/particle_game.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/particle_game.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_game.dir/main.cpp.o -c /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/main.cpp

CMakeFiles/particle_game.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_game.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/main.cpp > CMakeFiles/particle_game.dir/main.cpp.i

CMakeFiles/particle_game.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_game.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/main.cpp -o CMakeFiles/particle_game.dir/main.cpp.s

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.o: CMakeFiles/particle_game.dir/flags.make
CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.o: ../src/vendor/imgui/imgui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.o -c /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui.cpp

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui.cpp > CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.i

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui.cpp -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.s

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.o: CMakeFiles/particle_game.dir/flags.make
CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.o: ../src/vendor/imgui/imgui_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.o -c /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_demo.cpp

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_demo.cpp > CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.i

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_demo.cpp -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.s

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.o: CMakeFiles/particle_game.dir/flags.make
CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.o: ../src/vendor/imgui/imgui_draw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.o -c /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_draw.cpp

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_draw.cpp > CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.i

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_draw.cpp -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.s

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.o: CMakeFiles/particle_game.dir/flags.make
CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.o: ../src/vendor/imgui/imgui_impl_glfw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.o -c /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_impl_glfw.cpp

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_impl_glfw.cpp > CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.i

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_impl_glfw.cpp -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.s

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.o: CMakeFiles/particle_game.dir/flags.make
CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.o: ../src/vendor/imgui/imgui_impl_opengl3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.o -c /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_impl_opengl3.cpp

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_impl_opengl3.cpp > CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.i

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_impl_opengl3.cpp -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.s

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.o: CMakeFiles/particle_game.dir/flags.make
CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.o: ../src/vendor/imgui/imgui_tables.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.o -c /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_tables.cpp

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_tables.cpp > CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.i

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_tables.cpp -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.s

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.o: CMakeFiles/particle_game.dir/flags.make
CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.o: ../src/vendor/imgui/imgui_widgets.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.o -c /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_widgets.cpp

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_widgets.cpp > CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.i

CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/src/vendor/imgui/imgui_widgets.cpp -o CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.s

# Object files for target particle_game
particle_game_OBJECTS = \
"CMakeFiles/particle_game.dir/main.cpp.o" \
"CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.o" \
"CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.o" \
"CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.o" \
"CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.o" \
"CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.o" \
"CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.o"

# External object files for target particle_game
particle_game_EXTERNAL_OBJECTS =

particle_game: CMakeFiles/particle_game.dir/main.cpp.o
particle_game: CMakeFiles/particle_game.dir/src/vendor/imgui/imgui.cpp.o
particle_game: CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_demo.cpp.o
particle_game: CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_draw.cpp.o
particle_game: CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_glfw.cpp.o
particle_game: CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.o
particle_game: CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_tables.cpp.o
particle_game: CMakeFiles/particle_game.dir/src/vendor/imgui/imgui_widgets.cpp.o
particle_game: CMakeFiles/particle_game.dir/build.make
particle_game: /Library/Developer/CommandLineTools/SDKs/MacOSX11.3.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
particle_game: CMakeFiles/particle_game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable particle_game"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/particle_game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/particle_game.dir/build: particle_game
.PHONY : CMakeFiles/particle_game.dir/build

CMakeFiles/particle_game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/particle_game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/particle_game.dir/clean

CMakeFiles/particle_game.dir/depend:
	cd /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/batuhanyigit/Documents/C++/OpenGL/particle-game /Users/batuhanyigit/Documents/C++/OpenGL/particle-game /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug /Users/batuhanyigit/Documents/C++/OpenGL/particle-game/cmake-build-debug/CMakeFiles/particle_game.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/particle_game.dir/depend
