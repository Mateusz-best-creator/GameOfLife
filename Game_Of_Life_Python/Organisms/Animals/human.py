from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal


class Human(Animal):
    def __init__(self, name, row, column):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        image_path = "human.png"
        super().__init__(strength, initiative, name, character, row, column, image_path)

    def action():
        pass

    def collision():
        pass
