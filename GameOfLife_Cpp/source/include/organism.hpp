#pragma once

#include <string>
#include <vector>
#include "SDL2/SDL.h"

enum class ActionType
{
    MOVE,
    STAY,
    SOW,
    KILLING
};
enum class CollisionType
{
    FIGHT,
    MULTIPLICATION,
    POISON_PLANT,
    NONE
};
enum class OrganismType : unsigned char
{
    HUMAN = 'H',
    WOLF = 'w',
    SHEEP = 's',
    FOX = 'f',
    TURTLE = 't',
    ANTELOPE = 'a',
    CYBER_SHEEP = 'c',
    GRASS = 'G',
    SOW_THISTLE = 'S',
    GUARANA = 'U',
    BELLADONNA = 'B',
    SOSNOWSKY_HOGWEED = 'O',
};

struct Point
{
    int row, col;
    Point() : row(0), col(0) {}
    Point(int r, int c) : row(r), col(c) {}
    Point(const Point& p) : row(p.row), col(p.col) {}
};

struct ActionResult
{
    ActionType type;
    Point point;
    OrganismType orgainsm_type_to_add;
    std::vector<Point> points_to_remove;

    ActionResult(ActionType t, Point p, OrganismType o_type) : type(t), point(p), orgainsm_type_to_add(o_type) {}
    ActionResult(ActionType t, const std::vector<Point> p)
    {
        type = t;
        for (auto point : p)
            points_to_remove.push_back(point);
    }
    ActionResult(ActionType t) : type(t) {}
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
    int row, column, age, previous_row = -1, previous_column = -1;
    static const int MAX_ORGANISM_AMOUNT = 6;
    static const int BOARD_HEIGHT = 10, BOARD_WIDTH = 10;

private:
    int strength, initiative, default_strength;
    std::string name, filepath;
    char character;
    OrganismType type;
    static const int GUARANA_STRENGTH_INCREASE = 3;
    SDL_Texture *img = NULL;

public:
    // Constructors and destructors
    Organism(int, int, int, std::string, char, int, int, std::string, OrganismType);
    virtual ~Organism();

    // Setters and getters
    const int& get_strength() const { return this->strength; }
    int& get_strength() { return this->strength; }
    const int& get_initiative() const { return this->initiative; }
    const std::string& get_name() const { return this->name; }
    const char& get_character() const { return this->character; }
    const int& get_row() const { return this->row; }
    const int& get_column() const { return this->column; }
    const OrganismType& get_type() const { return this->type; }
    const int& get_age() const { return this->age; }
    int& get_age() { return this->age; }
    const int& get_default_strength() const { return this->default_strength; }
    int& get_default_strength() { return this->default_strength; }

    // Methods
    void draw(SDL_Renderer*, int, int, int, int);
    void move_message() const;
    void move_left();
    void move_top();
    void move_right();
    void move_bottom();
    void default_grid_update(std::vector<std::vector<char>>& grid_board) const;

    // Virtual methods
    virtual ActionResult action(std::vector<std::vector<char>>&) = 0;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) = 0;
    virtual int get_static_counter() = 0;
};