#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/* Partners: crjung2, hyunwoo6, awinick2
 * createmaze:
 * destroyMaze: destroyMaze deallocates the memory in the struct
 * It dellacoates with the inner-most structure so that a memory leak does occur
 * printMaze: printMaze prints the maze line by line for each row
 * solveMaze: solveMaze first tests the base cases if the current cell is not empty, outside, or at the end
 * it uses recursion to attempt a possible solution, and if it finds that the current solution doesn't work
 * it will backtrack and set the attempted path as visited
 */

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the
 * input file SIDE EFFECTS: None
 */

maze_t *createMaze(char *fileName)
{
    // Your code here. Make sure to replace following line with your own code.

    // OPEN FILE
    FILE *file;
    file = fopen(fileName, "r");

    // allocate memory for maze
    maze_t *maze = malloc(sizeof(maze_t));

    // initiate varaible for width and height and charater
    int w, h;
    char c;

    // read the width and height.
    fscanf(file, "%d %d", &w, &h);

    // set maze width and height of to w and h
    maze->width = w;
    maze->height = h;

    // allocate memeory for the correct amount of rows of the cells
    maze->cells = malloc(sizeof(maze->cells) * (maze->height));

    // allocate memory for each of the rows.
    for (int i = 0; i < maze->height; i++)
    {
        maze->cells[i] = malloc(sizeof(maze->cells[i]) * (maze->width));
    }

    // read new line so that it doesnt interfere with reading the maze data
    fscanf(file, "%c", &c);

    // loop through each of the cells of the maze.
    for (int i = 0; i < maze->height; i++)
    {
        for (int j = 0; j < maze->width; j++)
        {
            // read a single character
            fscanf(file, "%c", &c);
            // set the cell as the read character
            maze->cells[i][j] = c;

            // Set the start row and column
            if (c == 'S')
            {
                maze->startRow = i;
                maze->startColumn = j;
            }
            else if (c == 'E')
            {
                // Set the end row and column
                maze->endRow = i;
                maze->endColumn = j;
            }
        }
        // Set the start row and column

        fscanf(file, "%c", &c);
    }

    // close file after done reading.
    fclose(file);

    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including
 * the structure itself INPUTS:        maze -- pointer to maze structure that
 * contains all necessary information OUTPUTS:       None RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t *maze)
{
    // Your code here.
    // Deallocate in order to prevent memory
    for (int i = 0; i < maze->height; i++)
    {
        free(maze->cells[i]); // Deallocate the value of cells in the in maze
    }
    free(maze->cells); // Deallocate cells
    free(maze);        // Deallocate maze
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look
 * like examples) INPUTS:       maze -- pointer to maze structure that contains
 * all necessary information width -- width of the maze height -- height of the
 * maze OUTPUTS:      None RETURN:       None SIDE EFFECTS: Prints the maze to
 * the console
 */
void printMaze(maze_t *maze)
{
    // Your code here.
    for (int i = 0; i < maze->height; i++)
    {
        printf("%s\n", maze->cells[i]); // print the maze with each row per line
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first
 * search, INPUTS:               maze -- pointer to maze structure with all
 * necessary maze information col -- the column of the cell currently beinging
 * visited within the maze row -- the row of the cell currently being visited
 * within the maze OUTPUTS:              None RETURNS:              0 if the
 * maze is unsolvable, 1 if it is solved SIDE EFFECTS:         Marks maze cells
 * as visited or part of the solution path
 */
int solveMazeDFS(maze_t *maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    int w = maze->width;  // Width of the maze
    int h = maze->height; // Height of the maze
    if (col < 0 || row < 0 || col >= w || row >= h)
    {
        return 0; // Check if out-of-bounds
    }

    if (maze->cells[row][col] == 'E')
    {
        maze->cells[maze->startRow][maze->startColumn] = 'S';
        // Set the starting point back to 'S'
        // When editing the path, S gets over written to * or ~
        return 1; // If solution is found
    }

    if (maze->cells[row][col] != ' ' && maze->cells[row][col] != 'S')
    {
        return 0; // If cell is not empty and not Start (wall, visited)
    }

    maze->cells[row][col] = '*'; // Set current location to solution path

    if (solveMazeDFS(maze, col - 1, row))
    { // Check left if part of solution
        return 1;
    }
    if (solveMazeDFS(maze, col + 1, row))
    { // Check right if part of solution
        return 1;
    }
    if (solveMazeDFS(maze, col, row + 1))
    { // Check up if part of solution
        return 1;
    }
    if (solveMazeDFS(maze, col, row - 1))
    { // Check down if part of solution
        return 1;
    }

    // Since it is not part of solution
    maze->cells[row][col] = '~'; // Set current location to visited

    return 0;
}