# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/gova/Repo/Web_Signage/Mayil/Client/thirdparty/assimp-4.1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gova/Repo/Web_Signage/Mayil/Client/thirdparty/assimp-4.1.0

# Utility rule file for NightlyConfigure.

# Include the progress variables for this target.
include test/CMakeFiles/NightlyConfigure.dir/progress.make

test/CMakeFiles/NightlyConfigure:
	cd /home/gova/Repo/Web_Signage/Mayil/Client/thirdparty/assimp-4.1.0/test && /usr/bin/ctest -D NightlyConfigure

NightlyConfigure: test/CMakeFiles/NightlyConfigure
NightlyConfigure: test/CMakeFiles/NightlyConfigure.dir/build.make

.PHONY : NightlyConfigure

# Rule to build all files generated by this target.
test/CMakeFiles/NightlyConfigure.dir/build: NightlyConfigure

.PHONY : test/CMakeFiles/NightlyConfigure.dir/build

test/CMakeFiles/NightlyConfigure.dir/clean:
	cd /home/gova/Repo/Web_Signage/Mayil/Client/thirdparty/assimp-4.1.0/test && $(CMAKE_COMMAND) -P CMakeFiles/NightlyConfigure.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/NightlyConfigure.dir/clean

test/CMakeFiles/NightlyConfigure.dir/depend:
	cd /home/gova/Repo/Web_Signage/Mayil/Client/thirdparty/assimp-4.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gova/Repo/Web_Signage/Mayil/Client/thirdparty/assimp-4.1.0 /home/gova/Repo/Web_Signage/Mayil/Client/thirdparty/assimp-4.1.0/test /home/gova/Repo/Web_Signage/Mayil/Client/thirdparty/assimp-4.1.0 /home/gova/Repo/Web_Signage/Mayil/Client/thirdparty/assimp-4.1.0/test /home/gova/Repo/Web_Signage/Mayil/Client/thirdparty/assimp-4.1.0/test/CMakeFiles/NightlyConfigure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/NightlyConfigure.dir/depend

