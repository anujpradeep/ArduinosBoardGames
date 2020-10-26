#ifndef __MAZE_H
#define __MAZE_H

#include "constants_and_types.h"
#include "proc_mechanics.h"

#define CURSOR_SIZE 9 //same as assignment 1


/*
This struct is similar to the screenCord struct 
however this is specifically for the player movement
and so the type was not int16_t therefore we created a new
struct almost the same but instead its just int.
*/
struct coordinates{
	int xcord, ycord;
};

/*
This struct is used to store the coordinated of the starting
and ending positons on the maze. Since the start and end require
x and y values, it uses the struct coordinates.
*/
struct startEnd{
	coordinates start, end;
};

/*
This function is basically the same as the function
given to us in the joy_cursor.cpp file, and it redraws
the cursor of our player.
*/
void redrawCursor(uint16_t colour);

/*
This function is the same as redrawCursor however it is used 
to redraw the trails of our player.
*/
void redrawPrevCursor(uint16_t colour);

/*
This processes the moves the player makes in the maze.
*/
void playerMovement();

/*
This function determines which maze the player
has selected. It returns an int which is the maze
the player selected.
*/
int mazeSelect();

/*
This function determines if the move the player did
was valid or not. So if the player runs into a wall
it will return false.
*/
bool safe(int x, int y);

/*
This function basically controls the whole maze,
it basically acts as the main() for this file.
*/
void runMaze();

/*
This function is called when the player selects which
maze they wish to play, the int is the maze number and 
accordingly it stores the arrya of the desired maze.
*/
void mazeSelector(int c);

/*
This function sets up the maze that was chosen
it goes through an array and then accordingly sets up 
the maze walls. It returns struct startEnd which is 
the starting and ending locations of the maze.
*/
startEnd mazeSetup();
#endif