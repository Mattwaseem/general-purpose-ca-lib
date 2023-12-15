# GNU C++ Compiler
CPP = g++ # The C++ compiler to be used

# Compiler flags
CPPFLAGS = -g -O3 -std=c++11

# Directories
INCDIR = ../Include
SRCDIR = ../src
BINDIR = ../Bin

# Executable name
EXECUTABLE = neuron2neuron

# Source files
SOURCE = neuron2neuron.cpp $(SRCDIR)/cellular_automata.cpp

.PHONY: all clean run

all: $(BINDIR)/$(EXECUTABLE)

$(BINDIR)/$(EXECUTABLE): $(SOURCE)
	@echo "Compiling $(SOURCE)"
	$(CPP) $(CPPFLAGS) -o $(EXECUTABLE) $(SOURCE) -I$(INCDIR)
	@echo "Moving executable to $(BINDIR)"
	@mv $(EXECUTABLE) $(BINDIR)

run:
	@echo "Running $(EXECUTABLE)"
	@$(BINDIR)/$(EXECUTABLE)
	@echo "Execution finished"

clean:
	@echo "Cleaning up"
	@rm -f $(BINDIR)/$(EXECUTABLE)
