#include <stdlib.h>
#include <string.h>
#include "connect4_args.h"
#define PLAYER_MAX 2

int checkwin(int *winner, int connects, int rows, int cols, int **board)
{
	int cell;
	int offset;

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++)
		{
			offset = 0;
			cell = board[r][c];
			if (cell == 0)
				continue;

			// horizontal
			for ( int i = c; i < (c+connects); i++)
			{
				if (i == cols || board[r][i] != cell)
					break;

				if (i == ((c+connects)-1)) {
					*winner = cell;
					return 0;
				}
			}

			// vertical
			for ( int i = r; i < (r+connects); i++)
			{
				if (i == rows || board[i][c] != cell)
					break;

				if (i == ((r+connects)-1)) {
					*winner = cell;
					return 0;
				}
			}

			// up and right
			for ( int i = c; i < (c+connects); i++)
			{
				if (i == cols || (r-offset) < 0 || board[r-offset][i] != cell)
					break;

				if (i == ((c+connects)-1)) {
					*winner = cell;
					return 0;
				}
				offset++;
			}

			// up and left
			offset = 0;
			for ( int i = c; i > (c-connects); i--)
			{
				if (i < 0 || (r-offset) < 0 || board[r-offset][i] != cell)
					break;

				if (i == ((c-connects)+1)) {
					*winner = cell;
					return 0;
				}
				offset++;
			}
		}
	}

	return -1;
}

// if top row is full, we assume board is full
int checkfull(int cols, int **board)
{
	for (int i = 0; i < cols; i++)
	{
		if (board[0][i] == 0)
			return -1;
	}

	return 0;
}

// increments turn between players
void advance_turn(int *turn)
{
	(*turn)++;

	if (*turn > PLAYER_MAX)
		*turn = 1;

}

// place the players chip in the expected column
int place_chip(int player, int col, int rows, int **board)
{
	int r = 0;
	col--;

	if (board[0][col] != 0)
	{
		fprintf(stderr, "Column is full.\n");
		return -1;
	}

	while (board[r][col] == 0)
	{
		if (r == (rows-1) || board[r+1][col] != 0)
		{
			board[r][col] = player;
			return 0;
		}
		r++;
	}

	return -1;
}

// prints the board. 
void print_board(int rows, int cols, int **board)
{
	if (board == NULL)
	{
		fprintf(stderr, "Board is empty.\n");
	}
	else
	{
		fprintf(stderr, "\n");
		for(int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {

				if (board[i][j] == 0)
					fprintf(stderr, "-  ");
				else
					fprintf(stderr, "%i  ", board[i][j]);
			}
			fprintf(stderr, "\n");
		}
	}
}

// create the board with a pointer to a double int pointer. This allows the board to be accessed with board[r][c]
void create_board(int rows, int cols, int ***boardptr)
{
	// This will hold a list of offsets for accessing each row.
	*boardptr = (int **) malloc(rows * sizeof(int *));
	// This will hold the board itself in a list of values. 
	**boardptr = (int *) malloc(cols * rows * sizeof(int));

	if ( *boardptr == NULL || **boardptr == NULL) {
		perror("malloc()");
		exit(1);
	}

	// This sets up the list of offsets to hold the correct positions for each start of a row in the board itself. The size of a row is the number of columns in the board. 
	int **temp;
	for (int i = 0; i < rows; i++) {
		temp = ((*boardptr)+i);
		*temp = (**boardptr + (cols * i));
	}
}

