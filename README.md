# Tic-Tac-Toe

A small C++ console game. I wanted to keep the game rules separate from the code that asks for moves and prints the board, so the rules can be tested without going through the console.

## Build

You need CMake 3.20 or newer and a C++17 compiler.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Run the game with:

```sh
./build/tto
```

On Windows, the executable is usually under `build/Debug` or `build/Release`, depending on the CMake generator.

## How it works

- Two players take turns as X and O.
- Pick a board size from 2x2 to 10x10.
- A full row or column wins; a diagonal counts on a square board.
- Invalid moves and occupied cells are rejected.
- The game detects draws and lets players start another round.

The tests cover move validation, wins, reset behavior, and invalid board sizes.
