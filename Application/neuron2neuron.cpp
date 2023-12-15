#include <iostream>
#include <vector> // used as the data structure that will hold the data for the grid for the CA.
#include <random>
#include <sstream> // print to a string stream and use your -ostream and pipe to a text file.
#include <fstream> // read from a file.
#include "../Include/CellularAutomata.h"
#include "../src/cellular_automata.cpp"
using namespace std; // allows the use of std namespace without prefixing (i.e std::vector -> vector)

// state defintion:
// this is the first rule of the CA which defines what active and inactive states are for neurons
// Each cell, representing a neuron, has two states: Active (1) or Inactive (0).
const int INACTIVE = 0;
const int ACTIVE = 1;
double baseThreshold = 4.0;                                   // Base threshold
double randomFactor = static_cast<double>(rand()) / RAND_MAX; // Random factor between 0 and 1

// defining variability
double variability = 0.6; // You can adjust the value as needed

double dynamicThreshold = baseThreshold + (randomFactor * variability); // Adjusted threshold

// The function below will intilize a 2D grid with Moor's neighboorhood using the CA library for the nueron to nueorn CA
void initNueronGrid(CellularAutomata::Grid2D &grid)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (auto &row : grid)
    {
        for (auto &cell : row)
        {
            double prob = dis(gen);                   // Probability for the cell to be active
            cell = (prob < 0.25) ? INACTIVE : ACTIVE; // Adjust 0.5 to control the density of active cells
        }
    }
}

// Now that we have initialized the grid and used a random number generator to fill it with 1's and 0
// we can intilize the synaptic weights.The synaptic weights will be a vector data structure which will store
// the weights for each neuron (cell). A neuron with a higher snaptic weight will fire more often.
//
// This is the vector that will hold the weights for each neuron.
using SynapticWeights = std::vector<std::vector<double>>; // doubles used here but int used in CA grid??
// using SynapticWeights = std::vector<std::vector<std::vector<std::vector<double>>>>; we are using
// 2D vector to make it simple instead of a more realistic version which would be
// std::vector<std::vector<std::vector<std::vector<double>>>>;
// this makes the use of synaptic weights more realistic compare to our initial
// rudimentary model.
//
//
// This function initializes the synaptic weights for the CA.
void initializeSynapticWeights(SynapticWeights &weights, int size)
{
    // Resizing the weights vector to match the size of the grid
    weights.resize(size, std::vector<double>(size, 1.0));

    // Initialize each weight to a default value of 1.0
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            weights[i][j] = 1.0; // initilized weights to 1.0 at the start.
        }
    }
}

// Function to calculate dynamic threshold
double applyDynamicThreshold(const SynapticWeights &weights, const CellularAutomata::Grid2D &grid, int i, int j, double baseThreshold, double variability)
{
    double sumOfWeightedNeighbors = 0.0;
    int size = static_cast<int>(grid.size());

    for (int di = -1; di <= 1; ++di)
    {
        for (int dj = -1; dj <= 1; ++dj)
        {
            if (di == 0 && dj == 0)
                continue;
            int ni = (i + di + size) % size;
            int nj = (j + dj + size) % size;
            sumOfWeightedNeighbors += weights[i][j] * grid[ni][nj];
        }
    }

    double randomFactor = static_cast<double>(rand()) / RAND_MAX;
    double dynamicThreshold = baseThreshold + (randomFactor * variability);
    return dynamicThreshold;
}

// Now we have a cellular automata set up which was initialized using the general purpose CA. Then, it was
// updated with the inialization of synaptic weights for each cell within the CA.
//
//
// Next the firing rule with the help of the genral purpose library periodic boundary condition will be
// be implemented. The firing rule indicates to a cell based on a set of specific condition whether it
// will change state in the next time step or not. This essentially is a modified implementation of the CA
// specific to this simulation while still using functionalities of the general purpose library

