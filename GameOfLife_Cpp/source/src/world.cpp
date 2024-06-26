#include <iostream>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "world.hpp"
#include "human.hpp"
#include "wolf.hpp"
#include "sheep.hpp"
#include "fox.hpp"
#include "turtle.hpp"
#include "antelope.hpp"
#include "cyber_sheep.hpp"
#include "grass.hpp"
#include "sow_thistle.hpp"
#include "guarana.hpp"
#include "belladonna.hpp"
#include "sosnowsky_hogweed.hpp"

World::World()
    : grid_board(BOARD_SIZE, std::vector<char>(BOARD_SIZE, 'e'))
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create a window
    window = SDL_CreateWindow(
        "GameOfLife",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->WINDOW_HEIGHT, this->WINDOW_WIDTH,
        SDL_WINDOW_SHOWN
    );
    if (!window) 
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) 
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    this->initialize_organisms();
}

World::~World()
{
    std::cout << "Clearning world... BYE..." << std::endl;
    for (auto& o : this->organisms)
        delete o;
    this->organisms.clear();

    if (renderer) 
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) 
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void World::initialize_organisms()
{
    char characters[] = {'H', 'w', 's', 'f', 't', 'a', 'c', 'G', 'S', 'B', 'U', 'O'};

    for (char character : characters)
    {
        int random_amount = rand() % MAX_RANDOM_AMOUNT + 1;
        this->add_organism(random_amount, static_cast<OrganismType>(character));
    }
    this->update_grid_board();
}

void World::add_organism(int random_amount, OrganismType type, int specified_row, int specified_column)
{
    // We always want one human at the board
    if (type == OrganismType::HUMAN)
        random_amount = 1;
    
    // Add Organism random amount of times
    for (int i = 0; i < random_amount; i++)
    {
        int random_row = -1, random_column = -1;
        if (specified_row != -1 && specified_column != -1)
        {
            random_row = specified_row;
            random_column = specified_column;
        }
        else
        {
            do
            {
                random_row = rand() % this->BOARD_SIZE;
                random_column = rand() % this->BOARD_SIZE;
                assert(0 <= random_row && random_row < BOARD_SIZE && 0 <= random_column && random_column < BOARD_SIZE);
            } while (this->grid_board[random_row][random_column] != 'e');
        }

        switch (type)
        {
            case OrganismType::HUMAN:
                this->organisms.push_back(new Human(random_row, random_column));
                break;
            case OrganismType::WOLF:
                this->organisms.push_back(new Wolf(random_row, random_column));
                break;
            case OrganismType::SHEEP:
                this->organisms.push_back(new Sheep(random_row, random_column));
                break;
            case OrganismType::FOX:
                this->organisms.push_back(new Fox(random_row, random_column));
                break;
            case OrganismType::TURTLE:
                this->organisms.push_back(new Turtle(random_row, random_column));
                break;
            case OrganismType::ANTELOPE:
                this->organisms.push_back(new Antelope(random_row, random_column));
                break;
            case OrganismType::CYBER_SHEEP:
                this->organisms.push_back(new CyberSheep(random_row, random_column));
                break;
            case OrganismType::GRASS:
                this->organisms.push_back(new Grass(random_row, random_column));
                break;
            case OrganismType::SOW_THISTLE:
                this->organisms.push_back(new SowThistle(random_row, random_column));
                break;
            case OrganismType::GUARANA:
                this->organisms.push_back(new Guarana(random_row, random_column));
                break;    
            case OrganismType::BELLADONNA:
                this->organisms.push_back(new Belladonna(random_row, random_column));
                break;
            case OrganismType::SOSNOWSKY_HOGWEED:
                this->organisms.push_back(new SosnowskyHogweed(random_row, random_column));
                break;
            default:
                std::cout << "Incorrect organism type...\n";
                break;
        }
        if (!this->organisms.empty())
            this->grid_board[random_row][random_column] = this->organisms[this->organisms.size() - 1]->get_character();
    }
}

void World::draw_world() 
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Calculate the width and height of each cell
    int cellWidth = WINDOW_WIDTH / BOARD_SIZE;
    int cellHeight = WINDOW_HEIGHT / BOARD_SIZE;

    for (const auto& organism : this->organisms)
    {
        organism->draw(this->renderer, this->IMAGE_HEIGHT, this->IMAGE_WIDTH, organism->get_column() * cellWidth, organism->get_row() * cellHeight);
    }

    // Draw vertical & horizontal lines
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    for (int i = 1; i < BOARD_SIZE; i++)
        SDL_RenderDrawLine(renderer, i * cellWidth, 0, i * cellWidth, WINDOW_HEIGHT);
    for (int j = 1; j < BOARD_SIZE; j++)
        SDL_RenderDrawLine(renderer, 0, j * cellHeight, WINDOW_WIDTH, j * cellHeight);

    // Present the renderer
    SDL_RenderPresent(renderer);
}

