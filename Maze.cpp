#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<get.h>
#include<color.h>
using namespace std;

#define MAX 101 //maxRow + maxColumn + 1
#define WALL 1 //indicate the wall is up
#define PATH 0 //indicate the cells is previous path
#define CELLS 2500 //row * column
#define START 3 //start position
#define END 4 //end position

int x=0,y,R,C,er,ec;
int maze[MAX][MAX];
void mazeGenerator(int wMaze[ MAX ][ MAX ], int wSize ); //generate the maze
void startEnd(int wMaze[ MAX ][ MAX ], int wSize, int* wSRow, int* wSCol );//generate start and end position
void printMaze(int wMaze[ MAX ][ MAX ], int wSize );//display the maze
void movement(void);
int main(void)
{

   int size = 0, sRow = 0, sCol = 0;
 /* int gd=DETECT,gm;
   initgraph(&gd,&gm,"C:\TURBOC3\BGI");*/
color(2);
     system("cls");
   printf("My Maze Generator\n*****************\n\n");
   printf("Input the size of your desired maze (3 to 11): ");
   do{
      if(size < 3 || size > 11)


   scanf("%d", &size );//get the desired size from user
   }
      while(size < 3 || size > 11);
   system("cls");
   mazeGenerator( maze, size );
   startEnd( maze, size, &sRow, &sCol );
   printMaze( maze, size );
    movement();
   



}
//////////////////
//MAZE GENERATOR//
//////////////////
void mazeGenerator( int wMaze[ MAX ][ MAX ], int wSize ){



   void initMaze( int wMaze[ MAX ][ MAX ] ); //initalize the maze array
   int walled( int wMaze[ MAX ][ MAX ], int wRow, int wCol );//check neighbouring cells



   int counter = 0, row = 1, col = 1, visited = 1;
   int validNeighbour, valid, randValid, move;
   int neighbourRow[ 4 ];
   int neighbourCol[ 4 ];
   int step[ 4 ];
   int btRow[ CELLS ]; //backtrack row array
   int btCol[ CELLS ];//backtrack column array

   srand(time( 0 ));
   initMaze( wMaze );
   //start backtracking with first cell
   btRow[ 0 ] = 1;
   btCol[ 0 ] = 1;

   /*while VisitedCells < TotalCells*/
   while(visited < wSize * wSize){
      //initialize
      validNeighbour = -1;

      /*find all neighbors of CurrentCell with all walls intact*/
      //NORTH neighbour
      if(row - 2 > 0 && walled( wMaze, row - 2, col )){
	 validNeighbour++;
	 neighbourRow[ validNeighbour ] = row - 2;
	 neighbourCol[ validNeighbour ] = col;
	 step[ validNeighbour ] = 1;
      }
      //WEST neighbour
      if(col - 2 > 0 && walled( wMaze, row, col - 2 )){
	 validNeighbour++;
	 neighbourRow[ validNeighbour ] = row;
	 neighbourCol[ validNeighbour ] = col - 2;
	 step[ validNeighbour ] = 2;
      }
      //EAST neighbour
      if(col + 2 < wSize * 2 + 1 && walled( wMaze, row, col + 2 )){
	 validNeighbour++;
	 neighbourRow[ validNeighbour ] = row;
	 neighbourCol[ validNeighbour ] = col + 2;
	 step[ validNeighbour ] = 3;
      }
      //SOUTH neighbour
      //size * 2 + 1 -> size + wall + outerWall
      if(row + 2 < wSize * 2 + 1 && walled( wMaze, row + 2, col )){
	 validNeighbour++;
	 neighbourRow[ validNeighbour ] = row + 2;
	 neighbourCol[ validNeighbour ] = col;
	 step[ validNeighbour ] = 4;
      }

      //if one or more found
      if(validNeighbour != -1){
	 //choose one at random
	 valid = validNeighbour + 1;//number of valid neighbour
	 randValid = rand() % valid;

	 //make the new cell CurrentCell
	 row = neighbourRow[ randValid ];
	 col = neighbourCol[ randValid ];

	 counter++;

	 btRow[ counter ] = row;
	 btCol[ counter ] = col;

	 move = step[ randValid ];

	 //knock down the wall between it and CurrentCell
	 //NORTH
	 if(move == 1){
	    wMaze[ row + 1 ][ col ] = PATH;
	 }
	 //WEST
	 else if(move == 2){
	    wMaze[ row ][ col + 1 ] = PATH;
	 }
	 //EAST
	 else if(move == 3){
	    wMaze[ row ][ col - 1 ] = PATH;
	 }
	 //SOUTH
	 else if(move == 4){
	    wMaze[ row - 1 ][ col ] = PATH;
	 }

	 //add 1 to VisitedCells
	 visited++;
      }
      //if none found
      else{
	 //backtracking
	 row = btRow[ counter ];
	 col = btCol[ counter ];
	 counter--;
      }

   }
}

