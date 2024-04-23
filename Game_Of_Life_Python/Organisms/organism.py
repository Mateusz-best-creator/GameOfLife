from abc import ABC, abstractmethod
import pygame
import os

OrganismInitialData = {
    "wolf": {"strength": 9, "initiative": 5, "character": 'w'},
    "sheep": {"strength": 4, "initiative": 4, "character": 's'},
    "fox": {"strength": 3, "initiative": 7, "character": 'f'},
    "turtle": {"strength": 2, "initiative": 1, "character": 't'},
    "antelope": {"strength": 4, "initiative": 4, "character": 'a'},
    "cyber_sheep": {"strength": 11, "initiative": 4, "character": 'c'},
    "Human": {"strength": 5, "initiative": 4, "character": 'H'},
    "Grass": {"strength": 0, "initiative": 0, "character": 'G'},
    "Sow_thistle": {"strength": 0, "initiative": 0, "character": 'S'},
    "Guarana": {"strength": 0, "initiative": 0, "character": 'U'},
    "Belladonna": {"strength": 99, "initiative": 0, "character": 'B'},
    "Sosnowsky_hogweed": {"strength": 10, "initiative": 0, "character": 'O'},
}


class Organism(ABC):
    def __init__(self, strength, initiative, name, character, row, column, image_path):
        self.strength = strength
        self.initiative = initiative
        self.name = name
        self.character = character
        self.row = row
        self.column = column
        self.image_path = image_path
        self.JOURNAL_FILENAME = "journal.txt"
        self.age = 1

    @abstractmethod
    def action(self, grid_board):
        pass

    @abstractmethod
    def collision(self):
        pass

    def draw(self):
        return self.character

    def print(self, screen, top_coor, bottom_coor, left_coor, right_coor):
        image_path = ""
        for root, dirs, files in os.walk('.'):
            for name in files:
                if name == self.image_path:
                    image_path = os.path.abspath(os.path.join(root, name))
        image_height = abs(top_coor - bottom_coor)
        image_width = abs(left_coor - right_coor)
        img = pygame.transform.scale(pygame.image.load(
            image_path).convert_alpha(), (image_width, image_height))
        screen.blit(img, (left_coor+1, top_coor+1))

    # Some getters and setters
    def get_name(self):
        return self.name

    def get_initiative(self):
        return self.initiative

    def get_strength(self):
        return self.strength

    def get_character(self):
        return self.character

    def get_position_row(self):
        return self.row

    def get_position_column(self):
        return self.column

    def organism_go_left(self):
        self.column -= 1

    def organism_go_top(self):
        self.row -= 1

    def organism_go_right(self):
        self.column += 1

    def organism_go_bottom(self):
        self.row += 1

    def print_to_journal(self, message):
        with open(self.JOURNAL_FILENAME, 'a') as f:
            f.write(message)