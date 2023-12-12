#include <iostream>
#include <vector> // used as the data structure that will hold the data for the grid for the CA.
#include <random>
#include "../include/CellularAutomata.h"
#include <sstream> // print to a string stream and use your -ostream and pipe to a text file.
#include "../Include/CellularAutomata.h"
using namespace std; // allows the use of std namespace without prefixing (i.e std::vector -> vector)

// Constructor
// initilizes the class members (size_, dimension,boundary conditions as bc, neighbortype as nt)
CellularAutomata::CellularAutomata(int size, GridDimension dimension, BoundaryCondition bc, NeighborhoodType nt)
    : size_(size), dimension_(dimension), boundary_condition_(bc), neighborhood_type_(nt)
// below are conditional statements to set the grid_1d_ and grid_2d_ to the correct size
// depending on the dimension of the CA inputted by the application/user.
{
    if (dimension == GridDimension::OneD)
    {
        grid_1d_.resize(size, 0); // resize method used to resize grid as specified and initilize to 0.
    }
    else
    {
        grid_2d_.resize(size, std::vector<int>(size, 0)); // resize two a square grid size X size using vector of vector.
    }
}

// Initialize1D
// this method takes in the reference function(init_func)references to intilizationfunction1d and intializationfunction2D
// and calls the correct initialization function depending on the dimension of the CA given by the user.
void CellularAutomata::Initialize1D(const InitializationFunction1D &init_func)
{
    if (dimension_ != GridDimension::OneD) // dimension check to ensure intilization is one dimension only.
    {
        throw std::runtime_error("Initialization function for 1D grid called on a non-1D automaton");
    }
    init_func(grid_1d_); // both are reference functions which apply intilization logic once if condition is passed.
}

// Initialize2D
// same thing as the 1D but used in the context of 2D.
// main asks intilize2D to set up grid, initilize2D references and looks into init_funct on specific instructions.
void CellularAutomata::Initialize2D(const InitializationFunction2D &init_func)
{
    if (dimension_ != GridDimension::TwoD) // dimension check to ensure intilization is one dimension only.
    {
        throw std::runtime_error("Initialization function for 2D grid called on a non-2D automaton");
    }
    init_func(grid_2d_);
}

// getGrid2D implementation of memberfunction within class CellularAutomata.
// this method returns a reference to the grid_2d_ member variable.
// this is used to access the grid_2d_ member variable from outside the class.
const CellularAutomata::Grid2D &CellularAutomata::getGrid2D() const
{
    if (dimension_ != GridDimension::TwoD) // check if the CA simulation is indeed 2D. If not throw a runtime error using standard library error handeling
    {
        throw std::runtime_error("getGrid2D called on a non-2D automaton");
        // this is used to access the grid_2d_ member variable from outside the class.
    }
    return grid_2d_;
}

// ApplyRule1D
// this method takes in the pointer function Rulefunction1D as an argument which represent the rules applied
// to each cell in CA for a 1D grid.
void CellularAutomata::ApplyRule1D(const RuleFunction1D &rule_func)
{
    if (dimension_ != GridDimension::OneD)
    {
        throw std::runtime_error("Rule function for 1D grid called on a non-1D automaton");
    }
    Grid1D new_grid = grid_1d_;     // create a new grid to grid_1d and initilize it to the current state of grid_1d_
    for (int i = 0; i < size_; ++i) // loop through each cell in the grid_1d_
    {
        int neighbors = CalculateNeighbors1D(i);         // calculate the number of active neighbors
        new_grid[i] = rule_func(neighbors, grid_1d_[i]); // apply the rule_func (fxn pointer) to each cell which takes current state and number of neighbors
    }
    grid_1d_ = std::move(new_grid); // assign the new grid to gird_1d and transfer ownership of data from new_grid to grid_1d_
}

// ApplyRule2D
// the same logic as the 1D but used in the context of 2D.
void CellularAutomata::ApplyRule2D(const RuleFunction2D &rule_func)
{
    if (dimension_ != GridDimension::TwoD) // check if the CA simulation is indeed 2D. If not throw a runtime error using standard library error handeling
    {
        throw std::runtime_error("Rule function for 2D grid called on a non-2D automaton"); // standard lib error handeling if not 2D CA.
    }
    Grid2D new_grid = grid_2d_;     // create a new grid to grid_2d and initilize it to the current state of grid_2d_ and update cell states simulatenousely.
    for (int i = 0; i < size_; ++i) // iterate through the loop to access each cell in the grid_2d_
    {
        for (int j = 0; j < size_; ++j) // iterate through the nested loop to access each cell in the grid_2d_
        {
            int neighbors = CalculateNeighbors2D(i, j);            // calculate the number of active neighbors for the current cell
            new_grid[i][j] = rule_func(neighbors, grid_2d_[i][j]); // Apply the rule_func (fxn pointer) to each cell which takes current state and number of neighbors
        }
    }
    grid_2d_ = std::move(new_grid); // assign the new grid to gird_2d and transfer ownership of data from new_grid to grid_2d_
}

