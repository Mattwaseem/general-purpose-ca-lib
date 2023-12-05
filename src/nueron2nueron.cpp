#include "../include/CellularAutomata.h"

NeuronToNeuronCA::NeuronToNeuronCA(int width, int height, bool useMoore)
    : mooreCA(width, height), vonNeumannCA(width, height), useMooreNeighborhood(useMoore)
{
    initializeGrid();
}

void NeuronToNeuronCA::initializeGrid()
{
    // Initialize grid with neuron-specific states
    grid.resize(width);
    synapticWeights.resize(width);
    activationThresholds.resize(width);

    for (int x = 0; x < width; ++x)
    {
        grid[x].resize(height);
        synapticWeights[x].resize(height);
        activationThresholds[x].resize(height);

        for (int y = 0; y < height; ++y)
        {
            grid[x][y] = 0;                   // Initialize all neurons to inactive (0)
            activationThresholds[x][y] = 0.5; // Default threshold value, modify as needed

            // Initialize synaptic weights for each neighbor
            synapticWeights[x][y].resize(width);
            for (int nx = 0; nx < width; ++nx)
            {
                synapticWeights[x][y][nx].resize(height, 1.0); // Initialize weights, e.g., to 1.0

                for (int ny = 0; ny < height; ++ny)
                {
                    // Optionally customize the initial synaptic weights here
                    // For example, you might want different weights for immediate neighbors vs. distant ones
                }
            }
        }
    }
}

void NeuronToNeuronCA::updateGrid()
{
    // Now apply neuron-specific rules
    std::vector<std::vector<int>> newGrid = grid; // Copy the current grid state

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            float weightedSum = 0.0;
            std::vector<std::pair<int, int>> neighbors = getNeighbors(x, y); // Method to get neighbor coordinates

            // Calculate the weighted sum of active neighbors
            for (const auto &neighbor : neighbors)
            {
                int nx = neighbor.first, ny = neighbor.second;
                weightedSum += grid[nx][ny] * synapticWeights[x][y][nx][ny];
            }

            // Check against activation threshold
            if (weightedSum >= activationThresholds[x][y])
            {
                newGrid[x][y] = 1; // Activate neuron
                // Implement synaptic plasticity (increase weight if both neurons are active)
                if (grid[x][y] == 1)
                {
                    for (const auto &neighbor : neighbors)
                    {
                        int nx = neighbor.first, ny = neighbor.second;
                        synapticWeights[x][y][nx][ny] += plasticityRate; // Assume plasticityRate is defined
                    }
                }
            }
            else
            {
                // Implement LTP decay
                newGrid[x][y] = (grid[x][y] == 1 && weightedSum >= ltpThreshold) ? 1 : 0; // Keep neuron active if above LTP threshold
                // Decay synaptic weights
                for (const auto &neighbor : neighbors)
                {
                    int nx = neighbor.first, ny = neighbor.second;
                    synapticWeights[x][y][nx][ny] *= decayRate; // Assume decayRate is defined
                }
            }
        }
    }

    grid = newGrid; // Update the grid with the new state
}

void NeuronToNeuronCA::displayGrid() const
{
    if (useMooreNeighborhood)
    {
        mooreCA.displayGrid();
    }
    else
    {
        vonNeumannCA.displayGrid();
    }
}

int main()
{
    NeuronToNeuronCA n2nCA(20, 20, true); // Example dimensions and neighborhood
    n2nCA.initializeGrid();
    for (int step = 0; step < 100; ++step)
    { // Run for 100 steps
        n2nCA.updateGrid();
        n2nCA.displayGrid();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause for visibility
    }
    return 0;
}
