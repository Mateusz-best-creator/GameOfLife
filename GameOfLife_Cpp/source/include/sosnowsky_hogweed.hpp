#pragma once

#include "plant.hpp"

class SosnowskyHogweed : public Plant
{
private:
    static int SOSNOWSKY_HOGWEED_STATIC_COUNTER;

public:
    SosnowskyHogweed(int, int);
    SosnowskyHogweed(int, int, int, int, int);
    ~SosnowskyHogweed();

    virtual ActionResult action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
    bool can_eat(char) const;
};
