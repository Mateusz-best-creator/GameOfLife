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
    def __init__(self, screen_height=600, screen_width=600):
        # Screen stuff
        self.screen_height = screen_height
        self.screen_width = screen_width
        pygame.display.set_caption(
            "Mateusz Wieczorek s197743, World Simluation")

        # Pygame stuff
        pygame.init()
        self.screen = pygame.display.set_mode(
            (screen_height, screen_width))  # screen is our main surface
        self.clock = pygame.time.Clock()
        self.running = True

        # Font stuff

        # Title font
        self.font_title = pygame.font.SysFont("chalkduster.ttf", 72)
        self.title = self.font_title.render(
            "World Simulation", True, "#333333")
        self.title_width = self.title.get_width()
        self.title_left = (self.screen_width - self.title_width) / 2
        self.title_top = self.screen_height * 0.1

        # Organisms stuff
        self.ORGANISMS_TYPES = 12
        self.organisms = []

        # Initial screen stuff
        self.option_rectangle_width = self.screen_width / 3 - 50
        self.option_rectangle_height = self.screen_height * 0.15
        self.option_rectangle_offset = (
            self.screen_width - 3 * self.option_rectangle_width) / 4
        self.option_rectangle_left = []
        self.option_rectangle_top = self.screen_height * 0.7
        for i in range(1, 3+1):
            self.option_rectangle_left.append(
                self.option_rectangle_offset * i + (i - 1) * self.option_rectangle_width)

        # Option font
        self.font_option = pygame.font.SysFont("chalkduster.ttf", 24)
        self.option_font_color = "#333333"
        self.options_font = [self.font_option.render("Start Simulation", True, self.option_font_color),
                             self.font_option.render(
                                 "Load Simulation", True, self.option_font_color),
                             self.font_option.render("Quit Simulation", True, self.option_font_color)]
        self.options_font_left = [self.option_rectangle_left[i] +
                                  self.option_rectangle_width * 0.11 for i in range(3)]
        self.options_font_top = self.option_rectangle_top + \
            self.option_rectangle_height * 0.4

    def initialize_organisms(self):
        for index in range(1, self.ORGANISMS_TYPES + 1):

            random_amount = random.randrange(1, 3 + 1)

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
        self.initialize_organisms()
        self.draw_starting_screen()
        while self.running:
            # poll for events
            # pygame.QUIT event means the user clicked X to close your window
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False

            pygame.display.flip()
            self.clock.tick(60)
            pygame.display.update()

    def add_organisms(self, times, name, object_type):
        pass

    def draw_starting_screen(self):
        self.screen.fill("#ffffff")
        self.screen.blit(self.title, (self.title_left, self.title_top))
        # Draw all 3 option rectangles and all 3 text options
        for i in range(3):
            pygame.draw.rect(self.screen,
                             "#fc0101",
                             pygame.Rect(self.option_rectangle_left[i], self.option_rectangle_top, self.option_rectangle_width, self.option_rectangle_height), 2)

            self.screen.blit(
                self.options_font[i], (self.options_font_left[i], self.options_font_top))
