#include <iostream>
#include <cstdlib>
#include <ctime>

#include "world.h"
#include "animal.h"
#include "plant.h"

void add(std::vector<Organism*>& data, const std::string& name, int times, bool is_animal = true)
{
    if (is_animal)
    {
        for (int j = 0; j < times; j++)
            data.push_back(new Animal(name));
    }
    else
    {
        for (int j = 0; j < times; j++)
            data.push_back(new Plant(name));
    }
    
}

World::World(int h, int w)
    : height(h), width(w), max_organisms(h * w), number_of_organisms(0)
{
    srand(time(nullptr));

    // Get random number to decide how many kinds of this thing we want to initially have in our simulation
    int n_species;
    if (height * width < 15)
        n_species = 1;
    else if (height * width < 25)
        n_species = 2;
    else 
        n_species = 3;
    
    for (int i = 0; i < KINDS_OF_ORGANISMS; i++)
    {
        int randomNumber = rand() % n_species + 1;
        switch (i + 1)
        {
        // Wolf case
        case 1:
            add(organisms, "wolf", randomNumber);
            break;
        case 2:
            add(organisms, "sheep", randomNumber);
            break;
        case 3:
            add(organisms, "fox", randomNumber);
            break;
        case 4:
            add(organisms, "turtle", randomNumber);
            break;
        case 5:
            add(organisms, "antelope", randomNumber);
            break;
        case 6:
            add(organisms, "cyber_sheep", randomNumber);
            break;
        case 7:
            add(organisms, "grass", randomNumber, false);
            break;
        case 8:
            add(organisms, "sow_thistle", randomNumber, false);
            break;
        case 9:
            add(organisms, "guarana", randomNumber, false);
            break;
        case 10:
            add(organisms, "belladonna", randomNumber, false);
            break;
        case 11:
            add(organisms, "Sosnowsky_hogweed", randomNumber, false);
            break;
        }
    }
}

World::~World()
{
    for (auto organism: organisms)
        delete organism;
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

