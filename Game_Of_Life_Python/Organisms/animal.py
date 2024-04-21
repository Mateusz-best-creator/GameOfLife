from abc import ABC, abstractmethod
from Organisms.organism import Organism


class Animal(Organism, ABC):
    def __init__(self, strength, initiative, name, character, row, column, image_path):
        super().__init__(strength, initiative, name, character, row, column, image_path)

    @abstractmethod
    def action():
        pass

    @abstractmethod
    def collision():
        pass
