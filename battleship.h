#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
typedef struct _board board;

int parseArgs(int argc, char **argv, int *board_size, int *max_shots);
/*parseArgs parses the command line input arguments,
 *stores the user provided board size and max number shots 
 *Returns 0 for success and -1 for a malformed input*/


void randomFleetArrangement(board * b);
/*generates the random fleet arrangement, on blank_board and returns
 *a pointer to new board*/

void menuScreen();
/*Gives the user a welcome screen with instructions on how to play*/

int printUsage(void);
/*Prints an error message when inputs are incorrectly entered*/

int getTracker(board *b, int row, int col);
/*gets the value of the tracker to determine hits or misses */

void setTracker(board *b, int row, int col, double val);
/*Sets points of the board to 0, 1, or -1 depending on whether the spot is hit, missed, or unhit*/

void set(board * b, int row, int col, double val);
/*sets element of array where data rearding the fleet arrangement will be taken from*/

int  get(board * b, int row, int col);
/*take element from board for use*/

board * newBoard(int size);
/*creates a new board depending on specifications of user*/

void showBoard(board *b);
/*shows board */

void deleteBoard(board *b);
/* deletes board */

void printBoard(board *b);
/* print out board for user to view */

	      
void randomArrangeCarrier(board*b);
void randomArrangeBattleship(board*b);
void randomArrangeCruiser(board*b);
void randomArrangeSubmarine(board*b);
/* Randomly arranges the position of the respective ship on the board */

void trackTarget(board*b, int * row, int *col);
/* reads the user input for the targeted coordinate on the board, and will return an error if there is one.*/


void play(board *b, int maxhsots);
/*Takes the user input and tells them if their shot was a hit or miss, and removes one from the maximum shot count. 
  Then, it prints a new board after each shot. This continues until the user wins or loses the game.*/


	       
#endif
