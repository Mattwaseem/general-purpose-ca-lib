#ifndef CELLULAR_AUTOMATA_H
#define CELLULAR_AUTOMATA_H

#include <vector>
#include <iostream>
#include <vector>
#include <functional>
#include <random>

// how does enumerate know what is oneD, and TwoD and how does it implement this
enum class GridDimension
{
    OneD,
    TwoD
};
// how does enumerate know what is Fixed, Periodic and how does it implement this
enum class BoundaryCondition
{
    Fixed,
    Periodic,
    NoBoundary
};
// how does enumerate know what is Moore and VonNeumann and how does it implement this
enum class NeighborhoodType
{
    Moore,
    VonNeumann
};

class CellularAutomata
{
public:
    using Grid1D = std::vector<int>;
    using Grid2D = std::vector<std::vector<int>>;
    using RuleFunction1D = std::function<void(Grid1D &)>;
    using RuleFunction2D = std::function<void(Grid2D &)>;
    using InitializationFunction1D = std::function<void(Grid1D &)>;
    using InitializationFunction2D = std::function<void(Grid2D &)>;

    CellularAutomata(int size, GridDimension dimension, BoundaryCondition bc, NeighborhoodType nt)
        : size_(size), dimension_(dimension), boundary_condition_(bc), neighborhood_type_(nt)
    {
        if (dimension == GridDimension::OneD)
        {
            grid_1d_.resize(size, 0);
        }
        else
        {
            grid_2d_.resize(size, std::vector<int>(size, 0));
        }
    }

    void Initialize2D(InitializationFunction2D init_func)
    {
        if (dimension_ == GridDimension::TwoD)
        {
            init_func(grid_2d_);
        }
        else
        {
            throw std::runtime_error("Initialization function for 2D grid called on a non-2D automaton");
        }
    }

    void ApplyRule2D(RuleFunction2D rule_func)
    {
        if (dimension_ == GridDimension::TwoD)
        {
            rule_func(grid_2d_);
        }
        else
        {
            throw std::runtime_error("Rule function for 2D grid called on a non-2D automaton");
        }
    }

    void Print() const
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

private:
    int size_;
    GridDimension dimension_;
    BoundaryCondition boundary_condition_;
    NeighborhoodType neighborhood_type_;
    Grid1D grid_1d_;
    Grid2D grid_2d_;

    int CalculateNeighbors2D(int i, int j)
    {
        int neighbors = 0;
        for (int di = -1; di <= 1; ++di)
        {
            for (int dj = -1; dj <= 1; ++dj)
            {
                if (di == 0 && dj == 0)
                    continue; // Skip the center cell

                int ni = i + di;
                int nj = j + dj;

                // Boundary condition handling
                if (boundary_condition_ == BoundaryCondition::Periodic)
                {
                    ni = (ni + size_) % size_;
                    nj = (nj + size_) % size_;
                }
                else if (boundary_condition_ == BoundaryCondition::NoBoundary)
                {
                    if (ni < 0 || ni >= size_ || nj < 0 || nj >= size_)
                        continue;
                }

                neighbors += grid_2d_[ni][nj];
            }
        }
        return neighbors;
    }
};

#endif // CELLULAR_AUTOMATA_H
