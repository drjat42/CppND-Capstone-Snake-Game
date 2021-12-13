# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg


# Changes for Capstone
1. I have extended the Snake game for my Capstone project.
1. Collected Hex values for colors into named constants becuase it's not 1980.  Come on, man! (xxxx.cpp #yyyy)
1. Added obstacles to the grid that end the game if the snake collides with one.  (xxxx.cpp #yyyy)
1. Obstacles are stored in `Board` objects.
   - Obstacles are stored in private member vector accesses via a getter method.
   - `Game::Update` uses the board to decide if the snake has struck an obstacle
   - `Renderer::Render` uses the board to draw the obstacles
   - `Board` implements the rule of 5.
1. BoardLoader object runs in its own thread.  Every 10 - 15 seconds the BoardLoader 
   - wakes, checks a promise to see if the game has ended (the snake is not alive) and exits its thread if so.
   - creates a new board
   -XXXX grabs the lock and updates the shared board variable
   - goes back to sleep
1. Game thread ? spawns the BoardLoader thread with a promise.
   - Game thread fulfills the promise when the snake dies and then joins the BoardLoader before exiting.
1. There are two implementations of the abstract class`BoardLoader`that inherit the above behavior.
   - `RandomBoardLoader` creates a board by creating 10 obstacle blocks at random locations.  
   - `FileBoardLoader` loads boards from the `data` directory by cycling through all the files in that directory in alphabetical order.

#TODOs/Ideas
1. Done. Implement promise to detect when snake dies so BoardLoader thread can exit.
1. Done. Command line argmument to control which board loader to use.
1. More boards.
1. Ensure boards don't intersect snake when loaded by removing those obstacles from the board the first time it's loaded.
1. Use smart pointers to move board from loader to game maybe with channel
1. Bump the score every time a new board or output the number of boards loaded on the exit screen is loaded which means detecting a new board somehow.

# The README indicates which rubric points are addressed. The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed.

 - "A README with instructions is included with the project.  The README is included with the project and has instructions for building/running the project. If any additional libraries are needed to run the project, these are indicated with cross-platform installation instructions." This file, see lines 11 - 31 above.

 - "The README indicates which project is chosen. The README describes the project you have built. Thee README also indicates the file and class structure, along with the expected behavior or output of the program." - Lines 50 - XX above.

 - "The README includes information about each rubric point addressed. The README indicates which rubric points are addressed. The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed." - This bit right here.

- "The submission must compile and run.  The project code must compile and run without errors.  We strongly recommend using cmake and make, as provided in the starter repos. If you choose another build system, the code must compile on any reviewer platform." - Pretty much the whole thing.


CRITERIA
MEETS SPECIFICATIONS
The project demonstrates an understanding of C++ functions and control structures.

A variety of control structures are used in the project.

The project code is clearly organized into functions.

The project reads data from a file and process the data, or the program writes data to a file.

The project reads data from an external file or writes data to a file as part of the necessary operation of the program.

The project accepts user input and processes the input.

The project accepts input from a user as part of the necessary operation of the program.

Object Oriented Programming

CRITERIA
MEETS SPECIFICATIONS
The project uses Object Oriented Programming techniques.

The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.

Classes use appropriate access specifiers for class members.

All class data members are explicitly specified as public, protected, or private.

Class constructors utilize member initialization lists.

All class members that are set to argument values are initialized through member initialization lists.

Classes abstract implementation details from their interfaces.

All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.

Classes encapsulate behavior.

Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.

Classes follow an appropriate inheritance hierarchy.

Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.

Overloaded functions allow the same function to operate on different parameters.

One function is overloaded with different signatures for the same function name.

Derived class functions override virtual base class functions.

One member function in an inherited class overrides a virtual base class member function.

Templates generalize functions in the project.

One function is declared with a template that allows it to accept a generic parameter.

Memory Management

CRITERIA
MEETS SPECIFICATIONS
The project makes use of references in function declarations.

At least two variables are defined as references, or two functions use pass-by-reference in the project code.

The project uses destructors appropriately.

At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.

The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.

The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.

The project follows the Rule of 5.

For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.

The project uses move semantics to move data, instead of copying it, where possible.

For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.

The project uses smart pointers instead of raw pointers.

The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.

Concurrency

CRITERIA
MEETS SPECIFICATIONS
The project uses multithreading.

The project uses multiple threads in the execution.

A promise and future is used in the project.

A promise and future is used to pass data from a worker thread to a parent thread in the project code.

A mutex or lock is used in the project.

A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.

A condition variable is used in the project.

A std::condition_variable is used in the project code to synchronize thread execution.



