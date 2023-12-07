#include <iostream>
#include <vector>
#include <functional>
#include <random>

enum class GridDimension { OneD, TwoD };
enum class BoundaryCondition { Fixed, Periodic, NoBoundary };
enum class NeighborhoodType { Moore, VonNeumann };

class CellularAutomata {
public:
    using Grid1D = std::vector<int>;
    using Grid2D = std::vector<std::vector<int>>;
    using RuleFunction1D = std::function<int(int, int)>; // Function type for 1D
    using RuleFunction2D = std::function<int(int, int)>; // Function type for 2D
    using InitializationFunction1D = std::function<void(Grid1D&)>;
    using InitializationFunction2D = std::function<void(Grid2D&)>;

    CellularAutomata(int size, GridDimension dimension, BoundaryCondition bc, NeighborhoodType nt)
        : size_(size), dimension_(dimension), boundary_condition_(bc), neighborhood_type_(nt) {
        if (dimension == GridDimension::OneD) {
            grid_1d_.resize(size, 0);
        } else {
            grid_2d_.resize(size, std::vector<int>(size, 0));
        }
    }

    void Initialize1D(const InitializationFunction1D& init_func) {
        if (dimension_ == GridDimension::OneD) {
            init_func(grid_1d_);
        } else {
            throw std::runtime_error("Initialization function for 1D grid called on a non-1D automaton");
        }
    }

    void Initialize2D(const InitializationFunction2D& init_func) {
        if (dimension_ == GridDimension::TwoD) {
            init_func(grid_2d_);
        } else {
            throw std::runtime_error("Initialization function for 2D grid called on a non-2D automaton");
        }
    }

    void ApplyRule1D(const RuleFunction1D& rule_func) {
        if (dimension_ == GridDimension::OneD) {
            Grid1D new_grid = grid_1d_;
            for (int i = 0; i < size_; ++i) {
                int neighbors = CalculateNeighbors1D(i);
                new_grid[i] = rule_func(neighbors, grid_1d_[i]);
            }
            grid_1d_ = new_grid;
        } else {
            throw std::runtime_error("Rule function for 1D grid called on a non-1D automaton");
        }
    }

    void ApplyRule2D(const RuleFunction2D& rule_func) {
        if (dimension_ == GridDimension::TwoD) {
            Grid2D new_grid = grid_2d_;
            for (int i = 0; i < size_; ++i) {
                for (int j = 0; j < size_; ++j) {
                    int neighbors = CalculateNeighbors2D(i, j);
                    new_grid[i][j] = rule_func(neighbors, grid_2d_[i][j]);
                }
            }
            grid_2d_ = new_grid;
        } else {
            throw std::runtime_error("Rule function for 2D grid called on a non-2D automaton");
        }
    }

    void Print() const {
        if (dimension_ == GridDimension::OneD) {
            for (int cell : grid_1d_) {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        } else {
            for (const auto &row : grid_2d_) {
                for (int cell : row) {
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

    int CalculateNeighbors1D(int index) const {
        int neighbors = 0;
        for (int di = -1; di <= 1; ++di) {
            if (di == 0) continue; // Skip the center cell
            int ni = index + di;
            // Boundary condition handling for 1D
            if (boundary_condition_ == BoundaryCondition::Periodic) {
                ni = (ni + size_) % size_;
            } else if (boundary_condition_ == BoundaryCondition::NoBoundary) {
                if (ni < 0 || ni >= size_) continue;
            }
            neighbors += grid_1d_[ni];
        }
        return neighbors;
    }

    int CalculateNeighbors2D(int i, int j) const {
        int neighbors = 0;
        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                if (di == 0 && dj == 0) continue; // Skip the center cell
                int ni = i + di;
                int nj = j + dj;
                // Boundary condition handling for 2D
                if (boundary_condition_ == BoundaryCondition::Periodic) {
                    ni = (ni + size_) % size_;
                    nj = (nj + size_) % size_;
                } else if (boundary_condition_ == BoundaryCondition::NoBoundary) {
                    if (ni < 0 || ni >= size_ || nj < 0 || nj >= size_) continue;
                }
                neighbors += grid_2d_[ni][nj];
            }
        }
        return neighbors;
    }
};

int main() {
    int size = 10;
    CellularAutomata ca2D(size, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);

    // Define the initialization function for 2D
    CellularAutomata::InitializationFunction2D init_func_2d = [](CellularAutomata::Grid2D& grid) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 1);

        for (auto &row : grid) {
            for (int &cell : row) {
                cell = distrib(gen);
            }
        }
    };

    // Define the rule function for 2D
    CellularAutomata::RuleFunction2D rule_func_2d = [&ca2D](int neighbors, int current_state) {
        // Example rule: A cell becomes alive (1) if exactly 3 neighbors, otherwise stays the same
        return (neighbors == 3) ? 1 : current_state;
    };

    // Initialize and apply rules to the 2D cellular automaton
    ca2D.Initialize2D(init_func_2d);
    ca2D.ApplyRule2D(rule_func_2d);

    // Print the final state of the grid
    ca2D.Print();

    return 0;
}


/*
#include <iostream>
#include <vector>
#include <functional>
#include <random>

class CellularAutomata3D {
public:
    using Grid = std::vector<std::vector<std::vector<int>>>;
    using RuleFunction = std::function<void(int&, int)>;
    using InitializationFunction = std::function<void(Grid&)>;

    CellularAutomata3D(int size, bool use_moore_neighborhood = true)
        : size_(size), use_moore_neighborhood_(use_moore_neighborhood) {
        grid_.resize(size, std::vector<std::vector<int>>(size, std::vector<int>(size, 0)));
    }

    void Initialize(InitializationFunction init_func) {
        init_func(grid_);
    }

    void ApplyRule(RuleFunction rule_func) {
        Grid new_grid = grid_;
        Grid neighbors_sum = CalculateNeighborsSum();

        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                for (int k = 0; k < size_; ++k) {
                    rule_func(new_grid[i][j][k], neighbors_sum[i][j][k]);
                }
            }
        }

        grid_ = new_grid;
    }

    void Run(int steps, RuleFunction rule_func, InitializationFunction init_func) {
        Initialize(init_func);
        for (int i = 0; i < steps; ++i) {
            ApplyRule(rule_func);
        }
    }

    void Print() const {
        for (const auto &plane : grid_) {
            for (const auto &row : plane) {
                for (int cell : row) {
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

    Grid CalculateNeighborsSum() {
        Grid neighbors_sum(size_, std::vector<std::vector<int>>(size_, std::vector<int>(size_, 0)));

        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                for (int k = 0; k < size_; ++k) {
                    int sum = 0;
                    for (int di = -1; di <= 1; ++di) {
                        for (int dj = -1; dj <= 1; ++dj) {
                            for (int dk = -1; dk <= 1; ++dk) {
                                // Skip the center cell
                                if (di == 0 && dj == 0 && dk == 0) continue;
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

// Example usage
int main() {
    int size = 10; // Define the size of the grid
    CellularAutomata3D ca(size, true); // true for Moore neighborhood

    // Define the initialization function
    CellularAutomata3D::InitializationFunction init_func = [](CellularAutomata3D::Grid& grid) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 1);
        for (auto &plane : grid) {
            for (auto &row : plane) {
                for (int &cell : row) {
                    cell = distrib(gen);
                }
            }
        }
    };

    // Define the rule function
    CellularAutomata3D::RuleFunction rule_func = [](int& cell, int neighbors_sum) {
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
*/