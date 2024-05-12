#pragma once
#include <SDL.h>
#include <vector>

#include "organism.hpp"

class World
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    const int WINDOW_HEIGHT = 800, WINDOW_WIDTH = 800, BOARD_SIZE = 10;
    const int IMAGE_HEIGHT = WINDOW_HEIGHT / BOARD_SIZE, IMAGE_WIDTH = WINDOW_WIDTH / BOARD_SIZE;
    std::vector<Organism*> organisms;
    int turn_number = 1;

    std::vector<std::vector<char>> grid_board;

public:
    World();
    ~World();

    void initialize_organisms();
    void draw_world();
    void play_turn();

    void modify_grid_board(int, int, char);
};