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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.30.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.30.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/donnie/BuildingQTGUI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/donnie/BuildingQTGUI/build

# Utility rule file for BuildingQTGUI_autogen_timestamp_deps.

# Include any custom commands dependencies for this target.
include CMakeFiles/BuildingQTGUI_autogen_timestamp_deps.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BuildingQTGUI_autogen_timestamp_deps.dir/progress.make

BuildingQTGUI_autogen_timestamp_deps: CMakeFiles/BuildingQTGUI_autogen_timestamp_deps.dir/build.make
.PHONY : BuildingQTGUI_autogen_timestamp_deps

# Rule to build all files generated by this target.
CMakeFiles/BuildingQTGUI_autogen_timestamp_deps.dir/build: BuildingQTGUI_autogen_timestamp_deps
.PHONY : CMakeFiles/BuildingQTGUI_autogen_timestamp_deps.dir/build

CMakeFiles/BuildingQTGUI_autogen_timestamp_deps.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BuildingQTGUI_autogen_timestamp_deps.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BuildingQTGUI_autogen_timestamp_deps.dir/clean

CMakeFiles/BuildingQTGUI_autogen_timestamp_deps.dir/depend:
	cd /Users/donnie/BuildingQTGUI/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/donnie/BuildingQTGUI /Users/donnie/BuildingQTGUI /Users/donnie/BuildingQTGUI/build /Users/donnie/BuildingQTGUI/build /Users/donnie/BuildingQTGUI/build/CMakeFiles/BuildingQTGUI_autogen_timestamp_deps.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/BuildingQTGUI_autogen_timestamp_deps.dir/depend

