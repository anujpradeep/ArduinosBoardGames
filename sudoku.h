#ifndef __SUDOKU_H
#define __SUDOKU_H


#include "constants_and_types.h"
#include "proc_mechanics.h"
#define N 9

/*
This struct is to save a row and 
column indexes so we can call elements
of 2D arrays
*/
struct rowcol{
	int row;
	int col;
};

/*

*/
struct savedrow{
	int column[N];
};

/*
This functions acts like the main function
for Sudoku, it calls all of the necessary 
functions and allows the game to run
*/
void runSud();

/*
This function displays the numbers of 
our sudoku board. The default numbers are
white and the user inputted numbers are red.
*/
void sudDisplay();

/*
This functions sets up the whole game
it creates the board on the tft screen and 
also created all of the necessary buttons.
*/
void sudSetup();

/*
This function is for the selection screen
for which sudoku board the user wishes to play,
it returns an int, 1 for board 1 and 2 for board 2
*/
int sudSelect();


/*
This function loads the sudoku board 
depending on which game was selected by the user from
the sudSelect() function
*/
void sudLoad(int choice);

/*
This function determines the coloumn of where
the user touched on the board
*/
int getColumn(screenCord touched);

/*
This function determined the row of where the 
user touched on the board
*/
int getRow(screenCord touched);

/*

*/
bool ifsafe(int b[N][N],int row,int col,int num);

rowcol empty(int b[N][N]);

/*
This function uses an algorithm which is able to 
solve any sudoku board passed to it. For us this 
function only solves the boards that are uses in our
games
*/
bool solveBoard(int b[N][N]);

/*
This function determines which number the user
picks in order to input it onto the board.
*/
int selectedNum(screenCord touched);
#endif
