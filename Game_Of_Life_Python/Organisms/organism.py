from abc import ABC, abstractmethod

class Organism(ABC):
    def __init__(self, strength, initiative):
        self.strength = strength
        self.initiative = initiative

    @abstractmethod
    def action(self):
        pass

    @abstractmethod
    def collision(self):
        pass