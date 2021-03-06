# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/johan/projects/ipStats

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/johan/projects/ipStats

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/johan/projects/ipStats/CMakeFiles /home/johan/projects/ipStats/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/johan/projects/ipStats/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ipstats

# Build rule for target.
ipstats: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ipstats
.PHONY : ipstats

# fast build rule for target.
ipstats/fast:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/build
.PHONY : ipstats/fast

#=============================================================================
# Target rules for targets named pingip

# Build rule for target.
pingip: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pingip
.PHONY : pingip

# fast build rule for target.
pingip/fast:
	$(MAKE) -f CMakeFiles/pingip.dir/build.make CMakeFiles/pingip.dir/build
.PHONY : pingip/fast

#=============================================================================
# Target rules for targets named runipstats

# Build rule for target.
runipstats: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 runipstats
.PHONY : runipstats

# fast build rule for target.
runipstats/fast:
	$(MAKE) -f CMakeFiles/runipstats.dir/build.make CMakeFiles/runipstats.dir/build
.PHONY : runipstats/fast

IpNeigh.o: IpNeigh.cpp.o
.PHONY : IpNeigh.o

# target to build an object file
IpNeigh.cpp.o:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/IpNeigh.cpp.o
.PHONY : IpNeigh.cpp.o

IpNeigh.i: IpNeigh.cpp.i
.PHONY : IpNeigh.i

# target to preprocess a source file
IpNeigh.cpp.i:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/IpNeigh.cpp.i
.PHONY : IpNeigh.cpp.i

IpNeigh.s: IpNeigh.cpp.s
.PHONY : IpNeigh.s

# target to generate assembly for a file
IpNeigh.cpp.s:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/IpNeigh.cpp.s
.PHONY : IpNeigh.cpp.s

NetReport.o: NetReport.cpp.o
.PHONY : NetReport.o

# target to build an object file
NetReport.cpp.o:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/NetReport.cpp.o
.PHONY : NetReport.cpp.o

NetReport.i: NetReport.cpp.i
.PHONY : NetReport.i

# target to preprocess a source file
NetReport.cpp.i:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/NetReport.cpp.i
.PHONY : NetReport.cpp.i

NetReport.s: NetReport.cpp.s
.PHONY : NetReport.s

# target to generate assembly for a file
NetReport.cpp.s:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/NetReport.cpp.s
.PHONY : NetReport.cpp.s

SendPing.o: SendPing.cpp.o
.PHONY : SendPing.o

# target to build an object file
SendPing.cpp.o:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/SendPing.cpp.o
	$(MAKE) -f CMakeFiles/pingip.dir/build.make CMakeFiles/pingip.dir/SendPing.cpp.o
.PHONY : SendPing.cpp.o

SendPing.i: SendPing.cpp.i
.PHONY : SendPing.i

# target to preprocess a source file
SendPing.cpp.i:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/SendPing.cpp.i
	$(MAKE) -f CMakeFiles/pingip.dir/build.make CMakeFiles/pingip.dir/SendPing.cpp.i
.PHONY : SendPing.cpp.i

SendPing.s: SendPing.cpp.s
.PHONY : SendPing.s

# target to generate assembly for a file
SendPing.cpp.s:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/SendPing.cpp.s
	$(MAKE) -f CMakeFiles/pingip.dir/build.make CMakeFiles/pingip.dir/SendPing.cpp.s
.PHONY : SendPing.cpp.s

dbConnect.o: dbConnect.c.o
.PHONY : dbConnect.o

# target to build an object file
dbConnect.c.o:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/dbConnect.c.o
.PHONY : dbConnect.c.o

dbConnect.i: dbConnect.c.i
.PHONY : dbConnect.i

# target to preprocess a source file
dbConnect.c.i:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/dbConnect.c.i
.PHONY : dbConnect.c.i

dbConnect.s: dbConnect.c.s
.PHONY : dbConnect.s

# target to generate assembly for a file
dbConnect.c.s:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/dbConnect.c.s
.PHONY : dbConnect.c.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/ipstats.dir/build.make CMakeFiles/ipstats.dir/main.cpp.s
.PHONY : main.cpp.s

pingip.o: pingip.cpp.o
.PHONY : pingip.o

# target to build an object file
pingip.cpp.o:
	$(MAKE) -f CMakeFiles/pingip.dir/build.make CMakeFiles/pingip.dir/pingip.cpp.o
.PHONY : pingip.cpp.o

pingip.i: pingip.cpp.i
.PHONY : pingip.i

# target to preprocess a source file
pingip.cpp.i:
	$(MAKE) -f CMakeFiles/pingip.dir/build.make CMakeFiles/pingip.dir/pingip.cpp.i
.PHONY : pingip.cpp.i

pingip.s: pingip.cpp.s
.PHONY : pingip.s

# target to generate assembly for a file
pingip.cpp.s:
	$(MAKE) -f CMakeFiles/pingip.dir/build.make CMakeFiles/pingip.dir/pingip.cpp.s
.PHONY : pingip.cpp.s

runipstats.o: runipstats.c.o
.PHONY : runipstats.o

# target to build an object file
runipstats.c.o:
	$(MAKE) -f CMakeFiles/runipstats.dir/build.make CMakeFiles/runipstats.dir/runipstats.c.o
.PHONY : runipstats.c.o

runipstats.i: runipstats.c.i
.PHONY : runipstats.i

# target to preprocess a source file
runipstats.c.i:
	$(MAKE) -f CMakeFiles/runipstats.dir/build.make CMakeFiles/runipstats.dir/runipstats.c.i
.PHONY : runipstats.c.i

runipstats.s: runipstats.c.s
.PHONY : runipstats.s

# target to generate assembly for a file
runipstats.c.s:
	$(MAKE) -f CMakeFiles/runipstats.dir/build.make CMakeFiles/runipstats.dir/runipstats.c.s
.PHONY : runipstats.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... ipstats"
	@echo "... pingip"
	@echo "... rebuild_cache"
	@echo "... runipstats"
	@echo "... IpNeigh.o"
	@echo "... IpNeigh.i"
	@echo "... IpNeigh.s"
	@echo "... NetReport.o"
	@echo "... NetReport.i"
	@echo "... NetReport.s"
	@echo "... SendPing.o"
	@echo "... SendPing.i"
	@echo "... SendPing.s"
	@echo "... dbConnect.o"
	@echo "... dbConnect.i"
	@echo "... dbConnect.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... pingip.o"
	@echo "... pingip.i"
	@echo "... pingip.s"
	@echo "... runipstats.o"
	@echo "... runipstats.i"
	@echo "... runipstats.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

