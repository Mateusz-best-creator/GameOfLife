from world import World
import pygame

if __name__ == "__main__":
    world = World()
    world.run()
    world.initialize_organisms()
    pygame.quit()
