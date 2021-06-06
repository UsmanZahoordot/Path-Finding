
Design a robot navigation system which is able to conduct blind searches to find its path from start to goal state.  As input, the system will take a description of the maze stored as a text file.  The maze is a 2D grid with obstacles inside it.  An example of such a maze is given below:

| | | | | | | |
| :- | :- | :- | :- | :- | :- | :- |
| | | | | | |` `GOAL|
| | | | | | | |
| | | | | | | |
| | | | | | | |
| | | | | | | |
| | | | | | | |
| | | | | | | |
| | | | | | | |
| | | | | | | |
| | | | | | | |
|START| | | | | | |
| | | | | | | |
| | | | | | | |

The obstacles are filled rectangles of unknown dimensions and can be found anywhere in the maze.    The robot cannot be in those cells.  There are 3 actions allowed.  Up one cell (cost is 2), right one cell (cost is 2), diagonally up towards the right(cost is 3).  Carefully think about the configuration of a **state**. The system should output:

1. The complete path if goal is found otherwise failure
1. The total cost of the path
1. A grid which shows the path followed.  You do not need graphics for this output.  The grid can be made textually using 1 for obstacles, 0 for empty cells and ‘\*’ for path followed

**FORMAT OF INPUT FILE (sample file grid.txt for above grid provided.)**

Rows Cols //dimensions of the grid on line one 

start coordinates on line two 

goal coordinates on line three

the grid itself, one row per line.  There will be a zero for empty slot and one for an obstacle.  **The (0,0) coordinate is the bottom left cell.**  

You need to follow this format of text file as your code will be tested with similar grid files.

**ALGORITHMS TO IMPLEMENT**

1. Breadth-first search
1. Depth-first search
1. Iterative deepening search

