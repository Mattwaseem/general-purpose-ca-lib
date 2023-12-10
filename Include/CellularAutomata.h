// Include/CellularAutomata.h
#pragma once       // A preprocessor directive to prevent multiple inclusions of the header file during compilation.
#ifndef CELL_AUT_H // Include guard (if Cell_Aut_H not include yet define it and continue)
//- to prevent multiple inclusions of the header file during compilation.
#define CELL_AUT_H // header guard (proceed with including the header content )

#include <iostream>
#include <vector>
#include <functional>
#include <random>

// Enum declarations -> enumaration used to represent a set of configuration for the CA library
// Name constant rather than generic numbers were use to make the code more readable and understandable.

// Enumeration class declaration for grid dimensions of the CA
enum class GridDimension
{
    OneD,
    TwoD
};

// Enumeration class declaration for boundary conditions of the CA
enum class BoundaryCondition
{
    Fixed,
    Periodic,
    NoBoundary
};

// Enumeration class declaration for neighborhood type of the CA
enum class NeighborhoodType
{
    Moore,
    VonNeumann
};

// The core of the CA library: the CellularAutomata class.
// CellularAutomata class declaration
class CellularAutomata
{
public:
    // type aliases/defintion for 1D and 2D grids using standard vector as the primary data structure.
    using Grid1D = std::vector<int>;
    using Grid2D = std::vector<std::vector<int>>;

    // These are rule function types that take in the current state and the number of neighbors and return the new state.
    // they represent the rules that will be used to update the state of a cell based on its current state and the number of neighbors.
    using RuleFunction1D = std::function<int(int, int)>;
    using RuleFunction2D = std::function<int(int, int)>;

    // These are function types that take in a reference to the grid and initialize it.
    // by initilization the grid they set up the initial state of the CA.
    using InitializationFunction1D = std::function<void(Grid1D &)>; // defined as a function pointer (std::function).
    using InitializationFunction2D = std::function<void(Grid2D &)>;

    // Declaration of the member function to retrieve the 2D grid state
    const Grid2D &getGrid2D() const;

    // Constructor for the CellularAutomata class.
    // It takes in the size of the grid, the grid dimension, the boundary condition, and the neighborhood types and
    // initializes the member variables accordingly and generate an instance of the class CA.
    CellularAutomata(int size, GridDimension dimension, BoundaryCondition bc, NeighborhoodType nt);

    // Member functions for the CellularAutomata class.

    // These member functions are used to initialize the grid (1D/2D).
    void Initialize1D(const InitializationFunction1D &init_func);
    void Initialize2D(const InitializationFunction2D &init_func);
    // These member functions are used to apply the rules to the grid (1D/2D) to update the state of the CA.
    void ApplyRule1D(const RuleFunction1D &rule_func);
    void ApplyRule2D(const RuleFunction2D &rule_func);

    // This is the display function which prints the current state of the CA to the standard output/terminal
    void Print() const;

private: // private members of the CellularAutomata class that will not be accesible outside of the class.
    // represent the size of the grid in 1D it is number of cells and in 2D it is number of rows and columns.
    int size_;
    // A variable that stores the dimensionality of the grid (1D/2D) as defined by the enum class GridDimension.
    GridDimension dimension_;
    // The variable that holds the type of boundary condition as defined by the enum class BoundaryCondition.
    BoundaryCondition boundary_condition_;
    // The variable that holds the type of neighborhood as defined by the enum class NeighborhoodType.
    NeighborhoodType neighborhood_type_;
    // The data structures that store the current state of the CA in the grid
    Grid1D grid_1d_; // standard vector (AKA dynamic array) that contains 1D state of the CA
    Grid2D grid_2d_; // A vector of vectors from the standard library that contains 2D state of the CA

    // vectors are used to store the state of the CA because they automatically resize and dynamically manage
    // own memory. The also handle their own resizing.

    // These are private member functions that are used to calculate the number of neighbors for a given cell
    // CalculateNeighbors1D(int index) const - calculate the number of active neighbors around a given 1D grid
    // it takes the index of the cell and returns the count of neighbors based on specific neighborhood type
    // and boundary condition
    int CalculateNeighbors1D(int index) const;

    // CalculateNeighbors2D(int i, int j) const - calculate the number of active neighbors around a given 2D grid
    int CalculateNeighbors2D(int i, int j) const;
};

#endif // CELL_AUT_H - marks the end of the header guard conditional
