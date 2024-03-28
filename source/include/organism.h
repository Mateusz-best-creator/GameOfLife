#pragma once

// abstract class for all organisms
class Organism
{
private:
    int strength, initiative, position_x, position_y;

public:
    Organism();
    ~Organism();
    
    virtual void action() = 0;
    virtual void collision() = 0;
    virtual char draw() = 0;
};