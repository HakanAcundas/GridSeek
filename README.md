# GridSeek

GridSeek is a small grid (2D array) based path-finding project. It provides [Dijkstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Pseudocode) and [A*](https://en.wikipedia.org/wiki/A*_search_algorithm) algorithms for path finding.
Each grid is represented by a [Tile](src/map/tile.hpp) class that has movements cost in it. The Tile can be either [ForestTile](src/map/ForestTile.hpp) or [SnowTile]((src/map/SnowTile.hpp)). Each subclass movement cost can be configured in [global settings](shared/global_settings.hpp).

## Build with CMake

Create a build folder in your project folder:
'''
mkdir build
cd build
'''

Generate project files and build:
'''
cmake ..
cmake --build .
'''
After executing these commands, CMake will generate the GridSeek.exe file in your debug or release folder.

## Input System

I used Command architecture for the input system. The reason is, why not? :) It is more scalable than a normal switch, if input statements. Additionally, the “game loop” becomes more readable.

As you can see:
'''
Command* command = Input::get_instance().handle_input();
		if (command)
			command->execute();
'''

We can handle all commands (including input commands and other commands) with only one if condition.