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


class OptionType(Enum):
    NONE = 0
    PLAY_SIMULATION = 1
    LOAD_SIMULATION = 2
    QUIT_SIMULATION = 3


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

        # Title font
        self.font_title = pygame.font.SysFont("chalkduster.ttf", 72)
        self.title = self.font_title.render(
            "World Simulation", True, "#333333")
        self.title_width = self.title.get_width()
        self.title_left = (self.screen_width - self.title_width) / 2
        self.title_top = self.screen_height * 0.1

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

        # Option chosen by user
        self.chosen_option = OptionType.NONE

        # Option font
        self.font_option = pygame.font.SysFont("chalkduster.ttf", 24)
        self.option_font_color = "#333333"
        self.options_font = [self.font_option.render("Start Simulation", True, self.option_font_color),
                             self.font_option.render(
                                 "Load Simulation", True, self.option_font_color),
                             self.font_option.render("Quit Simulation", True, self.option_font_color)]
        self.options_font_left = [self.option_rectangle_left[i] +
                                  self.option_rectangle_width * 0.1 for i in range(3)]
        self.options_font_top = self.option_rectangle_top + \
            self.option_rectangle_height * 0.4

        # Organisms stuff
        self.ORGANISMS_TYPES = 12
        self.organisms = []

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
            for event in pygame.event.get():
                # pygame.QUIT event means the user clicked X to close your window
                if event.type == pygame.QUIT:
                    self.running = False
                elif event.type == pygame.MOUSEBUTTONUP:
                    pos = pygame.mouse.get_pos()

                    click_x, click_y = pos
                    # print("(x, y) = ", click_x, click_y)
                    if click_y >= self.option_rectangle_top and click_y <= self.option_rectangle_top + self.option_rectangle_height:
                        for index, option_left_distance in enumerate(self.option_rectangle_left):
                            if click_x >= option_left_distance and click_x <= option_left_distance + self.option_rectangle_width:
                                self.chosen_option = OptionType(index + 1)

            pygame.display.flip()
            self.clock.tick(60)
            pygame.display.update()

            if self.chosen_option == OptionType.PLAY_SIMULATION:
                self.play_simulation()
                self.draw_starting_screen()
            elif self.chosen_option == OptionType.LOAD_SIMULATION:
                self.load_simulation()
                self.draw_starting_screen()
            elif self.chosen_option == OptionType.QUIT_SIMULATION:
                self.running = False
            self.chosen_option = OptionType.NONE

    def add_organisms(self, times, name, object_type):
        pass

    def draw_starting_screen(self):
        self.screen.fill("#ffffff")
        self.screen.blit(self.title, (self.title_left, self.title_top))

        # Text instructions
        instruction_lines = ["During the game press P to go to the next turn. If",
                             "human is alive you will be asked to press one of, the",
                             "arrow keys to move. If human is not alive the game will",
                             "play and the journal will be shown on the left side."]
        instruction_font = pygame.font.SysFont("chalkduster.ttf", 24)
        instruction_font_color = "#333333"
        instruction_font_text = [instruction_font.render(
            instruction_lines[i], True, instruction_font_color) for i in range(len(instruction_lines))]
        instruction_width = instruction_font_text[len(
            instruction_lines) - 1].get_width()
        instruction_font_left = (self.screen_width - instruction_width) / 2
        INSTRUCTION_FONT_GAP = 18
        instruction_font_top = [self.screen_height * 0.4 +
                                INSTRUCTION_FONT_GAP * i for i in range(len(instruction_lines))]
        instruction_width = instruction_font_text[len(
            instruction_lines) - 1].get_width()

        # Draw all 3 option rectangles and all 3 text options
        for i in range(3):
            pygame.draw.rect(self.screen,
                             "#000000",
                             pygame.Rect(self.option_rectangle_left[i], self.option_rectangle_top, self.option_rectangle_width, self.option_rectangle_height), 2)
            # Subtracting 4 to account for the border thickness
            inner_rect_width = self.option_rectangle_width - 4
            inner_rect_height = self.option_rectangle_height - 4
            # Adding 2 to offset the border
            inner_rect_left = self.option_rectangle_left[i] + 2
            inner_rect_top = self.option_rectangle_top + 2
            pygame.draw.rect(self.screen,
                             "#c0c0c0",
                             pygame.Rect(inner_rect_left, inner_rect_top, inner_rect_width, inner_rect_height))

            self.screen.blit(
                self.options_font[i], (self.options_font_left[i], self.options_font_top))
        for i in range(len(instruction_lines)):
            self.screen.blit(
                instruction_font_text[i], (instruction_font_left, instruction_font_top[i]))

    def play_simulation(self):
        game_running = True
        self.screen.fill("#111141")
        print("running game!")
        while game_running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    game_running = False

            pygame.display.flip()
            self.clock.tick(60)
            pygame.display.update()

    def load_simulation(self):
        pass
