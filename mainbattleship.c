#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "battleship.h"
#include <time.h>

int main(int argc, char **argv){

  menuScreen();

  srand(time(0));

  int size = 8, maxshots, err;
  err = parseArgs(argc, argv, &size, &maxshots);

  //check for valid input and print message if there is
  if(err == -1)printUsage();

  else{
  //Creates a new board
  board *b;
  b = newBoard(size);
  //Arranges the fleet
  randomFleetArrangement(b);
  play(b, maxshots);
  }
}
