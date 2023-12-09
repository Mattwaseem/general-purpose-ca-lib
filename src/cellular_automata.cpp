#include <iostream>
#include <vector> // used as the data structure that will hold the data for the grid for the CA.
#include <random>
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
    if (dimension_ != GridDimension::TwoD)
    {
        throw std::runtime_error("Initialization function for 2D grid called on a non-2D automaton");
    }
    init_func(grid_2d_);
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
    if (dimension_ != GridDimension::TwoD)
    {
        throw std::runtime_error("Rule function for 2D grid called on a non-2D automaton");
    }
    Grid2D new_grid = grid_2d_;
    for (int i = 0; i < size_; ++i)
    {
        for (int j = 0; j < size_; ++j)
        {
            int neighbors = CalculateNeighbors2D(i, j);
            new_grid[i][j] = rule_func(grid_2d_[i][j], neighbors);
        }
    }
    grid_2d_ = std::move(new_grid);
}

// Print
string CellularAutomata::Print() const // this is the display method, const prevent this method from changing the state of the CA.
{
    stringstream ss; // stringstream used to print the grid in a specific format depending on the dimension.
    // Print the grid in a specific format depending on the dimension.
    if (dimension_ == GridDimension::OneD)
    {
        for (int cell : grid_1d_)
        {
            ss << cell << " ";
        }
        ss << "\n";
    }
    else
    {
        for (const auto &row : grid_2d_)
        {
            for (int cell : row)
            {
                ss << cell << " ";
            }
            ss << "\n";
        }
    }
    return ss.str(); // return the stringstream as a string
}

// CalculateNeighbors1D // update for Moore's neighborhood
int CellularAutomata::CalculateNeighbors1D(int index) const
{
    int neighbors = 0;
    for (int di = -1; di <= 1; ++di)
    {
        if (di == 0)
            continue; // Skip the center cell
        int ni = index + di;

        // Boundary condition handling
        switch (boundary_condition_)
        {
        case BoundaryCondition::Periodic:
            ni = (ni + size_) % size_;
            break;
        case BoundaryCondition::Fixed:
            if (ni < 0 || ni >= size_)
                ni = index; // Assume boundary cells are in the same state as the current cell
            break;
        case BoundaryCondition::NoBoundary:
            if (ni < 0 || ni >= size_)
                continue;
            break;
        }

        neighbors += grid_1d_[ni];
    }
    return neighbors;
}

// CalculateNeighbors2D
// Moore neighborhood logic (all eight neighbors)
// This is the default case in our current implementation
int CellularAutomata::CalculateNeighbors2D(int i, int j) const
{
    int neighbors = 0;
    for (int di = -1; di <= 1; ++di)
    {
        for (int dj = -1; dj <= 1; ++dj)
        {
            if (di == 0 && dj == 0)
                continue; // Skip the center cell

            // For Von Neumann neighborhood, consider only direct neighbors
            if (neighborhood_type_ == NeighborhoodType::VonNeumann && abs(di) + abs(dj) > 1)
            {
                continue;
            }

            int ni = i + di;
            int nj = j + dj;

            // Boundary condition handling
            switch (boundary_condition_)
            {
            case BoundaryCondition::Periodic:
                ni = (ni + size_) % size_;
                nj = (nj + size_) % size_;
                break;
            case BoundaryCondition::Fixed:
                if (ni < 0 || ni >= size_ || nj < 0 || nj >= size_)
                    continue;
                break;
            case BoundaryCondition::NoBoundary:
                if (ni < 0 || ni >= size_ || nj < 0 || nj >= size_)
                    continue;
                break;
            }

            neighbors += grid_2d_[ni][nj];
        }
    }
    return neighbors;


}

// This rule is specific for the 2D CA model
int majorityRule(int neighbors, int currentState)
{
    return (neighbors > 4) ? 1 : 0;
}

int totalisticRule(int neighbors, int currentState)
{
    return (neighbors == 3) ? 1 : 0;
}

int parityRule(int neighbors, int currentState)
{
    return (neighbors % 2 == 0) ? 1 : 0;
}

// This totalistic rule is specific for the 1D CA model
int totalisticRule_1D(int neighbors, int currentState){
     return (neighbors > 0) ? 1 : 0;
}

// This majority rule is specific for the 1D CA model
int majorityRule_1D(int neighbors, int currentState){
    return (neighbors >= 2) ? 1 : 0;
}
