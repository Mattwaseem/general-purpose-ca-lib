#include <iostream>
#include <vector> // used as the data structure that will hold the data for the grid for the CA.
#include <random>
#include "../Include/CellularAutomata.h"
#include "../src/cellular_automata.cpp"
using namespace std; // allows the use of std namespace without prefixing (i.e std::vector -> vector)

// Initialize a 1D grid with random values
void initGrid1D(CellularAutomata::Grid1D &grid)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (auto &cell : grid)
    {
        cell = dis(gen); // Randomly set each cell to 0 or 1
    }
}

// Example rule for 1D Cellular Automata
int rule1DExample(int neighbors, int currentState)
{
    // Simple rule: If the number of neighbors is greater than 1, set to 1, else 0
    return neighbors > 1 ? 1 : 0;
}

// initilizing a 2D CA
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

    //________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
    // Test 1: 1D, Periodic, Moore
    CellularAutomata ca1D_periodic_moore(10, GridDimension::OneD, BoundaryCondition::Periodic, NeighborhoodType::Moore);
    ca1D_periodic_moore.Initialize1D(initGrid1D);
    ca1D_periodic_moore.ApplyRule1D(rule1DExample);
    cout << "1D, Periodic, Moore: " << endl;
    ca1D_periodic_moore.Print();
    cout << endl
         << endl;

    // Test 2: 1D, Fixed, Moore
    CellularAutomata ca1D_fixed_moore(10, GridDimension::OneD, BoundaryCondition::Fixed, NeighborhoodType::Moore);
    ca1D_fixed_moore.Initialize1D(initGrid1D);
    ca1D_fixed_moore.ApplyRule1D(rule1DExample);
    cout << "1D, Fixed, Moore: " << endl;
    ca1D_fixed_moore.Print();
    cout << endl
         << endl;

    // Test 3: 1D, NoBoundary, Moore
    CellularAutomata ca1D_noboundary_moore(10, GridDimension::OneD, BoundaryCondition::NoBoundary, NeighborhoodType::Moore);
    ca1D_noboundary_moore.Initialize1D(initGrid1D);
    ca1D_noboundary_moore.ApplyRule1D(rule1DExample);
    cout << "1D, NoBoundary, Moore: " << endl;
    ca1D_noboundary_moore.Print();
    cout << endl
         << endl;

    return 0;
}
