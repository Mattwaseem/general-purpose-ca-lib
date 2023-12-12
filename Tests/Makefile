# GNU C++ Compiler
CPP = g++ # The C++ compiler to be used

# Compiler flags
# -g: Enables debugging information
# -O3: Enables compiler optimizations
# -std=c++11: Enables C++11 standard features
CPPFLAGS = -g -O3 -std=c++11

# Directories
INCDIR = ../include # Directory for header files
LIBDIR = ../Lib     # Directory for library files
BINDIR = ../Bin     # Directory for binary/executable files

# Executable name
EXECUTABLE = test_cellular_automata

# Source file for the executable
SOURCE = test_cellular_automata.cpp

# Linker flags
# -L: Specifies the path to the library directory
LDFLAGS = -L$(LIBDIR)

# Phony targets for make commands
.PHONY: all clean run

# Default target, builds the executable and copies it to BINDIR
all: $(BINDIR)/$(EXECUTABLE)

# Rule for creating the test_cellular_automata executable and moving it to BINDIR
$(BINDIR)/$(EXECUTABLE): $(SOURCE)
	@echo "Compiling $(SOURCE) and moving executable to $(BINDIR)"
	$(CPP) $(CPPFLAGS) -o $(EXECUTABLE) $(SOURCE) -I$(INCDIR) $(LDFLAGS)
	@echo "Moving executable to $(BINDIR)"
	@mv $(EXECUTABLE) $(BINDIR)


# Rule to run all executables in the BINDIR
run:
	@echo "Running executable $(EXECUTABLE) in $(BINDIR)"
	@$(BINDIR)/$(EXECUTABLE)
	@echo "Execution finished"
# Clean target to clean up the executable in BINDIR
clean:
	@echo "Cleaning up $(BINDIR)"
	@cd $(BINDIR) && rm -f $(EXECUTABLE) *.txt
