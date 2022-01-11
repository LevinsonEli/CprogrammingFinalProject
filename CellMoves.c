#include "CellMoves.h"
#include <stdio.h>

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src) {
	if (board[src->row - 'A'][src->col - 49] == ' ')		// If it's not a checker
		return NULL;
	else {
		SingleSourceMovesTree *tree = malloc(sizeof(SingleSourceMovesTree));
		if (!tree) {
			printf("Memory allocation failure. \n");
			exit(2);
		}
		tree->source = createMovesTreeNode();
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				tree->source->board[i][j] = board[i][j];
		tree->source->pos = src;
		tree->source->total_captures_so_far = 0;
		tree->source->next_moves[0] = FindSingleSourceMovesLeft(tree->source->board, src);
		tree->source->next_moves[1] = FindSingleSourceMovesRight(tree->source->board, src);
		return tree;
	}
	return NULL;
}

int SingleSourceMovesStatusLeft(Board board, checkersPos *src) {
	if (board[src->row - 'A'][src->col - 49] == 'T')
		return SingleSourceMovesStatusLeftT(board, src);
	else if (board[src->row - 'A'][src->col - 49] == 'B')
		return SingleSourceMovesStatusLeftB(board, src);
	return 0;
}

int SingleSourceMovesStatusRight(Board board, checkersPos *src) {
	if (board[src->row - 'A'][src->col - 49] == 'T')
		return SingleSourceMovesStatusRightT(board, src);
	else if (board[src->row - 'A'][src->col - 49] == 'B')
		return SingleSourceMovesStatusRightB(board, src);
	return 0;
}

int SingleSourceMovesStatusLeftB(Board board, checkersPos *src) {
	int x = src->col - 49, y = src->row - 'A';

	if (board[y][x] != 'B')
		return 0;

	if (x == 0 || y == 0 || board[y - 1][x - 1] == 'B' || 
			(x >= 2 && y >= 2 && board[y - 1][x - 1] == 'T' && board[y - 2][x - 2] != ' '))
		return 0;
	else if (x != 0 && y != 0 && board[y - 1][x - 1] == ' ')
		return 1;
	else if (x >= 2 && y >= 2 && board[y - 1][x - 1] == 'T' && board[y - 2][x - 2] == ' ')
		return 2;
	return 0;
}

int SingleSourceMovesStatusLeftT(Board board, checkersPos *src) {
	int x = src->col - 49, y = src->row - 'A';

	if (board[y][x] != 'T')
		return 0;

	if (x == 0 || y == 7 || board[y + 1][x - 1] == 'T' || 
			(x >= 2 && y <= 5 && board[y + 1][x - 1] == 'B' && board[y + 2][x - 2] != ' '))
		return 0;
	else if (x != 0 && y != 7 && board[y + 1][x - 1] == ' ')
		return 1;
	else if (x >= 2 && y <= 5 && board[y + 1][x - 1] == 'B' && board[y + 2][x - 2] == ' ')
		return 2;
	return 0;
}

int SingleSourceMovesStatusRightB(Board board, checkersPos *src) {
	int x = src->col - 49, y = src->row - 'A';

	if (board[y][x] != 'B')
		return 0;

	if (x == 7 || y == 0 || board[y - 1][x + 1] == 'B' || 
			(x <= 5 && y >= 2 && board[y - 1][x + 1] == 'T' && board[y - 2][x + 2] != ' '))
		return 0;
	else if (x != 7 && y != 0 && board[y - 1][x + 1] == ' ')
		return 1;
	else if (x <= 5 && y >= 2 && board[y - 1][x + 1] == 'T' && board[y - 2][x + 2] == ' ')
		return 2;
	return 0;
}

int SingleSourceMovesStatusRightT(Board board, checkersPos *src) {
	int x = src->col - 49, y = src->row - 'A';

	if (board[y][x] != 'T')
		return 0;

	if (x == 7 || y == 7 || board[y + 1][x + 1] == 'T' || 
			(x <= 5 && y <= 5 && board[y + 1][x + 1] == 'B' && board[y + 2][x + 2] != ' '))
		return 0;
	else if (x != 7 && y != 7 && board[y + 1][x + 1] == ' ')
		return 1;
	else if (x <= 5 && y <= 5 && board[y + 1][x + 1] == 'B' && board[y + 2][x + 2] == ' ')
		return 2;
	return 0;
}

Board *updateBoard(Board board, checkersPos *src, int status, char side) {
	Board * newBoard = (Board *)malloc(sizeof(Board));
	if (!newBoard) {
		printf("Memory allocation failure. \n");
		exit(2);
	}
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			(*newBoard)[i][j] = board[i][j];
	int i = 0, j = 0;
	if (board[src->row - 'A'][src->col - 49] == 'T')
		i = 1;
	else if (board[src->row - 'A'][src->col - 49] == 'B')
		i = -1;
	if (side == 'l' || side == 'L')
		j = -1;
	else if (side == 'r' || side == 'R')
		j = 1;

	(*newBoard)[src->row - 'A' + status * i][src->col - 49 + status * j] = board[src->row - 'A'][src->col - 49];
	(*newBoard)[src->row - 'A'][src->col - 49] = ' ';

	if (status == 2)
		(*newBoard)[src->row - 'A' + i][src->col - 49 + j] = ' ';

	return newBoard;
}

