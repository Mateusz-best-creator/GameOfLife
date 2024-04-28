from Organisms.organism import OrganismInitialData
from Organisms.plant import Plant
import random
from Organisms.animal import CollisionTypes


class SowThistle(Plant):

    static_counter = 0

    def __init__(self, name, row, column, given_strength = -1, given_initiative = -1):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1: strength = given_strength
        if given_initiative != -1: initiative = given_initiative
        super().__init__(strength, initiative, name, character, row, column, "sow_thistle.png")
        SowThistle.static_counter += 1
        self.type = SowThistle

    def action(self, grid_board):
        for _ in range(3):
            result = self.default_plant_action(grid_board, SowThistle, "Sow_thistle")
            if result:
                return result
        return None

    def collision(self, grid_board, organisms, current_index):
        return self.default_plant_collision()

    def get_static_counter(self):
        return SowThistle.static_counter
