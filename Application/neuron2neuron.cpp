// The required headers are included here.
#include <iostream>
#include <vector>
#include <random>
#include "../Include/CellularAutomata.h"

// The standard namespace is used to simplify syntax.
using namespace std;

// Constants representing the inactive and active states of cells, and a threshold value, are defined.
const int INACTIVE = 0;
const int ACTIVE = 1;
const int THRESHOLD = 3;

// A type alias 'SynapticWeights' is created for a 2D vector of doubles.
using SynapticWeights = vector<vector<double>>;

// initNeuronGrid function initializes the neuron grid with a mix of active and inactive states.
void initNeuronGrid(CellularAutomata::Grid2D &grid) {
    random_device rd; // A random number generator is initialized.
    mt19937 gen(rd()); // A Mersenne Twister pseudo-random generator is used.
    uniform_int_distribution<> dis(0, 100); // Uniform distribution between 0 and 100 is defined.

    // Iterates over each cell in the grid.
    for (auto &row : grid) {
        for (auto &cell : row) {
            // Each cell is set to active or inactive based on a random draw.
            cell = dis(gen) < 70 ? INACTIVE : ACTIVE;
        }
    }
}

// initializeSynapticWeights function sets the initial synaptic weights to 1.0 for all connections.
void initializeSynapticWeights(SynapticWeights &weights, int size) {
    weights.resize(size, vector<double>(size, 1.0));
}

// updateSynapticWeights function adjusts the synaptic weights based on the current grid state.
void updateSynapticWeights(SynapticWeights &weights, const CellularAutomata::Grid2D &grid, int grid_size, int step) {
    double increment = (step % 10 == 0) ? 0.1 : 0.05; // The increment varies with the step count.

    // Iterates over the grid to adjust weights.
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            // Increases weight for active cells.
            if (grid[i][j] == ACTIVE) {
                weights[i][j] += increment;
                weights[i][j] = min(weights[i][j], 4.0); // Caps the weight to avoid runaway growth.
            }
        }
    }
}

// applyDecayAndThreshold function reduces synaptic weights over time and imposes a maximum limit.
void applyDecayAndThreshold(SynapticWeights &weights, double decayRate, double ltpThreshold) {
    // Iterates over each weight to apply decay and threshold logic.
    for (auto &row : weights) {
        for (auto &weight : row) {
            weight -= decayRate; // Applies decay.
            weight = max(weight, 0.0); // Ensures weight doesn't fall below zero.
            if (weight > ltpThreshold) {
                weight = ltpThreshold; // Enforces a maximum threshold.
            }
        }
    }
}

// weightedFiringRule function determines the next state of a cell based on its current state, the number of active neighbors, and its synaptic weight.
int weightedFiringRule(int currentState, int sumOfNeighbors, double synapticWeight) {
    // Applies different logic depending on whether the current state is active or inactive.
    if (currentState == ACTIVE) {
        return (sumOfNeighbors * synapticWeight >= THRESHOLD + 1) ? ACTIVE : INACTIVE;
    } else {
        return (sumOfNeighbors * synapticWeight >= THRESHOLD) ? ACTIVE : INACTIVE;
    }
}

// The main function where the simulation is orchestrated.
int main() {
    int grid_size = 10;
    // CellularAutomata object is initialized with predefined parameters.
    CellularAutomata ca(grid_size, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);
    SynapticWeights weights;

    // Initializes the grid and synaptic weights.
    ca.Initialize2D(initNeuronGrid);
    initializeSynapticWeights(weights, grid_size);

    // The main simulation loop runs for a fixed number of steps.
    for (int step = 0; step < 20; ++step) {
        auto gridState = ca.GetGrid2D(); // Retrieves the current state of the grid.

        // Updates synaptic weights and applies decay and threshold logic.
        updateSynapticWeights(weights, gridState, grid_size, step);
        applyDecayAndThreshold(weights, 0.02, 2.5);

        // Iterates over each cell to update its state based on the weighted firing rule.
        for (int i = 0; i < grid_size; ++i) {
            for (int j = 0; j < grid_size; ++j) {
                int neighbors = ca.GetNeighbors2D(i, j);

                // Introduces random noise to make the grid behavior more dynamic.
                if (rand() % 100 < 20) {
                    gridState[i][j] = !gridState[i][j];
                } else {
                    gridState[i][j] = weightedFiringRule(gridState[i][j], neighbors, weights[i][j]);
                }
            }
        }

        // Updates the CellularAutomata's internal grid state.
        ca.UpdateGrid2D(gridState);
        // Prints the current state of the grid.
        cout << "Grid state after step " << step << ":\n";
        ca.Print();
    }

    return 0;
}
