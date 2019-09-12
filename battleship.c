#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "battleship.h"

typedef struct _board board;

struct _board{
  int size;
  int cells_ships;
  int sub;
  int unhit;
  int carrier;
  int battleship;
  int cruiser;
  int *data;
  int *tracker;
};
  
void  menuScreen(){
  printf("Welcome to Battleship! To play, take a shot by typing in the coordinate of a spot on the board, e.g 'a1'. The game will tell you whether your shot was a hit or miss. The goal is to sink all the ships before you run out of shots! Good luck!\n");
    }

int printUsage(void){
  printf("Error: to continue playing, please follow these guidlines: Size of the board can be between 5 and 20. Your max shots can be between 12 and n squared minus one, where n is the size of the board\n");
  return 0;
}

board * newBoard(int size){
  int i;
  board * b;
  if(size <= 0 || !size) return NULL;
  b = (board *) malloc(sizeof(board));
  if (!b) return NULL;
  b->size = size;
  b->data = (int *) malloc(size*size*sizeof(int));
  b->tracker = (int*)malloc(size*size*(sizeof(int)));
  if (!b->data) {
    free(b);
    return NULL;
  }
  if(!b->tracker){
    free(b);
    return NULL;
  }
   for(i = 0; i < size*size; i++){
			    
    b->data[i] = 0;
    b->tracker[i] = 0;
   }			    
   return b;
}

void setTracker(board *b, int row, int col, double val){
  b->tracker[(col-1) * b->size + row] = val;
}

int getTracker(board *b, int i, int j){
  return b->tracker[(j-1) * b->size + i ];
}

int get(board * b, int row, int col){
  return b->data[(col-1) *b->size + row];
}

void set(board * b, int row, int col, double val){
  b->data [(col-1) * b->size + row] = val;
}


void printBoard(board *b){
  int i = 0, j = 0;
  char c;
  for(c = 'a'; c < 'a'+b->size; ++c){
    printf("%c ", c);
  }
  for(i = 1; i<= b->size; i++){
    printf("\n");
    for(j=1;j<=b->size; j++){
      if(getTracker(b, i, j) == 0){
	printf(". ");
      }
      else if(getTracker(b,i,j) == 1){
	  printf("X ");
      }
      else if(getTracker(b,i,j) == -1){
	printf("O ");
      }
    }
  }
  printf("\n\n");
}

void showBoard(board *b){
  int i, j;
  for(i = 1; i <= b->size; i++){
    printf("\n");
    for(j = 1; j <=b->size; j++){
      printf("%d ", get(b,i,j));
    }
  }
  printf("\n\n");
}

int parseArgs(int argc, char ** argv, int *size, int * max_shots){
  //checks the function for invalid inputs
  if(argc < 2 || argc > 3 ){ 
    printUsage();
    return -1;
  }
  else if(argc == 2){ //if theres a second input by the user
    if(sscanf(argv[1], "%d", max_shots) != 1 || *max_shots<12 || *max_shots>((*size)*(*size))-1){
      printUsage();
      return -1;
    }
  }
  else if(argc == 3){ // if theres a third input by the user
    if(sscanf(argv[2], "%d", max_shots) != 1 || *max_shots<12 || *max_shots > ((*size)*(*size))-1){
      printUsage();
      return -1;
    }
    if(sscanf(argv[1], "%d", size) != 1 ||*size< 5 || *size > 20){
      printUsage();
      return -1;
    }
  }
  return 0;
}
void deleteBoard(board *b){
  if(b){
    free(b->data);
    free(b->tracker);
    free(b);
  }
}

void randomArrangeCarrier(board *b){
  int dir,randrow,randcol;
  while(1){
    dir = rand() % 4; //any direction from 0 to 3
  if(dir == 0){ 
    randrow = rand() % (b->size - 4 + 1) + 4;
    randcol = rand() % (b->size - 1 + 1) + 1;
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0 || get(b,randrow-2,randcol) !=0 || get(b,randrow-3,randcol) !=0 ) continue;
    set(b,randrow,randcol,1);
    set(b,randrow-1,randcol,1);
    set(b,randrow-2,randcol,1);
    set(b,randrow-3,randcol,1);
    break; //breaks the infinite loop
  }
  else if(dir == 1){
    randrow = rand() % ((b->size - 3) - 1 + 1) + 1; 
    randcol = rand() % (b->size - 1 + 1) + 1;  
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0 || get(b,randrow+2,randcol) !=0 || get(b,randrow+3,randcol) !=0 ) continue;
    set(b,randrow,randcol,1);
    set(b,randrow+1,randcol,1);
    set(b,randrow+2,randcol,1);
    set(b,randrow+3,randcol,1);
    break; 
  }
   else if(dir == 2){  
    randrow = rand() % (b->size - 1 + 1) + 1;  
    randcol = rand() % (b->size - 4 + 1) + 4;  
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0 || get(b,randrow,randcol-2) !=0 || get(b,randrow,randcol-3) !=0 ) continue;
    set(b,randrow,randcol,1);
    set(b,randrow,randcol-1,1);
    set(b,randrow,randcol-2,1);
    set(b,randrow,randcol-3,1);
    break; 
  }
   else if(dir == 3){ 
    randrow = rand() % (b->size - 1 + 1) + 1;  
    randcol = rand() % ((b->size-3) - 1 + 1) + 1;
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0 || get(b,randrow,randcol+2) !=0 || get(b,randrow,randcol+3) !=0 ) continue;
    set(b,randrow,randcol,1);
    set(b,randrow,randcol+1,1);
    set(b,randrow,randcol+2,1);
    set(b,randrow,randcol+3,1);
    break; 
    }
  }
}

