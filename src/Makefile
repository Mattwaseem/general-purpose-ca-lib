# GNU C++ Compiler
CPP = g++ # The C++ compiler to be used

# Compiler flags
CPPFLAGS = -g -O3 -std=c++11

# Include directory (relative to the src directory)
INCDIR = ../include

# Library directory (relative to the src directory)
LIBDIR = ../Lib

# Object file name
OBJECT = cellular_automata.o

# Source file
SOURCE = cellular_automata.cpp

# Static library name
LIBRARY = mylibca.a

.PHONY: all clean move_object

all: $(OBJECT)
	@echo "Creating static library $(LIBRARY)"
	ar rcs $(LIBRARY) $(OBJECT)
	@echo "Static library $(LIBRARY) created."
	@echo "Moving $(LIBRARY) to $(LIBDIR)"
	@mv $(LIBRARY) $(LIBDIR)/
	@echo "$(LIBRARY) moved to $(LIBDIR)"
	@echo "Current directory: `pwd`"
	@echo "Contents of $(LIBDIR):"
	@ls $(LIBDIR)
	@echo "Cleaning up object file $(OBJECT)"
	@rm -f $(OBJECT)

$(OBJECT): $(SOURCE) $(INCDIR)/CellularAutomata.h
	@echo "Compiling $(SOURCE) to object file"
	$(CPP) $(CPPFLAGS) -I$(INCDIR) -c $(SOURCE) -o $(OBJECT)
	@echo "$(SOURCE) compiled to $(OBJECT)"
	@echo "Contents of current directory:"
	@ls

clean:
	@echo "Cleaning up library file in $(LIBDIR)"
	@rm -f $(LIBDIR)/$(LIBRARY)
	@echo "Library file in $(LIBDIR) cleaned."
