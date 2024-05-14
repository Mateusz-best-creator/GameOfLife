#include <iostream>
#include "human.hpp"

int Human::HUMAN_STATIC_COUNTER = 0;

Human::Human(int row, int column)
    : Animal(5, 4, 0, "Human", 'H', row, column, "human.png", OrganismType::HUMAN)
{
    this->previous_row = row;
    this->previous_column = column;
    HUMAN_STATIC_COUNTER++;
}

Human::Human(int row, int column, int strength, int initiative, int age)
    : Animal(strength, initiative, age, "Human", 'H', row, column, "human.png", OrganismType::HUMAN)
{
    this->previous_row = row;
    this->previous_column = column;
    HUMAN_STATIC_COUNTER++;
}

Human::~Human()
{
    HUMAN_STATIC_COUNTER--;
}

ActionResult Human::action(std::vector<std::vector<char>>& grid_board)
{
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