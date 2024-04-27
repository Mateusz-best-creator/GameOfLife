from abc import ABC, abstractmethod
from Organisms.organism import Organism
import random
from enum import Enum


class MoveDirection(Enum):
    LEFT = 1
    RIGHT = 2
    TOP = 3
    BOTTOM = 4


class Animal(Organism, ABC):
    def __init__(self, strength, initiative, name, character, row, column, image_path):
        super().__init__(strength, initiative, name, character, row, column, image_path)

    @abstractmethod
    def action(self, grid_board):
        pass

    @abstractmethod
    def collision(self):
        pass

    @abstractmethod
    def get_static_counter(self):
        pass

    def default_action_animal(self, grid_board):

        self.age += 1

        self.previous_row = self.row
        self.previous_column = self.column

        direction = MoveDirection(random.randint(1, 4))

        # Check if the movement in the selected direction will keep the organism within the board bounds
        while True:
            if self.row == 0 and direction == MoveDirection.TOP:
                direction = MoveDirection(random.choice(
                    [MoveDirection.LEFT, MoveDirection.RIGHT, MoveDirection.BOTTOM]))
            elif self.row == 9 and direction == MoveDirection.BOTTOM:
                direction = MoveDirection(random.choice(
                    [MoveDirection.LEFT, MoveDirection.RIGHT, MoveDirection.TOP]))
            elif self.column == 0 and direction == MoveDirection.LEFT:
                direction = MoveDirection(random.choice(
                    [MoveDirection.TOP, MoveDirection.RIGHT, MoveDirection.BOTTOM]))
            elif self.column == 9 and direction == MoveDirection.RIGHT:
                direction = MoveDirection(random.choice(
                    [MoveDirection.TOP, MoveDirection.LEFT, MoveDirection.BOTTOM]))
            else:
                break

        grid_board[self.row][self.column] = 'e'
        name = self.name
        if name == "cyber_sheep":
            name = "cyber"
        self.print_to_journal(
            f"{name} from ({self.row}, {self.column}) to ")

        # Perform movement based on the selected direction
        if direction == MoveDirection.LEFT:
            self.organism_go_left()
        elif direction == MoveDirection.TOP:
            self.organism_go_top()
        elif direction == MoveDirection.RIGHT:
            self.organism_go_right()
        elif direction == MoveDirection.BOTTOM:
            self.organism_go_bottom()

        grid_board[self.row][self.column] = self.character
        self.print_to_journal(f"to ({self.row}, {self.column})\n")
