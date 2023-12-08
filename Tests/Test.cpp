#Include <cellular_automata.cpp>


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