void randomArrangeBattleship(board *b){
  int dir,randrow,randcol;
  while(1){
    dir = rand() % 4;//any direction  
  if(dir == 0){ 
    randrow = rand() % (b->size - 3 + 1) + 3; 
    randcol = rand() % (b->size - 1 + 1) + 1;
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0 || get(b,randrow-2,randcol) !=0) continue;
    set(b,randrow,randcol,2);
    set(b,randrow-1,randcol,2);
    set(b,randrow-2,randcol,2);
    break; //breaks the infinite loop 
  }
  else if(dir == 1){ 
    randrow = rand() % ((b->size - 2) - 1 + 1) + 1;  
    randcol = rand() % (b->size - 1 + 1) + 1;  
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0 || get(b,randrow+2,randcol) !=0) continue;
    set(b,randrow,randcol,2);
    set(b,randrow+1,randcol,2);
    set(b,randrow+2,randcol,2);
    break; 
  }
   else if(dir == 2){  
     randrow = rand() % (b->size - 1 + 1) + 1;   
     randcol = rand() % (b->size - 3 + 1) + 3;   
     if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0 || get(b,randrow,randcol-2) !=0) continue;
     set(b,randrow,randcol,2);
     set(b,randrow,randcol-1,2);
     set(b,randrow,randcol-2,2);
     break; 
  }
   else if(dir == 3){  
     randrow = rand() % (b->size - 1 + 1) + 1;  
     randcol = rand() % ((b->size-2) - 1 + 1) + 1;   
     if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0 || get(b,randrow,randcol+2) !=0) continue;
     set(b,randrow,randcol,2);
     set(b,randrow,randcol+1,2);
     set(b,randrow,randcol+2,2);
     break;
    }
  }
}

void randomArrangeCruiser(board *b){
  int dir,randrow,randcol;
  while(1){
    dir = rand() % 4; //any direction from 0 to 3
  if(dir == 0){ 
   randrow = rand() % (b->size - 3 + 1) + 3;   
   randcol = rand() % (b->size - 1 + 1) + 1; 
   if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0 || get(b,randrow-2,randcol) !=0) continue;
   set(b,randrow,randcol,3);
   set(b,randrow-1,randcol,3);
   set(b,randrow-2,randcol,3);
   break;  //breaks the infinite loop
  }
  else if(dir == 1){ 
   randrow = rand() % ((b->size - 2) - 1 + 1) + 1;  
   randcol = rand() % (b->size - 1 + 1) + 1;   
   if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0 || get(b,randrow+2,randcol) !=0) continue;
   set(b,randrow,randcol,3);
   set(b,randrow+1,randcol,3);
   set(b,randrow+2,randcol,3);
   break;  
  }
   else if(dir == 2){  
    randrow = rand() % (b->size - 1 + 1) + 1;  
    randcol = rand() % (b->size - 3 + 1) + 3;   
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0 || get(b,randrow,randcol-2) !=0) continue;
    set(b,randrow,randcol,3);
    set(b,randrow,randcol-1,3);
    set(b,randrow,randcol-2,3);
    break; 
  }
   else if(dir == 3){ 
    randrow = rand() % (b->size - 1 + 1) + 1;  
    randcol = rand() % ((b->size-2) - 1 + 1) + 1;  
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0 || get(b,randrow,randcol+2) !=0) continue;
    set(b,randrow,randcol,3);
    set(b,randrow,randcol+1,3);
    set(b,randrow,randcol+2,3);
    break; 
    }
  }
}

