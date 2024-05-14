#include "organism.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <cassert>
#include <iostream>

Organism::Organism(int strength, int initiative, int age, std::string name, char ch, int r, int c, std::string image_name, OrganismType t)
    : strength(strength), initiative(initiative), age(age), name(name), character(ch), row(r), column(c), type(t)
{
    int image_last_index = image_name.size() - 1;
    assert(row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH 
    && image_name.size() > 4
    && image_name[image_last_index] == 'g' 
    && image_name[image_last_index - 1] == 'n' 
    && image_name[image_last_index - 2] == 'p'
    && image_name[image_last_index - 3] == '.'); // Make sure image has .png extension
    filepath = "./source/Assets/" + image_name;
}

Organism::~Organism()
{

}

void Organism::move_message() const
{
    std::cout << this->get_name() << " moved from (" << this->previous_row << ", " 
    << this->previous_column << ") to (" << this->row << ", " << this->column << ")" << std::endl;
}

void Organism::draw(SDL_Renderer* renderer, int image_height, int image_width, int pos_x, int pos_y)
{
    // Load the texture if it's not already loaded
    if (!img)
    {
        img = IMG_LoadTexture(renderer, this->filepath.c_str());
        if (!img)
        {
            // Handle error if texture loading fails
            std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
            return;
        }
        SDL_QueryTexture(img, NULL, NULL, &image_width, &image_height);
    }

    SDL_Rect texr;
    texr.x = pos_x;
    texr.y = pos_y;
    texr.w = image_width;
    texr.h = image_height;
    
    // Copy the texture onto the renderer
    SDL_RenderCopy(renderer, img, NULL, &texr);
}

void Organism::move_left()
{
    assert(this->column > 0);
    this->column--;
    std::cout << "Move left: ";
}

void Organism::move_top()
{
    assert(this->row > 0);
    this->row--;
    std::cout << "Move top: ";
}

void Organism::move_right()
{
    assert(this->column < BOARD_WIDTH - 1);
    this->column++;
    std::cout << "Move right: ";
}

void Organism::move_bottom()
{
    assert(this->row < BOARD_HEIGHT - 1);
    this->row++;
    std::cout << "Move bottom: ";
}

void Organism::default_grid_update(std::vector<std::vector<char>>& grid_board) const
{
    assert(row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH);
    assert(previous_row >= 0 && previous_row < BOARD_HEIGHT && previous_column >= 0 && previous_column < BOARD_WIDTH);
    grid_board[previous_row][previous_column] = 'e';
    grid_board[row][column] = this->get_character();
}