void initMaze( int wMaze[ MAX ][ MAX ] ){
   int a, b;

   for(a  = 0; a < MAX; a++){
      for(b = 0; b < MAX; b++){
	 if(a % 2 == 0 || b % 2 == 0){
	    wMaze[ a ][ b ] = WALL;
	 }else{
	    wMaze[ a ][ b ] = PATH;
	 }
      }
   }
}

void printMaze( int wMaze[ MAX ][ MAX ], int wSize )
{
   int row, col;

   for(row = 0; row < wSize * 2 + 1; row++){

      if(wMaze[ row ][ 0 ] == START)
	 printf(" START -> ");
      else
	 printf("          ");
      for(col = 0; col < wSize * 2 + 1; col++){
	 if(wMaze[ row ][ col ] == WALL)
	    printf("%c",219);
	 else if(wMaze[ row ][ col ] == START)
	    {
	    printf("X");
	    y=row+1;  R=row;C=col;
	    x=11;
	    }
	 else
	    printf(" ");
      }

      if(wMaze[ row ][ wSize * 2 ] == END)
	 printf(" <- END");
		   // er=row;ec=size*2;
      printf("\n");
   }
   printf("\n");
   
   
}

int walled( int wMaze[ MAX ][ MAX ], int wRow, int wCol ){
   if(wMaze[ wRow - 1 ][ wCol ] == WALL &&
      wMaze[ wRow + 1 ][ wCol ] == WALL &&
      wMaze[ wRow ][ wCol + 1 ] == WALL &&
      wMaze[ wRow ][ wCol - 1 ] == WALL )
      return 1;

   return 0;
}
////////////////////////////////////
//START AND END POSITION GENERATOR//
////////////////////////////////////
void startEnd( int wMaze[ MAX ][ MAX ], int wSize, int* wSRow, int* wSCol ){
   int start, end,end1;

   do{
      start = rand() % (wSize * 2);//size + wall
   }while(start == 0 || wMaze[ start ][ 1 ] == WALL );

   do{
      end = rand() % (wSize * 2);
   }while(end == 0 || wMaze[ end ][ (wSize * 2) - 1 ] == WALL);
     do{
      end1 = rand() % (wSize * 2);
   }while(end == 0 || wMaze[ end1 ][ (wSize * 2) - 1 ] == WALL);

   wMaze[ start ][ 0 ] =  START;
   wMaze[ end ][ wSize * 2 ] = END;
   wMaze[ end1 ][ wSize * 2 ] = END;

   *wSRow = start;
   *wSCol = 0;
}

/////////////////
//MAZE TRAVERSE//
/////////////////
void movement( )
{
 int xb=x,yb=y,r=R,c=C,z=21,i=0,j=0;
 int rb=r,cb=c,brd;
 char inputkey;
getchar();
   while(1)
{cout<<"sucker";
   gotoxy(xb,yb);
   printf(" ");
   gotoxy(x,y);
   printf("");
   gotoxy(x,y);

   inputkey=cin.get();
	xb=x;
	yb=y;
	rb=r;
	cb=c;
 if(inputkey=='i')
 {

    y--;r--;
	  }

else if(inputkey=='k') {
   y++;r++;

	    }
else if(inputkey=='j') {
x--;c--;
     }
else if(inputkey=='l') {
x++;c++;  }
else  exit(0);

if(maze[r][c]==1)
{
x=xb;
y=yb;
r=rb;
c=cb;
}
if(maze[r][c]==4)
{gotoxy(35,7);
printf("you have reached the end");
gotoxy(x,y);}
}
}
