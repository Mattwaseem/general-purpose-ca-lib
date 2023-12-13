#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
#include "../Include/CellularAutomata.h"
#include "../src/cellular_automata.cpp"

using namespace std;

// State definition:
// Each cell, representing a neuron, has two states: Active (1) or Inactive (0).
const int INACTIVE = 0;
const int ACTIVE = 1;
const int THRESHOLD = 2;

// The function below will initialize a 2D grid with Moor's neighborhood using the CA library for the neuron to neuron CA
void initNueronGrid(CellularAutomata::Grid2D &grid) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    for (auto &row : grid) {
        for (auto &cell : row) {
            cell = dis(gen);
        }
    }
}

// This function applies the firing rule for a neuron.
// The applyFiringRule updates the state of each neuron based on the sum of the states of its neighbors and the threshold.
int applyFiringRule(int currentState, int sumOfNeighbors) {
    return (sumOfNeighbors >= THRESHOLD) ? ACTIVE : INACTIVE;
}

// Type definition for synaptic weights
using SynapticWeights = vector<vector<double>>;

// Function to initialize synaptic weights
void initializeSynapticWeights(SynapticWeights &weights, int size) {
    weights.resize(size, vector<double>(size, 1.0)); // Initial weight can be 1.0
    // More complex initializations can be added here if needed
}

// Function to retrieve the grid state from a CellularAutomata object
CellularAutomata::Grid2D getGridState(const CellularAutomata &ca) {
    // Use the public member function getGrid2D() to retrieve the grid state
    return ca.getGrid2D();
}

// Function to update synaptic weights based on the grid state
void updateSynapticWeights(SynapticWeights &weights, const CellularAutomata::Grid2D &grid) {
    // Example logic: Increase weight if both neurons are active
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            // Update weights based on the activity of neuron and its neighbors
            // This is a simplified example. You will need a more complex logic based on your model's requirements
            if (grid[i][j] == ACTIVE) {
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (di == 0 && dj == 0) continue;
                        int ni = (i + di + grid.size()) % grid.size();
                        int nj = (j + dj + grid[i].size()) % grid[i].size();
                        if (grid[ni][nj] == ACTIVE) {
                            weights[i][j] += 0.1; // Increase weight
                        }
                    }
                }
            }
        }
    }
}

// Function to apply decay and threshold to synaptic weights
void applyDecayAndThreshold(SynapticWeights &weights, double decayRate, double ltpThreshold) {
    for (auto &row : weights) {
        for (auto &weight : row) {
            weight -= decayRate;            // Apply decay
            weight = max(weight, 0.0);      // Ensure weight does not go below 0
            if (weight > ltpThreshold) {
                weight = ltpThreshold;       // Apply threshold
            }
        }
    }
}

// Weighted firing rule based on synaptic weights
int weightedFiringRule(int currentState, int sumOfNeighbors, double synapticWeight) {
    // Apply the firing rule based on the sum of neighbors, threshold, and synaptic weight
    return (sumOfNeighbors * synapticWeight >= THRESHOLD) ? ACTIVE : INACTIVE;
}

// Main function
int main() {
int grid_size = 10;

    BoundaryCondition chosenBoundaryCondition = BoundaryCondition::Periodic; // or BoundaryCondition::Periodic or BoundaryCondition::NoBoundary
    CellularAutomata ca(grid_size, GridDimension::TwoD, chosenBoundaryCondition, NeighborhoodType::Moore);
    SynapticWeights weights;

    ca.Initialize2D(initNueronGrid);  // Initialize the grid
    initializeSynapticWeights(weights, grid_size);  // Initialize synaptic weights

    // Open a file stream to output the grid states
    ofstream outputFile("../Utils/Plots/neuron2neuron_output.txt");

    // Simulation loop
 for (int step = 0; step < 100; ++step) {
        // Update the grid state based on a cellular automata rule
        ca.ApplyRule2D(majorityRule); // Replace 'majorityRule' with 'totalisticRule' or 'parityRule' as needed

        // Apply changes to the grid based on the current state and synaptic weights
        // This is where you should add logic to update the grid state
        // Example: ca.UpdateGridState(weights); (This is a placeholder for your grid update logic)

        // Retrieve the updated grid state
  CellularAutomata::Grid2D gridState = ca.getGrid2D();

        updateSynapticWeights(weights, gridState);
        applyDecayAndThreshold(weights, 0.05, 5.0);

        outputFile << "Grid state after step " << step << ":\n";
        for (const auto &row : gridState) {
            for (const auto &cell : row) {
                outputFile << cell << " ";
            }
            outputFile << "\n";
        }
        outputFile << "\n";
    }

    outputFile.close();
    return 0;
}