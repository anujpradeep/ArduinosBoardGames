#ifndef __TIC_TAC_TOE_H
#define __TIC_TAC_TOE_H

#include "constants_and_types.h"
#include "proc_mechanics.h"

/*
Resets our array so that if the user 
starts a new game the array is not the 
same as before
*/
void arrayReset();

/*
Sets up the tic tac toe board 
and game interface. Also calls arrayReset();
*/
void ticSetup();

/*
Checks all the different win conditions,
3 in row, vertically, horizontally, and 
diagonally. If the conditions are met
returns true.
*/
bool ticWin();

/*
This function checks whether all the board
spaces have been filled, if so, it returns
true and the game is over
*/
bool fullCheck();

/*
Depending on whos turn it is,
this function prints X or O wherever the 
player tapped on the screen
*/
void printXO(char player);

/*
This function determines where the player
tapped on the screen and then sets the
cursor accordingly and then calls printXO()
*/
bool ticSection(screenCord coordinates, bool turn);

/*
This function acts like our main for Tic Tac Toe
it calls all of the functions and handels everything 
needed to play.
*/
void ticTac();

#endif