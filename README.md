# CPPND: Capstone Project - Conway's Game of Life

This project was completed as the capstone project for the UDacoty C++ Nandegree. The project is an implementation of Conway's Game of Life using C++ and the SDL 2.0 library.

## Project Description

Conway's Game of Life is described here: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

When the project is built and run, a window should show consisting of the "Board" where the cellular automata reside.
There are also three buttons, the increase size button (+), the decrease size button (-), and the RUN button(||/>).

The player can select the initial state of the board by clicking on cells to enable them. When the RUN button is clicked the simulation will start and progress according to the following rules:
* Any live cell with two or three live neighbours survives.
* Any dead cell with three live neighbours becomes a live cell.
* All other live cells die in the next generation. Similarly, all other dead cells stay dead.

The (+) and (-) buttons will increase and decrease the size of the board respectively.

When the player exits the game, the current board state will be saved in json format in a savefile. When the game is next run, the board state will be loaded.

## Project Structure

GameManager class (.cpp and .h)
* This class handles the logic of the game, responds to game events, and makes calls to the SDLManager class and SaveFileManager classes as required.

SDLManager class (.cpp and .h)
* This is a wrapper class to encapsulate the functionality of the SDL library required to render the game and detect user input.

SaveFileManager class (.cpp and .h)
* This class handles file IO - saving the board layout as a json array and loading the board layout from the save file

Board class (.cpp and .h)
* This class contains the board size, and current state of cells

Button class (.cpp and .h)
* This class is used by SDLManager to encapsulate the functionality of a button, including positioning and rendering

Constants.h
* Contains the definition of the GAME_EVENTS enum that is used by multiple classes

Additional information
* savefile.txt and the images for button textures (.bmp files) are found in the /build folder

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL 2.0
  * Detailed instructions for installation can be found here: https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php

## Basic Build Instructions

1. Clone this repo.
2. Navigate to the /build directory.
3. Compile: `cmake .. && make`
4. Run it: `./GameOfLife`

## Rubric Points
* The project demonstrates an understanding of C++ functions and control structures.
  * This can be seen in classes throughout the project.

* The project reads data from a file and process the data, or the program writes data to a file.
  * This can be seen in the SaveFileManager class. The board layout is saved/loaded from a file in json format.

* The project accepts user input and processes the input.
  * User input is handled int the SDLManager "void handleEvents()" function, and processed in the "bool handleInput()" function in the GameManager class.

* The project uses Object Oriented Programming techniques.
  * This can be seen in the 5 classes outlined above in the project structure.

* Classes use appropriate access specifiers for class members.
  * All classes use private member variables with getter/ setter functions where appropriate.

* Class constructors utilize member initialization lists.
  * The button class utilises constructor arguments to initialize variables in a member initialization list.

* Classes encapsulate behavior.
  * Member variables are private with getter/setter functions.

* The project uses destructors appropriately.
  * GameManager class, SDLManager class, and the Button class all use destructors to deallocate memory, either using the delete key-word or by using specific SDL functions.