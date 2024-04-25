from Organisms.organism import OrganismInitialData
from Organisms.plant import Plant


class SosnowskyHogweed(Plant):

    static_counter = 0

    def __init__(self, name, row, column, given_strength = -1, given_initiative = -1):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1: strength = given_strength
        if given_initiative != -1: initiative = given_initiative
        super().__init__(strength, initiative, name, character, row, column, "sosnowsky_hogweed.png")
        SosnowskyHogweed.static_counter += 1

    def can_kill(self, grid_board, row, column):
        return (grid_board[row][column] == 'w' 
                or grid_board[row][column] == 's' 
                or grid_board[row][column] == 'f' 
                or grid_board[row][column] == 't' 
                or grid_board[row][column] == 'a'
                or grid_board[row][column] == 'H')

    # Kill avery animal except cyber_sheep in it's neighbourhood
    def action(self, grid_board):
        self.age += 1
        row = self.get_position_row()
        column = self.get_position_column()
        rows_columns_to_remove = []
        for i in range(-1, 2):
            for j in range(-1, 2):
                r, c = row + i, column + j
                if (i != 0 or j != 0) and r >= 0 and r < len(grid_board) and c >= 0 and c < len(grid_board[r]) and self.can_kill(grid_board, r, c):
                    rows_columns_to_remove.append((r, c))
                    self.print_to_journal(f"Sosnowsky killing at ({r}, {c})\n")
        if rows_columns_to_remove:
            return rows_columns_to_remove
        return None


    def collision(self):
        pass

    def get_static_counter(self):
        return SosnowskyHogweed.static_counter
