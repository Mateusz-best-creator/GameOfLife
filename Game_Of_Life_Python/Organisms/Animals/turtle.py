from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal, CollisionTypes
import random


class Turtle(Animal):

    static_counter = 0

    def __init__(self, name, row, column, given_strength=-1, given_initiative=-1):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1:
            strength = given_strength
        if given_initiative != -1:
            initiative = given_initiative
        super().__init__(strength, initiative, name, character, row, column, "turtle.png")
        Turtle.static_counter += 1
        self.type = Turtle

    def action(self, grid_board):
        rand = random.randint(1, 4)
        if (rand == 4):  # Means turtle move
            self.default_action_animal(grid_board)
        else:
            self.print_to_journal(
                f"{self.name} stays at ({self.row}, {self.column})\n")

    def collision(self, grid_board, organisms, current_index):
        return self.default_collision_animal(grid_board, organisms, current_index)

    def get_static_counter(self):
        return Turtle.static_counter