checkersPos * updatePos(Board board, checkersPos *src, int status, char side) {
	checkersPos * newPos = createPos();
	int i, j;
	if (board[src->row - 'A'][src->col - 49] == 'T')
		i = 1;
	else if (board[src->row - 'A'][src->col - 49] == 'B')
		i = -1;
	if (side == 'l' || side == 'L')
		j = -1;
	else if (side == 'r' || side == 'R')
		j = 1;

	if (status == 1) {
		newPos->row = src->row + i;
		newPos->col = src->col + j;
	}
	else if (status == 2) {
		newPos->row = src->row + 2 * i;
		newPos->col = src->col + 2 * j;
	}
	return newPos;
}

SingleSourceMovesTreeNode * FindNextCapturesLeft(Board board, checkersPos * src, int captures) {
	SingleSourceMovesTreeNode * move = createMovesTreeNode();
	if (SingleSourceMovesStatusLeft(board, src) == 2) {
		Board * tempBoard = updateBoard(board, src, 2, 'l');
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				move->board[i][j] = (*tempBoard)[i][j];
		free(tempBoard);
		move->pos = updatePos(board, src, 2, 'l');
		move->total_captures_so_far = captures + 1;
		move->next_moves[0] = FindNextCapturesLeft(move->board, move->pos, move->total_captures_so_far);
		move->next_moves[1] = FindNextCapturesRight(move->board, move->pos, move->total_captures_so_far);
	}
	else
		move = NULL;
	return move;
}
SingleSourceMovesTreeNode * FindNextCapturesRight(Board board, checkersPos * src, int captures) {
	SingleSourceMovesTreeNode * move = createMovesTreeNode();
	if (SingleSourceMovesStatusRight(board, src) == 2) {
		Board * tempBoard = updateBoard(board, src, 2, 'r');
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				move->board[i][j] = (*tempBoard)[i][j];
		free(tempBoard);
		move->pos = updatePos(board, src, 2, 'r');
		move->total_captures_so_far = captures + 1;
		move->next_moves[0] = FindNextCapturesLeft(move->board, move->pos, move->total_captures_so_far);
		move->next_moves[1] = FindNextCapturesRight(move->board, move->pos, move->total_captures_so_far);
	}
	else
		move = NULL;
	return move;
}

checkersPos * createPos() {
	checkersPos * pos = (checkersPos*)malloc(sizeof(checkersPos));
	if (!pos) {
		printf("Memory allocation failure.\n");
		exit(2);
	}
	return pos;
}
checkersPos * createPosWithDefaultCoords(char row, char col) {
	checkersPos * pos = (checkersPos*)malloc(sizeof(checkersPos));
	if (!pos) {
		printf("Memory allocation failure.\n");
		exit(2);
	}
	pos->row = row;
	pos->col = col;
	return pos;
}

SingleSourceMovesTreeNode * createMovesTreeNode() {
	SingleSourceMovesTreeNode * newNode  = (SingleSourceMovesTreeNode *)malloc(sizeof(SingleSourceMovesTreeNode));
	if (!newNode) {
		printf("Memory allocation failure. \n");
		exit(2);
	}
	return newNode;
}

Board * createNewBoard() {
	Board * newBoard = (Board*)malloc(sizeof(Board));
	if (!newBoard) {
		printf("Memory allocation failure.\n");
		exit(2);
	}
	return newBoard;
}

SingleSourceMovesTreeNode * FindSingleSourceMovesLeft(Board board, checkersPos * src) {
	int status = SingleSourceMovesStatusLeft(board, src);
	if (status == 0)
		return  NULL;
	else {
		SingleSourceMovesTreeNode * newNode = createMovesTreeNode();

		Board *tempBoard = updateBoard(board, src, status, 'l');
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				newNode->board[i][j] = (*tempBoard)[i][j];
		free(tempBoard);
		newNode->pos = updatePos(board, src, status, 'l');

		if (status == 1) {
			newNode->total_captures_so_far = 0;
			newNode->next_moves[0] = NULL;
			newNode->next_moves[1] = NULL;
		}
		else {
			newNode->total_captures_so_far = 1;
			newNode->next_moves[0] = FindNextCapturesLeft(newNode->board, newNode->pos, 1);
			newNode->next_moves[1] = FindNextCapturesRight(newNode->board, newNode->pos, 1);
		}
		return newNode;
	}
	return NULL;
}

SingleSourceMovesTreeNode * FindSingleSourceMovesRight(Board board, checkersPos * src) {
	int status = SingleSourceMovesStatusRight(board, src);
	if (status == 0)
		return  NULL;
	else {
		SingleSourceMovesTreeNode * newNode = createMovesTreeNode();
		Board *tempBoard = updateBoard(board, src, status, 'r');
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				newNode->board[i][j] = (*tempBoard)[i][j];
		free(tempBoard);
		newNode->pos = updatePos(board, src, status, 'r');
		if (status == 1) {
			newNode->total_captures_so_far = 0;
			newNode->next_moves[0] = NULL;
			newNode->next_moves[1] = NULL;
		}
		else {
			newNode->total_captures_so_far = 1;
			newNode->next_moves[0] = FindNextCapturesLeft(newNode->board, newNode->pos, 1);
			newNode->next_moves[1] = FindNextCapturesRight(newNode->board, newNode->pos, 1);
		}
		return newNode;
	}
	return NULL;
}
