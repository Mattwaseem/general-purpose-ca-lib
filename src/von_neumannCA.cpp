#include <iostream>
#include <vector>
#include "../Include/CellularAutomata.h"
using namespace std;

        VonNeumannCA::VonNeumannCA(int width , int height) : CellularAutomata(width , height){}

        void VonNeumannCA::initializeGrid(){
            // Implementation for initializing Von Neumann Grid
            // We will set initial states of each cell here
        }

        void VonNeumannCA::updateGrid()
        {
            std::vector<std::vector<int>> newGrid = grid;

            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    // Get the state of the current cell and its neighbors

                    // Retrieving the state of the current cell at coordinates (x,y)
                    int currentState = grid[x][y];

                    // Checking to see if the north neighbor isn't top edge of grid- if it is, it defaults to state 0
                    int northNeighbor = (y > 0) ? grid[x][y - 1] : 0;

                    // Checking to see if the south neighbor isn't top edge of grid- if it is, it defaults to state 0
                    int southNeighbor = (y < height - 1) ? grid[x][y + 1] : 0;

                    // Checking to see if the east neighbor isn't top edge of grid- if it is, it defaults to state 0
                    int eastNeighbor = (x < width - 1) ? grid[x + 1][y] : 0;

                    //  Checking to see if the west neighbor isn't top edge of grid- if it is, it defaults to state 0
                    int westNeighbor = (x > 0) ? grid[x - 1][y] : 0;

                    // Implement your Von Neumann CA rules here
                    // Update the newGrid based on the current state and neighbors
                    // newGrid[x][y] = updatedState;


                }
            }

            // Update the grid with the new state
            grid = newGrid;
        }

        void CellularAutomate::displayGrid() const{}




int main() {
    VonNeumannCA vn(10, 10);

    // You can now use the methods of the VonNeumannCA class
    vn.initializeGrid();
    vn.updateGrid();

    return 0;
}