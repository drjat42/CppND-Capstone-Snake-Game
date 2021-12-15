# CPPND: Capstone Snake Game Example

This my fork of the starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.  Please see the explanation of my [changes](#changes-for-capstone) and [how they fulfill the Capstone rubric](rubric-points-addressed) below.

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
4. Run it: `./SnakeGame` or `./SnakeGame file` or `./SnakeGame random`.  (The first two are equivalent.)


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
1. Collected Hex values for colors into named constants in `Renderer.h` becuase it's not 1980.  Come on, man! 
1. Added obstacles to the grid that end the game if the snake head collides with one. 
1. `Board` objects contain obstacles.
   - Obstacles are stored in private member vector accessed via a getter method.
   - Board also have private names and bonuses.
   - `Game::Update` uses the board to decide if the snake has struck an obstacle
   - `Renderer::Render` uses the board to draw the obstacles and the board name.
   - `Board` implements the rule of 5.
   - The name of the current board is displayed in the window title.
   - The bonus is added to the score as soon as a board is loaded, even if it immediately kills the snake.
   - The name of the final board is displayed on game exit.
1. A `BoardLoader` object runs in its own thread.  Every 10 - 15 seconds the BoardLoader 
   - checks a future to see if the game has ended (the snake is not alive) and exits its thread if so.
   - loads/creates a new board
   - `BoardLoader::LevelTimer` sends each board to the main thread via a parameterized `MessageQueue`.
1. `Game::Run` calls `BoardLoader::StartBoardLoadingThread` to spawn the `BoardLoader`thread and receives a promise.
   - Game thread fulfills the promise when the snake dies and then joins the `BoardLoader` thread before exiting.
1. There are two implementations of the abstract class`BoardLoader`that inherit the above behavior.
   - `RandomBoardLoader` creates a board by creating obstacle blocks at random locations.  It names boards sequentially.  The board level bonus also increases sequentially.
   - `FileBoardLoader` loads boards from the `data` directory by cycling through all the files in that directory in alphabetical order.  The name of the file is the name of the board.  The board level bonus cycles from 0 to the number of distinct boards.
   - A commandline argument controls which `BoardLoader` implementation is used.  "random" indicates to use the `RandomBoardLoader`.  "file" (or nothing) indicates to use the `FileBoardLoader`.  Any other commandline arguement(s) will produce a usage message.

#Future Ideas/Nice to haves
1. More boards.
1. When loading a new board, if it intersects the snake body, shorten the snake and turn the tail into obstacles.  
1. Cary the snake tails forward between boards as additional obstacles.
1. Use smart pointers to move board from loader to game maybe with channel.
1. Use pointers for BoardLoaders in main so that subclassing works more elegantly and only one loader is actually created.

## Rubric Points Addressed

 - "**A README with instructions is included with the project.**  The README is included with the project and has instructions for building/running the project. If any additional libraries are needed to run the project, these are indicated with cross-platform installation instructions." 
    - See [Basic Build Instructions](basic-build-instructions) above.

 - "**The README indicates which project is chosen.** The README describes the project you have built. Thee README also indicates the file and class structure, along with the expected behavior or output of the program." 
  - See [Changes for Capstone](changes-for-capstone) and []() above.

 - "**The README includes information about each rubric point addressed.** The README indicates which rubric points are addressed. The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed."   - This section right here.

- "**The submission must compile and run.**  The project code must compile and run without errors.  We strongly recommend using cmake and make, as provided in the starter repos. If you choose another build system, the code must compile on any reviewer platform." 
  - Pretty much the whole thing.

- "**The project demonstrates an understanding of C++ functions and control structures.** A variety of control structures are used in the project. The project code is clearly organized into functions."
  - The `Board`, `BoardLoader`, `FileBoardLoader`, and `RandomBoardLoader` classes are each organzied into member functions such as constructors, `Board::Obstacles`, `BoardLoader::StartBoardLoadingThread`, and`FileBoardLoader::LoadBoard`.  Control structures used include `while` and `for` loops, `if` blocks, function calls, and return statements.

- "**The project reads data from a file and processes the data, or the program writes data to a file.** The project reads data from an external file or writes data to a file as part of the necessary operation of the program."
  - The default FileBoardLoader reads the `data` directory to find board files and loads each file in turn.  It parses the file contents to construct each board and display the obstacles specified in the file.  The name of each file is used as the name of the board.

- "**The project accepts user input and processes the input.** The project accepts input from a user as part of the necessary operation of the program."
  - The original Snake Game repo does this.  I did not particularly extend this functionality except in that I changed how the snake interacts with the board obstacles.

- "**The project uses Object Oriented Programming techniques.** The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks."
  -  Added classes inlcude `Board`, `BoardLoader`, `FileBoardLoader`, and `RandomBoardLoader`.  
  -  `Board` is essentially a struct for obstacles, bonus, and board name with no real logic.  
  -  `BoardLoader` is an abstract class declaring four methods.  `StartBoardLoadingThread` begins the timer to load boards. `LevelTimer` iterates loading boards and sleeping for random intervals.  There is also a thread safe getter `getBoard`.  In additon, `BoardLoader::LoadBoard` is a pure virtual function implemented by the concrete derived classes `FileBoardLoader` and `RandomBoardLoader`.  
  -  `MessageQueue` is an auxilliary class in the `BoardLoader.cpp` and header files that safely sends data from one thread to the other.
  - `FileBoardLoader` cycles through all the files in the `data` directory, reading each in turn, to load a board.
  - `RandomBoardLoader` generates a number of random obstacles to generate a board.

- "**Classes use appropriate access specifiers for class members.** All class data members are explicitly specified as public, protected, or private."
  - `Board` has private data members `bonus`, `name` and `_obstacles`.
  - `BoardLoader` has private data members `_minLevelMS`, `_maxLevleMS`, `_board`, and `_threads`.
  - `FileBoardLaoder` has private data members `_nextBoardIndex`, `_boardDirectoryPath`, and `_boardNames`.
  - `RandomBoardLoader` has private data members `_gridWidth`, `gridHeight`, and `_maxObstacles`.

- "**Class constructors utilize member initialization lists.** All class members that are set to argument values are initialized through member initialization lists."
  - `Board`and `RandomBoardLoader`, and `FileBoardLoader` use initialization lists.
  - `RandomBoardLoader` and `FileBoardLoader` invoke the base class constructor in their initialization lists.
  - `FileBoardLoader` reads file names from disk to initialize its member variables.  Member variables of `BoardLoader` only need default initialization.

- "**Classes abstract implementation details from their interfaces.** All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways."
  - All classes and methods are documented. 

- "**Classes encapsulate behavior.** Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions."
  - `Board` is a struct for the holding state of a board.  `Obstacles`, `Name`, and `Bonus` are accessed via getters.
  - `BoardLoader` encapsulates the timer thread for and abstracts the notion of loading boards asynchronously. Boards are access via a threadsafe getter. 
  - `MessageQueue` encapsulates passing messages between threads safely.
  - `FileBoardLoader` handles loading boards from files.
  - `RandomBoardLoader` creates random boards.

- "**Classes follow an appropriate inheritance hierarchy.** Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified."
  - `BoardLoader` is an abstract class.  It is composed of a `Board` and appropriate threads and mutexes.  It abstracts the notion of loading a board in an pure virutal method `LoadBoard`.
  - `FileBoardLoader` and `RandomBoardLoader`provide the concrete implementations of the `LoadBoard` method.

- "**Overloaded functions allow the same function to operate on different parameters.** One function is overloaded with different signatures for the same function name."

- "**Derived class functions override virtual base class functions.** One member function in an inherited class overrides a virtual base class member function."
  - `FileBoardLoader::LoadBoard` and `RandomBoardLoader::LoadBoard` override pure virtual function `BoardLoader::LoadBoard`. 

- "**Templates generalize functions in the project.** One function is declared with a template that allows it to accept a generic parameter."
  - `MessageQueue::Send` and `Message::Receive` are templatized functions.

- "**The project makes use of references in function declarations.** At least two variables are defined as references, or two functions use pass-by-reference in the project code."
  - `Snake::Update` and `Renderer::Render` parameters have been extended to include a reference to a `Board`.
  - `Game::Run` parameters have been extended to include a reference to a `BoardLoader`.

- "**The project uses destructors appropriately.** At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor."

- "**The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.** The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction."

- "**The project follows the Rule of 5.** For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined."
  - The Rule of 5 is implemented for the `Board` object.

- "**The project uses move semantics to move data, instead of copying it, where possible.**  For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object."
  - `FileBoardLoader::LoadBoard` and `RandomBoardLoader::LoadBoard` return `Boards` by value.
  - `BoardLoader::LevelTimer` moves the returned `Board` into the `MessageQueue`.

- "**The project uses smart pointers instead of raw pointers.** The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers."

- "**The project uses multithreading.** The project uses multiple threads in the execution."
  - `BoardLoader::StartBoardLoadingThread` starts a new thread to load boards periodically.

- "**A promise and future is used in the project.** A promise and future is used to pass data from a worker thread to a parent thread in the project code."
  - `BoardLoader::LevelTimer` polls a future to determine when the game has ended and the board loading thread should exit.  `Game::Run` sets the promise when the snake dies.

- "**A mutex or lock is used in the project.** A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code."
  - `MessageQueue::recieve` uses a `std::unique_lock` to dequeue messages.  `MessageQueue::send` uses a `std::lock_guard` and the same `mutex` to enqueu messages in the shared `queue` variable.

- "**A condition variable is used in the project.** A std::condition_variable is used in the project code to synchronize thread execution."
  - `MessageQueue` uses a condition varialbe to synchronize between the `send` and `receive` methods.  (Sort of but not really, as the receive only blocks for 2 microseconds and then returns an empty optional if no message is ready.)



