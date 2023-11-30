#include 'CellularAutomata.h'
#include <vector>

class MooreCA : public CellularAutomata
{
public:
    MooreCA(int width, int height) : CellularAutomata(width, height)
    {
        // Additional initialization if needed
    }

    void initializeGrid() override
    {
        // Custom initialization for MooreCA, if needed
    }

    void updateGrid() override
    {
        std::vector<std::vector<int>> newGrid = grid;

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                int activeNeighbors = countActiveNeighbors(x, y);
                // Update logic based on Moore's neighborhood
                // Example: Simple Conway's Game of Life Rules
                if (grid[x][y] == 1)
                {
                    // Any live cell with fewer than two live neighbors dies (underpopulation).
                    // Any live cell with two or three live neighbors lives on to the next generation.
                    // Any live cell with more than three live neighbors dies (overpopulation).
                    newGrid[x][y] = (activeNeighbors == 2 || activeNeighbors == 3) ? 1 : 0;
                }
                else
                {
                    // Any dead cell with exactly three live neighbors becomes a live cell (reproduction).
                    newGrid[x][y] = (activeNeighbors == 3) ? 1 : 0;
                }
            }
        }

        grid = newGrid; // Update the grid for the next generation
    }

private:
    int countActiveNeighbors(int x, int y)
    {
        int count = 0;
        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j)
            {
                if (i == 0 && j == 0)
                    continue; // Skip the cell itself
                int newX = x + i, newY = y + j;
                // Check for boundary conditions
                if (newX >= 0 && newX < width && newY >= 0 && newY < height)
                {
                    count += grid[newX][newY];
                }
            }
        }
        return count;
    }
};
