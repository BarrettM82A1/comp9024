//
// COMP9024 Assignment 1 - Sliding-Tile Puzzle
//
// Solvability of the NxN sliding tile puzzle
// Specification: https://webcms3.cse.unsw.edu.au/COMP9024/19T2/resources/27266
// Tutorial: https://webcms3.cse.unsw.edu.au/COMP9024/19T2/resources/27984
//
// Authors:
// Lipeng Tao (z5048267@unsw.edu.au)
//
//
// Written: 26/06/2019
//
#include<stdio.h>
#include<stdlib.h>

#include "boardADT.h"

int main(){
    int N = 2, num=0;
    int pos;
    int* start = read_input(&N, &pos, &num);

    if(start == NULL || !check_valid(start, N, num)){
        printf("input error\n");
        return EXIT_FAILURE;
    }

    int i;
    printf("start: ");
    for(i=0;i<N*N;i++){
        if(*(start + i) == 0){
            printf("b ");
            continue;
        }
        printf("%d ", *(start + i));
    }
    printf("\n");

    boardADT_t start_board = create_board(N, pos);
    init_board(start_board, start);


    N = 2, num=0;
    int* goal = read_input(&N, &pos, &num);
    // check boards valid
    if(goal == NULL || !check_valid(goal, N, num)){
        printf("input error\n");
        return EXIT_FAILURE;
    }

    printf("goal: ");
    for(i=0;i<N*N;i++){
        if(*(goal + i) == 0){
            printf("b ");
            continue;
        }
        printf("%d ", *(goal + i));
    }
    printf("\n");

    boardADT_t goal_board = create_board(N, pos);
    init_board(goal_board, goal);


    int start_parity = get_disorder(start_board);
    int goal_parity = get_disorder(goal_board);
    // check boards solvable
    if(start_parity % 2 == goal_parity % 2){
        printf("solvavle\n");
    }else{
        printf("unsolvavle\n");
    }


    free(start);
    free(goal);

    free_board(goal_board);
    free_board(start_board);
    return EXIT_SUCCESS;
}
