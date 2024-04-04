#pragma once

#include <vector>
#include <string>

// abstract class for all organisms
class Organism
{
private:
    int position_row, position_column;
    char character;
    std::string name;

public:
    Organism(int, int, std::string);
    ~Organism();
    
    virtual void action(int, int) = 0;
    virtual void collision(char**, std::vector<Organism*>&) = 0;
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

    std::string& get_name() { return name; }
    const std::string& get_name() const { return name; }
};