# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build

# Include any dependencies generated for this target.
include pattern/CMakeFiles/test_pattern.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include pattern/CMakeFiles/test_pattern.dir/compiler_depend.make

# Include the progress variables for this target.
include pattern/CMakeFiles/test_pattern.dir/progress.make

# Include the compile flags for this target's objects.
include pattern/CMakeFiles/test_pattern.dir/flags.make

pattern/CMakeFiles/test_pattern.dir/test_pattern.cpp.o: pattern/CMakeFiles/test_pattern.dir/flags.make
pattern/CMakeFiles/test_pattern.dir/test_pattern.cpp.o: /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/pattern/test_pattern.cpp
pattern/CMakeFiles/test_pattern.dir/test_pattern.cpp.o: pattern/CMakeFiles/test_pattern.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object pattern/CMakeFiles/test_pattern.dir/test_pattern.cpp.o"
	cd /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/pattern && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT pattern/CMakeFiles/test_pattern.dir/test_pattern.cpp.o -MF CMakeFiles/test_pattern.dir/test_pattern.cpp.o.d -o CMakeFiles/test_pattern.dir/test_pattern.cpp.o -c /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/pattern/test_pattern.cpp

pattern/CMakeFiles/test_pattern.dir/test_pattern.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_pattern.dir/test_pattern.cpp.i"
	cd /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/pattern && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/pattern/test_pattern.cpp > CMakeFiles/test_pattern.dir/test_pattern.cpp.i

pattern/CMakeFiles/test_pattern.dir/test_pattern.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_pattern.dir/test_pattern.cpp.s"
	cd /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/pattern && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/pattern/test_pattern.cpp -o CMakeFiles/test_pattern.dir/test_pattern.cpp.s

pattern/CMakeFiles/test_pattern.dir/pattern.cpp.o: pattern/CMakeFiles/test_pattern.dir/flags.make
pattern/CMakeFiles/test_pattern.dir/pattern.cpp.o: /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/pattern/pattern.cpp
pattern/CMakeFiles/test_pattern.dir/pattern.cpp.o: pattern/CMakeFiles/test_pattern.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object pattern/CMakeFiles/test_pattern.dir/pattern.cpp.o"
	cd /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/pattern && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT pattern/CMakeFiles/test_pattern.dir/pattern.cpp.o -MF CMakeFiles/test_pattern.dir/pattern.cpp.o.d -o CMakeFiles/test_pattern.dir/pattern.cpp.o -c /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/pattern/pattern.cpp

pattern/CMakeFiles/test_pattern.dir/pattern.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_pattern.dir/pattern.cpp.i"
	cd /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/pattern && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/pattern/pattern.cpp > CMakeFiles/test_pattern.dir/pattern.cpp.i

pattern/CMakeFiles/test_pattern.dir/pattern.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_pattern.dir/pattern.cpp.s"
	cd /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/pattern && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/pattern/pattern.cpp -o CMakeFiles/test_pattern.dir/pattern.cpp.s

# Object files for target test_pattern
test_pattern_OBJECTS = \
"CMakeFiles/test_pattern.dir/test_pattern.cpp.o" \
"CMakeFiles/test_pattern.dir/pattern.cpp.o"

# External object files for target test_pattern
test_pattern_EXTERNAL_OBJECTS =

pattern/test_pattern: pattern/CMakeFiles/test_pattern.dir/test_pattern.cpp.o
pattern/test_pattern: pattern/CMakeFiles/test_pattern.dir/pattern.cpp.o
pattern/test_pattern: pattern/CMakeFiles/test_pattern.dir/build.make
pattern/test_pattern: pattern/CMakeFiles/test_pattern.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_pattern"
	cd /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/pattern && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_pattern.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
pattern/CMakeFiles/test_pattern.dir/build: pattern/test_pattern
.PHONY : pattern/CMakeFiles/test_pattern.dir/build

pattern/CMakeFiles/test_pattern.dir/clean:
	cd /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/pattern && $(CMAKE_COMMAND) -P CMakeFiles/test_pattern.dir/cmake_clean.cmake
.PHONY : pattern/CMakeFiles/test_pattern.dir/clean

pattern/CMakeFiles/test_pattern.dir/depend:
	cd /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/pattern /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/pattern /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P2kdtree/build/pattern/CMakeFiles/test_pattern.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : pattern/CMakeFiles/test_pattern.dir/depend

