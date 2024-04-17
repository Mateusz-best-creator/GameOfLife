#include "grass.h"

Grass::Grass(int row, int column)
	: Plant("Grass", row, column)
{
	get_strength() = 0;
	this->get_type() = OrganismType::Grass;
}

Grass::~Grass() {}

void Grass::action(char** board, int height, int width)
{
	Plant::default_action();
}