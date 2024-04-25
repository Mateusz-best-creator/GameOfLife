from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal


class CyberSheep(Animal):

    static_counter = 0

    def __init__(self, name, row, column, given_strength = -1, given_initiative = -1):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1: strength = given_strength
        if given_initiative != -1: initiative = given_initiative
        super().__init__(strength, initiative, name, character, row, column, "cyber_sheep.png")
        CyberSheep.static_counter += 1

    def action(self, grid_board):
        sosnowsky_rows = sosnowsky_columns = []
        for row in range(len(grid_board)):
            for col in range(len(grid_board[0])):
                if grid_board[row][col] == 'O': # Means we have sosnowsky hogweed, O is it's character
                    sosnowsky_rows.append(row)
                    sosnowsky_columns.append(col)

        # Sosnowsky not found
        if not len(sosnowsky_rows) or not len(sosnowsky_columns):
            Animal.default_action_animal()
        # Sosnowsky found        
        else:
            self.print_to_journal(f"{self.get_name()} from ({self.get_position_row()}, {self.get_position_column()}) to ")
            row, column = self.get_position_row(), self.get_position_column()
            
            # Find which hogweed is the closest
            min_distance = float("inf")
            min_index = -1
            for i in range(len(sosnowsky_rows)):
                distance = ((row - sosnowsky_rows[i]) ** 2 + (column - sosnowsky_columns[i]) ** 2) ** 0.5
                if distance < min_distance:
                    min_index = i
                    min_distance = distance
            sosnowsky_row = sosnowsky_rows[min_index]
            sosnowsky_col = sosnowsky_columns[min_index]

            if sosnowsky_row < row and row > 0:
                self.organism_go_top()
            elif sosnowsky_row > row and row < len(grid_board) - 1:
                self.organism_go_bottom()
            elif sosnowsky_col < column and column > 0:
                self.organism_go_left()
            elif sosnowsky_col > column and column < len(grid_board[0]) - 1:
                self.organism_go_right()
            self.print_to_journal(f"({self.get_position_row()}, {self.get_position_column()})\n")

    def collision(self):
        pass

    def get_static_counter(self):
        return CyberSheep.static_counter
