
#include "CellMoves.h"
#include "CellOptimalMove.h"
#include "CheckersMovesList.h"
#include "Game.h"

MultipleSourceMovesList * FindAllPossiblePlayerMoves(Board board, Player player) {
	Board * newBoard = createNewBoard();
	LoadBoard(fileNameBoard, newBoard);
	MultipleSourceMovesList * multiList = createMultipleSourceMovesList();
	int i = 0, j = 0, first = 1;
	while (i != BOARD_SIZE && j != BOARD_SIZE) {
		if ((*newBoard)[i][j] == player) {
			checkersPos * newPos = createPosWithDefaultCoords(i + 'A', j + 49);
			MultipleSourceMovesListCell * newMultiListCell = createMultipleSourceMovesListCell();
			newMultiListCell->single_source_moves_list = FindSingleSourceOptimalMove(FindSingleSourceMoves((*newBoard), newPos));
			if (newMultiListCell->single_source_moves_list != NULL) {
				if (first == 1) {
					multiList->head = newMultiListCell;
					first = 0;
				}
				else
					multiList->tail->next = newMultiListCell;
				multiList->tail = newMultiListCell;
				multiList->tail->next = NULL;
			}
			else {
				free(newMultiListCell);
				free(newPos);
			}
		}
		j++;
		if (j == BOARD_SIZE) {
			j = 0;
			i++;
		}
	}
	free(board);
	return multiList;
}

MultipleSourceMovesList * createMultipleSourceMovesList() {
	MultipleSourceMovesList * multiList = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	if (!multiList) {
		printf("Memory allocation failure.\n");
		exit(2);
	}
	return multiList;
}
MultipleSourceMovesListCell * createMultipleSourceMovesListCell() {
	MultipleSourceMovesListCell * multiListCell = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	if (!multiListCell) {
		printf("Memory allocation failure.\n");
		exit(2);
	}
	return multiListCell;
}