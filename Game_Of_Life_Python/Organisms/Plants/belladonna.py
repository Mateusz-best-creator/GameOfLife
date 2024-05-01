from Organisms.organism import OrganismInitialData
from Organisms.plant import Plant
from Organisms.animal import CollisionTypes

class Belladonna(Plant):

    static_counter = 0

    def __init__(self, name, row, column, given_strength = -1, given_initiative = -1):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1: strength = given_strength
        if given_initiative != -1: initiative = given_initiative
        super().__init__(strength, initiative, name, character, row, column, "belladonna.png")
        Belladonna.static_counter += 1
        self.type = Belladonna

    def action(self, grid_board):
        return self.default_plant_action(grid_board, Belladonna, "Belladonna")

    def collision(self, grid_board, organisms, current_index):
        
        for organism_index, organism in enumerate(organisms):

            if organism.get_position_row() == self.row and organism.get_position_column() == self.column and organism_index != current_index:

                self.print_to_journal(f"{self.character}vs{organism.get_character()} at {self.row},{self.column} -> {organism.get_character()} eat {self.character}, {self.character} eat {organism.get_character()}\n")
                return CollisionTypes("Fight"), organism_index

        return CollisionTypes("None"), None


    def get_static_counter(self):
        return Belladonna.static_counter

    def increase_static_counter(self):
        Belladonna.static_counter += 1

    def decrease_static_counter(self):
        Belladonna.static_counter -= 1
