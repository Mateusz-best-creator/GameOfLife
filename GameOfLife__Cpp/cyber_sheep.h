#pragma once

#include "animal.h"

class CyberSheep : public Animal
{
public:
	CyberSheep(int, int);
	CyberSheep(int, int, int, int);
	~CyberSheep();
	void action(char** board, int height, int width) override;
	bool return_is_sosnowsky(char** board, int& row, int& col, int height, int width);
};