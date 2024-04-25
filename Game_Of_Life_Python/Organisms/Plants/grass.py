from Organisms.organism import OrganismInitialData
from Organisms.plant import Plant
import random

class Grass(Plant):

    static_counter = 0

    def __init__(self, name, row, column, given_strength = -1, given_initiative = -1):
        self.strength = OrganismInitialData[name]["strength"]
        self.initiative = OrganismInitialData[name]["initiative"]
        self.character = OrganismInitialData[name]["character"]
        if given_strength != -1: self.strength = given_strength
        if given_initiative != -1: self.initiative = given_initiative
        super().__init__(self.strength, self.initiative, name, self.character, row, column, "grass.png")
        Grass.static_counter += 1

    def action(self, grid_board):
        return self.default_plant_action(grid_board, Grass, "Grass")

    def collision(self):
        pass

    def get_static_counter(self):
        return Grass.static_counter