// this function applies the firing rule fo a nueron.
// the applyfiringRule updates the state of each neuron based on the sum of the states of its neighbors and the threshold.
// Updated applyFiringRule function that uses the general-purpose library for periodic boundary conditions
int applyFiringRule(const SynapticWeights &weights, const CellularAutomata::Grid2D &grid, int i, int j)
{
    int size = static_cast<int>(grid.size());
    double sumOfWeightedNeighbors = 0.0;
    double randomFactor = static_cast<double>(rand()) / RAND_MAX; // Random factor between 0 and 1

    for (int di = -1; di <= 1; ++di)
    {
        for (int dj = -1; dj <= 1; ++dj)
        {
            // Skip the center cell
            if (di == 0 && dj == 0)
                continue;

            int ni = (i + di + size) % size;
            int nj = (j + dj + size) % size;

            // Use the weight of the neuron at (i, j) for all its neighbors
            double weight = weights[i][j];
            sumOfWeightedNeighbors += weight * grid[ni][nj];
        }
    }
    // Debugging: Log the sum of weighted neighbors
    // cout << "Cell (" << i << ", " << j << ") Sum: " << sumOfWeightedNeighbors << endl;
    double activationThreshold = baseThreshold + (randomFactor * 0.5);          // dynamicThreshold + (randomFactor * 0.5); // Adjust threshold with randomness and
                                                                                //  multiply to have low randomness factor
    return (sumOfWeightedNeighbors >= activationThreshold) ? ACTIVE : INACTIVE; // dynamicThreshold)
    // ? ACTIVE
    // : INACTIVE;
}
// accessing different grid states and how they are handeled.
// Function to retrieve the grid state from a CellularAutomata object
// Function to retrieve the grid state from a CellularAutomata object
CellularAutomata::Grid2D getGridState(const CellularAutomata &ca)
// if I make grid2D templated than I can get rid of the synaptic weights
// better improvement less code and
{
    // Use the public member function getGrid2D() to retrieve the grid state
    return ca.getGrid2D();
}

// setting a max weight so update function does not indefinitely increase weights

const double maxWeight = 5.0; // Define maxWeight

void updateSynapticWeights(SynapticWeights &weights, const CellularAutomata::Grid2D &grid)
{
    int size = grid.size();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            // If the current neuron is active, its synaptic weight is increased.
            // This increment signifies strengthening of the neuron's influence due to its activity.
            if (grid[i][j] == ACTIVE)
            {
                weights[i][j] += 0.01; // Increment the weight of the neuron

                // The following loop iterates over the neighbors of the current neuron.
                // This considers the influence of the neighboring neurons on the current neuron.
                for (int di = -1; di <= 1; ++di)
                {
                    for (int dj = -1; dj <= 1; ++dj)
                    {
                        // Skip the neuron itself
                        if (di == 0 && dj == 0)
                            continue;

                        // Calculate the coordinates of the neighboring neuron while
                        // handling the periodic boundary conditions.
                        int ni = (i + di + size) % size;
                        int nj = (j + dj + size) % size;

                        // If the neighboring neuron is also active, increase the weight further.
                        // This reflects the idea that simultaneous activity of a neuron and its neighbors
                        // can lead to stronger synaptic connections.
                        if (grid[ni][nj] == ACTIVE)
                        {
                            weights[i][j] += 0.00; // Additional increment for active neighbors
                        }
                    }
                }
            }

            // This line below ensurea that the weight does not exceed a predefined maximum value.
            // This prevents the synaptic strength from growing indefinitely.
            weights[i][j] = min(weights[i][j], maxWeight);
        }
    }
}

// the grid is not being updated based on the synaptic weights. and updated weights.
// go back and review the logic used here
// call function and compare variables current state vs. modification (possible sol. )

void applyDecayAndThreshold(SynapticWeights &weights, double decayRate, double ltpThreshold)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 0.01); // Small random factor

    for (auto &row : weights)
    {
        for (auto &weight : row)
        {
            double randomDecay = dis(gen);       // Random decay factor
            weight -= (decayRate + randomDecay); // Apply decay with randomness

            weight = std::max(weight, 1.0);
            weight = std::min(weight, ltpThreshold);
        }
    }
}

int main()
{
    int grid_size = 10; // Defines the size of the grid for the CA simulation

    // Initialize the cellular automata with specified grid size, dimension, boundary condition, and neighborhood type
    CellularAutomata ca(grid_size, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);

    // Initialize synaptic weights for each neuron
    SynapticWeights weights;
    initializeSynapticWeights(weights, grid_size);

    // Initialize the neuron grid with random states (ACTIVE or INACTIVE)
    ca.Initialize2D(initNueronGrid);
    cout << "Initial grid state:\n";
    ca.Print();

    // Simulation loop: Iteratively apply the firing rule and update synaptic weights
    for (int step = 0; step < 6; ++step)
    {
        // Apply the firing rule to the CA based on the current grid state and synaptic weights
        ca.ApplyRule2D([&weights, &ca](int i, int j)
                       { return applyFiringRule(weights, ca.GetGrid2D(), i, j); });

        // Retrieve the updated grid state
        CellularAutomata::Grid2D gridState = ca.GetGrid2D();

        // Update the synaptic weights based on the current grid state
        updateSynapticWeights(weights, gridState);

        // Apply decay and thresholding to the synaptic weights
        applyDecayAndThreshold(weights, 0.05, 5.0);

        // Print the grid state after each step for analysis
        cout << "Grid state after step " << step << ":\n";
        ca.Print();
    }

    // Additional functions for analyzing changes in grid states or synaptic weights can be added here

    return 0;
}
