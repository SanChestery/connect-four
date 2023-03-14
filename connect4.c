/*
	This is a very in dev version of our connect four game. It's not yet very smart or sophisticated.
	It aims to be used as a decent first draft which can be built upon. 

	Logic is primitive and most of the code is copy/paste and adapted from google. 
	Special shoutout to stackoverflow, as per usual the only reason I got working code.

	Build: gcc *.c -o main

	Todo:
	- smarter solution for replay
	- smarter solution for input handling? -> parse_args
	- maybe learn about proper input validation? Application seems very unsecure but idk it seems to work alright.

	V0.1 - t
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "connect4_args.h"
#include "connect4_logic.h"
#define INPUT_MAX 100

int main(int argc, char *argv[])
{
	
	struct arguments args;
	char input[INPUT_MAX];
	char *loadBuffer, *saveBuffer;
	int **board = NULL;
	int turn = 1;
	int move = 0;
	int winner = 0;

	// default values for inputs
	args.rows = 6;
	args.cols = 7;
	args.connect = 4;

	parse_args(argc, argv, &args);

	// create and initialize board 
	create_board(args.rows, args.cols, &board);
	for (int i = 0; i < args.rows; i++) {
		for (int j = 0; j < args.cols; j++) {
			board[i][j] = 0;
		}
	}

	// hello
	fprintf(stderr, "Rows: %i\nCols: %i\nConnects: %i\n\nGame start!\n", args.rows, args.cols, args.connect);
	print_board(args.rows, args.cols, board);

	// main 
	while (1)
	{
		// Print Player turn and get input
		fprintf(stderr, "(Player %i) ", turn);
		fgets(input, INPUT_MAX, stdin);
		move = atoi(input);

		// Quit
		if (strcmp(input, "q\n") == 0 ||
			strcmp(input, "Q\n") == 0 ||
			strcmp(input, "exit\n") == 0)
		{
			free(*board);
			free(board);
			exit(0);
		}
		
		// Place a chip if the user's input is a valid column.
		if (move > 0)
		{
			if (move > args.cols)
			{
				fprintf(stderr, "Column doesn't exist.\n");
			}
			else if (place_chip(turn, move, args.rows, board) == 0)
			{
				fprintf(stderr, "Player %i placed a chip in column %i\n", turn, move);
				print_board(args.rows, args.cols, board);
				advance_turn(&turn);
			}
		}
		else
		{
			fprintf(stderr, "Unrecognized input.\n");
		}

		// check for winner or full board
		if (checkwin(&winner, args.connect, args.rows, args.cols, board) >= 0 ||
			checkfull(args.cols, board) == 0)
		{
			if (winner > 0)
				fprintf(stderr, "Player %i wins!\nPlay again? (y/n) ", winner);
			else
				fprintf(stderr, "Game over, board is full!\nPlay again? (y/n) " );

			fgets(input, INPUT_MAX, stdin);

			// play again
			if (strcmp(input, "y\n") == 0 || strcmp(input, "Y\n") == 0)
			{
				create_board(args.rows, args.cols, &board);
				for (int i = 0; i < args.rows; i++) {
					for (int j = 0; j < args.cols; j++) {
						board[i][j] = 0;
					}
				}
				turn = 1;

				fprintf(stderr, "Rows: %i\nCols: %i\nConnects: %i\n\nGame start!\n", args.rows, args.cols, args.connect);
				print_board(args.rows, args.cols, board);
			}
			else
			{
				fprintf(stderr, "Goodbye!\n");
				free(*board);
				free(board);
				exit(0);
			}
		}
	}
	return 0;
}
