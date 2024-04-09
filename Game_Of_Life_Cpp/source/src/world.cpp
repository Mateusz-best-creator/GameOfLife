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

World::World(int h, int w)
    : height(h), width(w), max_organisms(h * w), number_of_organisms(0)
{
    initialize_game();
}

void World::initialize_game()
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
            break;
        case 11:
            add("Sosnowsky_hogweed", randomNumber, false);
            break;
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
        return first->get_initiative() > second->get_initiative();
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
        if (is_human)
            organisms.push_back(new Human(name, random_row, random_column));
        else if (is_animal)
            organisms.push_back(new Animal(name, random_row, random_column));
        else
            organisms.push_back(new Plant(name, random_row, random_column));
        board[random_row][random_column] = organisms[organisms.size() - 1]->get_character();
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
         << "n -> start new game\n"
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

    cout << "\nTurn: " << turn++ << "\n";
    cout << "Enter playing option: ";
    char key;
    std::cin >> key;
    ActionType type = static_cast<ActionType>(key);

    switch (type)
    {
    case QUIT:
        return false;
    case PLAY:
        //system("clear");
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
    while (cin.get() != '\n')
        continue;
    return true;
}

void World::play()
{
    bool selected = false;
    
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
    
    int counter = 0;
    for (auto& organism : organisms)
    {
        auto it = std::find(indexes_to_remove.begin(), indexes_to_remove.end(), counter++);

        // human arleady moved, we added new organism from multiplication, or we arleady deleted organism (it was killed in this turn)
        if (organism->get_name() == "Human" || it != indexes_to_remove.end())
            continue;

        organism->action(board, height, width);
        organism->collision(board, organisms, indexes_to_remove, organisms_to_add);

        update_world();
    }

    // Remove and deallocate objects from the organisms vector
    for (int index : indexes_to_remove) 
    {
        if (index >= 0 && index < organisms.size()) 
        {
            delete organisms[index];
            organisms.erase(organisms.begin() + index);
            update_world();
        }
    }
    indexes_to_remove.clear();
    
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
                    if (object.type == OrganismType::Animal)
                        organisms.push_back(new Animal(object.name, newRow, newColumn));
                    else if (object.type == OrganismType::Plant)
                        organisms.push_back(new Plant(object.name, newRow, newColumn));
                    update_world();
                    newRow = newColumn = 999;
                }
            }
        }
    }

    update_world();
}

int World::get_strength_at_square(int row, int column)
{
    for (const auto& organism : organisms)
    {
        if (organism->get_position_row() == row && organism->get_position_column() == column)
            return organism->get_strength();
    }
    return 0;
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
    organisms_file << height << " " << width << "\n";
    for (const auto& organism : organisms)
    {
        string type = (organism->get_type() == OrganismType::Animal) ? "Animal" : (organism->get_type() == OrganismType::Plant) ? "Plant" : "Human";
        organisms_file << type << " " << organism->get_name() << " " << organism->get_strength()  << " " 
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

    for (int i = 0; i < height; i++)
        delete[] board[i];
    delete[] board;
    for (auto& o : organisms)
        delete o;
    organisms.clear();
    
    string line;
    file >> height >> width;
    
    board = new char*[height];
    for (size_t i = 0; i < height; i++)
        board[i] = new char[width];
    
    while (getline(file, line)) 
    {
        string type, name;
        int strength, initiative, row, column;
        file >> type >> name >> strength >> initiative >> row >> column;
        Organism* new_org = nullptr;

        if (type == "Animal")
            new_org = new Animal(name, strength, initiative, row, column);
        else if (type == "Plant")
            new_org = new Plant(name, strength, initiative, row, column);
        else
            new_org = new Human(name, strength, initiative, row, column);

        if (new_org != nullptr)
            organisms.push_back(new_org);
    }
    update_world();
    turn = 1;
    system("clear");
    cout << "We start a new Game!!!\n";
    file.close();
}