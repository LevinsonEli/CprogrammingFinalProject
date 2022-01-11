#pragma once

#include "CellMoves.h"
#include "CellOptimalMove.h"
#include "CheckersMovesList.h"
#include <stdio.h>

/****    FUNCTION  DECLARATIONS     ****/
// First goes the explanation of the function and then the declaration itself.

/*	Turn
	This function gets a board and a player as parameters.
	The function loads the board from a file called fileNameBoard
	that is defined at 'CellMoves.h' file, does a move, prints on a screen what was 
	the move and stores the changed board to the file.
*/
void Turn(Board board, Player player);

/*	DoTheStep
	This function gets a board and a head of move list.
	The function creates a new board, does the move, changes the board and returns it.
*/
Board * DoTheStep(Board board, SingleSourceMovesListCell * theBestMovesListNode);

/*	ChooseBestMove
	This function gets a list of the moves as parameter.
	The function picks the best move from the list and returns it.
	( If there are some the same moves - it picks randomly ).
*/
MultipleSourceMovesListCell * ChooseBestMove(MultipleSourceMovesList * movesList);

/*	BiggestNumOfCaptures
	This function gets a list of moves and returns the number of captures 
	of the best move ( the move that does most captures ).
*/
int BiggestNumOfCaptures(MultipleSourceMovesList * movesList);

/*	pickTheBestMoveRandomly
	This function gets a list of best moves and their's amount.
	The function choose randomly one of the best moves and returns the move.
*/
MultipleSourceMovesListCell * pickTheBestMoveRandomly(MultipleSourceMovesList * bestMovesList, int bestMoves);

/*	freeTheMultiList
	The function gets a list of best move for every checker and frees the memory.
*/
void freeTheMultiList(MultipleSourceMovesList * multiList);