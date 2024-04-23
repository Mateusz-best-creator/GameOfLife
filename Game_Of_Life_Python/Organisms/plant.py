from abc import ABC, abstractmethod
from Organisms.organism import Organism


class Plant(Organism, ABC):
    def __init__(self, strength, initiative, name, character, row, column, image_path):
        super().__init__(strength, initiative, name, character, row, column, image_path)

    @abstractmethod
    def action(self, grid_board):
        pass

    @abstractmethod
    def collision(self):
        pass

    def default_plant_action(self):
        self.age += 1
