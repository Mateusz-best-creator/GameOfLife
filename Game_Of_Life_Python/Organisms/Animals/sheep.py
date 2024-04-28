from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal


class Sheep(Animal):

    static_counter = 0

    def __init__(self, name, row, column, given_strength = -1, given_initiative = -1):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1: strength = given_strength
        if given_initiative != -1: initiative = given_initiative
        super().__init__(strength, initiative, name, character, row, column, "sheep.png")
        Sheep.static_counter += 1
        self.type = Sheep

    def action(self, grid_board):
        self.default_action_animal(grid_board)

    def collision(self, grid_board, organisms, current_index):
        return self.default_collision_animal(grid_board, organisms, current_index)


    def get_static_counter(self):
        return Sheep.static_counter