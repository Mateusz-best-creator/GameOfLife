from Organisms.organism import OrganismInitialData
from Organisms.plant import Plant


class Belladonna(Plant):
    def __init__(self, name, row, column, given_strength = -1, given_initiative = -1):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1: strength = given_strength
        if given_initiative != -1: initiative = given_initiative
        super().__init__(strength, initiative, name,
                         character, row, column, "belladonna.png")

    def action(self, grid_board):
        pass

    def collision(self):
        pass
