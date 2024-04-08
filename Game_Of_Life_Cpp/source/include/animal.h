#pragma once

#include "organism.h"
#include <string>
#include <vector>


class Animal : public Organism
{
private:
    int initiative, strength;

protected:
    enum class Directions { LEFT = 0, TOP, RIGHT, BOTTOM, NONE };
    Directions previous_move = Directions::NONE;

public:
    Animal(std::string, int, int);
    Animal(std::string, int, int, int, int);
    ~Animal();

    virtual void action(char**, int, int) override;
    virtual void collision(char**, std::vector<Organism*>&, std::vector<int>&, std::vector<PlaceToAddOrganism>&) override;
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
    void fox_action(char**, std::string, int, int);
    // for turtle
    void turtle_action(std::string, int, int);
    // for antelope
    void antelope_action(std::string, int, int);
    // for cyber_sheep
    void cyber_sheep_action(char**, std::string, int, int);

    Directions& get_previous_move() { return previous_move; }
    const Directions& get_previous_move() const{ return previous_move; }
    void update_previous_move();
    void get_dimensions(char**, int&, int&);
};