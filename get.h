/*#include<iostream>
#include<stdio.h>
#include<time.h>
using namespace std;
int main()
{
char c,b;
int a=2;cout<<10;

//c=cin.get()	;
//a=cin.get();
c=getchar();
cout<<a<<endl<<c;
}Question
Sign in to vote
3
Sign in to vote*/
#include "windows.h"
#include "iostream"
using namespace std;

void gotoxy(int x,int y){
  HANDLE hConsole;
  COORD cursorLoc;
  std::cout.flush();
  cursorLoc.X = x;
  cursorLoc.Y = y;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsole, cursorLoc);
}

 



int main(){
      cout<<"line 1"<<endl;
      cout<<"line 2"<<endl;
      gotoxy(10,10);
      cout<<"line 3";
      cin.get();
}

