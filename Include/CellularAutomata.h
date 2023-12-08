// Include/CellularAutomata.h

#ifndef CELL_AUT_H
#define CELL_AUT_H

#include <iostream>
#include <vector>
#include <functional>
#include <random>

// Enum declarations
enum class GridDimension { OneD, TwoD };
enum class BoundaryCondition { Fixed, Periodic, NoBoundary };
enum class NeighborhoodType { Moore, VonNeumann };

// CellularAutomata class declaration
class CellularAutomata {
public:
    using Grid1D = std::vector<int>;
    using Grid2D = std::vector<std::vector<int>>;
    using RuleFunction1D = std::function<int(int, int)>;
    using RuleFunction2D = std::function<int(int, int)>;
    using InitializationFunction1D = std::function<void(Grid1D&)>;
    using InitializationFunction2D = std::function<void(Grid2D&)>;

    CellularAutomata(int size, GridDimension dimension, BoundaryCondition bc, NeighborhoodType nt);
    void Initialize1D(const InitializationFunction1D& init_func);
    void Initialize2D(const InitializationFunction2D& init_func);
    void ApplyRule1D(const RuleFunction1D& rule_func);
    void ApplyRule2D(const RuleFunction2D& rule_func);
    void Print() const;

private:
    int size_;
    GridDimension dimension_;
    BoundaryCondition boundary_condition_;
    NeighborhoodType neighborhood_type_;
    Grid1D grid_1d_;
    Grid2D grid_2d_;

    int CalculateNeighbors1D(int index) const;
    int CalculateNeighbors2D(int i, int j) const;
};

#endif // CELL_AUT_H
