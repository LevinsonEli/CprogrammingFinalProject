#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "CellOptimalMove.h"

typedef struct _multipleSourceMovesListCell {
	SingleSourceMovesList *single_source_moves_list;
	struct _multipleSourceMovesListCell *next;
} MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList {
	MultipleSourceMovesListCell *head;
	MultipleSourceMovesListCell *tail;
} MultipleSourceMovesList;

/****    FUNCTION  DECLARATIONS     ****/
// First goes the explanation of the function and then the declaration itself.

/*	FindAllPossiblePlayerMoves
	This function gets a board nad a player as parameters.
	The function loads the board from a file called fileNameBoard
	that is defined at 'CellMoves.h' file. Then the function creates a list, searches
	the best move for all checkers on the board that can move puts into the list and returns it.
*/
MultipleSourceMovesList * FindAllPossiblePlayerMoves(Board board, Player player);

/*	createMultipleSourceMovesList
	The function creates a MultipleSourceMovesList pointer
	checks memory allocation and returns the pointer.
*/
MultipleSourceMovesList * createMultipleSourceMovesList();

/*	createMultipleSourceMovesListCell
	The function creates a MultipleSourceMovesListCell pointer
	checks memory allocation and returns the pointer.
*/
MultipleSourceMovesListCell * createMultipleSourceMovesListCell();