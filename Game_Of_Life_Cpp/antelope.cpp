#include "antelope.h"
#include <iostream>

Antelope::Antelope(int row, int column)
    : Animal("antelope", row, column)
{
    get_strength() = 4;
    get_initiative() = 4;
    get_type() = OrganismType::Antelope;
}

Antelope::Antelope(int strength, int initiative, int row, int column)
    : Animal("sheep", row, column)
{
    get_strength() = strength;
    get_initiative() = initiative;
}

Antelope::~Antelope() {}

void Antelope::action(char** board, int height, int width)
{
    using std::cout;
    using std::endl;

    int row = this->get_position_row(), column = this->get_position_column();
    Directions direction = static_cast<Directions>(rand() % 4);

    // Find some good direction where we can go
    while (true)
    {
        if (row > 0 && direction == Directions::TOP) break;
        else if (column < width - 1 && direction == Directions::RIGHT) break;
        else if (column > 0 && direction == Directions::LEFT) break;
        else if (row < height - 1 && direction == Directions::BOTTOM) break;
        direction = static_cast<Directions>(rand() % 4);
    }

    int multiplier = rand() % 2 + 1;
    cout << this->get_name() << " moves from (" << row << ", " << column << ") to: ";

    switch (direction)
    {
    case Directions::TOP:
        if (row - multiplier >= 0) get_position_row() -= multiplier;
        else get_position_row()--;
        break;
    case Directions::BOTTOM:
        if (row + multiplier <= height - 1) get_position_row() += multiplier;
        else get_position_row()++;
        break;
    case Directions::LEFT:
        if (column - multiplier >= 0) get_position_column() -= multiplier;
        else get_position_column()--;
        break;
    case Directions::RIGHT:
        if (column + multiplier <= width - 1) get_position_column() += multiplier;
        else get_position_column()++;
        break;
    }
    cout << " (" << get_position_row() << ", " << get_position_column() << ")\n";
}