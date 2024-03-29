#pragma once

#include "organism.h"
#include <string>

class Animal : public Organism
{
private:
    std::string name;
    char character;
    int strength, initiative;
    

public:
    Animal(std::string, int, int);
    ~Animal();

    virtual void action() override;
    virtual void collision() override;
    virtual char draw() const override;

    char& get_character();
    const char& get_character() const;
    int& get_initiative();
    const int& get_initiative() const;

};