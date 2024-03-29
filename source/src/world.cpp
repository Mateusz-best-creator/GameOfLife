#include <iostream>
#include <cstdlib>
#include <ctime>

#include "world.h"
#include "animal.h"
#include "plant.h"

World::World(int h, int w)
    : height(h), width(w), max_organisms(h * w), number_of_organisms(0)
{
    board = new char*[height];
    for (int i = 0; i < height; i++)
        board[i] = new char[width];
    for (int i = 0; i < height; i++) 
        for (int j = 0; j < width; j++)
            board[i][j] = ' ';

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
    // Deallocate organism memory
    for (auto organism: organisms)
        delete organism;

    // Deallocate board memory
    for (int i = 0; i < height; i++)
        delete[] board[i];
    delete[] board;
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
            {
                if (board[i - 1][j - 1] != ' ')
                    std::cout << board[i - 1][j - 1];
                else
                    std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n";
}


void World::add(std::vector<Organism*>& data, const std::string& name, int times, bool is_animal)
{
    int random_row = rand() % height, random_column = rand() % width;
    
    for (int j = 0; j < times; j++)
    {
        while (board[random_row][random_column] != ' ')
        {
            random_row = rand() % height;
            random_column = rand() % width;
        }
        if (is_animal)
            data.push_back(new Animal(name, random_row, random_column));
        else
            data.push_back(new Plant(name, random_row, random_column));
        board[random_row][random_column] = name[0];
    }
}