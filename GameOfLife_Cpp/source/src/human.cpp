#include <iostream>
#include "human.hpp"

int Human::HUMAN_STATIC_COUNTER = 0;

Human::Human(int row, int column)
    : Animal(5, 4, 0, "Human", 'H', row, column, "human.png", OrganismType::HUMAN)
{
    this->previous_row = row;
    this->previous_column = column;
    HUMAN_STATIC_COUNTER++;
    ability_activated = false;
    ability_counter = 0;
}

Human::Human(int row, int column, int strength, int initiative, int age, bool activated, int counter, int def_strength)
    : Animal(strength, initiative, age, "Human", 'H', row, column, "human.png", OrganismType::HUMAN)
{
    this->previous_row = row;
    this->previous_column = column;
    HUMAN_STATIC_COUNTER++;
    ability_activated = activated;
    ability_counter = counter;
    this->get_default_strength() = def_strength;
}

Human::Human(const Human& other)
    : Animal(other.get_strength(), other.get_initiative(), other.get_age(), "Human", 'H', other.get_row(), other.get_column(), "human.png", OrganismType::HUMAN)
{
    this->previous_row = other.previous_row;
    this->previous_column = other.previous_column;
    HUMAN_STATIC_COUNTER++;
    ability_activated = other.ability_activated;
    ability_counter = other.ability_counter;
    this->get_default_strength() = other.get_default_strength();
}

Human::~Human()
{
    HUMAN_STATIC_COUNTER--;
}

ActionResult Human::action(std::vector<std::vector<char>>& grid_board)
{
    if (ability_activated)
    {
        this->get_strength()--;
        if (this->get_strength() == this->get_default_strength())
        {
            ability_activated = false;
            ability_counter = 5;
        }
    }
    else if (!ability_activated && ability_counter != 0)
        ability_counter--;

    bool isRunning = true;
    while (isRunning) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                exit(EXIT_SUCCESS);
            }
            else if (event.type == SDL_KEYDOWN)
            {
                bool moved = false;
                this->previous_row = this->row;
                this->previous_column = this->column;
                switch (event.key.keysym.sym) 
                {
                    case SDLK_q:
                        exit(EXIT_SUCCESS);
                        break;
                    case SDLK_a:
                        if (ability_activated)
                            std::cout << "Human ability arleady activated...\n";
                        else if (!ability_activated && ability_counter == 0)
                        {
                            std::cout << "Activating human ability +10 strength\n";
                            ability_activated = true;
                            this->get_default_strength() = this->get_strength();
                            this->get_strength() += 10;
                        }
                        else
                            std::cout << "Cannot activate ability now, you have to wait " << ability_counter << " more turns\n";
                        break;
                    case SDLK_UP:
                        if (this->row > 0)
                        {
                            this->row--;
                            moved = true;
                        }
                        break;
                    case SDLK_DOWN:
                        if (this->row < this->BOARD_HEIGHT - 1)
                        {
                            this->row++;
                            moved = true;
                        }
                        break;
                    case SDLK_LEFT:
                        if (this->column > 0)
                        {
                            this->column--;
                            moved = true;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (this->column < this->BOARD_WIDTH - 1)
                        {
                            this->column++;
                            moved = true;
                        }
                        break;
                }
                if (moved)
                    isRunning = false;
            }
        }
    }
    
    this->move_message();
    grid_board[previous_row][previous_column] = 'e';
    grid_board[row][column] = this->get_character();

    return ActionResult(ActionType::MOVE);
}

CollisionResult Human::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_animal(grid_board, organisms, current_index);
}

int Human::get_static_counter()
{
    return HUMAN_STATIC_COUNTER;
}