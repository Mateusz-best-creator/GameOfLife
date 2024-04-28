from Organisms.organism import OrganismInitialData
from Organisms.plant import Plant
from Organisms.animal import CollisionTypes


class Guarana(Plant):

    static_counter = 0

    def __init__(self, name, row, column, given_strength = -1, given_initiative = -1):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1: strength = given_strength
        if given_initiative != -1: initiative = given_initiative
        super().__init__(strength, initiative, name, character, row, column, "guarana.png")
        Guarana.static_counter += 1
        self.type = Guarana

    def action(self, grid_board):
        return self.default_plant_action(grid_board, Guarana, "Guarana")

    def collision(self, grid_board, organisms, current_index):
        return CollisionTypes("None"), None


    def get_static_counter(self):
        return Guarana.static_counter