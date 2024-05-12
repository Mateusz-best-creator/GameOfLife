#include "world.hpp"
#include <cstdlib> 
#include <ctime> 

int main(int argc, char* argv[]) 
{
    srand((unsigned)time(0)); 
    World world;
    world.draw_world();

    bool isRunning = true;
    while (isRunning) 
    {
        world.draw_world();
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                isRunning = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym) 
                {
                    case SDLK_p:
                        world.play_turn();
                        break;
                    case SDLK_q:
                        exit(EXIT_SUCCESS);
                        break;
                }
            }
        }
    }    
}
