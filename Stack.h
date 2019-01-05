//Connor Moore
//Data Structures
//Mouse Maze Stack Project
#pragma once
//main class that holds the variables and functions
class GameStack {
public:
	//this class is used to hold coordinates
	class xy {
	public:
		int xx, yy;
	};

	char Board[100][30];
	//array made from a class that holds two values.  This makes it easy to store coordinates like (0,0)
	xy Mouse[10000];
	int top;
	//this will store the final coordinates that the mouse wants to reach
	xy end;
	GameStack();
	//function to run the main code of the maze
	void RunMaze();
	//copys text file to board 2d array
	void InitializeMaze(bool game);
	//displays an updated maze
	void DisplayMaze();
	//adds a value to the top of the stack
	void push(int x, int y);
	//pops last value off of the stack
	void pop();
	//ends game
	void BlowUp();
	//this value checks to see if the game has been finished due to a mine
	bool mine;
};
