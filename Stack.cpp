//Connor Moore
//Data Structures
//Mouse Maze Stack Project

#include "Stack.h"
#include <iostream>
#include <fstream> 
#include <windows.h>
#include <string>

using namespace std;


//main function to run game
void GameStack::RunMaze() {
	//this value checks to see if the game has been finished due to a mine
	bool game = true;
	InitializeMaze(mine);
	//this flag will check to see if we need to pop a value off of the stack
	bool flag = true;
	//write the logic the makes the Mouse run through the maze
	//(Mouse[top - 1].xx != end.xx) && (Mouse[top - 1].yy != end.yy)
	while (game) {
		if (Mouse[top - 1].xx == end.xx && Mouse[top - 1].yy == end.yy) {
			game = false;
		}
		//checking one space down
		if (Board[Mouse[top - 1].xx][Mouse[top - 1].yy + 1] == '3' || Board[Mouse[top - 1].xx][Mouse[top - 1].yy + 1] == '0') {
			push(Mouse[top - 1].xx, Mouse[top - 1].yy + 1);
		}
		//checking one space to the right(from the user's perspective)
		else if (Board[Mouse[top-1].xx + 1][Mouse[top-1].yy] == '3' || Board[Mouse[top - 1].xx + 1][Mouse[top - 1].yy] == '0') {
			push(Mouse[top-1].xx + 1, Mouse[top-1].yy);
		}
		//checking on space to the left(from the user's perspective)
		//first half of the if statement makes sure we can move in this direction
		else if (Board[Mouse[top-1].xx - 1] >= 0 && (Board[Mouse[top-1].xx - 1][Mouse[top-1].yy] == '3' || Board[Mouse[top - 1].xx - 1][Mouse[top - 1].yy] == '0')) {
			push(Mouse[top-1].xx - 1, Mouse[top-1].yy);
		}
		//check to see if space above can be moved to
		else if (Board[Mouse[top-1].yy - 1] >= 0 && (Board[Mouse[top-1].xx][Mouse[top-1].yy - 1] == '3' || Board[Mouse[top - 1].xx][Mouse[top - 1].yy - 1] == '0')) {
			push(Mouse[top - 1].xx, Mouse[top - 1].yy-1);
		}
		//if the space is not an available option, the mouse must move back a space.
		//this can be done by popping the last position off of the stack
		else {

			pop();
		}
		//after checking if we should pop off the last value, we check to see if any surrounding spaces are a "mine"
		if (Board[Mouse[top - 1].xx][Mouse[top - 1].yy + 1] == '2') {
			//this function ends the game and breaks the main loop
			BlowUp();
			mine = true;
			break;
		}
		else if (Board[Mouse[top - 1].xx + 1][Mouse[top - 1].yy] == '2') {
			BlowUp();
			mine = true;
			break;
		}
		else if (Board[Mouse[top - 1].xx - 1] >= 0 && (Board[Mouse[top - 1].xx - 1][Mouse[top - 1].yy] == '2')) {
			BlowUp();
			mine = true;
			break;
		}
		else if (Board[Mouse[top - 1].yy - 1] >= 0 && (Board[Mouse[top - 1].xx][Mouse[top - 1].yy - 1] == '2')) {
			BlowUp();
			mine = true;
			break;
		}
		cout << endl;
		system("CLS");
		DisplayMaze();
		Sleep(100);
	}
	//print out the maze's finish coordinates as well as the final coordinates of the mouse
	cout << "Target Coordinates: "<< end.xx << "," << end.yy << endl;
	cout << "Final Coordinates: "<< Mouse[top - 1].xx << "," << Mouse[top - 1].yy << endl;
}

//constructor
GameStack::GameStack(){
	top = 0;
	mine = false;
	//push the first position onto the stack since the starting position will be the same for any map
	//the start of the maze is 1,0 since my maze is based off of (0,0)
	push(1,0);
}
//function to read a text file and turn it into the game board
void GameStack::InitializeMaze(bool game) {
	int row = 0, col = 0;
	char c;
	string x = "maze(nomine).txt";
	if (mine == false) {
		x = "maze.txt";
	}
	//name an instream file
	ifstream MazeFile;
	MazeFile.open(x);
	if (!MazeFile) {
		cout << "No Maze File Found.";
	}
	else {
		int x = 0;
		while (MazeFile >> c) {
			Board[row][col] = c;
			if (row == 0 && col == 0) {
				cout << "M";
			}
			//depending on the charater in the maze file, a different character is printed to the screen
			else if (c == '0') {
				cout << " ";
			}
			else if (c == '1')
				cout << (char)219;
			else if (c == '2')
				cout << "*";
			else if (c == '3') {
				cout << "=";
				end.xx = row;
				end.yy = col;
			}
			x++;
			if (x >= 100) {
				x = 0;
				cout << endl;
			}
			row++;
			if (row >= 100) {
				row = 0;
				col++;
			}
		}
	}
}
//after the mouse moves, this function will be called to show the updated maze
void GameStack::DisplayMaze() {
	for (int j = 0; j < 30; j++) {
		for (int i = 0; i < 100; i++) {
			char a = Board[i][j];
			if (i == Mouse[top-1].xx && j == Mouse[top-1].yy) {
				cout << "M";
			}
			else if (a == '0' || a == 'X') {
				cout << " ";
			}
			else if (a == '1')
				cout << (char)219;
			else if (a == '2')
				cout << "*";
			else if (a == '3') {
				cout << "=";
			}
			//this character is used to keep track of where the mouse has been.  This way it knows which ways to try next
			else if (a == 'O') {
				cout << " ";
			}
		}
		cout << endl;
	}
}
//adds the coordinates to a stack of a custom class "xy"
//leaves a trail of 0 so that the mouse can easily backtrack
void GameStack::push(int x, int y) {
	if (top >= 10000) {
		return;
	}
	else if (x > 99 || y > 29) {
		pop();
		return;
	}
	else {
		Mouse[top].xx = x;
		Mouse[top].yy = y;
		Board[Mouse[top].xx][Mouse[top].yy] = 'O';
		top++;
	}
}
//pops or removes the current top from the stack
//this function also replaces the board with a characte(X) so the Mouse will know it has already take this path

void GameStack::pop() {
	if (top <= 0) {
		top = 0;
		return;
	}
	//the top value is moved down one, since we do not need the value that is "popped" from the list, we do not return anything
	top--;
	//the position that was popped is replaced with an X so that the mouse knows it has traveled there
	Board[Mouse[top].xx][Mouse[top].yy] = 'X';
}
//function that ends the game
//shows the path the mouse took. 
void GameStack::BlowUp() {
	system("CLS");
	for (int j = 0; j < 30; j++) {
		for (int i = 0; i < 100; i++) {
			char a = Board[i][j];
			if (a == '0') {
				cout << " ";
			}
			else if (a == '1') {
				//just to add some visual effects, the inside of all the walls change to 0 when the mouse hits a "mine"
				if (Board[i - 1][j] == '1' && Board[i + 1][j] == '1' && Board[i][j + 1] == '1' && Board[i][j - 1] == '1') {
					cout << "0";
				}
				
				else {
					cout << (char)219;
				}
			}
			else if (a == '2')
				cout << "*";
			else if (a == '3') {
				cout << "=";
			}
			//this will put a trail of '+' along the path the mouse took 
			else if (a == 'O' || a == 'X') {
				cout << "+";
			}
		}
		cout << endl;
	}
}

