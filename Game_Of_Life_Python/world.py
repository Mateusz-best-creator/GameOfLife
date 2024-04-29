import pygame
from enum import Enum
import random
from helper import merge_sort

from Organisms.Animals.human import Human
from Organisms.Animals.wolf import Wolf
from Organisms.Animals.sheep import Sheep
from Organisms.Animals.turtle import Turtle
from Organisms.Animals.fox import Fox
from Organisms.Animals.antelope import Antelope
from Organisms.Animals.cyber_sheep import CyberSheep

from Organisms.Plants.grass import Grass
from Organisms.Plants.belladonna import Belladonna
from Organisms.Plants.sosnowsky_hogweed import SosnowskyHogweed
from Organisms.Plants.sow_thistle import SowThistle
from Organisms.Plants.guarana import Guarana

from Organisms.animal import CollisionTypes
import os

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
        self.JOURNAL_FILENAME = "journal.txt"
        self.SAVED_STATE_FILENAME = "organisms.txt"
        self.turn_number = 0

        # Pygame stuff
        pygame.init()
        self.screen = pygame.display.set_mode(
            (screen_height, screen_width))  # screen is our main surface
        self.clock = pygame.time.Clock()
        self.running = True
        self.is_human = True

        # Title font
        self.font_title = pygame.font.SysFont(
            "chalkduster.ttf", int(self.screen_height * 0.085))
        self.title = self.font_title.render("World Simulation", True, "#333333")
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
        self.font_option = pygame.font.SysFont(
            "chalkduster.ttf", int(self.screen_height * 0.085 * 0.45))
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

        self.organisms_to_add = []
        self.organisms_indexes_to_remove = []

    def initialize_organisms(self):
        for index in range(1, self.ORGANISMS_TYPES + 1):

            random_amount = random.randrange(1, 3 + 1)

            # Map index to a type name
            type = OrganismType(index)
            if type == OrganismType.HUMAN:
                # We always want 1 human at the board
                self.add_organisms(1, "Human", Human)
            elif type == OrganismType.WOLF:
                self.add_organisms(4, "wolf", Wolf)
            elif type == OrganismType.SHEEP:
                self.add_organisms(random_amount, "sheep", Sheep)
            elif type == OrganismType.FOX:
                self.add_organisms(random_amount, "fox", Fox)
            elif type == OrganismType.TURTLE:
                self.add_organisms(random_amount, "turtle", Turtle)
            elif type == OrganismType.ANTELOPE:
                self.add_organisms(random_amount, "antelope", Antelope)
            elif type == OrganismType.CYBER_SHEEP:
                self.add_organisms(random_amount, "cyber_sheep", CyberSheep)
            elif type == OrganismType.GRASS:
                self.add_organisms(random_amount, "Grass", Grass)
            elif type == OrganismType.SOW_THISTLE:
                self.add_organisms(random_amount, "Sow_thistle", SowThistle)
            elif type == OrganismType.GUARANA:
                self.add_organisms(random_amount, "Guarana", Guarana)
            elif type == OrganismType.BELLADONNA:
                self.add_organisms(random_amount, "Belladonna", Belladonna)
            elif type == OrganismType.SOSNOWSKY_HOGWEED:
                self.add_organisms(random_amount, "Sosnowsky_hogweed", SosnowskyHogweed)

    def add_organisms(self, times, name, object_type):
        for _ in range(times):
            random_row = random.randint(0, self.grid_height - 1)
            random_column = random.randint(0, self.grid_width - 1)
            while self.grid_board[random_row][random_column] != 'e':
                random_row = random.randint(0, self.grid_height - 1)
                random_column = random.randint(0, self.grid_width - 1)
            self.organisms.append(object_type(name, random_row, random_column))
            self.grid_board[random_row][random_column] = self.organisms[len(
                self.organisms) - 1].get_character()

    def update_grid_board(self):
        self.grid_board = [['e' for _ in range(self.grid_width)] for _ in range(self.grid_height)]
        for organism in self.organisms:
            row = organism.get_position_row()
            column = organism.get_position_column()
            self.grid_board[row][column] = organism.get_character()

    def sort_organisms(self):
        self.organisms = merge_sort(self.organisms)

    def run(self):
        self.initialize_organisms()
        self.draw_starting_screen()
        while self.running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
                elif event.type == pygame.MOUSEBUTTONUP:
                    pos = pygame.mouse.get_pos()
                    click_x, click_y = pos
                    if click_y >= self.option_rectangle_top and click_y <= self.option_rectangle_top + self.option_rectangle_height:
                        for index, option_left_distance in enumerate(self.option_rectangle_left):
                            if click_x >= option_left_distance and click_x <= option_left_distance + self.option_rectangle_width:
                                self.chosen_option = OptionType(index + 1)
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_q:
                        self.running = False

            pygame.display.flip()
            self.clock.tick(60)
            pygame.display.update()

            if self.chosen_option == OptionType.PLAY_SIMULATION:
                self.play_simulation()
                self.draw_starting_screen()
                self.organisms = []
                self.initialize_organisms()
            elif self.chosen_option == OptionType.LOAD_SIMULATION:
                self.load_simulation()
                self.play_simulation()
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

        instruction_font_size = int(self.screen_width * 0.03)
        instruction_font = pygame.font.SysFont(None, instruction_font_size)
        instruction_font_color = "#333333"
        instruction_font_text = [instruction_font.render(instruction_lines[i], True, instruction_font_color) for i in range(len(instruction_lines))]
        instruction_widths = [instruction_font_text[i].get_width() for i in range(len(instruction_lines))]
        instruction_font_left = [(self.screen_width - instruction_widths[i]) / 2 for i in range(len(instruction_lines))]
        INSTRUCTION_FONT_GAP = int(self.screen_height * 0.03)
        INSTRUCTION_FONT_TOP = 0.4
        instruction_font_top = [self.screen_height * INSTRUCTION_FONT_TOP + INSTRUCTION_FONT_GAP * i for i in range(len(instruction_lines))]

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

            self.screen.blit(self.options_font[i], (self.options_font_left[i], self.options_font_top))
        for i in range(len(instruction_lines)):
            self.screen.blit(instruction_font_text[i], (instruction_font_left[i], instruction_font_top[i]))

    def play_simulation(self):
        self.update_grid_board()
        self.clear_journal()
        pressed_play_key = False
        game_running = True
        self.draw_simulation_board()

        # Clear journal.txt file
        self.clear_journal()

        displayed_message = False

        while game_running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    game_running = False

                elif event.type == pygame.MOUSEBUTTONUP:
                    added_organism = self.handle_click_add(pressed_play_key)
                    if added_organism:
                        added_organism.print_to_journal(f"Adding {added_organism.get_character()} at ({added_organism.get_position_row()}, {added_organism.get_position_column()})\n")
                        self.turn_number += 1
                        self.organisms.append(added_organism)
                        self.grid_board[added_organism.get_position_row()][added_organism.get_position_column()] = added_organism.get_character()
                        self.draw_simulation_board()
                        pygame.display.update()
                    continue

                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_p:

                        # Find human object
                        human_object = None
                        human_index = -1

                        for index, organism in enumerate(self.organisms):
                            if type(organism) == Human:
                                human_object = organism
                                human_index = index
                                break

                        # Clear journal every turn
                        self.clear_journal()
                        self.turn_number += 1
                        pressed_play_key = True
                        if human_object:
                            if displayed_message:
                                displayed_message = False
                                self.draw_simulation_board()
                            self.display_message("Press one of arrow keys to move", self.screen_height * 0.965, self.screen_width * 0.5)
                            pygame.display.update()
                            human_object.action(self.grid_board)
                            
                            CollisionType, data = human_object.collision(self.grid_board, self.organisms, human_index)
                            self.organisms[human_index] = human_object
                            self.handle_human_collision(CollisionType, data)

                    elif event.key == pygame.K_a:
                        if not self.is_human:
                            self.display_message("Cant activate ability, no human...", self.screen_height * 0.965, self.screen_width * 0.5)
                            displayed_message = True

                        else:
                            self.display_message("Activating human special ability...", self.screen_height * 0.965, self.screen_width * 0.5)
                            displayed_message = True
                            self.organisms[human_index].activate_ability()

                    elif event.key == pygame.K_s:

                        self.display_message("Saving State Of The Simulation...", self.screen_height * 0.965, self.screen_width * 0.5)
                        displayed_message = True
                        self.save_state_of_simulation()
                        self.clear_journal()

                    elif event.key == pygame.K_q:
                        
                        self.turn_number = 0
                        self.clear_journal()
                        return

            if pressed_play_key:
                organisms_to_add = []
                rows_cols_organisms_to_remove = []
                indexes_organisms_to_remove = []
                for index, organism in enumerate(self.organisms):

                    if index in indexes_organisms_to_remove or (organism.get_position_row(), organism.get_position_column()) in rows_cols_organisms_to_remove:
                        continue

                    if type(organism) == SosnowskyHogweed:

                        result = organism.action(self.grid_board)
                        self.update_grid_board()
                        if result:
                            for record in result:
                                rows_cols_organisms_to_remove.append(record)
                        CollisionType, data = organism.collision(self.grid_board, self.organisms, index)
                        if CollisionType == CollisionTypes.MULTIPLICATION:
                            organisms_to_add.append(data)
                        elif CollisionType == CollisionTypes.FIGHT:
                            indexes_organisms_to_remove.append(index)
                            indexes_organisms_to_remove.append(data)

                    elif type(organism) != Human:

                        new_organism = organism.action(self.grid_board)
                        if new_organism:
                            organisms_to_add.append(new_organism)
                        CollisionType, data = organism.collision(self.grid_board, self.organisms, index)
                        if CollisionType == CollisionTypes.MULTIPLICATION:
                            organisms_to_add.append(data)
                        elif CollisionType == CollisionTypes.FIGHT:
                            if type(organism) == Belladonna:
                                indexes_organisms_to_remove.append(index)
                            indexes_organisms_to_remove.append(data)

                pressed_play_key = False

                for o in organisms_to_add:
                    self.organisms.append(o)

                if len(rows_cols_organisms_to_remove):
                    self.remove_organisms(rows_cols_organisms_to_remove)

                if len(indexes_organisms_to_remove):
                    self.remove_indexes_organisms(indexes_organisms_to_remove)

                self.sort_organisms()
                self.update_grid_board()
                self.draw_simulation_board()

            pygame.display.flip()
            self.clock.tick(60)
            pygame.display.update()
        self.turn_number = 0

    def draw_simulation_board(self):
        self.screen.fill("#ffffff")
        color_line = "#000000"
        vertical_line_left = self.screen_width*0.25
        separating_line_thickness = 5
        pygame.draw.line(self.screen, color_line, (vertical_line_left, 0), (vertical_line_left, self.screen_height), separating_line_thickness)
        pygame.draw.line(self.screen, color_line, (vertical_line_left, self.screen_height * 0.8), (self.screen_width, self.screen_height * 0.8), separating_line_thickness)
        playing_board_height = self.screen_height * 0.8
        board_line_thickness = 2
        board_line_height = playing_board_height / self.grid_height
        playing_board_width = self.screen_width - vertical_line_left
        board_line_width = playing_board_width / self.grid_width

        # Display playing board
        for i in range(self.grid_height):
            self.squares_top.append(i*board_line_height)
            self.squares_bottom.append((i+1)*board_line_height - 1)
            pygame.draw.line(self.screen, color_line, (vertical_line_left, i * board_line_height),
                             (self.screen_width, i * board_line_height), board_line_thickness)
        for i in range(self.grid_width):
            self.squares_left.append(vertical_line_left + i * board_line_width)
            self.squares_right.append(vertical_line_left + (i+1) * board_line_width - 1)
            pygame.draw.line(self.screen, color_line, (vertical_line_left + i * board_line_width, 0),
                             (vertical_line_left + i * board_line_width, self.screen_height*0.8))

        # Display all our organisms inside grid
        for organism in self.organisms:
            organism_row = organism.get_position_row()
            organism_column = organism.get_position_column()
            organism.print(self.screen, self.squares_top[organism_row], self.squares_bottom[organism_row],
                           self.squares_left[organism_column], self.squares_right[organism_column])

        journal_font = pygame.font.SysFont(None, int(self.screen_height * 0.085 * 0.275))
        journal_font_left = self.screen_width * 0.02
        journal_vertical_offset = self.screen_height * 0.03
        # Display journal
        counter = 1
        self.screen.blit(journal_font.render
                         (f"Turn {self.turn_number}",
                          True, self.option_font_color),
                         (journal_font_left, counter * journal_vertical_offset))
        counter += 1
        with open(self.JOURNAL_FILENAME) as f:
            for line in f:
                # Remove last ? character
                line = line[:-1]
                # Make sure we wont go beyong the screem
                if journal_vertical_offset * counter >= self.screen_height:
                    return
                self.screen.blit(journal_font.render(line, True, self.option_font_color),
                                 (journal_font_left, counter * journal_vertical_offset))
                counter += 1
        # Display available options for user
        self.display_message("Press n to add new animal by clicking on a cell", self.screen_height * 0.825, self.screen_width * 0.27)
        self.display_message("Press a to activate human ability", self.screen_height * 0.86, self.screen_width * 0.27)
        self.display_message("Press s to save current state of the game", self.screen_height * 0.895, self.screen_width * 0.27)
        self.display_message("Press p to go to the next turn", self.screen_height * 0.93, self.screen_width * 0.27)
        self.display_message("Press q to quit", self.screen_height * 0.965, self.screen_width * 0.27)

    def save_state_of_simulation(self):
        with open(self.SAVED_STATE_FILENAME, 'w') as f:
            f.write(f"{self.turn_number}\n")
            for organism in self.organisms:
                f.write(f"""{organism.get_name()} {organism.get_strength()} {organism.get_initiative()} {
                        organism.get_position_row()} {organism.get_position_column()}\n""")

    def display_message(self, message, top_coor, left_coor):
        # Display text message in bottom rectangle
        chosen_option_font = pygame.font.SysFont(None, int(self.screen_height * 0.04))
        self.screen.blit(chosen_option_font.render(message, True, self.option_font_color),(left_coor, top_coor))

    def load_simulation(self):
        self.clear_journal()
        self.organisms.clear()
        with open(self.SAVED_STATE_FILENAME, 'r') as f:
            for index, line in enumerate(f):
                if index == 0:
                    self.turn_number = int(line)
                    continue
                name, strength, initiative, row, column = line.split(" ")
                strength = int(strength)
                initiative = int(initiative)
                row = int(row)
                column = int(column)
                if name == "Human":
                    self.organisms.append(Human(name, row, column, strength, initiative))
                elif name == "wolf":
                    self.organisms.append(Wolf(name, row, column, strength, initiative))
                elif name == "sheep":
                    self.organisms.append(Sheep(name, row, column, strength, initiative))
                elif name == "antelope":
                    self.organisms.append(Antelope(name, row, column, strength, initiative))
                elif name == "fox":
                    self.organisms.append(Fox(name, row, column, strength, initiative))
                elif name == "turtle":
                    self.organisms.append(Turtle(name, row, column, strength, initiative))
                elif name == "cyber_sheep":
                    self.organisms.append(CyberSheep(name, row, column, strength, initiative))
                elif name == "Grass":
                    self.organisms.append(Grass(name, row, column, strength, initiative))
                elif name == "Guarana":
                    self.organisms.append(Guarana(name, row, column, strength, initiative))
                elif name == "Belladonna":
                    self.organisms.append(Belladonna(name, row, column, strength, initiative))
                elif name == "Sow_thistle":
                    self.organisms.append(SowThistle(name, row, column, strength, initiative))
                elif name == "Sosnowsky_hogweed":
                    self.organisms.append(SosnowskyHogweed(name, row, column, strength, initiative))

    def clear_journal(self):
        with open(self.JOURNAL_FILENAME, 'w') as f:
            pass

    def remove_organisms(self, coordinates):
        indexes_to_remove = []
        for row, column in coordinates:
            for index, organism in enumerate(self.organisms):
                if organism.get_position_row() == row and organism.get_position_column() == column:
                    indexes_to_remove.append(index)

        # Sort indices in descending order to prevent issues with changing indices
        indexes_to_remove.sort(reverse=True)
        for index in indexes_to_remove:
            self.organisms[index].decrease_static_counter()
            if type(self.organisms[index]) == Human:
                    self.is_human = False
            del self.organisms[index]

    def remove_indexes_organisms(self, indexes):
        indexes.sort(reverse=True)
        for index in indexes:
            if 0 <= index < len(self.organisms):
                self.organisms[index].decrease_static_counter()
                if type(self.organisms[index]) == Human:
                    self.is_human = False
                del self.organisms[index]

    def handle_human_collision(self, CollisionType, data):
        
        if CollisionType == CollisionTypes.NONE:
            return

        if CollisionType == CollisionTypes.MULTIPLICATION:
            self.organisms.append(data)
            self.draw_simulation_board()
            pygame.display.update()
        
        elif CollisionType == CollisionTypes.FIGHT and 0 <= data < len(self.organisms):
            self.organisms[data].decrease_static_counter()
            if type(self.organisms[data]) == Human:
                    self.is_human = False
            del self.organisms[data]

    def handle_click_add(self, pressed_play_key):
        pos = pygame.mouse.get_pos()
        click_x, click_y = pos
        self.clear_journal()
        pressed_play_key = False
        
        row, column = -1, -1
        for i in range(0, len(self.squares_top)):
            if self.squares_top[i] <= click_y < self.squares_bottom[i]:
                row = i
                break
        for i in range(0, len(self.squares_left)):
            if self.squares_left[i] <= click_x < self.squares_right[i]:
                column = i
                break

        if row == -1 or column == -1:
            return

        if 0 <= row < len(self.grid_board) and 0 <= column < len(self.grid_board[0]) and self.grid_board[row][column] != 'e':
            self.display_message("Cant add here, select empty cell...", self.screen_height * 0.965, self.screen_width * 0.5)
            return

        option = self.add_organism_click()
        if option == 1: return Antelope("antelope", row, column)
        if option == 2: return Belladonna("Belladonna", row, column)
        if option == 3: return CyberSheep("cyber_sheep", row, column)
        if option == 4: return Fox("fox", row, column)
        if option == 5: return Grass("Grass", row, column)
        if option == 6: return Guarana("Guarana", row, column)
        if option == 7: return Sheep("sheep", row, column)
        if option == 8: return SosnowskyHogweed("Sosnowsky_hogweed", row, column)
        if option == 9: return SowThistle("Sow_thistle", row, column)
        if option == 10: return Turtle("turtle", row, column)
        if option == 11: return Wolf("wolf", row, column)

        return None

    def add_organism_click(self):
        self.screen.fill("#ffffff")
        self.screen.blit(self.font_title.render("Choose Your Animal", True, "#333333"), (self.title_left, self.title_top))

        image_height = image_width = 80
        images = []

        image_path = ""
        for root, dirs, files in os.walk('.'):
            for name in files:
                if name.endswith(".png") and name != "human.png":
                    image_path = os.path.abspath(os.path.join(root, name))
                    images.append(pygame.transform.scale(pygame.image.load(image_path).convert_alpha(), (image_height, image_width)))

        choosing_option = True
        images_top_coordinates = [150 + i * 100 for j in range(2) for i in range(6)]
        images_bottom_coordinates = [150 + image_height + i * 100 for j in range(2) for i in range(6)]
        images_left_coordinates = [(self.screen_width - (2 * image_width)) / 4 for i in range(6)]
        images_right_coordinates = [images_left_coordinates[i] + image_width for i in range(6)]

        for i in range(6):
            images_left_coordinates.append(images_left_coordinates[0] + image_width + ((self.screen_width - 2 * image_width) / 2))
            images_right_coordinates.append(images_left_coordinates[i + 6] + image_width)

        for i in range(len(images_top_coordinates) - 1): # No human
            self.screen.blit(images[i], (images_left_coordinates[i], images_top_coordinates[i]))

        while choosing_option:
            for event in pygame.event.get():

                if event.type == pygame.QUIT:
                    choosing_option = False
                    return 1

                elif event.type == pygame.MOUSEBUTTONUP:
                    pos = pygame.mouse.get_pos()
                    click_x, click_y = pos
                    for i in range(len(images_left_coordinates) - 1):
                        if images_left_coordinates[i] <= click_x < images_right_coordinates[i] and images_top_coordinates[i] <= click_y < images_bottom_coordinates[i]:
                            return i + 1

            pygame.display.flip()
            self.clock.tick(60)
            pygame.display.update()

        option = 1
        self.draw_simulation_board()
        pygame.display.update()
        return option