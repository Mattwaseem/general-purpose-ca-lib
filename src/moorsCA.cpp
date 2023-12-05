#include "CellularAutomata.h"

// Constructor
MooreCA::MooreCA(int width, int height) : CellularAutomata(width, height)
{
    // Additional initialization if needed
}

// Initialize the grid with default values
void MooreCA::initializeGrid()
{
    // Implement the initialization logic for the grid
    // You can set initial states for each cell here
}

// Count the active neighbors in Moore's neighborhood
int MooreCA::countActiveNeighbors(int x, int y)
{
    int count = 0;
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
                continue; // Skip the cell itself
            int newX = x + i, newY = y + j;
            if (newX >= 0 && newX < width && newY >= 0 && newY < height)
            {
                count += grid[newX][newY];
            }
        }
    }
    return count;
}

// Update the grid based on Moore's neighborhood rule
void MooreCA::updateGrid()
{
    std::vector<std::vector<int>> newGrid = grid;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int activeNeighbors = countActiveNeighbors(x, y);

            // Implement your Moore CA rules here
            // The logic to update the newGrid based on the current state and neighbors
            // Example rule:
            // newGrid[x][y] = (activeNeighbors > 3) ? 1 : 0;
        }
    }

    grid = newGrid; // Update the grid with the new state
}
