# GNU C++ Compiler
CPP = g++ # C++ Compiler

# Compiler flags -g for debug, -O3 for optimized version, -std=c++11 to enable C++11 features
CPPFLAGS = -g -O3 -std=c++11

# The directory where the include files needed to create the object files are
INC_DIR = ../../Include

# Bin directory where the executables will be stored
BIN_DIR = ../../Bin

# Object files containing sorting algorithms
Moore_OBJS = $(BIN_DIR)/moore.o
Vonn_OBJS = $(BIN_DIR)/vonn.o


# Rule for compiling bfs.cpp to an object file
$(BIN_DIR)/vonn.o: von_neumannCA.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<

# Rule for compiling bfs.cpp to an object file
$(BIN_DIR)/moore.o: moorsCA.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


# Rule to copy input files to BIN_DIR
$(BIN_DIR)/%: %
	@echo "Copying $< to $@"
	@cp $< $@

# Target for creating Moore Neighborhood executable
Moore: $(Moore_OBJS) $(addprefix $(BIN_DIR)/,$(INPUT_FILES))
	$(CPP) -O3 -o $(BIN_DIR)/$@ $(Moore_OBJS)

# Target for creating Vonn Neumann neighborhood executable
Vonn: $(Vonn_OBJS)
	$(CPP) -O3 -o $(BIN_DIR)/$@ $(Vonn_OBJS)

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
