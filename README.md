# GameOfLife

This repository contains a Game of Life simulation implemented in three programming languages: C++, Java, and Python.

- The C++ project uses the console to display the entire simulation.
- The Java implementation utilizes Swing for the graphical user interface.
- The Python version utilizes the Pygame framework for visualization.

Feel free to explore each implementation and experiment with the Game of Life simulation in different programming environments!

## Running the C++ Project



## Running the Java Project

I used the Swing library to build this Game of Life simulation. If you want to clone this repo with the Java project, you have to clone the submodule:

```sh
git clone --recurse-submodules https://github.com/Mateusz-best-creator/GameOfLife.git
```

Once you've cloned the project, you can open your IDE and start the game! Messages about what is going on are displayed in the console. You can click on an empty cell and then decide by typing the appropriate character in the console what kind of organism you want to add. At the beginning you have to type board height and width, then at the start of the turn, you can:

- Press `p` to play
- Press `s` to save the state of the game to a file
- Press `r` to read the state of the game from a file

Once you've clicked `p`, you can use the arrow keys to move the human if they are alive or press `s` to activate the human's special ability, which temporarily increases their strength.

<img src="Screenshots/Game_Of_Life_Java.png" alt="Simulation" width="450">


## Running the Python Project

This is a Python GameOfLife project. To run it, you need to have Python installed along with the Pygame framework on your computer. You can check your Python version by typing:

```
python --version
```
or
```
python3 --version
```

To check if Pygame is installed, run:

```
pip show pygame
```

To get started, clone this repository using SSH or HTTP:
```
git clone <url>
```

And then execute:

```
python main.py
```
or
```
python3 main.py
```

The entire project should launch, and you should be able to play!

<img src="Screenshots/start_page.png" alt="Start Page" width="450">
<img src="Screenshots/simulation.png" alt="Simulation Gameplay" width="450">
<img src="Screenshots/adding_animal.png" alt="Adding Animals" width="450">
