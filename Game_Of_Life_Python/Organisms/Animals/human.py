from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal
import pygame


class Human(Animal):

    ABILITY_STRENGTH_INCREASE = 10

    def __init__(self, name, row, column, given_strength=-1, given_initiative=-1, default_strength = None, ability_activated = None):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1:
            strength = given_strength
        if given_initiative != -1:
            initiative = given_initiative
        super().__init__(strength, initiative, name, character, row, column, "human.png")
        self.type = Human
        if ability_activated == True:
            self.ability_activated = True
            self.default_strength = default_strength
        else:
            self.ability_activated = False
            self.default_strength = strength

    def action(self, grid_board):

        self.previous_row = self.row
        self.previous_column = self.column

        grid_board[self.row][self.column] = 'e'
        self.print_to_journal(f"{self.name} from ({self.row}, {self.column}) to ")

        running = True
        while running:
            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_LEFT:
                        if self.column > 0:
                            self.organism_go_left()
                        running = False
                    elif event.key == pygame.K_RIGHT:
                        if self.column < len(grid_board[0]) - 1:
                            self.organism_go_right()
                        running = False
                    elif event.key == pygame.K_UP:
                        if self.row > 0:
                            self.organism_go_top()
                        running = False
                    elif event.key == pygame.K_DOWN:
                        if self.row < len(grid_board) - 1:
                            self.organism_go_bottom()
                        running = False

        grid_board[self.row][self.column] = self.character
        self.print_to_journal(f"""({self.row}, {self.column})\n""")

        if self.ability_activated:
            self.strength -= 1
            if self.strength == self.default_strength:
                self.ability_activated = False

    def collision(self, grid_board, organisms, current_index):
        return self.default_collision_animal(grid_board, organisms, current_index)

    def get_static_counter(self):
        return 1

    def increase_static_counter(self):
        pass

    def decrease_static_counter(self):
        pass

    def get_default_strength(self):
        return self.default_strength

    def get_ability_activated(self):
        return self.ability_activated
    
    def set_default_strength(self, value):
        self.strength = value

    def activate_ability(self):
        
        if not self.ability_activated:
            self.ability_activated = True
            self.strength += Human.ABILITY_STRENGTH_INCREASE
            return True
        return False
