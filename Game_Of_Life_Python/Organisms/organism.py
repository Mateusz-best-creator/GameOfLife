from abc import ABC, abstractmethod

OrganismInitialData = {
    "wolf": { "strength": 9, "initiative": 5, "character": 'w' },
    "sheep": { "strength": 4, "initiative": 4, "character": 's' },
    "fox": { "strength": 3, "initiative": 7, "character": 'f' },
    "turtle": { "strength": 2, "initiative": 1, "character": 't' },
    "antelope": { "strength": 4, "initiative": 4, "character": 'a' },
    "cyber_sheep": { "strength": 11, "initiative": 4, "character": 'c' },
    "Human": { "strength": 5, "initiative": 4, "character": 'H' },
    "Grass": { "strength": 0, "initiative": 0, "character": 'G' },
    "SowThistle": { "strength": 0, "initiative": 0, "character": 'S' },
    "Guarana": { "strength": 0, "initiative": 0, "character": 'U' },
    "Belladonna": { "strength": 99, "initiative": 0, "character": 'B' },
    "SosnowskyHogweed": { "strength": 10, "initiative": 0, "character": 'O' },
}

class Organism(ABC):
    def __init__(self, strength, initiative, name, character, row, column):
        self.strength = strength
        self.initiative = initiative
        self.name = name
        self.character = character
        self.row = row
        self.column = column

    @abstractmethod
    def action(self):
        pass

    @abstractmethod
    def collision(self):
        pass

    def draw(self):
        return self.character
    
    # Some getters and setters
    def get_name(self):
        return self.name
    def get_initiative(self): 
        return self.initiative
    def get_name(self):
        return self.name
    def get_character(self):
        return self.character
    def get_position_row(self):
        return self.row
    def get_position_column(self):
        return self.column