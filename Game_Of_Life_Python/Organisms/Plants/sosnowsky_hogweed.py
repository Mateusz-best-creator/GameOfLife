from Organisms.organism import OrganismInitialData
from Organisms.plant import Plant
from Organisms.animal import CollisionTypes


class SosnowskyHogweed(Plant):

    static_counter = 0

    def __init__(self, name, row, column, given_strength=-1, given_initiative=-1):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        if given_strength != -1:
            strength = given_strength
        if given_initiative != -1:
            initiative = given_initiative
        super().__init__(strength, initiative, name,
                         character, row, column, "sosnowsky_hogweed.png")
        SosnowskyHogweed.static_counter += 1
        self.type = SosnowskyHogweed

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
        rows_columns_to_remove = []
        for i in range(-1, 2):
            for j in range(-1, 2):

                if i == 0 and j == 0:
                    continue
                r, c = self.row + i, self.column + j

                if r >= 0 and r < len(grid_board) and c >= 0 and c < len(grid_board[r]) and self.can_kill(grid_board, r, c):
                    rows_columns_to_remove.append((r, c))
                    self.print_to_journal(f"Sosnowsky kill {grid_board[r][c]} at ({r}, {c})\n")
                    grid_board[r][c] = 'e'

        if len(rows_columns_to_remove):
            return rows_columns_to_remove
        self.print_to_journal(
            f"Sosnowsky at ({self.row}, {self.column}) will not kill\n")
        return None

    def collision(self, grid_board, organisms, current_index):
        
        for organism_index, organism in enumerate(organisms):

            if organism.get_position_row() == self.row and organism.get_position_column() == self.column and organism_index != current_index and organism.get_name() != "cyber_sheep":
                
                self.print_to_journal(f"{self.character}vs{organism.get_character()} at {self.row},{self.column} -> {organism.get_character()} eat {self.character}, {self.character} eat {organism.get_character()}\n")
                return CollisionTypes("Fight"), organism_index

        return self.default_plant_collision()


    def get_static_counter(self):
        return SosnowskyHogweed.static_counter

    def increase_static_counter(self):
        SosnowskyHogweed.static_counter += 1

    def decrease_static_counter(self):
        SosnowskyHogweed.static_counter -= 1