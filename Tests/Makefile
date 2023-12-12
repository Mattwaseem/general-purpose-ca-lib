# GNU C++ Compiler
CPP = g++ 
CPPFLAGS = -g -O3 -std=c++11

# Directories
INCDIR = ../include
LIBDIR = ../Lib
BINDIR = ../Bin
DATADIR = ../Utils/Data
TESTDIR = ../Tests

# Executable name
EXECUTABLE = test_cellular_automata

# Source file
SOURCE = test_cellular_automata.cpp

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
	@echo "Moving .txt files to $(DATADIR)"
	@mv *.txt $(DATADIR)
	@echo "Execution finished"

clean:
	@echo "Cleaning up"
	@rm -f $(BINDIR)/$(EXECUTABLE) $(DATADIR)/*.txt $(TESTDIR)/*.txt
