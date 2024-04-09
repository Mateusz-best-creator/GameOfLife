from abc import ABC, abstractmethod
from organism import Organism

class Animal(Organism, ABC):
    def __init__(self):
        pass

    @abstractmethod
    def action():
        pass
    
    @abstractmethod
    def collision():
        pass
