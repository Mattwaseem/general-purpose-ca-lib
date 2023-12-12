#include <iostream>
#include <vector> // used as the data structure that will hold the data for the grid for the CA.
#include <random>
#include <sstream> // print to a string stream and use your -ostream and pipe to a text file.
#include <fstream> // read from a file.
#include "../include/CellularAutomata.h"
#include "../src/cellular_automata.cpp"
using namespace std; // allows the use of std namespace without prefixing (i.e std::vector -> vector)

// Initialize a 1D grid with random values
void initGrid1D(CellularAutomata::Grid1D &grid)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1); // Uniformly distributing the random values 

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
    std::uniform_int_distribution<> dis(0, 1); // Uniformly distributing the random values

    for (auto &row : grid)
    {
        for (auto &cell : row)
        {
            cell = dis(gen); // Randomly set each cell to 0 or 1
        }
    }
}


// Function to print results of 2D cellular automata that use majority rule
void PrintToFile_2D_majority( CellularAutomata &ca,  const std::string &fileName)
{
    std::ofstream outputFile(fileName);

    if (outputFile.is_open())
    {   // Since we want 10 iterations, we will get the grid each time
        for (int iteration = 0; iteration < 10; ++iteration)
        {
            // Access the internal state using the new method
            const CellularAutomata::Grid2D &grid = ca.GetGrid2D();

            // Print the iteration number
            outputFile << "Iteration " << iteration + 1 << ":\n";

            // Print the grid to the file
            for (const auto &row : grid)
            {
                for (int cell : row)
                {
                    outputFile << cell << ' ';
                }
                outputFile << '\n';
            }

            // Apply the rule for the next iteration
            ca.ApplyRule2D(majorityRule);
        } 

        outputFile.close();
        std::cout << "Results saved to file: " << fileName << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}

// Function to print results of 2D cellular automata that use parity rule
void PrintToFile_2D_parity( CellularAutomata &ca,  const std::string &fileName)
{
    std::ofstream outputFile(fileName);

    if (outputFile.is_open())
    {   // Since we want 10 iterations, we will get the grid each time
        for (int iteration = 0; iteration < 10; ++iteration)
        {
            // Access the internal state using the new method
            const CellularAutomata::Grid2D &grid = ca.GetGrid2D();

            // Print the iteration number
            outputFile << "Iteration " << iteration + 1 << ":\n";

            // Print the grid to the file
            for (const auto &row : grid)
            {
                for (int cell : row)
                {
                    outputFile << cell << ' ';
                }
                outputFile << '\n';
            }

            // Apply the rule for the next iteration
            ca.ApplyRule2D(parityRule);
        }

        outputFile.close();
        std::cout << "Results saved to file: " << fileName << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}

// Function to print results of 2D cellular automata that use totalistic rule
void PrintToFile_2D_totalistic( CellularAutomata &ca,  const std::string &fileName)
{
    std::ofstream outputFile(fileName);

    if (outputFile.is_open())
    {   // Since we want 10 iterations, we will get the grid each time
        for (int iteration = 0; iteration < 10; ++iteration)
        {
            // Access the internal state using the new method
            const CellularAutomata::Grid2D &grid = ca.GetGrid2D();

            // Print the iteration number
            outputFile << "Iteration " << iteration + 1 << ":\n";

            // Print the grid to the file
            for (const auto &row : grid)
            {
                for (int cell : row)
                {
                    outputFile << cell << ' ';
                }
                outputFile << '\n';
            }

            // Apply the rule for the next iteration
            ca.ApplyRule2D(totalisticRule);
        }

        outputFile.close();
        std::cout << "Results saved to file: " << fileName << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}

// Function to print results of 1D cellular automata that use majority rule
void PrintToFile_1D_majority( CellularAutomata &ca,  const std::string &fileName)
{
    std::ofstream outputFile(fileName);

    if (outputFile.is_open())
    {   // Since we want 10 iterations, we will get the grid each time
        for (int iteration = 0; iteration < 10; ++iteration)
        {
            // Access the internal state using the new method
            const CellularAutomata::Grid1D &grid = ca.GetGrid1D();

            // Print the iteration number
            outputFile << "Iteration " << iteration + 1 << ":\n";

            // Print the grid to the file
               for(int cell : grid){
                    outputFile << cell << ' ';
               }
               outputFile << "\n";

            // Apply the rule for the next iteration
            ca.ApplyRule1D(majorityRule);
        } 

        outputFile.close();
        std::cout << "Results saved to file: " << fileName << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}

// Function to print results of 1D cellular automata that use parity rule
void PrintToFile_1D_parity( CellularAutomata &ca,  const std::string &fileName)
{
    std::ofstream outputFile(fileName);

    if (outputFile.is_open())
    {   // Since we want 10 iterations, we will get the grid each time
        for (int iteration = 0; iteration < 10; ++iteration)
        {
            // Access the internal state using the new method
            const CellularAutomata::Grid1D &grid = ca.GetGrid1D();

            // Print the iteration number
            outputFile << "Iteration " << iteration + 1 << ":\n";

            // Print the grid to the file
               for(int cell : grid){
                    outputFile << cell << ' ';
               }
               outputFile << "\n";

            // Apply the rule for the next iteration
            ca.ApplyRule1D(parityRule);
        } 

        outputFile.close();
        std::cout << "Results saved to file: " << fileName << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}

// Function to print results of 1D cellular automata that use totalistic rule
void PrintToFile_1D_totalistic( CellularAutomata &ca,  const std::string &fileName)
{
    std::ofstream outputFile(fileName);

    if (outputFile.is_open())
    {   // Since we want 10 iterations, we will get the grid each time
        for (int iteration = 0; iteration < 10; ++iteration)
        {
            // Access the internal state using the new method
            const CellularAutomata::Grid1D &grid = ca.GetGrid1D();

            // Print the iteration number
            outputFile << "Iteration " << iteration + 1 << ":\n";

            // Print the grid to the file
               for(int cell : grid){
                    outputFile << cell << ' ';
               }
               outputFile << "\n";

            // Apply the rule for the next iteration
            ca.ApplyRule1D(totalisticRule);
        } 

        outputFile.close();
        std::cout << "Results saved to file: " << fileName << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}



int main()
{

    // Testing out the 2D, Periodic, and Moore conditions (majorityRule)
    CellularAutomata ca2D(10, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);

    // Initialize the grid
    ca2D.Initialize2D(initGrid2D);

    // Print the final state
    cout << "Results of 2D , Periodic, and Moore (majority): " << endl;
    ca2D.Print();
    cout << endl
         << endl
         << endl;
     string filename1 = "2D_Periodic_Moore.txt";
     PrintToFile_2D_majority(ca2D , filename1);

    // Testing out the 2D , Fixed , and Moore conditions (majorityRule)
    CellularAutomata ca2d_1(10, GridDimension::TwoD, BoundaryCondition::Fixed, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_1.Initialize2D(initGrid2D);

    // Printing out the final state
    cout << "Results of 2D, Fixed, and Moore (majority): " << endl;
    cout << ca2d_1.Print() << endl
         << endl
         << endl;
     string filename2 = "2D_Fixed_Moore.txt";
     PrintToFile_2D_majority(ca2d_1, filename2);

    // Testing out the 2D , NoBoundary , and Moore conditions (majorityRule)
    CellularAutomata ca2d_2(10, GridDimension::TwoD, BoundaryCondition::NoBoundary, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_2.Initialize2D(initGrid2D);

    // Printing out the final state
    cout << "Results of 2D, NoBoundary, and Moore (majority): " << endl;
    ca2d_2.Print(); // formatted output >> printing to a string.
    cout << endl
         << endl
         << endl;
    string filename3 = "2D_NoBoundary_Moore.txt";
     PrintToFile_2D_majority(ca2d_2 , filename3);

    // Testing out the 2D, Periodic, and Moore conditions (totalisticRule)
    CellularAutomata ca2d_3(10, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_3.Initialize2D(initGrid2D);

    // Printing out the final state
    cout << "Results of 2D, Periodic, and Moore (totalistic): " << endl;
    ca2d_3.Print();
    cout << endl
         << endl
         << endl;
     string filename4 = "2D_Periodic_Moore_totalistic.txt";
     PrintToFile_2D_totalistic(ca2d_3 , filename4);

    // Testing out the 2D, Fixed, and Moore conditions (totalisticRule)
    CellularAutomata ca2d_4(10, GridDimension::TwoD, BoundaryCondition::Fixed, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_4.Initialize2D(initGrid2D);

    // Printing out the final state
    cout << "Results of 2D, Fixed, and Moore (totalistic): " << endl;
    ca2d_4.Print();
    cout << endl
         << endl
         << endl;
     string filename5 = "2D_Fixed_Moore_totalistic.txt";
     PrintToFile_2D_totalistic(ca2d_4 , filename5);

    // Testing out the 2D, NoBoundary, and Moore conditions (totalisticRule)
    CellularAutomata ca2d_5(10, GridDimension::TwoD, BoundaryCondition::NoBoundary, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_5.Initialize2D(initGrid2D);

    // Printing out the final state
    cout << "Results of 2D, NoBoundary, and Moore (totalistic): " << endl;
    ca2d_5.Print();
    cout << endl
         << endl
         << endl;
     string filename6 = "2D_NoBoundary_Moore_totalistic.txt";
     PrintToFile_2D_totalistic(ca2d_5, filename6);

    // Testing out the 2D, Periodic, and Moore conditions (parityRule)
    CellularAutomata ca2d_6(10, GridDimension::TwoD, BoundaryCondition::Periodic, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_6.Initialize2D(initGrid2D);

    // Priting out the final state
    cout << "Results of 2D, Periodic, and Moore (parity): " << endl;
    ca2d_6.Print();
    cout << endl
         << endl
         << endl;
     string filename7 = "2D_Periodic_Moore_parity.txt";
     PrintToFile_2D_parity(ca2d_6 , filename7);

    // Testing out the 2D, Fixed, and Moore conditions (parityRule)
    CellularAutomata ca2d_7(10, GridDimension::TwoD, BoundaryCondition::Fixed, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_7.Initialize2D(initGrid2D);

    // Priting out the final state
    cout << "Results of 2D, Fixed, and Moore (parity): " << endl;
    ca2d_7.Print();
    cout << endl
         << endl
         << endl;
     string filename8 = "2D_Fixed_Moore_parity.txt";
     PrintToFile_2D_parity(ca2d_7 , filename8);

    // Testing out the 2D, NoBoundary, and Moore conditions (parityRule)
    CellularAutomata ca2d_8(10, GridDimension::TwoD, BoundaryCondition::NoBoundary, NeighborhoodType::Moore);

    // Initializing the grid
    ca2d_8.Initialize2D(initGrid2D);

    // Priting out the final state
    cout << "Results of 2D, NoBoundary, and Moore (parity): " << endl;
    ca2d_8.Print();
    cout << endl
         << endl
         << endl;
     string filename9 = "2D_NoBoundary_Moore_paity.txt";
     PrintToFile_2D_parity(ca2d_8 , filename9);

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

    // Test 4: 1D, Periodic, Von Neumann (parityRule)
    CellularAutomata ca1D_periodic_vn(10, GridDimension::OneD, BoundaryCondition::Periodic, NeighborhoodType::VonNeumann);
    ca1D_periodic_vn.Initialize1D(initGrid1D);
    ca1D_periodic_vn.ApplyRule1D(parityRule);
    cout << "1D, Periodic, VN (parityRule): " << endl;
    ca1D_periodic_vn.Print();
    cout << endl
         << endl;
     string filename10 = "1D_Periodic_VN_parity.txt";
     PrintToFile_1D_parity(ca1D_periodic_vn,filename10);

    // Test 5: 1D, Fixed, Von Neumann (parityRule)
    CellularAutomata ca1D_fixed_vn(10, GridDimension::OneD, BoundaryCondition::Fixed, NeighborhoodType::VonNeumann);
    ca1D_fixed_vn.Initialize1D(initGrid1D);
    ca1D_fixed_vn.ApplyRule1D(parityRule);
    cout << "1D, Fixed, VN (parityRule): " << endl;
    ca1D_fixed_vn.Print();
    cout << endl
         << endl;
     string filename11 = "1D_Fixed_VN_parity.txt";
     PrintToFile_1D_parity(ca1D_fixed_vn,filename11);

    // Test 6: 1D, NoBoundary, Von Neumann (parityRule)
    CellularAutomata ca1D_nobound_vn(10, GridDimension::OneD, BoundaryCondition::NoBoundary, NeighborhoodType::VonNeumann);
    ca1D_nobound_vn.Initialize1D(initGrid1D);
    ca1D_nobound_vn.ApplyRule1D(parityRule);
    cout << "1D, NoBoundary, VN (parityRule): " << endl;
    ca1D_nobound_vn.Print();
    cout << endl
         << endl;
     string filename12 = "1D_NoBoundary_VN_parity.txt";
     PrintToFile_1D_parity(ca1D_nobound_vn, filename12);

    // Test 7: 1D, Periodic, Von Neumann (totalisticRule_1D)
    CellularAutomata ca1D_periodic_vn2(10, GridDimension::OneD, BoundaryCondition::Periodic, NeighborhoodType::VonNeumann);
    ca1D_periodic_vn2.Initialize1D(initGrid1D);
    ca1D_periodic_vn2.ApplyRule1D(totalisticRule_1D);
    cout << "1D, Periodic, VN (totalisticRule_1D): " << endl;
    ca1D_periodic_vn2.Print();
    cout << endl
         << endl;
     string filename13 = "1D_Periodic_VN_totalistic.txt";
     PrintToFile_1D_totalistic(ca1D_periodic_vn2,filename13);

    // Test 8: 1D, Fixed, Von Neumann (totalisticRule_1D)
    CellularAutomata ca1D_fixed_vn2(10, GridDimension::OneD, BoundaryCondition::Fixed, NeighborhoodType::VonNeumann);
    ca1D_fixed_vn2.Initialize1D(initGrid1D);
    ca1D_fixed_vn2.ApplyRule1D(totalisticRule_1D);
    cout << "1D, Fixed, VN (totalisticRule_1D): " << endl;
    ca1D_fixed_vn2.Print();
    cout << endl
         << endl;
     string filename14 = "1D_Fixed_VN_totalistic.txt";
     PrintToFile_1D_totalistic(ca1D_fixed_vn2,filename14);

    // Test 9: 1D, NoBoundary, Von Neumann (totalisticRule_1D)
    CellularAutomata ca1D_nobound_vn2(10, GridDimension::OneD, BoundaryCondition::NoBoundary, NeighborhoodType::VonNeumann);
    ca1D_nobound_vn2.Initialize1D(initGrid1D);
    ca1D_nobound_vn2.ApplyRule1D(totalisticRule_1D);
    cout << "1D, NoBoundary, VN (totalisticRule_1D): " << endl;
    ca1D_nobound_vn2.Print();
    cout << endl
         << endl;
     string filename15 = "1D_NoBoundary_VN_totalistic.txt";
     PrintToFile_1D_totalistic(ca1D_nobound_vn2,filename15);

    // Test 10: 1D, Periodic, Von Neumann (majorityRule_1D)
    CellularAutomata ca1D_periodic_vn3(10, GridDimension::OneD, BoundaryCondition::Periodic, NeighborhoodType::VonNeumann);
    ca1D_periodic_vn3.Initialize1D(initGrid1D);
    ca1D_periodic_vn3.ApplyRule1D(majorityRule_1D);
    cout << "1D, Periodic, VN (majorityRule_1D): " << endl;
    ca1D_periodic_vn3.Print();
    cout << endl
         << endl;
     string filename16 = "1D_Periodic_VN_majority.txt";
     PrintToFile_1D_majority(ca1D_periodic_vn3,filename16);

    // Test 11: 1D, Fixed, Von Neumann (majorityRule_1D)
    CellularAutomata ca1D_fixed_vn3(10, GridDimension::OneD, BoundaryCondition::Fixed, NeighborhoodType::VonNeumann);
    ca1D_fixed_vn3.Initialize1D(initGrid1D);
    ca1D_fixed_vn3.ApplyRule1D(majorityRule_1D);
    cout << "1D, Fixed, VN (majorityRule_1D): " << endl;
    ca1D_fixed_vn3.Print();
    cout << endl
         << endl;
     string filename17 = "1D_Fixed_VN_majority.txt";
     PrintToFile_1D_majority(ca1D_fixed_vn3,filename17);

    // Test 12: 1D, NoBoundary, Von Neumann (majorityRule_1D)
    CellularAutomata ca1D_nobound_vn3(10, GridDimension::OneD, BoundaryCondition::NoBoundary, NeighborhoodType::VonNeumann);
    ca1D_nobound_vn3.Initialize1D(initGrid1D);
    ca1D_nobound_vn3.ApplyRule1D(majorityRule_1D);
    cout << "1D, NoBoundary, VN (majorityRule_1D): " << endl;
    ca1D_nobound_vn3.Print();
    cout << endl
         << endl;
     string filename18 = "1D_NoBoundary_VN_majority.txt";
     PrintToFile_1D_majority(ca1D_nobound_vn3,filename18);

    return 0;
}
