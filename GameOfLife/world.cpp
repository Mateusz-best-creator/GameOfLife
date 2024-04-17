#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "world.h"
#include "animal.h"
#include "plant.h"
#include "human.h"
#include "wolf.h"
#include "sheep.h"
#include "fox.h"
#include "turtle.h"
#include "antelope.h"
#include "cyber_sheep.h"
#include "grass.h"
#include "sow_thistle.h"
#include "guarana.h"
#include "belladonna.h"
#include "sosnowsky_hogweed.h"

std::string getOperatingSystem()
{
#if defined(__linux__)
    std::cout << "Hello, GNU/Linux!" << '\n';
    return "linux";
#elif defined(_WIN32)
    std::cout << "Hello, Windows!" << '\n';
    return "windows";
#endif
}

World::World(int h, int w)
    : height(h), width(w), max_organisms(h* w), number_of_organisms(0)
{
    OS = getOperatingSystem();
    initialize_game();
}

void World::initialize_game()
{
    board = new char* [height];
    for (int i = 0; i < height; i++)
        board[i] = new char[width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j] = ' ';

    srand(time(nullptr));

    // Get random number to decide how many kinds of this thing we want to initially have in our simulation
    int n_species;
    if (height * width <= 50)
        n_species = 1;
    else if (height * width <= 100)
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
            add("wolf", randomNumber);
            break;
        case 2:
            add("sheep", randomNumber);
            break;
        case 3:
            add("fox", randomNumber);
            break;
        case 4:
            add("turtle", randomNumber);
            break;
        case 5:
            add("antelope", randomNumber);
            break;
        case 6:
            add("cyber_sheep", randomNumber);
            break;
        case 7:
            add("Grass", randomNumber, false);
            break;
        case 8:
            add("Sow_thistle", randomNumber, false);
            break;
        case 9:
            add("Guarana", randomNumber, false);
            break;
        case 10:
            add("Belladonna", randomNumber, false);
            break;/*
        case 11:
            add("Sosnowsky_hogweed", randomNumber, false);
            break;
            */
        case 12:
            // We always want one human at our board
            add("Human", 1, false, true);
            break;
            
        default:
            break;
        }
    }

    sort_organisms();
}

// Sort organisms based on their initiative, from highest to lowest
void World::sort_organisms()
{
    std::sort(organisms.begin(), organisms.end(), [](const Organism* first, const Organism* second)
        {
            int one = first->get_initiative(), two = second->get_initiative();
            if (one == two)
                return first->get_age() > second->get_age();
            return one > two;
        });
}

void World::add(const std::string& name, int times, bool is_animal, bool is_human)
{
    int random_row = rand() % height, random_column = rand() % width;

    for (int j = 0; j < times; j++)
    {
        while (board[random_row][random_column] != ' ')
        {
            random_row = rand() % height;
            random_column = rand() % width;
        }
        if (name == "wolf") organisms.push_back(new Wolf(random_row, random_column));
        else if (name == "sheep") organisms.push_back(new Sheep(random_row, random_column));
        else if (name == "fox") organisms.push_back(new Fox(random_row, random_column));
        else if (name == "turtle") organisms.push_back(new Turtle(random_row, random_column));
        else if (name == "antelope") organisms.push_back(new Antelope(random_row, random_column));
        else if (name == "cyber_sheep") organisms.push_back(new CyberSheep(random_row, random_column));
        else if (name == "Grass") organisms.push_back(new Grass(random_row, random_column));
        else if (name == "Sow_thistle") organisms.push_back(new SowThistle(random_row, random_column));
        else if (name == "Guarana") organisms.push_back(new Guarana(random_row, random_column));
        else if (name == "Belladonna") organisms.push_back(new Belladonna(random_row, random_column));
        else if (name == "Human") organisms.push_back(new Human(random_row, random_column));
        
        board[random_row][random_column] = organisms[organisms.size() - 1]->get_character();
    }
}

World::~World()
{
    clear_resources();
}

void World::clear_resources()
{
    // Deallocate organism memory
    for (auto organism : organisms)
        delete organism;
    organisms.clear();

    // Deallocate board memory
    for (int i = 0; i < height; i++)
        delete[] board[i];
    delete[] board;
}

