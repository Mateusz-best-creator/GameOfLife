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
    def __init__(self, screen_height=800, screen_width=800):
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
        options_font_widths = [self.options_font[i].get_width()
                               for i in range(len(self.options_font))]
        self.options_font_left = [self.option_rectangle_left[i] + (
            (self.option_rectangle_width - options_font_widths[i]) / 2) for i in range(len(self.options_font))]
        self.options_font_top = self.option_rectangle_top + \
            self.option_rectangle_height * 0.4

        # Organisms stuff
        self.ORGANISMS_TYPES = 12
        self.organisms = []

        # Grid dimensions
        self.grid_height = 10
        self.grid_width = 10
        self.grid_board = [
            ['e' for _ in range(self.grid_width)] for _ in range(self.grid_height)]
        # Dimensions for all squares in game simulation
        self.squares_top = []
        self.squares_bottom = []
        self.squares_left = []
        self.squares_right = []

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
                self.add_organisms(3, "Human", Human)

    def add_organisms(self, times, name, object_type):
        print("Object type = ", object_type)
        random_row = random.randint(0, self.grid_height - 1)
        random_column = random.randint(0, self.grid_width - 1)
        while self.grid_board[random_row][random_column] == 'e':
            random_row = random.randint(0, self.grid_height - 1)
            random_column = random.randint(0, self.grid_width - 1)
        self.organisms.append(object_type(name, random_row, random_column))
        self.grid_board[random_row][random_column] = self.organisms[len(
            self.organisms) - 1].get_character()

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

    def draw_starting_screen(self):
        self.screen.fill("#ffffff")
        self.screen.blit(self.title, (self.title_left, self.title_top))

        # Text instructions
        instruction_lines = ["During the game press P to go to the next turn. If",
                             "human is alive you will be asked to press one of, the",
                             "arrow keys to move. If human is not alive the game will",
                             "play and the journal will be shown on the left side."]
        instruction_font = pygame.font.SysFont(None, 24)
        instruction_font_color = "#333333"
        instruction_font_text = [instruction_font.render(
            instruction_lines[i], True, instruction_font_color) for i in range(len(instruction_lines))]
        instruction_widths = [instruction_font_text[i].get_width()
                              for i in range(len(instruction_lines))]
        instruction_font_left = [
            (self.screen_width - instruction_widths[i]) / 2 for i in range(len(instruction_lines))]
        INSTRUCTION_FONT_GAP = 18
        INSTRUCTION_FONT_TOP = 0.4
        instruction_font_top = [self.screen_height * INSTRUCTION_FONT_TOP +
                                INSTRUCTION_FONT_GAP * i for i in range(len(instruction_lines))]

        # Draw all 3 option rectangles and all 3 text options
        for i in range(len(self.options_font)):
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
                instruction_font_text[i], (instruction_font_left[i], instruction_font_top[i]))

    def play_simulation(self):
        game_running = True
        self.screen.fill("#ffffff")
        self.draw_simulation_board()
        while game_running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    game_running = False
                elif event.type == pygame.MOUSEBUTTONUP:
                    pos = pygame.mouse.get_pos()
                    click_x, click_y = pos
                    print(f"(x,y) = ({click_x},{click_y})")

            pygame.display.flip()
            self.clock.tick(60)
            pygame.display.update()

    def draw_simulation_board(self):
        color_line = "#000000"
        vertical_line_left = self.screen_width*0.25
        separating_line_thickness = 5
        pygame.draw.line(self.screen, color_line, (vertical_line_left, 0),
                         (vertical_line_left, self.screen_height), separating_line_thickness)
        pygame.draw.line(self.screen, color_line, (vertical_line_left, self.screen_height * 0.8),
                         (self.screen_width, self.screen_height * 0.8), separating_line_thickness)
        playing_board_height = self.screen_height*0.8
        board_line_thickness = 2
        board_line_height = playing_board_height / self.grid_height
        playing_board_width = self.screen_width - vertical_line_left
        board_line_width = playing_board_width / self.grid_width

        # Display playing board
        for i in range(self.grid_height):
            for j in range(self.grid_height):
                self.squares_top.append(j*board_line_height)
                self.squares_bottom.append((j+1)*board_line_height - 1)
            pygame.draw.line(self.screen, color_line, (vertical_line_left, i * board_line_height),
                             (self.screen_width, i * board_line_height), board_line_thickness)
        for i in range(self.grid_width):
            for j in range(self.grid_width):
                self.squares_left.append(
                    vertical_line_left + j * board_line_width)
                self.squares_right.append(
                    vertical_line_left + (j+1) * board_line_width - 1)
            pygame.draw.line(self.screen, color_line, (vertical_line_left + i * board_line_width, 0),
                             (vertical_line_left + i * board_line_width, self.screen_height*0.8))

        # Display all our organisms inside grid
        for organism in self.organisms:
            organism_row = organism.get_position_row()
            organism_column = organism.get_position_column()
            organism.print(self.screen, self.squares_top[organism_row], self.squares_bottom[organism_row],
                           self.squares_left[organism_column], self.squares_right[organism_column])

    def load_simulation(self):
        print("Loading simulation from ./filenames/organisms.txt")
