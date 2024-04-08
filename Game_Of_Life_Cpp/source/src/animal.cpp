#include "animal.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>

Animal::Animal(std::string n, int row, int column)
    : Organism(row, column, n)
{
    std::string name = get_name();
    
    if (n != "Human")
        this->get_type() = OrganismType::Animal;
    
    if (name == "wolf")
    {
        strength = 9;
        initiative = 5;
    }
    else if (name == "sheep")
    {
        strength = 4;
        initiative = 4;
    }
    else if (name == "fox")
    {
        strength = 3;
        initiative = 7;
    }
    else if (name == "turtle")
    {
        strength = 2;
        initiative = 1;
    }
    else if (name == "antelope")
    {
        strength = 4;
        initiative = 4;
    }
    else if (name == "cyber_sheep")
    {
        strength = 11;
        initiative = 4;
    }
    else if (name == "Human")
    {
        strength = 5;
        initiative = 4;
    }
}

Animal::Animal(std::string n, int s, int i, int row, int column)
    : Organism(row, column, n), strength(s), initiative(i)
{
    get_position_row() = row;
    get_position_column() = column;
}

Animal::~Animal()
{

}

void Animal::action(char** board, int height, int width)
{
    std::string name = get_name();
    this->get_type() = OrganismType::Animal;
    if (name == "wolf" || name == "sheep")
        default_action(name, height, width);
    else if (name == "fox")
        fox_action(board, name, height, width);
    else if (name == "turtle")
        turtle_action(name, height, width);
    else if (name == "antelope")
        antelope_action(name, height, width);
    else if (name == "cyber_sheep")
        cyber_sheep_action(board, name, height, width);
}

char Animal::draw() const
{
    return get_character();
}

/*
    All animal actions implementation
*/

void Animal::default_action(std::string name, int height, int width) 
{
    using std::cout;

    // Get the current position
    int& current_row = get_position_row();
    int& current_column = get_position_column();

    while (true) 
    {
        // Generate a random number between 0 and 3 to represent the four directions
        int d = rand() % 4;
        Directions direction = static_cast<Directions>(d);

        // Update the position based on the randomly chosen direction
        switch (direction) 
        {
            case Directions::LEFT:
                if (current_column > 0) 
                {
                    cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the left\n";
                    get_position_column()--;
                    previous_move = Directions::LEFT;
                    return;
                }
                break;
            case Directions::TOP: // Move top
                if (current_row > 0) 
                {
                    cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the top\n";
                    get_position_row()--;
                    previous_move = Directions::TOP;
                    return;
                }
                break;
            case Directions::RIGHT: // Move right
                if (current_column < width - 1) 
                {
                    cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the right\n";
                    get_position_column()++;
                    previous_move = Directions::RIGHT;
                    return;
                }
                break;
            case Directions::BOTTOM: // Move bottom
                if (current_row < height - 1) 
                {
                    cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the bottom\n";
                    get_position_row()++;
                    previous_move = Directions::BOTTOM;
                    return;
                }
                break;
            default:
                cout << "Invalid direction\n";
                previous_move = Directions::NONE;
                break;
        }
    }
}

bool fox_can_go(char c)
{
    return c == 't' || c == 'G' || c == 'S' || c == 'U' || c == ' ';
}

void Animal::fox_action(char** board, std::string name, int height, int width)
{
    using std::cout;
    using std::endl;
    
    std::set<Directions> s;

    Directions direction = static_cast<Directions>(rand() % 4);
    int row = this->get_position_row(), column = this->get_position_column();
    while (true)
    {
        if (row > 0 && direction == Directions::TOP)
        {
            char top_board = board[row - 1][column];
            if (fox_can_go(top_board))
            {
                get_position_row()--;
                cout << this->get_name() << " moves one square top to: (" << this->get_position_row() << ", " << this->get_position_column() << ")\n";
                return;
            }
        }
        else if (row < height - 1 && direction == Directions::BOTTOM)
        {
            char bottom_board = board[row + 1][column];
            if (fox_can_go(bottom_board))
            {
                get_position_row()++;
                cout << this->get_name() << " moves one square bottom to: (" << this->get_position_row() << ", " << this->get_position_column() << ")\n";
                return;
            }
        }
        else if (column > 0 && direction == Directions::LEFT)
        {
            char left_board = board[row][column - 1];
            if (fox_can_go(left_board))
            {
                get_position_column()--;
                cout << this->get_name() << " moves one square left to: (" << this->get_position_row() << ", " << this->get_position_column() << ")\n";
                return;
            }
        }
        else if (column < width - 1 && direction == Directions::RIGHT)
        {
            char right_board = board[row][column + 1];
            if (fox_can_go(right_board))
            {
                get_position_column()++;
                cout << this->get_name() << " moves one square right to: (" << this->get_position_row() << ", " << this->get_position_column() << ")\n";
                return;
            }
        }
        s.insert(direction);
        if (s.size() >= 4)
        {
            cout << "Fox cant move anywhere, it stays where it is: (" << row << ", " << column << ")\n";
            return; 
        }
        direction = static_cast<Directions>(rand() % 4);
    }
}

void Animal::turtle_action(std::string name, int height, int width)
{
    int randomNum = rand() % 4 + 1;
    if (randomNum != 4)
        std::cout << name << " stays at the same position: (" << get_position_row() <<", " << get_position_column() << ")\n";
    else
        default_action(name, height, width);
}

void Animal::antelope_action(std::string name, int height, int width)
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

bool return_is_sosnowsky(char** board, int& row, int& col, int height, int width)
{
    for (size_t i = 0; i < height; i++) 
    {
        for (size_t j = 0; j < width; j++) 
        {
            if (board[i][j] == 'O')
            {
                row = i;
                col = j;
                return true;
            }
        }
    }
    
    return false;
}

