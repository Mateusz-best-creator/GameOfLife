from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal


class CyberSheep(Animal):
    def __init__(self, name, row, column, given_strength = -1, given_initiative = -1):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1: strength = given_strength
        if given_initiative != -1: initiative = given_initiative
        super().__init__(strength, initiative, name,
                         character, row, column, "cyber_sheep.png")

    def action(self):
        pass

    def collision(self):
        pass
