from Organisms.organism import OrganismInitialData
from Organisms.plant import Plant


class SosnowskyHogweed(Plant):
    def __init__(self, name, row, column):
        strength = OrganismInitialData[name]["strength"]
        initiative = OrganismInitialData[name]["initiative"]
        character = OrganismInitialData[name]["character"]
        super().__init__(strength, initiative, name,
                         character, row, column, "sosnowsky_hogweed.png")

    def action():
        pass

    def collision():
        pass
