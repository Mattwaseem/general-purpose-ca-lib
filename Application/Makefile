# GNU C++ Compiler
CPP = g++ # The C++ compiler to be used

# Compiler flags
# -g: Enables debugging information
# -O3: Enables compiler optimizations
# -std=c++11: Enables C++11 standard features
CPPFLAGS = -g -O3 -std=c++11

# Directories
INCDIR = ../include
LIBDIR = ../Lib
BINDIR = ../Bin


# Executable name
EXECUTABLE = neuron2neuron

# Source file
SOURCE = neuron2neuron.cpp

LDFLAGS = -L$(LIBDIR)

.PHONY: all clean run

all: $(BINDIR)/$(EXECUTABLE)

$(BINDIR)/$(EXECUTABLE): $(SOURCE)
	@echo "Compiling $(SOURCE)"
	$(CPP) $(CPPFLAGS) -o $(EXECUTABLE) $(SOURCE) -I$(INCDIR) $(LDFLAGS)
	@echo "Moving executable to $(BINDIR)"
	@mv $(EXECUTABLE) $(BINDIR)

run:
	@echo "Running $(EXECUTABLE)"
	@$(BINDIR)/$(EXECUTABLE)
	@echo "Execution finished"

clean:
	@echo "Cleaning up"
	@rm -f $(BINDIR)/$(EXECUTABLE)
