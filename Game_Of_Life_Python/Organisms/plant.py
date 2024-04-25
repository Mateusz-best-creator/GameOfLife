from abc import ABC, abstractmethod
from Organisms.organism import Organism
import random

class Plant(Organism, ABC):
    def __init__(self, strength, initiative, name, character, row, column, image_path):
        super().__init__(strength, initiative, name, character, row, column, image_path)
        self.probability = 0.1 # 10% that plant will sow

    @abstractmethod
    def action(self, grid_board):
        pass

    @abstractmethod
    def collision(self):
        pass

    @abstractmethod
    def get_static_counter(self):
        pass

    def default_plant_action(self, grid_board, type, organsim_name):
        self.age += 1
        rand = random.random()
        if rand > self.probability or self.get_static_counter() >= 7:
            return None
        row, col = self.get_position_row(), self.get_position_column()
        for i in range(-1, 2):  
            for j in range(-1, 2):
                if i != 0 or j != 0:
                    if 0 <= row + i < len(grid_board) and 0 <= col + j < len(grid_board[row + i]):  
                        if grid_board[row + i][col + j] == 'e':
                            self.print_to_journal(f"Creating {self.get_name()} at ({row + i}, {col + j})\n")
                            return type(organsim_name, row + i, col + j)
        return None