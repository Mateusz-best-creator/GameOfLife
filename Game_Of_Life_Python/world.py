import pygame
from Organisms.organism import Organism

class World:
    def __init__(self, height = 800, width = 800):
        # Screen stuff
        self.height = height
        self.width = width
        pygame.display.set_caption("Mateusz Wieczorek s197743, World Simluation")

        # Pygame stuff
        pygame.init()
        self.screen = pygame.display.set_mode((height, width))
        self.clock = pygame.time.Clock()
        self.running = True

        # Font stuff
        self.font = pygame.font.SysFont(None, 24)
        self.font1 = pygame.font.SysFont("chalkduster.ttf", 72)
        self.title = self.font1.render("World Simulation", True, "#333333")

        # Organisms stuff
        self.ORGANISMS_TYPES = 12
        self.organisms = []

    def initialize_organisms(self):
        pass
            
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