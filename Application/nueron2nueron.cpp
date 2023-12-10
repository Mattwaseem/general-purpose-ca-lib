#include <iostream>
#include <vector> // used as the data structure that will hold the data for the grid for the CA.
#include <random>
#include "../include/CellularAutomata.h"
#include "../src/cellular_automata.cpp"
using namespace std; // allows the use of std namespace without prefixing (i.e std::vector -> vector)

// state defintion:
// this is the first rule of the CA which defines what active and inactive states are for neurons
// Each cell, representing a neuron, has two states: Active (1) or Inactive (0).
const int INACTIVE = 0;
const int ACTIVE = 1;
const int THRESHOLD = 2;

// The function below will intilize a 2D grid with Moor's neighboorhood using the CA library for the nueron to nueorn CA
void initNueronGrid(CellularAutomata::Grid2D &grid)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (auto &row : grid)
    {
        for (auto &cell : row)
        {
            cell = dis(gen);
        }
    }
}

// this function applies the firing rule fo a nueron.
// the init function initilized the grid and filled it with random states of (0,1)
// the applyfiringRule updates the state of each neuron based on the sum of the states of its neighbors and the threshold.
// Firing rule that updates a single cell's state
int applyFiringRule(int currentState, int sumOfNeighbors)
{
    return (sumOfNeighbors >= THRESHOLD) ? ACTIVE : INACTIVE;
}

using SynapticWeights = std::vector<std::vector<double>>;

void initializeSynapticWeights(SynapticWeights &weights, int size)
{
    weights.resize(size, std::vector<double>(size, 1.0)); // Initial weight can be 1.0
    // More complex initializations can be added here if needed
}

// accessing different grid states and how they are handeled.
// Function to retrieve the grid state from a CellularAutomata object
// Function to retrieve the grid state from a CellularAutomata object
CellularAutomata::Grid2D getGridState(const CellularAutomata &ca)
{
    // Use the public member function getGrid2D() to retrieve the grid state
    return ca.getGrid2D();
}

void updateSynapticWeights(SynapticWeights &weights, const CellularAutomata::Grid2D &grid)
{
    // Example logic: Increase weight if both neurons are active
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            // Update weights based on the activity of neuron and its neighbors
            // This is a simplified example. You will need a more complex logic based on your model's requirements
            if (grid[i][j] == ACTIVE)
            {
                for (int di = -1; di <= 1; ++di)
                {
                    for (int dj = -1; dj <= 1; ++dj)
                    {
                        if (di == 0 && dj == 0)
                            continue;
                        int ni = (i + di + grid.size()) % grid.size();
                        int nj = (j + dj + grid[i].size()) % grid[i].size();
                        if (grid[ni][nj] == ACTIVE)
                        {
                            weights[i][j] += 0.1; // Increase weight
                        }
                    }
                }
            }
        }
    }
}

void applyDecayAndThreshold(SynapticWeights &weights, double decayRate, double ltpThreshold)
{
    for (auto &row : weights)
    {
        for (auto &weight : row)
        {
            weight -= decayRate;            // Apply decay
            weight = std::max(weight, 0.0); // Ensure weight does not go below 0
            if (weight > ltpThreshold)
            {
                weight = ltpThreshold; // Apply threshold
            }
        }
    }
}

int weightedFiringRule(int currentState, int sumOfNeighbors, double synapticWeight)
{
    // Apply the firing rule based on the sum of neighbors, threshold, and synaptic weight
    return (sumOfNeighbors * synapticWeight >= THRESHOLD) ? ACTIVE : INACTIVE;
}

int main()
{
    int grid_size = 10;
    CellularAutomata ca(grid_size, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);
    SynapticWeights weights;
    std::cout << "Initil grid" << std::endl;
    ca.Print();
    ca.ApplyRule2D(applyFiringRule); // Apply firing rule to CA
    std::cout << "grid after applying rule2D applying firing rule" << std::endl;
    ca.Print();

    // Initialize grid and weights
    ca.Initialize2D(initNueronGrid);
    ca.Print();
    std::cout << "Grid after applying Init2d and initNueron" << std::endl;

    initializeSynapticWeights(weights, grid_size);
    ca.Print();
    std::cout << "Grid after synapticweight check " << std::endl;

    // Update loop (you may want to run this multiple times)
    ca.Print();
    std::cout << "Grid before update loop includes [synpaticweight/decay] " << std::endl;

    for (int step = 0; step < 100; ++step)
    {
        // Retrieve the grid state using the new function
        CellularAutomata::Grid2D gridState = ca.getGrid2D();

        // Update synaptic weights based on the retrieved grid state
        updateSynapticWeights(weights, gridState);

        // Apply decay and threshold to synaptic weights
        applyDecayAndThreshold(weights, 0.05, 5.0);

        // Optional: Print grid state and/or weights for analysis
        std::cout << "Grid state after step " << step << ":\n";
        ca.Print();
    }
    return 0;
}
