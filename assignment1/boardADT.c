//
// COMP9024 Assignment 1 - Sliding-Tile Puzzle
//
// implication file of board adt
//
// 1.structure for the board
// 2.operation function for the board
//
//
// Authors:
// Lipeng Tao (z5048267@unsw.edu.au)
//
//
// Written: 24/06/2019
//
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#include<math.h>

#include "boardADT.h"

#define EMPTY 0

// create a new board which is NxN board, the empty space position is 'pos'
boardADT_t create_board(int N, int pos){
    // dynamic allocation memory
    boardADT_t board = malloc(sizeof(struct boardADT));
    // initialize dynamic allocation array
    board->board = malloc(sizeof(int*)*N);

    // initialize array
    int i = 0;
    for(i=0;i<N;i++){
        *(board->board+i) = (int*)malloc(sizeof(int)*N);
    }

    board->col = (int)(pos / N);
    board->row = pos % N;

    board->N = N;

    return board;
}

// init the board 'B' with the input data
void init_board(boardADT_t B, int* input){
    int N = B->N;
    int i=0, value=0;
    for(i=0;i<N*N;i++){
        value = *(input+i);
        if(value == 0){
            B->row = i / N;
            B->col = i % N;
        }
        
        *((*(B->board+(i/N)))+(i%N)) = value;
        
    }
}
// get the disorder of the board
int get_disorder(boardADT_t B){
    int N = B->N;

    int i=0, k=0;

    int num=0;
    for(k=0;k<N*N;k++){
        int cur = *((*(B->board+(k/N)))+(k%N)); 
        for(i=k+1;i<N*N;i++){
            if(*((*(B->board+(i/N)))+(i%N)) < cur && *((*(B->board+(i/N)))+(i%N)) != 0){
                num ++;
            }
        }

    }

    // N is even
    if(N % 2 == 0){
        num += B->row + 1;
    }

    return num;
    
}
// extend memory by the need
int* extend_memory(int* input, int* N, int *num){
    int* tmp = input;
        if(*num >= (*N)*(*N)){
            (*N) ++;
            input = malloc(sizeof(int)*((*N)*(*N)));
            int i;
            for(i=0;i<((*N)-1)*((*N)-1);i++){
                *(input+i) = *(tmp+i);
            }
            free(tmp);   
        }

        return input;
}
// read data from stdin
int* read_input(int* N, int* pos, int *num){
    int* input = malloc(sizeof(int)*(*N)*(*N));

    char c;
    int element = 0;
    // whether current position is space or number
    int valid = 0;

    // read each number
    while (1)
    {
        if(scanf("%c", &c) == EOF){
            if(valid == 1){
                *(input+(*num)) = (int)element;
                (*num) ++;
                element = 0;
            }
            return input;
        }

        if(c == ' ' || c == '\t'){
            if(valid == 1){

                input = extend_memory(input, N, num);
                *(input+(*num)) = (int)element;
                (*num) ++;
                element = 0;
            }
            valid = 0;
            continue;
        }else if(c == 'b'){
                if(valid == 0){
                    valid = 1;
                    element = 0;
                    *pos = *num;

                    // check if extend memory
                    input = extend_memory(input, N, num);

                    *(input+(*num)) = (int)element;
                    (*num) ++;

                    element = 0;

                    valid = 0;

                    continue;

                }else{
                    free(input);
                    return NULL;
                }
        }else if(c == '\n'){
                if(valid == 1){
                    *(input+(*num)) = (int)element;
                    (*num) ++;
                    element = 0;
                }
                return input;
        }else if(!isdigit(c)){
                free(input);
                return NULL;
        }else{
            valid = 1;
        }

        element *= 10;
        element += (c-'0');
        
        
    }
    return input;

}
// check the input data is valid or not
int check_valid(int* input, int N, int num){

    //printf("%d %d\n", num, N);

    if(N % 2== 1){
        num ++;
    }

    if(num != N*N){
        return 0;
    }

    int i,j;
    for(i=0;i<N*N;i++){
        for(j=i+1;j<N*N;j++){
            if(*(input+i) == *(input+j)){
                return 0;
            }
        }
    }

    return 1;
}
// free all memory by malloc
void free_board(boardADT_t B){
    int i=0;
    for(i=0;i<B->N;i++){
        free(*(B->board+i));
    }
    free(B->board);
}
