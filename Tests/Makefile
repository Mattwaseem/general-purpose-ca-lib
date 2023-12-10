# GNU C++ Compiler
CPP = g++ # C++ Compiler

# Compiler flags -g for debug, -O3 for optimized version, -std=c++11 to enable C++11 features
CPPFLAGS = -g -O3 -std=c++11

# Directories
INCDIR = ../Include
LIBDIR = ../Lib
BINDIR = ../Bin

# Executable name
EXECUTABLE = test_cellular_automata

# Source file for the executable
SOURCE = test_cellular_automata.cpp

# Input files
INPUT_FILES = ca2d_2.txt

# Phony targets for make commands
.PHONY: all clean copy_input

# Default target
all: $(EXECUTABLE) copy_input

# Rule for creating the test_cellular_automata executable
$(EXECUTABLE): $(SOURCE) $(INCDIR)/CellularAutomata.h
	$(CPP) $(CPPFLAGS) -o $(EXECUTABLE) $(SOURCE) -I$(INCDIR)
	mv $(EXECUTABLE) $(BINDIR)/

# Rule to copy input files to BINDIR
copy_input: $(addprefix $(BINDIR)/,$(INPUT_FILES))

$(BINDIR)/%: %
	@echo "Copying $< to $@"
	@cp $< $@

# Clean target to clean up the executable and input files in BINDIR
clean:
	cd $(BINDIR) && rm -f $(EXECUTABLE) $(INPUT_FILES)
