from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal
import random

class Turtle(Animal):
    def __init__(self, name, row, column):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        super().__init__(strength, initiative, name, character, row, column, "turtle.png")

    def action(self):
        rand = random.randint(1, 4)
        if (rand == 4): # Means turtle move
            self.default_action_animal()
        else:
            self.print_to_journal(f"{self.name} stays at ({self.get_position_row()}, {self.get_position_column()})")

    def collision(self):
        pass
