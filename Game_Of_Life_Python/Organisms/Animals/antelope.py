from Organisms.organism import OrganismInitialData
from Organisms.animal import Animal
import random
from Organisms.animal import MoveDirection

class Antelope(Animal):
    def __init__(self, name, row, column):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        super().__init__(strength, initiative, name, character, row, column, "antelope.png")

    def action(self):
        self.age += 1
        direction = MoveDirection(random.randint(1, 4))
        height = width = 10
        # Find some good direction where we can go
        while True:
            if self.row > 0 and direction == MoveDirection.TOP:
                break
            elif self.column < width - 1 and direction == MoveDirection.RIGHT:
                break
            elif self.column > 0 and direction == MoveDirection.LEFT:
                break
            elif self.row < height - 1 and direction == MoveDirection.BOTTOM:
                break
            direction = MoveDirection(random.randint(1, 4))

        multiplier = random.randint(1, 2)
        print(f"{self.get_name()} moves from ({self.row}, {self.column}) to:", end=" ")

        # Update position based on direction
        if direction == MoveDirection.TOP:
            self.row = max(0, self.row - multiplier)
        elif direction == MoveDirection.BOTTOM:
            self.row = min(height - 1, self.row + multiplier)
        elif direction == MoveDirection.LEFT:
            self.column = max(0, self.column - multiplier)
        elif direction == MoveDirection.RIGHT:
            self.column = min(width - 1, self.column + multiplier)

        print(f"({self.row}, {self.column})")

    def collision(self):
        pass
