# GameOfLife

This repository contains a Game of Life simulation implemented in three programming languages: C++, Java, and Python.

- The C++ project uses the console to display the entire simulation.
- The Java implementation utilizes Swing for the graphical user interface.
- The Python version utilizes the Pygame framework for visualization.

Feel free to explore each implementation and experiment with the Game of Life simulation in different programming environments!

## Running the C++ Project

Before running the C++ project, you need to create a build directory for CMake. Follow these steps:

1. Create the build directory by running the following command:
    ```
    cmake -S source/ -B build
    ```

2. After creating the build directory, you have two options to compile and run the project:
    - Option 1: Execute the `script_build.sh` script. This script will run CMake and compile your binary automatically. You can do this by running:
        ```
        ./script_build.sh
        ```
    
    - Option 2: Alternatively, you can run the binary directly by typing the following commands:
        ```
        cmake --build build/
        ./build/GameOfLife
        ```

3. Make sure you have CMake installed on your system. If you encounter any permission issues with the `script_build.sh` script, you can change the permissions using the following command:
    ```
    chmod 755 script_build.sh
    ```

Enjoy exploring the C++ implementation of the Game of Life!

<img src="Screenshots/Game_Of_Life_Cpp.png" alt="Simulation" width="250">
<img src="Screenshots/Game_Of_Life_Cpp_2.png" alt="Simulation" width="250">
