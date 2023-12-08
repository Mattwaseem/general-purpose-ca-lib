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
void CellularAutomata::Initialize2D(const InitializationFunction2D &init_func)
{
    if (dimension_ != GridDimension::TwoD)
    {
        throw std::runtime_error("Initialization function for 2D grid called on a non-2D automaton");
    }
    init_func(grid_2d_);
}

// ApplyRule1D
void CellularAutomata::ApplyRule1D(const RuleFunction1D &rule_func)
{
    if (dimension_ != GridDimension::OneD)
    {
        throw std::runtime_error("Rule function for 1D grid called on a non-1D automaton");
    }
    Grid1D new_grid = grid_1d_;
    for (int i = 0; i < size_; ++i)
    {
        int neighbors = CalculateNeighbors1D(i);
        new_grid[i] = rule_func(neighbors, grid_1d_[i]);
    }
    grid_1d_ = std::move(new_grid);
}

// ApplyRule2D
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
            new_grid[i][j] = rule_func(neighbors, grid_2d_[i][j]);
        }
    }
    grid_2d_ = std::move(new_grid);
}

// Print
void CellularAutomata::Print() const
{
    if (dimension_ == GridDimension::OneD)
    {
        for (int cell : grid_1d_)
        {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
    else
    {
        for (const auto &row : grid_2d_)
        {
            for (int cell : row)
            {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        }
    }
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
// This is the default case in your current implementation
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

void initGrid2D(CellularAutomata::Grid2D &grid)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (auto &row : grid)
    {
        for (auto &cell : row)
        {
            cell = dis(gen); // Randomly set each cell to 0 or 1
        }
    }
}

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

int main()
{

    // Testing out the 2D, Periodic, and Moore conditions (majorityRule)
    CellularAutomata ca2D(10, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);

    // Initialize the grid
    ca2D.Initialize2D(initGrid2D);

    // Apply a rule
    ca2D.ApplyRule2D(majorityRule);

    // Print the final state
    cout << "Results of 2D , Periodic, and Moore (majority): " << endl;
    ca2D.Print();
    cout << endl
         << endl
         << endl;

    // Testing out the 2D , Fixed , and Moore conditions (majorityRule)
    CellularAutomata ca2d_1(10, GridDimension::TwoD, BoundaryCondition::Fixed, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_1.Initialize2D(initGrid2D);

    // Apply a rule
    ca2d_1.ApplyRule2D(majorityRule);

    // Printing out the final state
    cout << "Results of 2D, Fixed, and Moore (majority): " << endl;
    ca2d_1.Print();
    cout << endl
         << endl
         << endl;

    // Testing out the 2D , NoBoundary , and Moore conditions (majorityRule)
    CellularAutomata ca2d_2(10, GridDimension::TwoD, BoundaryCondition::NoBoundary, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_2.Initialize2D(initGrid2D);

    // Apply a rule
    ca2d_2.ApplyRule2D(majorityRule);

    // Printing out the final state
    cout << "Results of 2D, NoBoundary, and Moore (majority): " << endl;
    ca2d_2.Print();
    cout << endl
         << endl
         << endl;

    // Testing out the 2D, Periodic, and Moore conditions (totalisticRule)
    CellularAutomata ca2d_3(10, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_3.Initialize2D(initGrid2D);

    // Apply a rule
    ca2d_3.ApplyRule2D(totalisticRule);

    // Printing out the final state
    cout << "Results of 2D, Periodic, and Moore (totalistic): " << endl;
    ca2d_3.Print();
    cout << endl
         << endl
         << endl;

    // Testing out the 2D, Fixed, and Moore conditions (totalisticRule)
    CellularAutomata ca2d_4(10, GridDimension::TwoD, BoundaryCondition::Fixed, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_4.Initialize2D(initGrid2D);

    // Apply a rule
    ca2d_4.ApplyRule2D(totalisticRule);

    // Printing out the final state
    cout << "Results of 2D, Fixed, and Moore (totalistic): " << endl;
    ca2d_4.Print();
    cout << endl
         << endl
         << endl;

    // Testing out the 2D, NoBoundary, and Moore conditions (totalisticRule)
    CellularAutomata ca2d_5(10, GridDimension::TwoD, BoundaryCondition::NoBoundary, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_5.Initialize2D(initGrid2D);

    // Apply a rule
    ca2d_5.ApplyRule2D(totalisticRule);

    // Printing out the final state
    cout << "Results of 2D, NoBoundary, and Moore (totalistic): " << endl;
    ca2d_5.Print();
    cout << endl
         << endl
         << endl;

    // Testing out the 2D, Periodic, and Moore conditions (parityRule)
    CellularAutomata ca2d_6(10, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_6.Initialize2D(initGrid2D);

    // Apply a rule
    ca2d_6.ApplyRule2D(parityRule);

    // Priting out the final state
    cout << "Results of 2D, Periodic, and Moore (parity): " << endl;
    ca2d_6.Print();
    cout << endl
         << endl
         << endl;

    // Testing out the 2D, Fixed, and Moore conditions (parityRule)
    CellularAutomata ca2d_7(10, GridDimension::TwoD, BoundaryCondition::Fixed, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_7.Initialize2D(initGrid2D);

    // Apply a rule
    ca2d_7.ApplyRule2D(parityRule);

    // Priting out the final state
    cout << "Results of 2D, Fixed, and Moore (parity): " << endl;
    ca2d_7.Print();
    cout << endl
         << endl
         << endl;

    // Testing out the 2D, NoBoundary, and Moore conditions (parityRule)
    CellularAutomata ca2d_8(10, GridDimension::TwoD, BoundaryCondition::NoBoundary, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_8.Initialize2D(initGrid2D);

    // Apply a rule
    ca2d_8.ApplyRule2D(parityRule);

    // Priting out the final state
    cout << "Results of 2D, NoBoundary, and Moore (parity): " << endl;
    ca2d_8.Print();
    cout << endl
         << endl
         << endl;

    return 0;
}
