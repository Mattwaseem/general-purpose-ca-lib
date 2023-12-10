#include <iostream>
#include <vector> // used as the data structure that will hold the data for the grid for the CA.
#include <random>
#include "../include/CellularAutomata.h"
using namespace std; // allows the use of std namespace without prefixing (i.e std::vector -> vector)

// state defintion:
// this is the first rule of the CA which defines what active and inactive states are for neurons
// Each cell, representing a neuron, has two states: Active (1) or Inactive (0).
const int INACTIVE = 0;
const int ACTIVE = 1;
const int THRESHOLD = 6;

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

// this function would allow us to apply the firing rule fo a nueron.
// the init function initilized the grid and filled it with random states of (0,1)
// the applyfiringRule updates the state of each neuron based on the sum of the states of its neighbors and the threshold.
// Firing rule that updates a single cell's state
int applyFiringRule(int currentState, int Neighbors) // neighbors is referring to sum of all the neighbors
{
    return (Neighbors >= THRESHOLD) ? ACTIVE : INACTIVE;
}

// Synaptic weight rule implementation - synaptic weights influence the activation of each nueron based on its neighbors
//  this is the second rule of the CA which defines the synaptic weights for each neuron
//  declaring a vector of vectors to store the synaptic weights for each neuron
using SynapticWeights = vector<vector<double>>;
void initSynapticWeights(SynapticWeights &weights, int size)
{
    weights.resize(size, std::vector<double>(size, 1.0));
}

// Synaptic Plasticity for Long-Term Potentiation - AKA repetitive firing becomes easier and easier
// when the synaptic weights between two neuros are increased the two nueron fire together more frequently.
// it will use the SynapticWeights function.
void updateSynapticWeights(SynapticWeights &weights, const CellularAutomata::Grid2D &grid)
{
    // increase weight if both neurons are active for a specific amount of time steps.
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == ACTIVE)
            {
                for
            }
        }
    }
}

int main()
{
    // Example usage
    int grid_size = 10; // Define the size of your grid
    CellularAutomata ca(grid_size, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);

    // Initialize the grid with the neuron setup
    ca.Initialize2D(initNueronGrid);

    // Apply the firing rule
    ca.ApplyRule2D(applyFiringRule);

    // Display the updated grid
    ca.Print();

    return 0;
}