void World::update_world()
{
    sort_organisms();
    // Clear the board
    for (size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++)
            board[i][j] = ' ';
    // Update the board with organism positions
    for (const auto& organism : organisms)
    {
        int row = organism->get_position_row();
        int column = organism->get_position_column();

        // Check if the position is within the bounds of the board
        if (row >= 0 && row < height && column >= 0 && column < width)
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
        << "s -> save game\n"
        << "o -> open game file\n\n";

    cout << "If you hit p you have the following options as a human:\n"
        << "arrows -> move\n"
        << "a -> stay at current position\n"
        << "s -> activate special ability\n\n";

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
    
    legend();
    cout << "\nTurn: " << turn++ << "\n";
    drawWorld();

    cout << "Enter playing option: ";
    char key;
    std::cin >> key;
    ActionType type = static_cast<ActionType>(key);

    switch (type)
    {
    case QUIT:
        return false;
    case PLAY:
        play();
        break;
    case SAVE_GAME:
        save_game();
        break;
    case OPEN_GAME:
        load_game();
        break;
    default:
        cout << "Invalid option!\n";
        break;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

void World::remove_killed_organisms(std::vector<int>& indexes_to_remove)
{
    // Remove and deallocate objects from the organisms vector
    for (int index : indexes_to_remove)
    {
        if (index >= 0 && index < organisms.size())
        {
            delete organisms[index];
            organisms.erase(organisms.begin() + index);
        }
    }
    update_world();
    indexes_to_remove.clear();
}

void World::play()
{
    bool selected = false;
    if (OS == "windows")
        system("cls");
    else if (OS == "linux")
        system("clear");
    drawWorld();
    std::vector<int> indexes_to_remove;
    std::vector<PlaceToAddOrganism> organisms_to_add;

    if (is_human_on_map)
    {
        for (auto& organism : organisms)
        {
            if (Human* derivedPtr = dynamic_cast<Human*>(organism))
            {
                organism->action(board, height, width);
                organism->collision(board, organisms, indexes_to_remove, organisms_to_add);
                selected = true;
                update_world();
                break;
            }
        }
        if (!selected)
            is_human_on_map = false;
    }
    else
        std::cout << "\nJournal:\n\n";

    remove_killed_organisms(indexes_to_remove);

    int counter = 0;
    for (auto& organism : organisms)
    {
        organism->get_age()++;
        auto it = std::find(indexes_to_remove.begin(), indexes_to_remove.end(), counter++);

        // human arleady moved, we added new organism from multiplication, or we arleady deleted organism (it was killed in this turn)
        if (organism->get_name() == "Human" || it != indexes_to_remove.end())
            continue;

        organism->action(board, height, width);
        organism->collision(board, organisms, indexes_to_remove, organisms_to_add);

        update_world();
    }

    remove_killed_organisms(indexes_to_remove);
    
    // Add objects from multiplication to the organisms vector
    for (const auto& object : organisms_to_add)
    {
        int row = object.new_row, column = object.new_column;
        for (int newRow = row - 1; newRow <= row + 1; ++newRow)
        {
            for (int newColumn = column - 1; newColumn <= column + 1; ++newColumn)
            {
                if (newRow >= 0 && newRow < height && newColumn >= 0 && newColumn < width && board[newRow][newColumn] == ' ')
                {
                    std::cout << "Creating another " << object.name << " at (" << newRow << ", " << newColumn << ")\n";
                    switch (object.type)
                    {
                    case OrganismType::Wolf:
                        organisms.push_back(new Wolf(newRow, newColumn));
                        break;
                    case OrganismType::Sheep:
                        organisms.push_back(new Sheep(newRow, newColumn));
                        break;
                    case OrganismType::Fox:
                        organisms.push_back(new Fox(newRow, newColumn));
                        break;
                    case OrganismType::Turtle:
                        organisms.push_back(new Turtle(newRow, newColumn));
                        break;
                    case OrganismType::Antelope:
                        organisms.push_back(new Antelope(newRow, newColumn));
                        break;
                    case OrganismType::CyberSheep:
                        organisms.push_back(new CyberSheep(newRow, newColumn));
                        break;
                    case OrganismType::Grass:
                        organisms.push_back(new Grass(newRow, newColumn));
                        break;
                    case OrganismType::SowThistle:
                        organisms.push_back(new SowThistle(newRow, newColumn));
                        break;
                    case OrganismType::Guarana:
                        organisms.push_back(new Guarana(newRow, newColumn));
                        break;
                    case OrganismType::Belladonna:
                        organisms.push_back(new Belladonna(newRow, newColumn));
                        break;
                    case OrganismType::SosnowskyHogweed:
                        organisms.push_back(new SosnowskyHogweed(newRow, newColumn));
                        break;
                    case OrganismType::Human:
                        organisms.push_back(new Human(newRow, newColumn));
                        break;
                    default:
                        // Handle the case when the organism type is not recognized
                        break;
                    }
                    update_world();
                    newRow = newColumn = 999;
                }
            }
        }
    }
    
    update_world();
}

void World::save_game()
{
    using namespace std;
    string board_filename;
    cout << "Enter filename to save your board: ";
    cin >> board_filename;
    cout << "Saving board to " << board_filename << endl;
    string organisms_filename;
    cout << "Enter filename to save your organisms: ";
    cin >> organisms_filename;
    cout << "Saving organisms to " << organisms_filename << endl;

    // Combine directory path and filename
    string board_file_path = "./filenames/" + board_filename;
    string organisms_file_path = "./filenames/" + organisms_filename;

    // Open board file
    ofstream board_file(board_file_path);
    if (!board_file.is_open())
    {
        std::cerr << "Error opening file: " << board_filename << std::endl;
        return;
    }
    int temp_height = height + 2, temp_width = width + 2;
    for (size_t i = 0; i < temp_height; i++)
    {
        for (size_t j = 0; j < temp_width; j++)
        {
            if (i == 0 || i == temp_height - 1)
                board_file << "-";
            else if (j == 0 || j == temp_width - 1)
                board_file << "|";
            else
                board_file << board[i - 1][j - 1];
        }
        board_file << std::endl;
    }
    board_file.close();

    // Open organisms file
    ofstream organisms_file(organisms_file_path);
    if (!organisms_file.is_open())
    {
        std::cerr << "Error opening file: " << organisms_filename << std::endl;
        return;
    }
    organisms_file << turn - 1 << " " << height << " " << width << "\n";
    for (const auto& organism : organisms)
    {
        organisms_file << organism->get_name() << " " << organism->get_strength() << " "
            << organism->get_initiative() << " " << organism->get_position_row() << " " << organism->get_position_column() << "\n";
    }
    organisms_file.close();
}


void World::load_game()
{
    using namespace std;

    string filename;
    cout << "Give filename from where you want to load your game: ";
    cin >> filename;

    ifstream file("./filenames/" + filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    clear_resources();

    string line;
    file >> turn >> height >> width;

    board = new char* [height];
    for (size_t i = 0; i < height; i++)
        board[i] = new char[width];

    while (getline(file, line))
    {
        string name;
        int strength, initiative, row, column;
        file >> name >> strength >> initiative >> row >> column;
        Organism* new_org = nullptr;

        if (name == "wolf") new_org = new Wolf(strength, initiative, row, column);
        else if (name == "sheep") new_org = new Sheep(strength, initiative, row, column);
        else if (name == "fox") new_org = new Fox(strength, initiative, row, column);
        else if (name == "turtle") new_org = new Turtle(strength, initiative, row, column);
        else if (name == "antelope") new_org = new Antelope(strength, initiative, row, column);
        else if (name == "cyber_sheep") new_org = new CyberSheep(strength, initiative, row, column);
        else if (name == "Grass") new_org = new Grass(row, column);
        else if (name == "Sow_thistle") new_org = new SowThistle(row, column);
        else if (name == "Guarana") new_org = new Guarana(row, column);
        else if (name == "Belladonna") new_org = new Belladonna(row, column);
        else if (name == "Sosnowsky_hogweed") new_org = new SosnowskyHogweed(row, column);
        else if (name == "Human") new_org = new Human(strength, initiative, row, column);

        if (new_org)
            organisms.push_back(new_org);
    }
    update_world();
    if (OS == "windows")
        system("cls");
    else if (OS == "linux")
        system("clear");
    cout << "We load a game from ./filenames/" << filename << endl;
    file.close();
}