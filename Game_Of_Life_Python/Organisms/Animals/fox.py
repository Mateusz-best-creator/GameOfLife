from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal
import random
from Organisms.animal import MoveDirection

class Fox(Animal):
    def __init__(self, name, row, column, given_strength = -1, given_initiative = -1):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1: strength = given_strength
        if given_initiative != -1: initiative = given_initiative
        super().__init__(strength, initiative, name, character, row, column, "fox.png")

    def fox_can_go(self, character):
        return character == 't' or character == 'G' or character == 'U' or character == 'S' or character == 'e'

    def action(self, grid_board):
        row, column = self.get_position_row(), self.get_position_column()
        rand = random.randint(1, 4)
        indexes = [i % 4 + 1 for i in range(rand, rand + 4)]
        moved = False
        for index in indexes:
            dir = MoveDirection(index)
            print(f"Dir= ", dir)
            if dir == MoveDirection.LEFT and column > 0:
                if self.fox_can_go(grid_board[row][column - 1]):
                    self.organism_go_left()
                    moved = True
            elif dir == MoveDirection.RIGHT and column < len(grid_board[0]) - 1:
                if self.fox_can_go(grid_board[row][column + 1]):
                    self.organism_go_right()
                    moved = True
            elif dir == MoveDirection.TOP and row > 0:
                if self.fox_can_go(grid_board[row - 1][column]):
                    self.organism_go_top()
                    moved = True
            elif dir == MoveDirection.BOTTOM and row < len(grid_board) - 1:
                if self.fox_can_go(grid_board[row + 1][column]):
                    self.organism_go_bottom()
                    moved = True
            if moved:
                self.print_to_journal(f"{self.get_name()} from ({row}, {column}) to ")
                self.print_to_journal(f"({self.get_position_row()}, {self.get_position_column()})\n")
                return

        self.print_to_journal(f"{self.get_name()} stays at ({self.get_position_row()}, {self.get_position_column()})\n")


    def collision(self):
        pass