// Print
string CellularAutomata::Print() const // this is the display method, const prevent this method from changing the state of the CA.
{
    stringstream ss; // stringstream used to print the grid in a specific format depending on the dimension.
    // Print the grid in a specific format depending on the dimension.
    if (dimension_ == GridDimension::OneD) // if dimension is 1D, print the grid_1d_ in a specific format.
    {
        for (int cell : grid_1d_) // iterate through the grid_1d_ and print each cell
        {
            std::cout << cell << " "; // print each cell with a space after it
        }
        std::cout << "\n"; // print a new line after the grid is printed.
    }
    else // if dimension is 2D, print the grid_2d_ in a specific 2D format.
    {
        for (const auto &row : grid_2d_) // iterate through the grid_2d_ and print each row
        {
            for (int cell : row) // iterate through each cell in the row
            {
                std::cout << cell << " "; // print each cell with a space after it
            }
            std::cout << "\n"; // print a new line after the row is printed.
        }
    }
    return ss.str(); // return the stringstream as a string
}

// CalculateNeighbors1D // update for Moore's neighborhood
// this function is responsible for calculating the number of neighbors a cell have
// depending on the neighborhood type and boundary condition.
// this function is used in the context of 1D CA.
int CellularAutomata::CalculateNeighbors1D(int index) const
// int index is the cell which neighbors need to be calculated for.
{
    int neighbors = 0; // used to keep track of neighbor count around int index
    for (int di = -1; di <= 1; ++di)
    {
        if (di == 0)  // this is the index being considered whose neighbors are counted
            continue; // Skip the center cell
        int ni = index + di;

        // Boundary condition handling
        // the boundary is periodic and it wraps around similar to a torus
        // the boundaries have neighbors on the opposite side of the grid
        switch (boundary_condition_)
        {
        case BoundaryCondition::Periodic: // boundary periodic = torus shaped.
            ni = (ni + size_) % size_;    // if ni (neighbor index) is less than 0 or greater
                                          // than the size of the grid (size_), wrap around
                                          // using the modulo operator (size_ % ni).
            break;                        // break out of the switch if the boundary condition is periodic.

        case BoundaryCondition::Fixed: // boundary fixed = cells at edges have fixed values
                                       // and don't interact with cell outside the grid
            if (ni < 0 || ni >= size_) // if neighbor index (ni) less than 0 or greater than or equal
                ni = index;            // Assume boundary cells are in the same state as the current cell
            break;
        case BoundaryCondition::NoBoundary: // no specific boundary rules cells outside the grid are ignored
                                            // if neighbor index (ni) less than 0 or greater than or equal to grid
                                            // size, the loop continues to the next iteration w/o counting
            if (ni < 0 || ni >= size_)      // size_ = grid size, if ni is less than 0 or greater than or equal to grid size,
                continue;                   // continue to the next iteration without counting the neighbor.
            break;
        }

        neighbors += grid_1d_[ni]; // add the neighbor to the neighbor count
    }
    return neighbors; // return the total number of neighbors around int index.
}

// CalculateNeighbors2D
// Moore neighborhood logic (all eight neighbors)
// This is the default case in our current implementation
// This is CalculateNeighbors2D within class CellularAutomata.

// Purpose: to calculate the number of neighbors a cell has in 2D CA.

