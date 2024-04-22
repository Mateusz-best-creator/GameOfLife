from abc import ABC, abstractmethod
from Organisms.organism import Organism


class Plant(Organism, ABC):
    def __init__(self, strength, initiative, name, character, row, column, image_path):
        super().__init__(strength, initiative, name, character, row, column, image_path)

    @abstractmethod
    def action(self):
        pass

    @abstractmethod
    def collision(self):
        pass