void Animal::cyber_sheep_action(char** board, std::string name, int height, int width)
{
    int sosnowsky_row, sosnowsky_column;
    int row = this->get_position_row(), column = this->get_position_column();
    if (return_is_sosnowsky(board, sosnowsky_row, sosnowsky_column, height, width))
    {
        int row_diff = sosnowsky_row - row;
        int col_diff = sosnowsky_column - column;

        // Determine the direction
        if (row_diff < 0 && col_diff < 0) 
        {
            // Move towards top-left
            this->get_position_column()--;
        } 
        else if (row_diff < 0 && col_diff > 0) 
        {
            // Move towards top-right
            this->get_position_column()++;
        } 
        else if (row_diff > 0 && col_diff < 0) 
        {
            // Move towards bottom-left
            this->get_position_row()++;
        } 
        else if (row_diff > 0 && col_diff > 0) 
        {
            // Move towards bottom-right
            this->get_position_row()++;
        } 
        else if (row_diff < 0 && col_diff == 0) 
        {
            // Move straight up
            this->get_position_row()--;
        } 
        else if (row_diff > 0 && col_diff == 0) 
        {
            // Move straight down
            this->get_position_row()++;
        } 
        else if (row_diff == 0 && col_diff < 0) 
        {
            // Move straight left
            this->get_position_column()--;
        } 
        else if (row_diff == 0 && col_diff > 0) 
        {
            // Move straight right
            this->get_position_column()++;
        }
    }
    else
        default_action(name, height, width);
}

/*
    Function that will handle collisions between animals
*/
void Animal::collision(char** board, std::vector<Organism*>& organisms, std::vector<int>& indexes_to_remove, std::vector<PlaceToAddOrganism>& organisms_to_add)
{
    using namespace std;

    int height, width;
    get_dimensions(board, height, width);

    int row = get_position_row(), column = get_position_column();
    if (board[row][column] == ' ')
        return;

    for (size_t i = 0; i < organisms.size(); i++)
    {
        auto organism = organisms[i];
        // We found collisions
        if (organism->get_position_row() == row
        && organism->get_position_column() == column
        && this->get_index() != organism->get_index())
        {
            cout << "Collision " << this->get_name() << " with " << organism->get_name() << " at (" << row << ", " << column << ")" << endl;

            // Fight case
            if (this->get_name() != organism->get_name() && organism->get_name() != "turtle")
            {
                float probability = (rand() % 100 + 1) / 100.0;
                if (probability < 0.5 && this->get_name() == "antelope")
                {
                    cout << this->get_name() << " escapes from fight! ";
                    update_previous_move();
                    cout << "It goes back to (" << this->get_position_row() << ", " << this->get_position_column() << ")\n";
                    return;
                }
                else if (probability < 0.5 && organism->get_name() == "antelope")
                {
                    cout << this->get_name() << " escapes from fight! ";
                    for (int newRow = row - 1; newRow <= row + 1; ++newRow) 
                    {
                        for (int newColumn = column - 1; newColumn <= column + 1; ++newColumn) 
                        {
                            if (newRow >= 0 && newRow < height && newColumn >= 0 && newColumn < width && board[newRow][newColumn] == ' ') 
                            {
                                organism->get_position_row() = newRow;
                                organism->get_position_column() = newColumn;
                                cout << "It goes back to (" << organism->get_position_row() << ", " << organism->get_position_column() << ")\n";
                                return;
                            }
                        }
                    }
                }

                if (this->get_strength() >= organism->get_strength() && organism->get_name() != "Belladonna")
                {
                    cout << this->get_name() << " wins the battle with " << organism->get_name() << " at (" << row << ", " << column << ")\n";
                    indexes_to_remove.push_back(i);
                    if (organism->get_name() == "Guarana")
                        this->get_strength() += EAT_GUARANA_STRENGTH_INCERASE;
                    return;
                }
                else
                {
                    cout << organism->get_name() << " wins the battle with " << this->get_name() << " at (" << row << ", " << column << ")\n";
                    for (size_t k = 0; k < organisms.size(); k++)
                    {
                        if (this->get_index() == organisms[k]->get_index())
                        {
                            indexes_to_remove.push_back(k);
                            return;
                        }
                    }
                }
            }
            // Fight with turtle case
            else if (this->get_name() != organism->get_name() && organism->get_name() == "turtle")
            {
                update_previous_move();
                std::cout << "Turtle at (" << row << ", " << column << ") reflects the attack! " << get_name() 
                << " is going back to: (" << get_position_row() << ", " << get_position_column() << ")\n";
            }
            else if (this->get_name() == organism->get_name())
            {
                cout << "Multiplication of " << this->get_name() << " at (" << row << ", " << column << ")\n";
                update_previous_move();
                int counter = 0;
                for (const auto& o : organisms)
                    if (o->get_name() == this->get_name())
                        counter++;
                if (counter > 5)
                    cout << "We cant add more " << this->get_name() << " beacuse we arleady have " << counter << " of them!\n";
                else
                    organisms_to_add.push_back({OrganismType::Animal, this->get_name(), this->get_position_row(), this->get_position_column()});
            }
        }
    }
}

void Animal::update_previous_move()
{
    if (previous_move == Directions::LEFT) get_position_column()++;
    else if (previous_move == Directions::TOP) get_position_row()++;
    else if (previous_move == Directions::RIGHT) get_position_column()--;
    else if (previous_move == Directions::BOTTOM) get_position_row()--;
    
    previous_move = Directions::NONE;
}

void Animal::get_dimensions(char** board, int& height, int& width)
{
    int h = 0, w = 0;
    while (board[h] != NULL)
        h++;
    while (board[0][w] != '\0')
        w++;
    height = h;
    width = w;
}