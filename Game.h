#pragma once
#include "Turn.h"

/****    FUNCTION  DECLARATIONS     ****/
// First goes the explanation of the function and then the declaration itself.

/*	StoreBoard
	This function gets a board and a file name as parameters.
	The function stores the board to the file according to the rules:
	every cell - two bits: 00 - ' ', 01 - 'T', 10 - 'B'.
*/
void StoreBoard(Board board, char *  filename);

/*	LoadBoard
	This function gets a file name and a pointer to a board.
	The function load the board from the file according to the rules:
	every cell - two bits: 00 - ' ', 01 - 'T', 10 - 'B'.
*/
void LoadBoard(char *filename, Board * board);

/*	PlayGame
	The function gets a board and a player, that must to start the game.
	And start playing computer with himself.
*/
void PlayGame(Board board, Player starting_player);

/*	SmbdyWin
	This function gets a board and checks if someone of the players riched the end of the board.
	Retruns 1 if yes and 0 - if didn't.
*/
int SmbdyWin(Board board);

/*	printBoard
	The function gets a board and prints it on the screen.
*/
void printBoard(Board board);

/*	setBit
	The function gets a byte ( char ) and a number of bit ( i ).
	The function 'sets' the i's bit in the byte and returns it.
*/
unsigned char setBit(unsigned char ch, int i);

/*	isBitISet
	The function gets a byte ( char ) and a number of bit ( i ).
	The function returns 1 if the i's bit is setted in the byte.
	And 0 - if not.
*/
int isBitISet(unsigned char ch, int i);

/*	verifyFileOpening
	The function gets a file and checks if it opened successfully.
*/
void verifyFileOpening(FILE * file);
