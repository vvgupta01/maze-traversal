This project was compiled with clang version 6.0.1 and requires a Linux system with ImageMagick to generate animations.

### Overview
This project implements Breadth-First Search (BFS) and Depth-First Search (DFS) to traverse a randomly generated rectangular maze. The maze is generated through a collection of disjoint sets with acyclic paths, which guarantees that only one path exists from any tile to any other tile. 

In this context, a solution is defined as any path from (0, 0) to a tile in the last row. Since every solution is unique, the number of possible solutions is equal to the width of the maze. Three variants of both traversals are implemented, including shortest-path, set path, and longest-path. Therefore, the shortest-path is the first solution found, while the longest-path is the last solution found. The set-path is simply the solution from (0, 0) to (width - 1, height - 1), which may be the shortest/longest path as well.

Furthermore, both traversals can be visualized in the form of a search animation and solution image, which can be found in the __visualization__ directory. An example of longest-path BFS and DFS on a 50x50 maze:

![BFS Search](/visualization/bfs-search.gif) 
![DFS Search](/visualization/dfs-search.gif)

### Running
The project can be compiled with `make` and ran with `./main` for a user-friendly interface that provides a guided entry of inputs. The algorithm only requires the width and height of the maze, as well as the type of traversal to run (both BFS and DFS are automatically run). 
Command-line argument can also be provided for quick input. For instance, `./main 100 50 1` finds the shortest-path for a randomly generated maze with a width of 100 tiles and height of 50 tiles. Traversal type is mapped as follows: 1 = shortest-path, 2 = set-path, and 3 = longest-path. The maximum width/height is 1000 tiles, while animations are supported for mazes up to a maximum of 10000 tiles (100x100) to prevent long run times. 
