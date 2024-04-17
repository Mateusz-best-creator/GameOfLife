#include "belladonna.h"

Belladonna::Belladonna(int row, int column)
    : Plant("Belladonna", row, column)
{
    get_strength() = 99;
    this->get_type() = OrganismType::Belladonna;
}

Belladonna::~Belladonna() {}

void Belladonna::action(char** board, int height, int width)
{
    
}