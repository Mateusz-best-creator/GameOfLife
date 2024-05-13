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
    const int MAX_RANDOM_AMOUNT = 3;

    std::vector<std::vector<char>> grid_board;
    std::vector<int> organism_indexes_to_remove;
    std::vector<OrganismType> o_types;
    std::vector<Point> points_to_multiply;

public:
    World();
    ~World();

    void initialize_organisms();
    void add_organism(int, OrganismType,  int specified_row = -1, int specified_column = -1);
    void draw_world();
    void play_turn();
    void sort_organisms();
    void remove_organisms();
    void multiply_organisms();
    void update_grid_board();
    void modify_grid_board(int, int, char);
};