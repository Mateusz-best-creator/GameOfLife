#pragma once

#include "plant.h"

class SosnowskyHogweed : public Plant
{
public:
	SosnowskyHogweed(int, int);
	~SosnowskyHogweed();
	void action(char**, int, int) override;
};