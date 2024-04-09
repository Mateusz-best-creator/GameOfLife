from abc import ABC, abstractmethod
from organism import Organism

class Animal(Organism, ABC):
    def __init__(self, strength, initiative, name, character, row, column):
        super().__init__(strength, initiative, name, character, row, column)

    @abstractmethod
    def action():
        pass
    
    @abstractmethod
    def collision():
        pass
