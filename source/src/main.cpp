#include <iostream>
#include "world.h"

int main() 
{
    std::cout << "-------------------------\nMateusz Wieczorek s197743\n-------------------------\n" << std::endl;

    int n, m;
    std::cout << "Pls give board dimensions:\nHeight: ";
    std::cin >> n;
    std::cout << "Width: ";
    std::cin >> m;

    World world(n, m);
    world.drawWorld();
}
