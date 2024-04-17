#include "plant.h"
#include <iostream>
#include "animal.h"

Plant::Plant(const std::string& n, int row, int column)
    : Organism(row, column, n)
{
    std::string name = get_name();
    if (name == "Grass")
        strength = 0;
    else if (name == "Sow_thistle")
        strength = 0;
    else if (name == "Guarana")
        strength = 0;
    else if (name == "Belladonna")
        strength = 99;
    else if (name == "Sosnowsky_hogweed")
        strength = 10;
}

Plant::Plant(const std::string& n, int s, int i, int row, int column)
    : Organism(row, column, n)
{
    strength = s;
    get_position_row() = row;
    get_position_column() = column;
}

Plant::~Plant()
{

}

void Plant::action(char** board, int height, int width)
{
    std::string name = this->get_name();
    this->action(board, height,  width);
}

void Plant::default_action()
{
    using std::cout;
    using std::endl;

    double d = (rand() % 100 + 1) / 100.0;
    if (d <= probability)
        can_sow = true;
    else
        can_sow = false;
}

void getDimensions(char** board, int& height, int& width)
{
    int h = 0, w = 0;
    while (board[h] != NULL)
        h++;
    while (board[0][w] != '\0')
        w++;
    height = h;
    width = w;
}

/*
    For plants here we will try to create another plants
*/
void Plant::collision(char** board, std::vector<Organism*>& organisms, std::vector<int>& indexes_to_remove, std::vector<PlaceToAddOrganism>& added_plants)
{
    using std::cout;

    int height, width;
    getDimensions(board, height, width);
    int row = this->get_position_row(), column = this->get_position_column();

    // Special case for sosnowsky plant
    if (this->get_name() == "Sosnowsky_hogweed")
    {
        sosnowsky_collision(row, column, height, width, organisms, indexes_to_remove);
        return;
    }

    if (can_sow)
    {
        cout << this->get_name() << " at (" << row << ", " << column << ") will sow\n";

        int counter = 0;
        for (const auto& o : organisms)
            if (o->get_name() == this->get_name())
                counter++;
        if (counter > 5)
            cout << "We cant add more " << this->get_name() << " beacuse we arleady have " << counter << " of them!\n";
        else;
            added_plants.push_back({ this->get_type(), this->get_name(), this->get_position_row(), this->get_position_column()});
    }
    else
        cout << this->get_name() << " at (" << row << ", " << column << ") will not sow\n";
}

void Plant::sosnowsky_collision(int row, int column, int height, int width, std::vector<Organism*>& organisms, std::vector<int>& indexes_to_remove)
{
    using std::cout;

    cout << "Sosnowsky_hogweed at (" << row << ", " << column << ") kills every animal in its neighboorhood!\n";
    for (int newRow = row - 1; newRow <= row + 1; newRow++)
    {
        for (int newColumn = column - 1; newColumn <= column + 1; newColumn++)
        {
            if (newRow >= 0 && newRow < height && newColumn >= 0 && newColumn < width)
            {
                for (int i = 0; i < organisms.size(); i++)
                {
                    auto o = organisms[i];
                    if (o->get_position_row() == newRow && o->get_position_column() == newColumn && o->get_name() != "Human" && o->get_name() != "cyber_sheep")
                    {
                        if (Animal* ptr = dynamic_cast<Animal*>(o))
                        {
                            std::cout << "Killing " << o->get_name() << " at (" << newRow << ", " << newColumn << ")\n";
                            indexes_to_remove.push_back(i);
                            break;
                        }
                    }
                }
            }
        }
    }
}

char Plant::draw() const
{
    return get_character();
}