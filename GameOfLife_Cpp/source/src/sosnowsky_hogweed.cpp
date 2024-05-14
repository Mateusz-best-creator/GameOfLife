#include "sosnowsky_hogweed.hpp"
#include <cassert>
#include <iostream>

int SosnowskyHogweed::SOSNOWSKY_HOGWEED_STATIC_COUNTER = 0;

SosnowskyHogweed::SosnowskyHogweed(int row, int column)
    : Plant(10, 0, 0, "SosnowskyHogweed", 'O', row, column, "sosnowsky_hogweed.png", OrganismType::SOSNOWSKY_HOGWEED)
{
    SOSNOWSKY_HOGWEED_STATIC_COUNTER++;
}

SosnowskyHogweed::SosnowskyHogweed(int row, int column, int strength, int initiative, int age)
    : Plant(strength, initiative, age, "SosnowskyHogweed", 'O', row, column, "sosnowsky_hogweed.png", OrganismType::SOSNOWSKY_HOGWEED)
{
    SOSNOWSKY_HOGWEED_STATIC_COUNTER++;
}

SosnowskyHogweed::~SosnowskyHogweed()
{
    SOSNOWSKY_HOGWEED_STATIC_COUNTER--;
}

ActionResult SosnowskyHogweed::action(std::vector<std::vector<char>>& grid_board)
{
    std::vector<Point> points;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            int new_row = row + i;
            int new_column = column + j;
            if (!(new_row >= 0 && new_row < BOARD_HEIGHT && new_column >= 0 && new_column < BOARD_WIDTH))
                continue;
            assert(new_row >= 0 && new_row < BOARD_HEIGHT && new_column >= 0 && new_column < BOARD_WIDTH);
            if (can_eat(grid_board[new_row][new_column]))
            {
                points.push_back(Point(new_row, new_column));
                std::cout << this->get_name() << " at (" << row << ", " << column << ") eats " << grid_board[new_row][new_column] << " at (" << new_row << ", " << new_column << ")\n";
            }
        }
    }
    return ActionResult(ActionType::KILLING, points);
}

CollisionResult SosnowskyHogweed::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_plant();
}

int SosnowskyHogweed::get_static_counter()
{
    return SOSNOWSKY_HOGWEED_STATIC_COUNTER;
}

bool SosnowskyHogweed::can_eat(char ch) const
{
    return ch == 'w' || ch == 's' || ch == 'H' || ch == 'f' || ch == 'a' || ch == 't';
}