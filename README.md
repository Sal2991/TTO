# Tic-Tac-Toe

A two-player console Tic-Tac-Toe game written in C++17. The game rules are separated from console input/output so the core logic can be tested independently.

## Features

- Configurable boards from 2x2 through 10x10
- Alternating X and O turns
- Row and column win detection; diagonal wins on square boards
- Rejection of out-of-range and occupied-cell moves
- Draw detection and a replay prompt
- Unit-style checks for move validation, wins, draw handling, reset behavior, and invalid board sizes

## Requirements

- CMake 3.20 or newer
- A C++17-compatible compiler

## Build

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

Run the game:

```sh
./build/tto
```

On multi-configuration generators such as Visual Studio, the executable is typically under `build/Release` (or `build/Debug`).
