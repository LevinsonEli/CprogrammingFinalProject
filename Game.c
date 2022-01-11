
#include "Turn.h"
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1 

void StoreBoard(Board board, char *  filename) {
	FILE * file = fopen(filename, "wb");
	verifyFileOpening(file);

	unsigned char ch = 0;
	int m = 0;
	int k = 1;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == ' ')
				m = -1;
			else if (board[i][j] == 'T')
				m = 0;
			else if (board[i][j] == 'B')
				m = 1;
			ch = ch << 2;
			ch = setBit(ch, m);
			if ((j + 1) % 4 == 0)
				fwrite(&ch, sizeof(char), 1, file);
		}
	fclose(file);
}

void LoadBoard(char *filename, Board * board) {
	FILE * file = fopen(filename, "rb");
	verifyFileOpening(file);

	unsigned char ch = 0;
	int i = 0, j = 0;
	int m = 7;
	fread(&ch, sizeof(char), 1, file);
	while (ch != EOF && i != BOARD_SIZE) {
		if (isBitISet(ch, m - 1) == 1)
			(*board)[i][j] = 'T';
		else if (isBitISet(ch, m) == 1)
			(*board)[i][j] = 'B';
		else
			(*board)[i][j] = ' ';
		m -= 2;
		if (m < 0) {
			fread(&ch, sizeof(char), 1, file);
			m = 7;
		}
		j++;
		if (j == 8) {
			j = 0;
			i++;
		}
	}
	fclose(file);
}

void PlayGame(Board board, Player starting_player) {
	printBoard(board);
	if (starting_player != 'B' && starting_player != 'T') {
		printf("Only 'B' and 'T' players play. \n");
		return;
	}
	StoreBoard(board, fileNameBoard);
	Board * newBoard = createNewBoard();
	LoadBoard(fileNameBoard, newBoard);

	Player player1 = starting_player, player2 = 'T' + 'B' - starting_player;
	while (SmbdyWin(*newBoard) == 0) {
		Turn(newBoard, player1);
		LoadBoard(fileNameBoard, newBoard);
		if (SmbdyWin(*newBoard) == 1 ||												// If player1 won
			FindAllPossiblePlayerMoves(*newBoard, player2) == NULL ||			// or player2 can't move
			FindAllPossiblePlayerMoves(*newBoard, player2)->head->single_source_moves_list == NULL)
			break;
		Turn(newBoard, player2);
		LoadBoard(fileNameBoard, newBoard);
		if (SmbdyWin(*newBoard) == 1 ||												// If player2 won
			FindAllPossiblePlayerMoves(*newBoard, player1) == NULL ||			// or player1 can't move
			FindAllPossiblePlayerMoves(*newBoard, player1)->head->single_source_moves_list == NULL)
			break;
	}
	free(newBoard);
}

int SmbdyWin(Board board) {
	for (int i = 0; i < BOARD_SIZE; i++)
		if (board[0][i] == 'B')
			return 1;
	for (int i = 0; i < BOARD_SIZE; i++)
		if (board[7][i] == 'T')
			return 1;
	return 0;
}

void printBoard(Board board) {
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("| |1|2|3|4|5|6|7|8|\n");
	printf("+-+-+-+-+-+-+-+-+-+\n");
	for (int j = 0; j < BOARD_SIZE; j++) {
		printf("|%c|", j + 'A');
		for (int i = 0; i < BOARD_SIZE; i++)
			printf("%c|", board[j][i]);
		printf("\n");
		printf("+-+-+-+-+-+-+-+-+-+\n");
	}
	fflush(stdout);
}

int isBitISet(unsigned char ch, int i) {
	unsigned char mask = 1 << i;
	if ((ch & mask) == 0)
		return 0;
	else return 1;
}
unsigned char setBit(unsigned char ch, int i) {
	if (i < 0)
		return ch;
	unsigned char mask = 1 << i;
	return ch | mask;
}

void verifyFileOpening(FILE * file) {
	if (!file) {
		printf("Failed to open the file. \n");
		exit(2);
	}
}