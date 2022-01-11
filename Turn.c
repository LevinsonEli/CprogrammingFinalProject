
//#include "CellMoves.h"
//#include "CellOptimalMove.h"
//#include "CheckersMovesList.h"
#include "Turn.h"
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>

void Turn(Board board, Player player) {
	if (player != 'B' && player != 'T') {
		printf("Only 'B' and 'T' players play. \n");
		return;
	}
	Board * newBoard = createNewBoard();
	LoadBoard(fileNameBoard, newBoard);

	MultipleSourceMovesList * multiList = FindAllPossiblePlayerMoves(*newBoard, player);
	if (multiList == NULL || multiList->head == NULL)
		return;
	MultipleSourceMovesListCell * multiListCell = multiList->head;
	if (multiListCell->next == NULL)
		return;

	MultipleSourceMovesListCell * theBestCellMove = ChooseBestMove(multiList);
	if (theBestCellMove == NULL)
		return;

	SingleSourceMovesListCell * theBestMovesListNode = theBestCellMove->single_source_moves_list->head;
	newBoard = DoTheStep(*newBoard, theBestMovesListNode);
	if (player == 'T')
		printf("player TOP_DOWN's turn\n");
	else if (player == 'B')
		printf("player BUTTOM_UP's turn\n");
	printf("%C%d->%C%d\n", theBestCellMove->single_source_moves_list->head->position->row,
		theBestCellMove->single_source_moves_list->head->position->col - 48,
		theBestCellMove->single_source_moves_list->tail->position->row,
		theBestCellMove->single_source_moves_list->tail->position->col - 48);
	fflush(stdout);
	StoreBoard(*newBoard, fileNameBoard);
	free(newBoard);
	freeTheMultiList(multiList);
	free(theBestCellMove);
}

void freeTheMultiList(MultipleSourceMovesList * multiList) {
	MultipleSourceMovesListCell * multiListCell = multiList->head;
	while (multiListCell != NULL) {
		free(multiListCell);
		multiListCell = multiListCell->next;
	}
	free(multiList);
}

Board * DoTheStep(Board board, SingleSourceMovesListCell * theBestMovesListNode) {
	if (theBestMovesListNode == NULL)
		return NULL;
	Board * tempBoard = createNewBoard();
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			(*tempBoard)[i][j] = board[i][j];

	SingleSourceMovesListCell * curMove = theBestMovesListNode;
	while (curMove->next != NULL) {
		int status = abs(curMove->next->position->col - curMove->position->col);
		char side;
		if (curMove->next->position->col - curMove->position->col < 0)
			side = 'l';
		else
			side = 'r';
		tempBoard = updateBoard(tempBoard, curMove->position, status, side);
		curMove = curMove->next;
	}
	return tempBoard;
}

MultipleSourceMovesListCell * ChooseBestMove(MultipleSourceMovesList * movesList) {
	if (movesList == NULL || movesList->head == NULL)
		return NULL;
	MultipleSourceMovesListCell * moveCell = movesList->head;
	if (moveCell->next == NULL)
		return moveCell;

	// Searching the biggest amount of captures
	int bestNumOfCaptures = BiggestNumOfCaptures(movesList);

	// Creating a list of the best moves
	MultipleSourceMovesList * bestMovesList = createMultipleSourceMovesList();
	int bestMoves = 0;
	//moveCell = movesList->head;
	while (moveCell != NULL) {
		if (bestNumOfCaptures == moveCell->single_source_moves_list->tail->captures) {
			if (bestMoves == 0)
				bestMovesList->head = bestMovesList->tail = moveCell;
			else {
				bestMovesList->tail->next = moveCell;
				bestMovesList->tail = moveCell;
			}
			bestMoves++;
		}
		moveCell = moveCell->next;
	}
	return pickTheBestMoveRandomly(bestMovesList, bestMoves);
}

int BiggestNumOfCaptures(MultipleSourceMovesList * movesList) {
	MultipleSourceMovesListCell * moveCell = movesList->head;
	if (moveCell->next == NULL)
		return moveCell;
	int bestNumOfCaptures = 0;
	while (moveCell != NULL) {
		if (bestNumOfCaptures < moveCell->single_source_moves_list->tail->captures)
			bestNumOfCaptures = moveCell->single_source_moves_list->tail->captures;
		moveCell = moveCell->next;
	}
	return bestNumOfCaptures;
}

MultipleSourceMovesListCell * pickTheBestMoveRandomly(MultipleSourceMovesList * bestMovesList, int bestMoves) {
	int randNumOfBestMoves = (rand()) % bestMoves;
	int tempCounterOfBestMoves = 0;
	MultipleSourceMovesListCell * moveCell = bestMovesList->head;
	if (moveCell->next == NULL || randNumOfBestMoves == 0)		// Only one move
		return moveCell;
	while (moveCell != NULL) {
		if (tempCounterOfBestMoves == randNumOfBestMoves)
			return moveCell;
		moveCell = moveCell->next;
	}
	return moveCell;
}