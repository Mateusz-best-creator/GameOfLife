#include "world.h"
#include <iostream>

World::World(int h, int w)
    : height(h), width(w)
{

}

World::~World()
{

}

void World::drawWorld() const
{
    std::cout << "\n\n";
    int temp_height = height + 2, temp_width = width + 2;
    for (size_t i = 0; i < temp_height; i++)
    {
        for (size_t j = 0; j < temp_width; j++)
        {
            if (i == 0 || i == temp_height - 1)
                std::cout << "-";
            else if (j == 0 || j == temp_width - 1)
                std::cout << "|";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n";
}

