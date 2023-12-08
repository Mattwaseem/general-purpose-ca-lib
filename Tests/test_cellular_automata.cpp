#include <iostream>
#include <vector> // used as the data structure that will hold the data for the grid for the CA.
#include <random>
#include "../Include/CellularAutomata.h"
#include "../src/cellular_automata.cpp"
using namespace std; // allows the use of std namespace without prefixing (i.e std::vector -> vector)

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