bool is_in_set(const std::set<int>& set, int value)
{
    for (const auto& v : set)
    {
        if (value == v)
            return true;
    }
    return false;
}

void World::play_turn()
{
    this->sort_organisms();
    std::cout << "\n### Turn number " << this->turn_number << " ###\n" << std::endl;
    int index = 0;

    this->update_grid_board();

    for (auto& organism : this->organisms)
    {
        organism->get_age()++;
     
        if (is_in_set(organism_indexes_to_remove, index))
        {
            index++;
            continue;
        }

        ActionResult action_result = organism->action(this->grid_board);
        CollisionResult collision_result = organism->collision(this->grid_board, this->organisms, index);

        switch (action_result.type)
        {
            case ActionType::SOW:
                this->points_to_multiply.push_back(action_result.point);
                this->o_types.push_back(action_result.orgainsm_type_to_add);
                break;
            case ActionType::KILLING:
                for (const Point& point : action_result.points_to_remove)
                {
                    int local_organism_index = 0;
                    for (const auto& o : this->organisms)
                    {
                        if (o->get_row() == point.row && o->get_column() == point.col)
                        {
                            this->organism_indexes_to_remove.insert(local_organism_index);
                            break;
                        }
                        local_organism_index++;
                    }
                }
                break;
            case ActionType::MOVE:
            case ActionType::STAY:
            default:
                break;
        }
        switch (collision_result.type)
        {
            case CollisionType::FIGHT:
                for (const int& index : collision_result.organism_indexes)
                    organism_indexes_to_remove.insert(index);
                break;
            case CollisionType::MULTIPLICATION:
                this->points_to_multiply.push_back(collision_result.point);
                this->o_types.push_back(collision_result.organism_type_to_add);
                break;
            case CollisionType::NONE:
            default:
                break;
        }
        index++;
    }

    this->turn_number++;

    remove_organisms();
    multiply_organisms();
    update_grid_board();
}

void World::sort_organisms()
{
    std::sort(organisms.begin(), organisms.end(), [](const Organism* first, const Organism* second)
    {
        int initiative_one = first->get_initiative(), initiative_two = second->get_initiative();
        if (first->get_type() == OrganismType::HUMAN)
            return true;
        else if (second->get_type() == OrganismType::HUMAN)
            return false;
        else if (initiative_one == initiative_two)
            return first->get_age() > second->get_age();
        return initiative_one > initiative_two;
    });
}

void World::update_grid_board()
{
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            this->grid_board[i][j] = 'e';
    for (auto& o : this->organisms)
        this->grid_board[o->get_row()][o->get_column()] = o->get_character();
}

void World::modify_grid_board(int row, int column, char ch)
{
    assert(row >= 0 && row < this->BOARD_SIZE && column >= 0 && column < this->BOARD_SIZE);
    this->grid_board[row][column] = ch;
}

void World::remove_organisms()
{
    std::vector<int> i_remove(organism_indexes_to_remove.begin(), organism_indexes_to_remove.end());
    std::sort(i_remove.begin(), i_remove.end(), std::greater<int>());
    for (size_t index : i_remove)
    {
        assert(index < this->organisms.size());
        auto o = organisms[index];
        std::cout << "Removing " << o->get_name() << " at (" << o->get_row() << ", " << o->get_column() << ")\n";
        delete organisms.at(index);
        organisms.erase(organisms.begin() + index);
    }
    this->organism_indexes_to_remove.clear();
}

void World::multiply_organisms()
{
    for (size_t i = 0; i < points_to_multiply.size(); i++)
    {
        bool added = false;
        Point point = points_to_multiply.at(i);
        OrganismType type = o_types.at(i);

        for (int j = -1; j <= 1; j++)
        {
            for (int k = -1; k <= 1; k++)
            {
                if (j == 0 && k == 0)
                    continue;
                int new_row = point.row + j;
                int new_column = point.col + k;

                if (new_row < 0 || new_row >= BOARD_SIZE || new_column < 0 || new_column >= BOARD_SIZE)
                    continue;
                assert(new_row >= 0 && new_row < BOARD_SIZE && new_column >= 0 && new_column < BOARD_SIZE);
                if (grid_board[new_row][new_column] == 'e')
                {
                    std::cout << "Creating new " << static_cast<char>(type) << " at (" << new_row << ", " << new_column << ")\n";
                    this->add_organism(1, type, new_row, new_column);
                    added = true;
                    break;
                }
            }
            if (added)
                break;
        }
    }
    this->points_to_multiply.clear();
    this->o_types.clear();
}

