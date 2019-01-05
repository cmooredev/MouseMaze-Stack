//Connor Moore
//Data Structures
//Mouse Maze Stack Project
#include <windows.h>
#include <iostream>
#include <conio.h>
#include "Stack.h"

using namespace std;

int main() {
	int num;
	GameStack Game;
	Game.RunMaze();
	cout << endl;
	if (Game.mine == true) {
		cout << "The mouse has died, would you like to let him finish the maze with no mines?" << endl << "Enter 1 to let him continue.";
		cin >> num;
		if (num == 1) {
			Game.top = 0;
			//the start of the maze is 1,0 since my maze is based off of (0,0)
			Game.push(1,0);
			Game.RunMaze();
		}
	}
	system("pause");
	return 0;
}