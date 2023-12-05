#ifndef CELLULAR_AUTOMATA_H
#define CELLULAR_AUTOMATA_H

#include <vector>

// Base class for Cellular Automata
class CellularAutomata
{
protected:
    int width, height;
    std::vector<std::vector<int>> grid;

public:
    CellularAutomata(int width, int height);
    virtual void initializeGrid();
    virtual void displayGrid() const;
    virtual void updateGrid() = 0;
};



// Specific implementation for Moore's Neighborhood
class MooreCA : public CellularAutomata
{
public:
    MooreCA(int width, int height);
    void initializeGrid() override;
    void updateGrid() override;

private:
    int countActiveNeighbors(int x, int y);
};



// Specific implementation for Von Neumann's Neighborhood (if you have one)
class VonNeumannCA : public CellularAutomata
{
    // Similar structure to MooreCA
    public:
        VonNeumannCA(int width , int height);
        void initializeGrid() override;
        void updateGrid() override;
};

#endif // CELLULAR_AUTOMATA_H