void World::save_to_file()
{
    std::cout << "Saving state of the game to " << FILEPATH << std::endl;
    std::ofstream file(FILEPATH);

    if (!file.is_open())
    {
        std::cout << "Error opening " << FILEPATH << std::endl;
        exit(EXIT_FAILURE);
    }

    for (const auto& organism : this->organisms)
    {
        if (organism->get_type() == OrganismType::HUMAN)
        {
            Human* original = static_cast<Human*>(organism);
            Human* temp = new Human(*original);
            file << temp->get_character() << " " << temp->get_strength() << " " << temp->get_initiative() << " " << temp->get_age()
            << " " << temp->get_row() << " " << temp->get_column() << " " << temp->get_ability_activated() << " " << temp->get_ability_counter() 
            << " " << temp->get_default_strength() << std::endl;
            delete temp;
        }
        else
            file << organism->get_character() << " " << organism->get_strength() << " " << organism->get_initiative() << " " 
            << organism->get_age() << " " << organism->get_row() << " " << organism->get_column() << std::endl;
    }
}

void World::read_from_file()
{
    std::cout << "Loading state of the game from " << FILEPATH << std::endl;
    std::ifstream file(FILEPATH);

    if (!file.is_open())
    {
        std::cout << "Error opening " << FILEPATH << std::endl;
        exit(EXIT_FAILURE);
    }

    for (auto& o : this->organisms)
        delete o;
    this->organisms.clear();

    std::string line;
    while (getline (file, line)) 
    {
        // Human case
        if (line[0] == 'H')
        {
            std::istringstream iss(line);
            char arg0;
            int strength, initiative, age, row, col;
            char activated;
            int counter, def_strength;
            iss >> arg0 >> strength >> initiative >> age >> row >> col >> activated >> counter >> def_strength;
            bool is_activated = activated == 'Y' ? true : false;
            this->organisms.push_back(new Human(row, col, strength, initiative, age, is_activated, counter, def_strength));
        }
        else
        {
            std::istringstream iss(line);
            char arg0;
            int strength, initiative, age, row, col;
            iss >> arg0 >> strength >> initiative >> age >> row >> col;

            OrganismType type = static_cast<OrganismType>(arg0);
            switch (type)
            {
                case OrganismType::WOLF:
                    this->organisms.push_back(new Wolf(row, col, strength, initiative, age));
                    break;
                case OrganismType::SHEEP:
                    this->organisms.push_back(new Sheep(row, col, strength, initiative, age));
                    break;
                case OrganismType::FOX:
                    this->organisms.push_back(new Fox(row, col, strength, initiative, age));
                    break;
                case OrganismType::TURTLE:
                    this->organisms.push_back(new Turtle(row, col, strength, initiative, age));
                    break;
                case OrganismType::ANTELOPE:
                    this->organisms.push_back(new Antelope(row, col, strength, initiative, age));
                    break;
                case OrganismType::CYBER_SHEEP:
                    this->organisms.push_back(new CyberSheep(row, col, strength, initiative, age));
                    break;
                case OrganismType::GRASS:
                    this->organisms.push_back(new Grass(row, col, strength, initiative, age));
                    break;
                case OrganismType::SOW_THISTLE:
                    this->organisms.push_back(new SowThistle(row, col, strength, initiative, age));
                    break;
                case OrganismType::GUARANA:
                    this->organisms.push_back(new Guarana(row, col, strength, initiative, age));
                    break;    
                case OrganismType::BELLADONNA:
                    this->organisms.push_back(new Belladonna(row, col, strength, initiative, age));
                    break;
                case OrganismType::SOSNOWSKY_HOGWEED:
                    this->organisms.push_back(new SosnowskyHogweed(row, col, strength, initiative, age));
                    break;
                default:
                    std::cout << "Incorrect organism type...\n";
                    break;
            }
        }
        std::cout << "Line = " << line << std::endl;
    }
    this->update_grid_board();
}