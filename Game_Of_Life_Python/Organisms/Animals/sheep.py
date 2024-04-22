from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal


class Sheep(Animal):
    def __init__(self, name, row, column):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        super().__init__(strength, initiative, name, character, row, column, "sheep.png")

    def action(self):
        self.default_action_animal()

    def collision(self):
        pass
