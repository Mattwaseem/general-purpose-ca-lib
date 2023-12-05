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
public:
    // Similar structure to MooreCA
    public:
        VonNeumannCA(int width , int height);
        void initializeGrid() override;
        void updateGrid() override;
    VonNeumannCA(int width, int height);
    void initializeGrid() override;
    void updateGrid() override;

private:
    int countActiveNeighbors(int x, int y);
};

class NeuronToNeuronCA
// Neuron to Neuron Cellular Automat
{
private:
    MooreCA mooreCA;
    VonNeumannCA vonNeumannCA;
    bool useMooreNeighborhood;
    std::vector<std::vector<std::vector<std::vector<float>>>> synapticWeights;
    std::vector<std::vector<float>> activationThresholds;
    float plasticityRate;
    float decayRate;
    float ltpThreshold;

    std::vector<std::pair<int, int>> getNeighbors(int x, int y) const;

public:
    NeuronToNeuronCA(int width, int height, bool useMoore);
    void initializeGrid();
    void updateGrid();
    void displayGrid() const;
    void setPlasticityRate(float rate);
    void setDecayRate(float rate);
    void setLtpThreshold(float threshold);
    void setActivationThreshold(int x, int y, float threshold);
};

#endif // CELLULAR_AUTOMATA_H
