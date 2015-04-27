# Arendall_CSCI2270_FinalProject

## Matthew Arendall
## Tree Maze Wizard

**Project Summary**

Goal: Find a random number given in a Red Black Binary Search Tree.

The program will prompt the user to choose a difficulty level and ask 
the user questions to move 'left', 'right', or 'back'.
The user will have to choose which direction to go until they finish the 
maze. The path will either end in a 'Dead End' or a 'Success' that you found your number.
If you run into a 'Dead End', you will be directed back at the root of the maze.
If you win, there will be results to show your score, print the tree, or try again.
The score was calculated by using a ratio between the height of the tree 
and how many guess the user inputted.
The path will be built randomly each time using the red black tree
algorithm to give equal paths. The user will also have an option to quit or go back to the main
menu at any time. 

**How to Run**
Once in the Repository, https://github.com/maar9185/Arendall_CSCI2270_FinalProject.git
In the terminal, run the following to compile and play the game:
	g++ -std=c++11 mainProject.cpp MovieTree.cpp -o test
	./test
	
Next, the game will ask you to choose a difficulty

	1. Easy
	2. Medium
	3. Hard
	4. Quit
	
The difficulty relates to how large the tree is (Easy has the smallest tree).

The game then lists your number to find and your current root number.
```
ex)
	You chose Medium
	Try to find: 64
	You are currently at: 84
```
Then the game asks you directions to try to find your number.

	1. Left
	2. Right
	3. Back
	4. Give Up
	
If you hit a 'Dead End' the program returns you back to the root. 
If you found the number you are looking for, you win! The game also prints
the path you took every time you hit a dead end or win.
You also have the option to give up at any time.

Once you have finished or given up, the game presents the following menu:
Maze Tree Wizard Results

	1. Show Score
    2. Print Tree Maze
    3. Try Again
    4. Quit

1. The score is based off a ratio between the height of the tree and how many 
guesses it took you to find your number. If you gave up, it will simply you tell
you lost and better luck next time.
2. The print tree maze option prints the tree starting from the root, and it
displays all of its branches listing its parents.
3. Brings you back to the first menu to choose a difficulty.
4. Quits out of the program.

**Dependencies**
The following include files are needed to run the Tree Maze Game

	#include iostream
	#include "MovieTree.h"
	#include stdio.h
	#include stdlib.h
	#include vector

All of these are standard and require no special installations.

**System Requirements**
There are no additional system requirements other than the operating system.
My program is for Windows, Mac, or Linux. You must use a virtual machine if 
you are using Windows. The game runs through the terminal.

**Group	Members**
None

**Contributors**
Abby Caballero

**Open issues/bugs**
The game could look cooler!
