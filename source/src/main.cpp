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
    world.legend();
    int turn = 0;
    std::cout << "\nTurn " << turn++ << ":\n";
    world.drawWorld();

    while (true)
    {
        std::cout << "\nTurn " << turn++ << ":\n";
        if (!world.makeTurn())
            break;
        //world.update_world();
        world.drawWorld();
    }
}
