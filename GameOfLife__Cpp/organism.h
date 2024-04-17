#pragma once

#include <vector>
#include <string>

enum class OrganismType : char { Wolf = 'w', Sheep='s', Fox='f', Turtle='t', 
    Antelope='a', CyberSheep='c', Grass='g', SowThistle='S', Guarana='U', Belladonna='B',
    SosnoskyHogweed='O', Human = 'H',
};
const int EAT_GUARANA_STRENGTH_INCERASE = 3;

struct PlaceToAddOrganism
{
    OrganismType type;
    std::string name;
    int new_row, new_column;
};

// abstract class for all organisms
class Organism
{
private:
    int position_row, position_column, age;
    char character;
    std::string name;
    int index;
    static int num_of_organisms;
    OrganismType organism_type;

public:
    Organism(int, int, std::string);
    ~Organism();

    virtual void action(char**, int, int) = 0;
    virtual void collision(char**, std::vector<Organism*>&, std::vector<int>&, std::vector<PlaceToAddOrganism>&) = 0;
    virtual char draw() const = 0;
    virtual const int& get_initiative() const = 0;
    virtual const int& get_strength() const = 0;

    // Getters and setters
    int& get_position_row() { return position_row; }
    const int& get_position_row() const { return position_row; }
    int& get_position_column() { return position_column; }
    const int& get_position_column() const { return position_column; }
    char& get_character() { return character; }
    const char& get_character() const { return character; }
    int& get_age() { return age; }
    const int& get_age() const { return age; }

    std::string& get_name() { return name; }
    const std::string& get_name() const { return name; }
    int& get_index() { return index; }
    const int& get_index() const { return index; }
    OrganismType& get_type() { return organism_type; }
    const OrganismType& get_type() const { return organism_type; }
};