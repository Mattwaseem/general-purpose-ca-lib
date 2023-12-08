#include <iostream>
#include <vector>
#include <functional>
#include <random>

class CellularAutomata3D
{
public:
    using Grid = std::vector<std::vector<std::vector<int>>>;
    using RuleFunction = std::function<void(int &, int)>;
    using InitializationFunction = std::function<void(Grid &)>;

    CellularAutomata3D(int size, bool use_moore_neighborhood = true)
        : size_(size), use_moore_neighborhood_(use_moore_neighborhood)
    {
        grid_.resize(size, std::vector<std::vector<int>>(size, std::vector<int>(size, 0)));
    }

    void Initialize(InitializationFunction init_func)
    {
        init_func(grid_);
    }
    // make modifications here to incldue totalistic rule as well and give the option of choosin - area of focus
    // or other.
    // if else switc statement/class inheritance -
    // define the rule functions
    void ApplyRule(RuleFunction rule_func)
    {
        Grid new_grid = grid_;
        Grid neighbors_sum = CalculateNeighborsSum();

        for (int i = 0; i < size_; ++i)
        {
            for (int j = 0; j < size_; ++j)
            {
                for (int k = 0; k < size_; ++k)
                {
                    rule_func(new_grid[i][j][k], neighbors_sum[i][j][k]);
                }
            }
        }

        grid_ = new_grid;
    }

    void Run(int steps, RuleFunction rule_func, InitializationFunction init_func)
    {
        Initialize(init_func);
        for (int i = 0; i < steps; ++i)
        {
            ApplyRule(rule_func);
        }
    }

    void Print() const
    {
        for (const auto &plane : grid_)
        {
            for (const auto &row : plane)
            {
                for (int cell : row)
                {
                    std::cout << cell << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
    }

private:
    int size_;
    bool use_moore_neighborhood_;
    Grid grid_;
    // understand this and make sure we can choose between the moors and vonnouman. - area of focus.
    Grid CalculateNeighborsSum()
    {
        Grid neighbors_sum(size_, std::vector<std::vector<int>>(size_, std::vector<int>(size_, 0)));

        for (int i = 0; i < size_; ++i)
        {
            for (int j = 0; j < size_; ++j)
            {
                for (int k = 0; k < size_; ++k)
                {
                    int sum = 0;
                    for (int di = -1; di <= 1; ++di)
                    {
                        for (int dj = -1; dj <= 1; ++dj)
                        {
                            for (int dk = -1; dk <= 1; ++dk)
                            {
                                // Skip the center cell
                                if (di == 0 && dj == 0 && dk == 0)
                                    continue;
                                int ni = (i + di + size_) % size_;
                                int nj = (j + dj + size_) % size_;
                                int nk = (k + dk + size_) % size_;
                                sum += grid_[ni][nj][nk];
                            }
                        }
                    }
                    neighbors_sum[i][j][k] = sum;
                }
            }
        }
        return neighbors_sum;
    }
};
// void new_funct(int i)
// Example usage
int main()
{
    int size = 10;                     // Define the size of the grid
    CellularAutomata3D ca(size, true); // true for Moore neighborhood

    // Define the initialization function
    CellularAutomata3D::InitializationFunction init_func = [](CellularAutomata3D::Grid &grid)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 1);
        for (auto &plane : grid)
        {
            for (auto &row : plane)
            {
                for (int &cell : row)
                {
                    cell = distrib(gen);
                }
            }
        }
    };
    // you can change these to specific rule rule functions.
    //
    // Define the rule function
    CellularAutomata3D::RuleFunction rule_func = [](int &cell, int neighbors_sum)
    {
        // Implement your rule here. This is a simple example that flips the cell state based on neighbors sum
        cell = (neighbors_sum % 2 == 0) ? 1 : 0;
    };

    // Run the cellular automata
    int steps = 5; // Define the number of steps to simulate
    ca.Run(steps, rule_func, init_func);

    // Print the final state of the grid
    ca.Print();

    return 0;
}
