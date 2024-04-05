#pragma once

#include "organism.h"
#include <string>
#include <vector>


class Animal : public Organism
{
private:
    int initiative, strength;
    int previous_move = -1;

public:
    Animal(std::string, int, int);
    ~Animal();

    virtual void action(int, int) override;
    virtual void collision(char**, std::vector<Organism*>&) override;
    virtual char draw() const override;

    int& get_initiative() { return initiative; }
    const int& get_initiative() const { return initiative; }
    int& get_strength() { return strength; }
    const int& get_strength() const { return strength; }

    /*
    All actions performed by different animal species
    */
    // For wolf and sheep
    void default_action(std::string, int, int);
    // for fox
    void fox_action(std::string, int, int);
    // for turtle
    void turtle_action(std::string, int, int);
    // for antelope
    void antelope_action(std::string, int, int);
    // for cyber_sheep
    void cyber_sheel_action(std::string, int, int);
};