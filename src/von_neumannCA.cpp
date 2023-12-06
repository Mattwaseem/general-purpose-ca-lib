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

protected:
    int size_;
    bool use_moore_neighborhood_;
    Grid grid_;

    int getSize() const{
        return size_;
    }

    virtual Grid CalculateNeighborsSum() {
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



class VonNeumannCellularAutomata3D : public CellularAutomata3D {
public:
    VonNeumannCellularAutomata3D(int size, bool use_moore_neighborhood = true)
        : CellularAutomata3D(size, use_moore_neighborhood) {}

private:
    Grid CalculateNeighborsSum() override {
        Grid neighbors_sum(size_, std::vector<std::vector<int>>(size_, std::vector<int>(size_, 0)));

        int size_ = getSize();

        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                for (int k = 0; k < size_; ++k) {
                    int sum = 0;

                    // Add north neighbor
                    sum += grid_[(i - 1 + size_) % size_][j][k];

                    // Add south neighbor
                    sum += grid_[(i + 1) % size_][j][k];

                    // Add west neighbor
                    sum += grid_[i][(j - 1 + size_) % size_][k];

                    // Add east neighbor
                    sum += grid_[i][(j + 1) % size_][k];

                    // Add up neighbor
                    sum += grid_[i][j][(k - 1 + size_) % size_];

                    // Add down neighbor
                    sum += grid_[i][j][(k + 1) % size_];

                    neighbors_sum[i][j][k] = sum;
                }
            }
        }
        return neighbors_sum;
    }
};

// Example usage
int main() {
    int size = 5;

    // Create an instance of VonNeumannCellularAutomata3D
    VonNeumannCellularAutomata3D vonNeumannCA(size);

    // Define a rule function (for example, a simple one that increments the value)
    CellularAutomata3D::RuleFunction ruleFunc = [](int& cell, int neighborsSum) {
        // Increment the cell value if the sum of neighbors is greater than 5
        if (neighborsSum > 5) {
            cell++;
        }
    };

    // Define an initialization function (for example, set random initial values)
    CellularAutomata3D::InitializationFunction initFunc = [](CellularAutomata3D::Grid& grid) {
        // Set random initial values (0 or 1) to the cells
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 1);

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                for (int k = 0; k < grid[i][j].size(); ++k) {
                    grid[i][j][k] = dis(gen);
                }
            }
        }
    };

    // Initialize, apply rules, and run the simulation for a certain number of steps
    vonNeumannCA.Run(5, ruleFunc, initFunc);

    // Print the final state of the grid
    vonNeumannCA.Print();
    return 0;
}

