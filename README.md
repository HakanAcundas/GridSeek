# GridSeek

GridSeek is a small grid (2D array) based path finding project. It provides Dijkstra and A* algorithms for path finding.
Each grid is represented by a Tile class that has movements cost in it. Tile class can be either be ForestTile or SnowTile. Each subclass movement cost can be configured in shared/global_settings.hpp file.

## Build with CMake

Create a build folder in your project folder:
mkdir build
cd build

Generate project files and build:
cmake ..
cmake --build .

After executing these command, cmake will generate GridSeek.exe file in your debug or release folder.

## UML Diagram


## Input System

I used Command architecture for input system. The reason is, why not? :)

The biggest advantage of this is architecture is it increases the "game loop" readability.


With only 1 if condition, we can handle all input commands.