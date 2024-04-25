#include "sow_thistle.h"

SowThistle::SowThistle(int row, int column)
	: Plant("Sow_thistle", row, column)
{
	get_strength() = 0;
    this->get_type() = OrganismType::SowThistle;
}

SowThistle::~SowThistle() {}

void SowThistle::action(char** board, int height, int width)
{
    for (size_t i = 0; i < 3; i++)
    {
        Plant::default_action();
        if (this->get_can_sow()) break;
    }
}