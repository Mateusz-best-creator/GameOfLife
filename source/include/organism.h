#pragma once

// abstract class for all organisms
class Organism
{
private:
    int position_row, position_column;
    char character;

public:
    Organism(int, int, char);
    ~Organism();
    
    virtual void action() = 0;
    virtual void collision() = 0;
    virtual char draw() const = 0;
    virtual const int& get_initiative() const = 0;

    // Getters and setters
    int& get_position_row() { return position_row; }
    const int& get_position_row() const { return position_row; }
    int& get_position_column() { return position_column; }
    const int& get_position_column() const { return position_column; }
    char& get_character() { return character; }
    const char& get_character() const { return character; }
};