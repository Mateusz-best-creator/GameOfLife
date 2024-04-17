#include "sosnowsky_hogweed.h"
#include <iostream>

SosnowskyHogweed::SosnowskyHogweed(int row, int column)
    : Plant("Sow_thistle", row, column)
{
    get_strength() = 0;
    this->get_type() = OrganismType::SosnowskyHogweed;
}

SosnowskyHogweed::~SosnowskyHogweed() {}

// Do nothing
void SosnowskyHogweed::action(char** board, int height, int width)
{
    return;
}