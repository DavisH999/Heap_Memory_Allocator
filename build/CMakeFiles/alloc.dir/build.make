# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/cmpt201/units/long_assignments/a10-DavisH999

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cmpt201/units/long_assignments/a10-DavisH999/build

# Include any dependencies generated for this target.
include CMakeFiles/alloc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/alloc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/alloc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/alloc.dir/flags.make

CMakeFiles/alloc.dir/src/main.c.o: CMakeFiles/alloc.dir/flags.make
CMakeFiles/alloc.dir/src/main.c.o: ../src/main.c
CMakeFiles/alloc.dir/src/main.c.o: CMakeFiles/alloc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cmpt201/units/long_assignments/a10-DavisH999/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/alloc.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/alloc.dir/src/main.c.o -MF CMakeFiles/alloc.dir/src/main.c.o.d -o CMakeFiles/alloc.dir/src/main.c.o -c /home/cmpt201/units/long_assignments/a10-DavisH999/src/main.c

CMakeFiles/alloc.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alloc.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cmpt201/units/long_assignments/a10-DavisH999/src/main.c > CMakeFiles/alloc.dir/src/main.c.i

CMakeFiles/alloc.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alloc.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cmpt201/units/long_assignments/a10-DavisH999/src/main.c -o CMakeFiles/alloc.dir/src/main.c.s

CMakeFiles/alloc.dir/src/alloc.c.o: CMakeFiles/alloc.dir/flags.make
CMakeFiles/alloc.dir/src/alloc.c.o: ../src/alloc.c
CMakeFiles/alloc.dir/src/alloc.c.o: CMakeFiles/alloc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cmpt201/units/long_assignments/a10-DavisH999/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/alloc.dir/src/alloc.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/alloc.dir/src/alloc.c.o -MF CMakeFiles/alloc.dir/src/alloc.c.o.d -o CMakeFiles/alloc.dir/src/alloc.c.o -c /home/cmpt201/units/long_assignments/a10-DavisH999/src/alloc.c

CMakeFiles/alloc.dir/src/alloc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alloc.dir/src/alloc.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cmpt201/units/long_assignments/a10-DavisH999/src/alloc.c > CMakeFiles/alloc.dir/src/alloc.c.i

CMakeFiles/alloc.dir/src/alloc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alloc.dir/src/alloc.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cmpt201/units/long_assignments/a10-DavisH999/src/alloc.c -o CMakeFiles/alloc.dir/src/alloc.c.s

# Object files for target alloc
alloc_OBJECTS = \
"CMakeFiles/alloc.dir/src/main.c.o" \
"CMakeFiles/alloc.dir/src/alloc.c.o"

# External object files for target alloc
alloc_EXTERNAL_OBJECTS =

alloc: CMakeFiles/alloc.dir/src/main.c.o
alloc: CMakeFiles/alloc.dir/src/alloc.c.o
alloc: CMakeFiles/alloc.dir/build.make
alloc: CMakeFiles/alloc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cmpt201/units/long_assignments/a10-DavisH999/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable alloc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alloc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/alloc.dir/build: alloc
.PHONY : CMakeFiles/alloc.dir/build

CMakeFiles/alloc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/alloc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/alloc.dir/clean

CMakeFiles/alloc.dir/depend:
	cd /home/cmpt201/units/long_assignments/a10-DavisH999/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cmpt201/units/long_assignments/a10-DavisH999 /home/cmpt201/units/long_assignments/a10-DavisH999 /home/cmpt201/units/long_assignments/a10-DavisH999/build /home/cmpt201/units/long_assignments/a10-DavisH999/build /home/cmpt201/units/long_assignments/a10-DavisH999/build/CMakeFiles/alloc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/alloc.dir/depend
