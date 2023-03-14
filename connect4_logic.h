#ifndef C4_LOGIC_H
#define C4_LOGIC_H

int checkfull(int cols, int **board);
int checkwin(int *winner, int connects, int rows, int cols, int **board);
void advance_turn(int *turn);
int place_chip(int player, int col, int rows, int **board);
void print_board(int rows, int cols, int **board);
void create_board(int rows, int cols, int ***board);

#endif
