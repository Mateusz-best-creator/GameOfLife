import pygame
from enum import Enum
import random

from Organisms.Animals.human import Human

# Enum type for types of organisms
class OrganismType(Enum):
    WOLF = 1
    SHEEP = 2
    FOX = 3
    TURTLE = 4
    ANTELOPE = 5
    CYBER_SHEEP = 6
    GRASS = 7
    SOW_THISTLE = 8
    GUARANA = 9
    BELLADONNA = 10
    SOSNOWSKY_HOGWEED = 11
    HUMAN = 12

class World:
    def __init__(self, screen_height = 600, screen_width = 600):
        # Screen stuff
        self.screen_height = screen_height
        self.screen_width = screen_width
        pygame.display.set_caption("Mateusz Wieczorek s197743, World Simluation")

        # Pygame stuff
        pygame.init()
        self.screen = pygame.display.set_mode((screen_height, screen_width))
        self.clock = pygame.time.Clock()
        self.running = True

        # Font stuff
        self.font = pygame.font.SysFont(None, 24)
        self.font1 = pygame.font.SysFont("chalkduster.ttf", 72)
        self.title = self.font1.render("World Simulation", True, "#333333")

        # Organisms stuff
        self.ORGANISMS_TYPES = 12
        self.organisms = []

        # Board stuff
        self.height = 10
        self.width = 10

    def initialize_organisms(self):
        for index in range(1, self.ORGANISMS_TYPES + 1):

            random_amount = random.randrange(1, 3 + 1)
            print("RAnd = ", random_amount)
            
            # Map index to a type name
            type = OrganismType(index)
            if type == OrganismType.WOLF:
                pass
            elif type == OrganismType.WOLF:
                pass
            elif type == OrganismType.SHEEP:
                pass
            elif type == OrganismType.FOX:
                pass
            elif type == OrganismType.TURTLE:
                pass
            elif type == OrganismType.ANTELOPE:
                pass
            elif type == OrganismType.CYBER_SHEEP:
                pass
            elif type == OrganismType.GRASS:
                pass
            elif type == OrganismType.SOW_THISTLE:
                pass
            elif type == OrganismType.GUARANA:
                pass
            elif type == OrganismType.BELLADONNA:
                pass
            elif type == OrganismType.SOSNOWSKY_HOGWEED:
                pass
            elif type == OrganismType.HUMAN:
                self.organisms.append(Human("Human", 1, 1))
    
    def run(self):
        while self.running:
            # poll for events
            # pygame.QUIT event means the user clicked X to close your window
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False

            self.screen.fill("#ffffff")
            self.screen.blit(self.title, (200, 40))


            pygame.display.flip()
            self.clock.tick(60)
            pygame.display.update()

    def add_organisms(self, times, name, object_type):
        pass





