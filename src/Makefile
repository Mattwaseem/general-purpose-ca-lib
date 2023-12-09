# GNU C++ Compiler
CPP = g++ # C++ Compiler

# Compiler flags -g for debug, -O3 for optimized version, -std=c++11 to enable C++11 features
CPPFLAGS = -g -O3 -std=c++11

# Include directory (relative to the src directory)
INCDIR = ../Include

# Library directory (relative to the src directory)
LIBDIR = ../Lib

# Object file name
OBJECT = cellular_automata.o

# Source file
SOURCE = cellular_automata.cpp

# Phony targets for make commands
.PHONY: all clean move_object

# Default target
all: $(OBJECT) move_object

# Rule for compiling cellular_automata.cpp to an object file
$(OBJECT): $(SOURCE) $(INCDIR)/CellularAutomata.h
	$(CPP) $(CPPFLAGS) -I$(INCDIR) -c $(SOURCE) -o $(OBJECT)

# Move the object file to the library directory
move_object:
	-mv $(OBJECT) $(LIBDIR)/

# Clean target to clean up the object file
clean:
	-rm -f $(LIBDIR)/$(OBJECT)
