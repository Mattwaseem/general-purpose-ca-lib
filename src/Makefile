# GNU C++ Compiler
CPP = g++ # C++ Compiler

# Compiler flags -g for debug, -O3 for optimized version, -std=c++11 to enable C++11 features
CPPFLAGS = -g -O3 -std=c++11

# Name of the executable
EXECUTABLE = cellautvec

# Source file
SOURCE = cellautvec.cpp

# Phony targets for make commands
.PHONY: all clean

# Default target
all: $(EXECUTABLE)

# Rule for compiling cellautvec.cpp to an executable
$(EXECUTABLE): $(SOURCE)
	$(CPP) $(CPPFLAGS) -o $@ $<

# Clean target to clean up the executable
clean:
	rm -f $(EXECUTABLE)
