//
// COMP9024 Assignment 1 - Sliding-Tile Puzzle
//
// header file of board adt
//
// 1.interfaces of board functions
//
//
// Authors:
// Lipeng Tao (z5048267@unsw.edu.au)
//
//
// Written: 24/06/2019
//
typedef struct boardADT
{
    // record the board
    int** board;

    // empty space position 
    int row;
    int col;

    // record the NxN
    int N;

} *boardADT_t;

// create a new board which is NxN board, the empty space position is 'pos'
boardADT_t create_board(int N, int pos);

// init the board 'B' with the input data
void init_board(boardADT_t B, int* input);
// get the disorder of the board
int get_disorder(boardADT_t B);

// read data from stdin
int* read_input(int *N, int *pos, int* num);

// check the input data is valid or not
int check_valid(int* input, int N, int num);

// extend memory by the need
int* extend_memory(int* input, int* N, int *num);

// free all memory by malloc
void free_board(boardADT_t B);
