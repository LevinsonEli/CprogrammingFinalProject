#include "CellMoves.h"
#include "CellOptimalMove.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int theBiggestNumOfCaptures(SingleSourceMovesTreeNode * node) {
	if (node == NULL || (node->next_moves[0] == NULL && node->next_moves[1] == NULL))
		return 0;
	else if (node->next_moves[0] != NULL && node->next_moves[1] == NULL)		// Can move only to the left
		return node->next_moves[0]->total_captures_so_far + theBiggestNumOfCaptures(node->next_moves[0]);
	else if (node->next_moves[0] == NULL && node->next_moves[1] != NULL)		// Can move only to the right
		return node->next_moves[1] + theBiggestNumOfCaptures(node->next_moves[1]);
	else																		// Choose the maximum amount of captures
		return max(node->next_moves[0], node->next_moves[1]) + max(theBiggestNumOfCaptures(node->next_moves[0]),
			theBiggestNumOfCaptures(node->next_moves[1]));
}

SingleSourceMovesList * FindSingleSourceOptimalMove(SingleSourceMovesTree * moves_tree) {
	if (moves_tree == NULL || (moves_tree->source->next_moves[0] == NULL && moves_tree->source->next_moves[1] == NULL))
		return NULL;
	else {
		SingleSourceMovesTreeNode * moves_node = moves_tree->source;
		SingleSourceMovesList * list = createNewMovesList();			// Creating a new moves list
		SingleSourceMovesListCell * headCell = createNewMovesCell();	// Creating the head of the list ( the default position of the move )
		headCell->captures = 0;											// By default there is no capture yet
		headCell->position = moves_node->pos;
		headCell->next = NULL;
		list->head = list->tail = headCell;
		SingleSourceMovesListCell * listCell = createNewMovesCell();	// Creating the next part of the move
		int i;															// i - is the index of next_moves array ( tree ). 0 or 1 (left or right)
		if (moves_node->next_moves[0] != NULL && moves_node->next_moves[1] == NULL)			// If there is a move only to left
			i = 0;
		else if (moves_node->next_moves[0] == NULL && moves_node->next_moves[1] != NULL)	// If there is a move only to right
			i = 1;
		else {																				// If there are two possible sides to move: choose with the biggest amount of captures
			if ((moves_node->next_moves[0]->total_captures_so_far + theBiggestNumOfCaptures(moves_node->next_moves[0])) > 
				(moves_node->next_moves[1]->total_captures_so_far + theBiggestNumOfCaptures(moves_node->next_moves[1])))
				i = 0;
			else if ((moves_node->next_moves[0]->total_captures_so_far + theBiggestNumOfCaptures(moves_node->next_moves[0])) <
						(moves_node->next_moves[1]->total_captures_so_far + theBiggestNumOfCaptures(moves_node->next_moves[1])))
				i = 1;
			else																			// If amount of captures of left and right sides are the same: choose randomly one
				i = rand() % 2;
		}
		listCell->captures = moves_node->next_moves[i]->total_captures_so_far;				// Update the next part of the move
		listCell->position = moves_node->next_moves[i]->pos;
		list->head->next = listCell;														// Update the list
		list->tail = listCell;
		list->tail->next = NULL;
		if (listCell->captures == 1)														// If this part of move was a capture
			listCell->next = FindSingleSourceNextMoves(list, moves_node->next_moves[i]);	// Search the continue of captures of the move and add them if they are
		else
			listCell->next = NULL;
		return list;
	}
}

SingleSourceMovesListCell * FindSingleSourceNextMoves(SingleSourceMovesList * list, SingleSourceMovesTreeNode * moves_node) {
	if (moves_node->next_moves[0] == NULL && moves_node->next_moves[1] == NULL)
		return NULL;
	SingleSourceMovesListCell * listCell = createNewMovesCell();
	int i;
	if (moves_node->next_moves[0] != NULL && moves_node->next_moves[1] == NULL		// Can capture only to the left
		&& moves_node->next_moves[0]->total_captures_so_far != 0)
		i = 0;
	else if (moves_node->next_moves[1] != NULL && moves_node->next_moves[0] == NULL			// Can capture only to the right
		&& moves_node->next_moves[1]->total_captures_so_far != 0)
		i = 1;
	else if (moves_node->next_moves[0]->total_captures_so_far != 0 && moves_node->next_moves[1]->total_captures_so_far != 0) {
		if (theBiggestNumOfCaptures(moves_node->next_moves[0]) > theBiggestNumOfCaptures(moves_node->next_moves[1]))
			i = 0;
		else if (theBiggestNumOfCaptures(moves_node->next_moves[0]) < theBiggestNumOfCaptures(moves_node->next_moves[1]))
			i = 1;
		else
			i = rand() % 2;
	}
	else
		return NULL;
	listCell->captures = moves_node->next_moves[i]->total_captures_so_far;
	listCell->position = moves_node->next_moves[i]->pos;
	list->tail = listCell;
	listCell->next = FindSingleSourceNextMoves(list, moves_node->next_moves[i]);	// Find the next step of the capture move
	return listCell;
}


SingleSourceMovesList * createNewMovesList() {
	SingleSourceMovesList * list = (SingleSourceMovesList *)malloc(sizeof(SingleSourceMovesList));
	if (!list) {
		printf("Memory allocation failure.\n");
		exit(2);
	}
	return list;
}

SingleSourceMovesListCell * createNewMovesCell() {
	SingleSourceMovesListCell * newCell = (SingleSourceMovesListCell *)malloc(sizeof(SingleSourceMovesListCell));
	if (!newCell) {
		printf("Memory allocation failure.\n");
		exit(2);
	}
	return newCell;
}