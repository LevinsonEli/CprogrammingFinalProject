#include "CellMoves.h"
#include "CellOptimalMove.h"
#include "CheckersMovesList.h"
#include "Turn.h"
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	time_t t;
	srand((unsigned)time(&t));
	Board * board = (Board*)malloc(sizeof(Board));
	if (!board) {
		printf("Memory allocation failure. \n");
		exit(2);
	}
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (((i == 0 || i == 2) && j % 2 == 1) || (i == 1 && j % 2 == 0))
				(*board)[i][j] = 'T';
			else if (((i == 5 || i == 7) && j % 2 == 0) || (i == 6 && j % 2 == 1))
				(*board)[i][j] = 'B';
			else
				(*board)[i][j] = ' ';
		}

	PlayGame(board, 'B');

	return 0;
}