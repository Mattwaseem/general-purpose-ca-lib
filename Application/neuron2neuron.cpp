// Includes standard input/output stream libraries, vector, random, and algorithm functionalities
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
// Includes the CellularAutomata header from the 'Include' directory
#include "../Include/CellularAutomata.h"

using namespace std;

// Function to initialize the neuron grid with random values
void initNeuronGrid(CellularAutomata::Grid2D &grid, mt19937 &gen) {
    uniform_int_distribution<> dis(0, 100); // Uniform distribution for random numbers between 0 and 100

    // Iterate through each row and cell of the grid
    for (auto &row : grid) {
        for (auto &cell : row) {
            int randVal = dis(gen); // Generate a random value
            // Assign cell state based on random value thresholds
            if (randVal < 70) cell = CellularAutomata::INACTIVE;
            else if (randVal < 80) cell = CellularAutomata::ACTIVE_1;
            else if (randVal < 90) cell = CellularAutomata::ACTIVE_2;
            else cell = CellularAutomata::ACTIVE_3;
        }
    }
}

// Function to add random activity in the grid
void addRandomActivity(CellularAutomata::Grid2D &grid, mt19937 &gen, int activityRate) {
    uniform_int_distribution<> dis(0, 100); // Distribution for random activity decision
    uniform_int_distribution<> stateDis(1, 3); // Random state between ACTIVE_1 and ACTIVE_3

    // Iterate through each cell and randomly activate some based on the activity rate
    for (auto &row : grid) {
        for (auto &cell : row) {
            if (dis(gen) < activityRate) {
                cell = stateDis(gen);
            }
        }
    }
}

// Function to apply weighted firing rules based on current state, active neighbors, and randomness
int weightedFiringRule(int currentState, int activeNeighborCount, mt19937 &gen, int step) {
    uniform_int_distribution<> randomChoice(0, 1); // Binary random choice

    // Switch statement for different cell states
    switch (currentState) {
        case CellularAutomata::ACTIVE_1:
            // Randomness added to the majority rule
            if (randomChoice(gen)) {
                return CellularAutomata::MajorityRule(activeNeighborCount);
            }
            break;
        case CellularAutomata::ACTIVE_2:
            // Randomness and periodic change added to the totalistic rule
            if (randomChoice(gen) || step % 5 == 0) {
                return CellularAutomata::TotalisticRule(activeNeighborCount);
            }
            break;
        case CellularAutomata::ACTIVE_3:
            // Random deactivation or transition to a lower active state
            return randomChoice(gen) ? CellularAutomata::INACTIVE : CellularAutomata::ACTIVE_2;
        default:
            break;
    }
    return currentState;
}

// Main function
int main() {
    int grid_size = 10; // Size of the grid
    mt19937 gen(random_device{}()); // Random number generator
    CellularAutomata ca(grid_size, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore); // Cellular automata instance

    // Initialize the grid with random values
    ca.Initialize2D([&gen](CellularAutomata::Grid2D& grid){ initNeuronGrid(grid, gen); });

    // Simulation loop for 20 steps
    for (int step = 0; step < 20; ++step) {
        auto gridState = ca.GetGrid2D(); // Get the current state of the grid

        // Add random activity every third step
        if (step % 3 == 0) {
            addRandomActivity(gridState, gen, 5); // 5% chance of activating a cell
        }

        // Iterate through each cell to apply the firing rule
        for (int i = 0; i < grid_size; ++i) {
            for (int j = 0; j < grid_size; ++j) {
                int activeNeighbors = ca.GetNeighbors2D(i, j); // Get count of active neighbors
                gridState[i][j] = weightedFiringRule(gridState[i][j], activeNeighbors, gen, step); // Apply the firing rule
            }
        }

        // Update the grid with the new state
        ca.UpdateGrid2D(gridState);
        cout << "Grid state after step " << step << ":\n";
        ca.Print(); // Print the current state of the grid
    }

    return 0;
}
