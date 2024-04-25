#include "guarana.h"

Guarana::Guarana(int row, int column)
	: Plant("Guarana", row, column)
{
	get_strength() = 0;
	this->get_type() = OrganismType::Guarana;
}

Guarana::~Guarana() {}

void Guarana::action(char** board, int height, int width)
{
	Plant::default_action();
}