void randomArrangeSubmarine(board *b){
  int dir,randrow,randcol;
  while(1){
    dir = rand() % 4;//any direction from 0 to 3 

  if(dir == 0){ 
    randrow = rand() % (b->size - 2 + 1) + 2;
    randcol = rand() % (b->size - 1 + 1) + 1;   
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0) continue;
    set(b,randrow,randcol,4);
    set(b,randrow-1,randcol,4);
    break;  //breaks the infinite loop
  }
  else if(dir == 1){
    randrow = rand() % ((b->size - 1) - 1 + 1) + 1; 
    randcol = rand() % (b->size - 1 + 1) + 1;  
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0) continue;
    set(b,randrow,randcol,4);
    set(b,randrow+1,randcol,4);
    break;  
  }
   else if(dir == 2){ 
    randrow = rand() % (b->size - 1 + 1) + 1;  
    randcol = rand() % (b->size - 2 + 1) + 2;   
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0) continue;
    set(b,randrow,randcol,4);
    set(b,randrow,randcol-1,4);;
    break;  
  }
   else if(dir == 3){ 
    randrow = rand() % (b->size - 1 + 1) + 1;
    randcol = rand() % ((b->size-1) - 1 + 1) + 1;
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0) continue;
    set(b,randrow,randcol,4);
    set(b,randrow,randcol+1,4);
    break; 
    }
  }
}


     
void randomFleetArrangement(board *b){
  randomArrangeCarrier(b);
  randomArrangeSubmarine(b);
  randomArrangeBattleship(b);
  randomArrangeCruiser(b);
  b->unhit = 12;
  b->carrier = 4;
  b->battleship = 3;
  b->cruiser = 3;
  b->sub = 2;
}

void trackTarget(board * b, int * tRow, int * tCol){
  char cell[4];
  int row;
  char col;
  int ret;
  int size = b->size;
  char *p;

  while(1){
    printf("Enter the cell you'd like to target: ");
    if(fgets(cell,sizeof(cell),stdin) != NULL) {

      if ((p=strchr(cell,'\n'))) {
	  *p=0;
	}
	else {
	scanf("%*[^\n]");
	scanf("%*c");
	}
      
      
      ret = sscanf(cell,"%d%c",&row,&col);
      if (ret != 2 || col<97 || col>122){
      printf( "Error. To continue, please input the row number followed by the column letter.\n"); 
      continue;
      }
      if (row<1 || row > size) {
      printf("Error. To continue, please input the row number followed the column letter.\n"); 
      continue;
      }
      if (col-96 > size) {
	printf("Error. To continue, please input a number within the range of the board size\n"); 
      continue; 
      }
      if (getTracker(b,row,col-96) != 0) {
        printf("You already shot at this cell.\n");
        continue;
      }
      *tRow = row;
      *tCol = col - 96;
      break;
    } 
    else {
      printf("Error!You must input the number of rows followed by the letter column.\n"); 
      continue;
    }      
  }
}


void play(board *b, int max_shots) {
 int row, col;
 int remain = max_shots;
 int a1 = 0,a2 = 0, a3 = 0,a4 = 0;

 while (b->unhit > 0 && remain > 0 && (remain >= b->unhit)) {
  printBoard(b);
  printf("\nYou have %d shots remaining.\n",remain);
  trackTarget(b,&row,&col);
  if (get(b,row,col) == 0) {
    printf("\nMiss!\n");
    setTracker(b,row,col,-1);
    remain--;
  }
  if (get(b,row,col) == 1) {
    printf("\nHit!\n");
    setTracker(b,row,col,1);
    b->carrier--;
    b->unhit--;
    remain--;
   }
  if (get(b,row,col) == 2) {
    printf("\nHit!\n");
    setTracker(b,row,col,1);
    b->battleship--;
    b->unhit--;
    remain--;
  }
  if (get(b,row,col) == 3) {
    printf("\nHit!\n");
    setTracker(b,row,col,1);
    b->cruiser--;
    b->unhit--;
    remain--;
  }
  if (get(b,row,col) == 4) {
    printf("\nHit!\n");
    setTracker(b,row,col,1);
    b->sub--;
    b->unhit--;
    remain--;
   }
  if (b->carrier == 0 && a1 == 0 ) {
    printf("\nYou sunk the Carrier!\n");
    a1 = 1;
  }
   if (b->battleship == 0 && a2 == 0 ) {
     printf("\nYou sunk the Battleship!\n");
    a2 = 1;
  }
  if (b->cruiser == 0 && a3 == 0 ) {
    printf("\nYou sunk the Cruiser!\n");
    a3 = 1;
  }
  if (b->sub == 0 && a4 == 0 ) {
    printf( "\nYou sunk the Submarine!\n" );
    a4 = 1;
  }
 }
 if (remain == 0 && b->unhit > 0) {
   printf("\n You ran out of shots :( Game over.\n"); 
 }
 if (remain < b->unhit && b->unhit>0 && remain>0) {
   printf("\n You ran out of shots :( Game over. \n");
 }
 if (b->unhit == 0 && remain >= 0) {
   printf("\nCongratulations! You won the game!\n");
 }
}
    
	  

