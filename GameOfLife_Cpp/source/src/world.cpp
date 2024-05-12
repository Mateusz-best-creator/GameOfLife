#include <iostream>
#include <cassert>

#include "world.hpp"
#include "human.hpp"
#include "wolf.hpp"

World::World()
    : grid_board(BOARD_SIZE, std::vector<char>(BOARD_SIZE, 'e'))
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create a window
    window = SDL_CreateWindow(
        "GameOfLife",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->WINDOW_HEIGHT, this->WINDOW_WIDTH,
        SDL_WINDOW_SHOWN
    );
    if (!window) 
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) 
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    this->initialize_organisms();
}

World::~World()
{
    for (auto o : this->organisms)
        delete o;

    if (renderer) 
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) 
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void World::initialize_organisms()
{
    // Just random adding
    this->organisms.push_back(new Wolf(0, 0));
    this->organisms.push_back(new Human(5, 5));
}

void World::draw_world() 
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Calculate the width and height of each cell
    int cellWidth = WINDOW_WIDTH / BOARD_SIZE;
    int cellHeight = WINDOW_HEIGHT / BOARD_SIZE;

    for (auto organism : this->organisms)
    {
        organism->draw(this->renderer, this->IMAGE_HEIGHT, this->IMAGE_WIDTH, organism->get_column() * cellWidth, organism->get_row() * cellHeight);
    }

    // Draw vertical & horizontal lines
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    for (int i = 1; i < BOARD_SIZE; i++)
        SDL_RenderDrawLine(renderer, i * cellWidth, 0, i * cellWidth, WINDOW_HEIGHT);
    for (int j = 1; j < BOARD_SIZE; j++)
        SDL_RenderDrawLine(renderer, 0, j * cellHeight, WINDOW_WIDTH, j * cellHeight);

    // Present the renderer
    SDL_RenderPresent(renderer);
}

void World::play_turn()
{
    std::cout << "### Turn number " << this->turn_number << "  ###" << std::endl;
    for (auto organism : this->organisms)
    {
        Organism::ActionType action_type = organism->action(this->grid_board);
        Organism::CollisionType collision_type = organism->collision();

        switch (action_type)
        {
        case Organism::ActionType::MOVE:
            break;
        default:
            break;
        }
        switch (collision_type)
        {
        case Organism::CollisionType::FIGHT:
            break;
        case Organism::CollisionType::MULTIPLICATION:
            break;
        default:
            break;
        }
    }

    this->turn_number++;
}

void World::modify_grid_board(int row, int column, char ch)
{
    assert(row >= 0 && row < this->BOARD_SIZE && column >= 0 && column < this->BOARD_SIZE);
    this->grid_board[row][column] = ch;
}