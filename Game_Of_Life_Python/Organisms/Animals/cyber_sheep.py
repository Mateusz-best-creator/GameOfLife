from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal


class CyberSheep(Animal):

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
                         character, row, column, "cyber_sheep.png")
        CyberSheep.static_counter += 1
        self.type = CyberSheep

    def action(self, grid_board):
        sosnowsky_rows = []
        sosnowsky_columns = []
        for row in range(len(grid_board)):
            for col in range(len(grid_board[row])):
                # Means we have sosnowsky hogweed, O is its character
                if grid_board[row][col] == 'O':
                    sosnowsky_rows.append(row)
                    sosnowsky_columns.append(col)

        # Sosnowsky not found
        if not sosnowsky_rows or not sosnowsky_columns:
            self.default_action_animal(grid_board)
            return  # Stop execution if no hogweed is found

        # Sosnowsky found, use cyber for short instaed of cyber_sheep
        self.print_to_journal(
            f"""cyber from ({self.row}, {self.column}) to """
        )
        grid_board[self.row][self.column] = 'e'
        self.previous_row = self.row
        self.previous_column = self.column

        # Find which hogweed is the closest
        min_distance = float("inf")
        min_index = -1
        for i in range(len(sosnowsky_rows)):
            distance_squared = (
                (self.row - sosnowsky_rows[i]) ** 2 +
                (self.column - sosnowsky_columns[i]) ** 2
            )
            if distance_squared < min_distance:
                min_index = i
                min_distance = distance_squared

        sosnowsky_row = sosnowsky_rows[min_index]
        sosnowsky_col = sosnowsky_columns[min_index]

        # Move towards the closest hogweed if it's within bounds
        if sosnowsky_row < self.row and self.row > 0:
            self.organism_go_top()
        elif sosnowsky_row > self.row and self.row < len(grid_board) - 1:
            self.organism_go_bottom()
        elif sosnowsky_col < self.column and self.column > 0:
            self.organism_go_left()
        elif sosnowsky_col > self.column and self.column < len(grid_board[0]) - 1:
            self.organism_go_right()

        grid_board[self.row][self.column] = self.character
        self.print_to_journal(f"({self.row}, {self.column})\n")

    def collision(self, grid_board, organisms, current_index):
        return "None", None

    def get_static_counter(self):
        return CyberSheep.static_counter
