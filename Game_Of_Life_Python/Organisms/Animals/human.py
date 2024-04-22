from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal
import pygame

class Human(Animal):
    def __init__(self, name, row, column):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        super().__init__(strength, initiative, name, character, row, column, "human.png")

    def action(self):
        print("Enter human move, arrow key!")
        while True:
            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_LEFT:
                        if self.get_position_column() > 0:
                            self.organism_go_left()
                        return
                    elif event.key == pygame.K_RIGHT:
                        if self.get_position_column() < 9: # Board size, indexed from zero
                            self.organism_go_right()
                        return
                    elif event.key == pygame.K_UP:
                        if self.get_position_row() > 0:
                            self.organism_go_top()
                        return
                    elif event.key == pygame.K_DOWN:
                        if self.get_position_row() < 9: # Board size, indexed from 0
                            self.organism_go_bottom()
                        return

    def collision(self):
        pass
