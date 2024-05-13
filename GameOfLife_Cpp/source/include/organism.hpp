#pragma once

#include <string>
#include <vector>
#include "SDL2/SDL.h"

enum class ActionType
{
    MOVE,
    STAY
};
enum class CollisionType
{
    FIGHT,
    MULTIPLICATION,
    NONE
};
enum class OrganismType : unsigned char
{
    HUMAN = 'H',
    WOLF = 'w',
    SHEEP = 's',
    TURTLE = 't',
    FOX = 'f',
    GRASS = 'G'
};

struct Point
{
    int row, col;
    Point() : row(0), col(0) {}
    Point(int r, int c) : row(r), col(c) {}
};

struct CollisionResult
{
    CollisionType type;
    std::vector<int> organism_indexes;
    Point point;
    OrganismType organism_type_to_add;

    CollisionResult(CollisionType t, Point i, OrganismType o_type) : type(t), point(i), organism_type_to_add(o_type) {}
    CollisionResult(CollisionType t, std::vector<int> i) : type(t), organism_indexes(i) {}
    CollisionResult(CollisionType t) : type(t) {}
};

class Organism
{
protected:
    enum class Direction : int
    {
        LEFT = 1,
        TOP = 2,
        RIGHT = 3,
        BOTTOM = 4,
        NONE = 5,
    };
    int row, column, age = 0, previous_row = -1, previous_column = -1;
    static const int MAX_ORGANISM_AMOUNT = 5;
    static const int BOARD_HEIGHT = 10, BOARD_WIDTH = 10;

private:
    int strength, initiative, default_strength;
    std::string name, filepath;
    unsigned char character;
    OrganismType type;
    static const int GUARANA_STRENGTH_INCREASE = 3;
    SDL_Texture *img = NULL;

public:
    // Constructors and destructors
    Organism(int, int, std::string, unsigned char, int, int, std::string, OrganismType);
    virtual ~Organism();

    // Setters and getters
    const int& get_strength() const { return this->strength; }
    int& get_strength() { return this->strength; }
    const int& get_initiative() const { return this->initiative; }
    const std::string& get_name() const { return this->name; }
    const unsigned char& get_character() const { return this->character; }
    const int& get_row() const { return this->row; }
    const int& get_column() const { return this->column; }
    const OrganismType& get_type() const { return this->type; }
    const int& get_age() const { return this->age; }
    int& get_age() { return this->age; }


    // Methods
    void draw(SDL_Renderer*, int, int, int, int);
    void move_message() const;
    void move_left();
    void move_top();
    void move_right();
    void move_bottom();

    // Virtual methods
    virtual ActionType action(std::vector<std::vector<char>>&) = 0;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) = 0;
    virtual int get_static_counter() = 0;
};