#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

#include "world.h"
#include "animal.h"
#include "plant.h"
#include "human.h"

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
    if (height * width <= 16)
        n_species = 1;
    else if (height * width <= 25)
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
            add(organisms, "Grass", randomNumber, false);
            break;
        case 8:
            add(organisms, "Sow_thistle", randomNumber, false);
            break;
        case 9:
            add(organisms, "Guarana", randomNumber, false);
            break;
        case 10:
            add(organisms, "Belladonna", randomNumber, false);
            break;
        case 11:
            add(organisms, "Sosnowsky_hogweed", randomNumber, false);
            break;
        case 12:
            // We always want one human at our board
            add(organisms, "Human", 1, false, true);
            break;
        default:
            break;
        }
    }

    // Sort organisms based on their initiative, from highest to lowest
    std::sort(organisms.begin(), organisms.end(), [](const Organism* first, const Organism* second)
    {
        return first->get_initiative() > second->get_initiative();
    });
}

void World::add(std::vector<Organism*>& data, const std::string& name, int times, bool is_animal, bool is_human)
{
    int random_row = rand() % height, random_column = rand() % width;
    
    for (int j = 0; j < times; j++)
    {
        while (board[random_row][random_column] != ' ')
        {
            random_row = rand() % height;
            random_column = rand() % width;
        }
        if (is_human)
            data.push_back(new Human(name, random_row, random_column));
        else if (is_animal)
            data.push_back(new Animal(name, random_row, random_column));
        else
            data.push_back(new Plant(name, random_row, random_column));
        board[random_row][random_column] = data[data.size() - 1]->get_character();
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

void World::update_world()
{
    for (size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++)
            board[i][j] = ' ';
    
    for (const auto& organism : organisms)
    {
        int row = organism->get_position_row();
        int column = organism->get_position_column();
        board[row][column] = organism->get_character();
    }
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
                std::cout << board[i - 1][j - 1];
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n";
}

void World::legend() 
{
    using std::cout;
    using std::setw;
    using std::left;

    cout << "\nOptions that are available:\n"
         << "q -> quit game\n"
         << "p -> go to the next turn\n"
         << "n -> start new game\n"
         << "s -> save game\n"
         << "o -> open game file\n\n";

    cout << "If you hit p you have the following options as a human:\n"
         << "arrows -> move\n"
         << "s -> stay at current position\n"
         << "a -> activate special ability\n\n";

    cout << "Legend of symbols:\n"
         << left << setw(25) << "w -> wolf"
         << left << setw(25) << "s -> sheep"
         << left << setw(25) << "f -> fox"
         << left << "t -> turtle\n"
         
         << left << setw(25) << "a -> antelope"
         << left << setw(25) << "c -> cyber_sheep"
         << left << setw(25) << "G -> grass"
         << left << "S -> sow_thistle\n"
         
         << left << setw(25) << "U -> guarana"
         << left << setw(25) << "B -> belladonna"
         << left << setw(25) << "O -> Sosnowsky_hogweed"
         << left << "H -> human\n\n";
}

// performs one turn
bool World::makeTurn()
{
    using namespace std;
    char key;
    std::cin >> key;
    if (key == 'Q' || key == 'q')
        return false;

    if (key == 'p')
    {
        for (auto& organism : organisms)
        {
            if (Human* derivedPtr = dynamic_cast<Human*>(organism))
            {
                organism->action(height, width);
                break;
            }
        }
        
        // Performs simulation
        for (auto& organism : organisms)
        {
            // Human moves at the begginning of the turn
            if (Human* derivedPtr = dynamic_cast<Human*>(organism))
                continue;
            organism->action(height, width);
            // organism->collision();
        }
    }
    while (cin.get() != '\n')
        continue;
    
    return true;
}