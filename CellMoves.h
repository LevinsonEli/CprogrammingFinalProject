#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 8
#define fileNameBoard "board.bin"

typedef struct _checkersPos {
	char row;
	char col;
} checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;

typedef struct _SingleSourceMovesTreeNode {
	Board board;
	checkersPos *pos;
	unsigned short total_captures_so_far;
	struct _SingleSourceMovesTreeNode *next_moves[2];
} SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTreeNode *source;
} SingleSourceMovesTree;

/****    FUNCTION  DECLARATIONS     ****/
// First goes the explanation of the function and then the declaration itself.

/*	FindSingleSourceMoves
	This function gets a board and a position of the cell on the board as parameters.
	If there is a checker in this cell the function returns a binary tree of all
	posible moves of the checker. And if there is no checke the function return NULL. 
*/
SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src);

/*	SingleSourceMovesStatusLeftB
	This function gets a board and a position of the cell on the board as parameters.
	The function returns 2 - if there is a caprute for 'B' checker to the left.
	The function returns 1 - if there is a simple move for 'B' checker to the left.
	The function returns 0 - if there is no possible moves for 'B' checker to the left.
	If the given cell is not a 'B' checker, the function returns 0.
*/
int SingleSourceMovesStatusLeftB(Board board, checkersPos *src);

/*	SingleSourceMovesStatusLeftT
	This function gets a board and a position of the cell on the board as parameters.
	The function returns 2 - if there is a caprute for T' checker to the left.
	The function returns 1 - if there is a simple move for 'T' checker to the left.
	The function returns 0 - if there is no possible moves for 'T' checker to the left.
	If the given cell is not a 'T' checker, the function returns 0.
*/
int SingleSourceMovesStatusLeftT(Board board, checkersPos *src);

/*	SingleSourceMovesStatusLeft
	This function gets a board and a position of the cell on the board as parameters.
	The function returns 2 - if there is a caprute the checker to the left.
	The function returns 1 - if there is a simple move for the checker to the left.
	The function returns 0 - if there is no possible moves for the checker to the left.
	If the given cell if not a checker, the function returns 0.
*/
int SingleSourceMovesStatusLeft(Board board, checkersPos *src);

/*	SingleSourceMovesStatusRightB
	This function gets a board and a position of the cell on the board as parameters.
	The function returns 2 - if there is a caprute for 'B' checker to the right.
	The function returns 1 - if there is a simple move for 'B' checker to the right.
	The function returns 0 - if there is no possible moves for 'B' checker to the right.
	If the given cell is not a 'B' checker, the function returns 0.
*/
int SingleSourceMovesStatusRightB(Board board, checkersPos *src);

/*	SingleSourceMovesStatusRightT
	This function gets a board and a position of the cell on the board as parameters.
	The function returns 2 - if there is a caprute for 'T' checker to the right.
	The function returns 1 - if there is a simple move for 'T' checker to the right.
	The function returns 0 - if there is no possible moves for 'T' checker to the right.
	If the given cell is not a 'T' checker, the function returns 0.
*/
int SingleSourceMovesStatusRightT(Board board, checkersPos *src);

/*	SingleSourceMovesStatusRight
	This function gets a board and a position of the cell on the board as parameters.
	The function returns 2 - if there is a caprute the checker to the right.
	The function returns 1 - if there is a simple move for the checker to the right.
	The function returns 0 - if there is no possible moves for the checker to the right.
	If the given cell if not a checker, the function returns 0.
*/
int SingleSourceMovesStatusRight(Board board, checkersPos *src);

/*	updateBoard
	This function gets a pointer to board, a position of the cell on the board,
	a status of move of the checker (1, 2) and a side for move ('l', 'r').
	The function creates a new board and changes it (after copying the given board)
	by the given status and side: capture or simple move, left or right move.
	And returns a pointer to the new created board.
*/
Board *updateBoard(Board board, checkersPos *src, int status, char side);

/*	updatePos
	This function gets a pointer to board, a position of the cell on the board,
	a status of move of the checker (1, 2) and a side for move ('l', 'r').
	The function creates a new position (checkersPos) and updates it (after copying the
	given position) by the given status and side: capture or simple move, left or right move.
	And returns a pointer to the new created checker's position.
*/
checkersPos * updatePos(Board board, checkersPos *src, int status, char side);

/*	FindSingleSourceMovesLeft
	This function gets a board and a position of the cell on the board as parameters.
	The function returns the tree of possible moves to the left.
*/
SingleSourceMovesTreeNode * FindSingleSourceMovesLeft(Board board, checkersPos * src);

/*	FindSingleSourceMovesRight
	This function gets a board and a position of the cell on the board as parameters.
	The function returns the tree of possible moves to the right.
*/
SingleSourceMovesTreeNode * FindSingleSourceMovesRight(Board board, checkersPos * src);

/*	FindNextCapturesLeft
	This function gets a board, a position of the cell on the board and number of captures so far as parameters.
	The function returns the tree of possible moves to the left side that are captures.
*/
SingleSourceMovesTreeNode * FindNextCapturesLeft(Board board, checkersPos * src, int captures);

/*	FindNextCapturesRight
	This function gets a board, a position of the cell on the board and number of captures so far as parameters.
	The function returns the tree of possible moves to the right side that are captures.
*/
SingleSourceMovesTreeNode * FindNextCapturesRight(Board board, checkersPos * src, int captures);

/*	createPos
	The function creates new checkersPos pointer, checks the memory allocation and returns the pointer.
*/
checkersPos * createPos();

/*	createPos
	This function gets a row and a column as parameters.
	The function creates new checkersPos pointer with the given coords, 
	checks the memory allocation and returns the pointer.
*/
checkersPos * createPosWithDefaultCoords(char row, char col);

/*	createNewBoard
	The function creates new Board pointer, checks the memory allocation
	and returns the pointer.
*/
Board * createNewBoard();

/*	createMovesTreeNode
	The function creates new SingleSourceMovesTreeNode,
	checks memory allocation and returns the pointer.
*/
SingleSourceMovesTreeNode * createMovesTreeNode();
