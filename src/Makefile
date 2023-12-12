# GNU C++ Compiler
CPP = g++ # The C++ compiler to be used

# Compiler flags
# -g: Enables debugging information
# -O3: Enables compiler optimizations
# -std=c++11: Enables C++11 standard features
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

# Phony targets for make commands
.PHONY: all clean move_object

# Default target, builds the static library and moves it to LIBDIR
all: $(OBJECT)
	@echo "Creating static library $(LIBRARY)"
	ar rcs $(LIBRARY) $(OBJECT)
	@echo "Moving $(LIBRARY) to $(LIBDIR)"
	@mv $(LIBRARY) $(LIBDIR)/
	@echo "Cleaning up object file"
	@rm -f $(OBJECT)

# Rule for compiling cellular_automata.cpp to an object file
$(OBJECT): $(SOURCE) $(INCDIR)/CellularAutomata.h
	@echo "Compiling $(SOURCE) to object file"
	$(CPP) $(CPPFLAGS) -I$(INCDIR) -c $(SOURCE) -o $(OBJECT)

# Clean target to clean up the library file in LIBDIR
clean:
	@echo "Cleaning up library file in $(LIBDIR)"
	@rm -f $(LIBDIR)/$(LIBRARY)