// consideraton: Moor's neighboorhood is defualt option but can handle von Nuemann.
// Parameters : int i, int j - the cell whose neighbors need to be calculated for.
// Returns : int neighbors - the total number of neighbors around int index.
int CellularAutomata::CalculateNeighbors2D(int i, int j) const
{
    int neighbors = 0;               // used to keep track of neighbor count around int index
    for (int di = -1; di <= 1; ++di) // loop through each cell in the grid_1d_
    {
        for (int dj = -1; dj <= 1; ++dj) // loop through each cell in the grid_1d_
        {
            if (di == 0 && dj == 0) // this is the index being considered whose neighbors are counted
                continue;           // Skip the center cell

            // For Von Neumann neighborhood, consider only direct neighbors
            // if neighborhood_type_ is von Neumann and di + dj > 1, skip the cell.
            // this conditions skips the diagnol neighbors.
            if (neighborhood_type_ == NeighborhoodType::VonNeumann && abs(di) + abs(dj) > 1)
            {
                continue;
            }

            int ni = i + di; // the coordinates of neighboring cells in relation to the neighbor index
            int nj = j + dj; // the coordinates of neighboring cells in relation to the neighbor index

            // Boundary condition handling
            // this switch statement handles the boundary conditions for the 2D CA.
            // the boundary is periodic and it wraps around similar to a torus
            // if the boundary is fixed it assumes cells at edges have fixed value
            // if no boundary is specified, cells outside the grid are ignored.
            switch (boundary_condition_)
            {
            case BoundaryCondition::Periodic: // (ni + size_) % size  and (nj + size_)%size_
                                              // are used to adjust coordinates
                ni = (ni + size_) % size_;    // this takes current value of ni add size_ and takes the
                                              // remainder or modulo of size_. The result is if ni becomes
                                              // greater or equal  size_ it wraps ariubd to a valid coordinate within the grid
                nj = (nj + size_) % size_;    // this takes current value of nj and does the same as ni to wrap around the cells
                                              // at the bottom edge of the grid and wrap around the top.
                break;
            case BoundaryCondition::Fixed:                          // this case handles fixed boundary condition for 2D Grid CA.
                if (ni < 0 || ni >= size_ || nj < 0 || nj >= size_) // if ni is less than 0 or greater than or equal to grid size,continue
                                                                    // and ignore the cells beyond the grid's edges which do not effect the simulation
                                                                    // these cells beyond the edges are considered constant in this simulation logic.
                    continue;                                       // if the neighbor cell is outside the grid boundaries skip the processing of the neighbor and move to the next one
                break;                                              // exit switch statement if boundary condition is fixed and logic is applied

            case BoundaryCondition::NoBoundary:                     // this condition treats the boundaries as if they extend infinitely in all directions
                if (ni < 0 || ni >= size_ || nj < 0 || nj >= size_) // if ni is less than 0 or greater than or equal to grid size, if true it neighbor cell is
                                                                    // is outside the grid boundaries, ignore them and continue to the next cell.
                    continue;                                       // continue to the next iteration without counting the neighbor.
                break;                                              // once the logic is applied exit the switch statement.
            }

            neighbors += grid_2d_[ni][nj]; // used to count the number of neighboring cells that have specific states within 2D grid with simulating CA.
        }
    }
    return neighbors; // return total neighbor count based on the conditions that were applied
}

// This rule is specific for the 2D CA model
int majorityRule(int neighbors, int currentState)
// purpose : to determine the new state of a cell based on the majority of its neighboring cells being in state 1 or initial state.
{
    return (neighbors > 4) ? 1 : 0; // if neighbors is greater than 4 current cell is set(?) to 1 else (:-> otherwise) set it to 0.
}

int totalisticRule(int neighbors, int currentState)
// purpose: implement the totalistic rule where the new state of a cell depends on the exact count of neighboring cells in state 1 (3 in this case)
{
    return (neighbors == 3) ? 1 : 0; // if the number of neighboring cells in state 1 ('neighbors') is equal to 3 the current cell state cell should be set to 1;
}

int parityRule(int neighbors, int currentState)
// purpose: to check the parity (even/or odd) of the number of neighboring cells in state 1.
{
    return (neighbors % 2 == 0) ? 1 : 0; // if the number of neighboring cells in state 1 ('neighbors') is even the current cell state cell should be set to 1;
                                         // otherwise, set the current cell state to 0.//
}

// This totalistic rule is specific for the 1D CA model
// This function is used to implement the totalistic rule for the 1D CA model.
int totalisticRule_1D(int neighbors, int currentState)
{
    return (neighbors > 0) ? 1 : 0; // if the number of neighboring cells in state 1 ('neighbors') is greater than 0 the current cell state cell should be set to 1;
                                    // otherwise it is set to 0.
}

// This majority rule is specific for the 1D CA model
// This function is used to implement the majority rule for the 1D CA model.
int majorityRule_1D(int neighbors, int currentState)
{
    return (neighbors >= 2) ? 1 : 0; // if the number of neighboring cells in state 1 ('neighbors') is greater than or equal to 2 the current cell state cell should be set to 1;
                                     // otherwise it is set to 0.
}

