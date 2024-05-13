#include "organism.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <cassert>
#include <iostream>

Organism::Organism(int strength, int initiative, std::string name, unsigned char character, int row, int column, std::string image_name, OrganismType type)
    : strength(strength), initiative(initiative), name(name), character(character), row(row), column(column), type(type)
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
}

void Organism::move_top()
{
    assert(this->row > 0);
    this->row--;
}

void Organism::move_right()
{
    assert(this->column < BOARD_WIDTH - 1);
    this->column++;
}

void Organism::move_bottom()
{
    assert(this->row < BOARD_HEIGHT - 1);
    this->row++;
}