#ifndef __HELPER_H__
#define __HELPER_H__

#include <map>
#include <string>

struct AnimalInfo
{
    int strength, initiative;
    char character;

    AnimalInfo(int s = 0, int i = 0, char c = ' ')
        : strength(s), initiative(i), character(c) {}
};

extern std::map<std::string, AnimalInfo> animalsInfo;

struct PlantInfo
{
    int strength;
    char character;

    PlantInfo(int s = 0, char c = ' ')
        : strength(s), character(c) {}
};

extern std::map<std::string, PlantInfo> plantsInfo;

#endif
