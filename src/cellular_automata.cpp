#include <iostream>
#include <vector>

class CellularAutomata
{
protected:
    int width, height;                  // set up the intiial CA box with a lenght and width
    std::vector<std::vector<int>> grid; // setting up the grid  using a standard vector.

public:
    CellularAutomata(int width, int height) : width(width), height(height)
    {
        grid.resize(width, std::vector<int>(height, 0));
    }

    virtual void initializeGrid()
    {
        // Initialize grid with default values or states
    }

    virtual void displayGrid() const
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                // Display each cell's state here
                // For example:
                // std::cout << grid[x][y] << " ";
            }
            // std::cout << std::endl; // Uncomment these lines if using std::cout for display
        }
    }

    // Abstract method to be overridden in derived classes
    virtual void updateGrid() = 0;
};
