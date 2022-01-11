#pragma once
#include "CellMoves.h"

typedef struct _SingleSourceMovesListCell {
	checkersPos *position;
	unsigned short captures;
	struct _SingleSourceMovesListCell *next;
} SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell *head;
	SingleSourceMovesListCell *tail;
} SingleSourceMovesList;

/****    FUNCTION  DECLARATIONS     ****/
// First goes the explanation of the function and then the declaration itself.

/*	FindSingleSourceOptimalMove
	This function gets a tree of all possible moves of the checker.
	The function chooses the optimal (with most amount of captures) move for the checker
	or picks randomly from same best moves and returns a list of steps of the move.
*/
SingleSourceMovesList * FindSingleSourceOptimalMove(SingleSourceMovesTree * moves_tree);

/*	FindSingleSourceNextMoves
	This function gets a list of steps of a move and a node from possible moves tree af a checker.
	The function returns next steps of the best move (only captures) and updates the tail of the list. 
*/
SingleSourceMovesListCell * FindSingleSourceNextMoves(SingleSourceMovesList * list, SingleSourceMovesTreeNode * moves_node);

/*	theBiggestNumOfCaptures
	This function gets a node from possible moves tree and returns the biggest
	amount of captures that the checker can do.
*/
int theBiggestNumOfCaptures(SingleSourceMovesTreeNode * node);

/*	createNewMovesCell
	The function creates a new SingleSourceMovesListCell pointer, 
	checks the memory allocation and returns the pointer.
*/
SingleSourceMovesListCell * createNewMovesCell();

/*	createNewMovesList
	The function creates a new SingleSourceMovesList pointer, 
	checks the memory allocation and returns the pointer.
*/
SingleSourceMovesList * createNewMovesList();
