from world import World
import pygame

if __name__ == "__main__":
    world = World()
    world.initialize_organisms()
    world.run()
    pygame.quit()
