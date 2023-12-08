#include "CellularAutomata.h"

// Constructor
CellularAutomata::CellularAutomata(int size, GridDimension dimension, BoundaryCondition bc, NeighborhoodType nt)
    : size_(size), dimension_(dimension), boundary_condition_(bc), neighborhood_type_(nt) {
    if (dimension == GridDimension::OneD) {
        grid_1d_.resize(size, 0);
    } else {
        grid_2d_.resize(size, std::vector<int>(size, 0));
    }
}

// Initialize1D
void CellularAutomata::Initialize1D(const InitializationFunction1D& init_func) {
    if (dimension_ != GridDimension::OneD) {
        throw std::runtime_error("Initialization function for 1D grid called on a non-1D automaton");
    }
    init_func(grid_1d_);
}

// Initialize2D
void CellularAutomata::Initialize2D(const InitializationFunction2D& init_func) {
    if (dimension_ != GridDimension::TwoD) {
        throw std::runtime_error("Initialization function for 2D grid called on a non-2D automaton");
    }
    init_func(grid_2d_);
}

// ApplyRule1D
void CellularAutomata::ApplyRule1D(const RuleFunction1D& rule_func) {
    if (dimension_ != GridDimension::OneD) {
        throw std::runtime_error("Rule function for 1D grid called on a non-1D automaton");
    }
    Grid1D new_grid = grid_1d_;
    for (int i = 0; i < size_; ++i) {
        int neighbors = CalculateNeighbors1D(i);
        new_grid[i] = rule_func(neighbors, grid_1d_[i]);
    }
    grid_1d_ = std::move(new_grid);
}

// ApplyRule2D
void CellularAutomata::ApplyRule2D(const RuleFunction2D& rule_func) {
    if (dimension_ != GridDimension::TwoD) {
        throw std::runtime_error("Rule function for 2D grid called on a non-2D automaton");
    }
    Grid2D new_grid = grid_2d_;
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            int neighbors = CalculateNeighbors2D(i, j);
            new_grid[i][j] = rule_func(neighbors, grid_2d_[i][j]);
        }
    }
    grid_2d_ = std::move(new_grid);
}

// Print
void CellularAutomata::Print() const {
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

// CalculateNeighbors1D // update for Moore's neighborhood
int CellularAutomata::CalculateNeighbors1D(int index) const {
    int neighbors = 0;
    for (int di = -1; di <= 1; ++di) {
        if (di == 0) continue;  // Skip the center cell
        int ni = index + di;

        // Boundary condition handling
        switch (boundary_condition_) {
            case BoundaryCondition::Periodic:
                ni = (ni + size_) % size_;
                break;
            case BoundaryCondition::Fixed:
                if (ni < 0 || ni >= size_) ni = index; // Assume boundary cells are in the same state as the current cell
                break;
            case BoundaryCondition::NoBoundary:
                if (ni < 0 || ni >= size_) continue;
                break;
        }

        neighbors += grid_1d_[ni];
    }
    return neighbors;
}

// CalculateNeighbors2D
// Moore neighborhood logic (all eight neighbors)
// This is the default case in your current implementation
int CellularAutomata::CalculateNeighbors2D(int i, int j) const {
    int neighbors = 0;
    for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) continue;  // Skip the center cell

            // For Von Neumann neighborhood, consider only direct neighbors
            if (neighborhood_type_ == NeighborhoodType::VonNeumann && abs(di) + abs(dj) > 1) {
                continue;
            }

            int ni = i + di;
            int nj = j + dj;

            // Boundary condition handling
            switch (boundary_condition_) {
                case BoundaryCondition::Periodic:
                    ni = (ni + size_) % size_;
                    nj = (nj + size_) % size_;
                    break;
                case BoundaryCondition::Fixed:
                    if (ni < 0 || ni >= size_ || nj < 0 || nj >= size_) continue;
                    break;
                case BoundaryCondition::NoBoundary:
                    if (ni < 0 || ni >= size_ || nj < 0 || nj >= size_) continue;
                    break;
            }

            neighbors += grid_2d_[ni][nj];
        }
    }
    return neighbors;
}

#include <random>

void initGrid2D(CellularAutomata::Grid2D& grid) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (auto& row : grid) {
        for (auto& cell : row) {
            cell = dis(gen); // Randomly set each cell to 0 or 1
        }
    }
}


int majorityRule(int neighbors, int currentState) {
    return (neighbors > 4) ? 1 : 0;
}

int totalisticRule(int neighbors, int currentState) {
    return (neighbors == 3) ? 1 : 0;
}

int parityRule(int neighbors, int currentState) {
    return (neighbors % 2 == 0) ? 1 : 0;
}

int main() {
    CellularAutomata ca2D(10, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);

    // Initialize the grid
    ca2D.Initialize2D(initGrid2D);

    // Apply a rule
    ca2D.ApplyRule2D(majorityRule);

    // Print the final state
    ca2D.Print();

    return 0;
}

