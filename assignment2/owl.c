// COMP9024 Assignment 2 - Ordered Word Ladder
//
// compares 2 arbitrary null-terminated strings and returns 1 if the strings satisfy one 	of the 2 conditions above, and 0 otherwise 
// Generating a graph and output the number of nodes and edges 
// calculate the longest path and print paths by generating graph
// Using Graph array matrix ADT
// Authors:
// Lipeng TAO (z5048267@unsw.edu.au)
//
//
// Written: 04/08/2019
//
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "Graph.h"


#define MAX_WORDS_NUM 1000
#define MAX_WORD_LEN 21

int differByOne(char *, char *);
int read_words(char words[MAX_WORDS_NUM][MAX_WORD_LEN]);
void print_words(int num, char words[MAX_WORDS_NUM][MAX_WORD_LEN]);
void init_graph(int num, char words[MAX_WORDS_NUM][MAX_WORD_LEN], Graph g);

int print_ladders(int num, int max_len, int cur, char words[MAX_WORDS_NUM][MAX_WORD_LEN], 
		int* path,  int path_len, int **dist, int* id){
    // if the max len is 1, that means the current node is the last one in this path,
    // so print all the node in the path
    if(max_len == 1){
        if(*id > 99){
            return 0;
        }
        printf("%2d: ", *id);
        int count = 0;
        for(int i=0;i<num-1;i++){
            if(path[i] == 1){
                printf("%s -> ", words[i]);
                count ++;
            }
        }

        printf("%s\n", words[cur]);
        (*id) = (*id) + 1;
    }else{
        // search next node whose distance between cur to the node is  max len,
        // and continue to print ladders
        for(int i=cur+1;i<num;i++){
            if(dist[cur][i] == max_len){
                //path[paths[cur][i]] = 1;
                path[cur] = 1;
                //paths[cur][i]
                print_ladders(num, max_len-1, i, words, path, path_len, dist, id);
                //path[paths[cur][i]] = 0;
                path[cur] = 0;
            }
        }
    }
    return 0;
}

int find_longest_path(int num, Graph g, char words[MAX_WORDS_NUM][MAX_WORD_LEN]){

    int* max_lengths = malloc(sizeof(int)*num);
    for (int i = 0; i < num; i++) {
        max_lengths[i] = 1;
    }

    int** dist = malloc(sizeof(int*)*num);
    //int** paths = malloc(sizeof(int*)*num);

    for(int i=0;i<num;i++){
        dist[i] = malloc(sizeof(int)*num);
        //paths[i] = malloc(sizeof(int)*num);
    }

    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            dist[i][j] = 0; 
            //paths[i][j] = j;
        }
    }

    for(int i=0;i<num;i++){
        for(int j=i+1;j<num;j++){
            if(isEdge(newEdge(i, j), g)){
               dist[i][j] = 1; 
            }
        }
    }

    // calcualte the number of v in each path 
    int max_len = 0;
    for(int i=num-1;i>=0;i--){
        max_len = 1;
        for(int j=i+1;j<num;j++){
            // if j and i is connected
            if(isEdge(newEdge(i, j), g)){
                dist[i][j] = 1 + max_lengths[j];
                if (1 + max_lengths[j] > max_len) {
                    max_len = 1 + max_lengths[j];
                }
            }

        }
        max_lengths[i] = max_len;
    }

    // find the max_lengths path in all paths
    max_len = 0;
    for (int i = 0; i < num; i++){
        if (max_lengths[i] > max_len){ 
            max_len = max_lengths[i];
	}
    }

    int id = 1;
    printf("Longest ladder length: %d\n", max_len);
    printf("Longest ladders:\n");
    // if the max len is 1, that means all the node should be printed
    if(max_len == 1){
        for(int i=0;i<num;i++){
            // the max number of the paths that will be outputed is 99
            if(i == 99){
                return max_len;
            }
            printf("%2d: %s\n", i+1, words[i]);
        }
        return  max_len;
    }

    for(int i=0;i<num;i++){
        for(int j=i+1;j<num;j++){
            // if the dist between i and j is max len, then print ladders
            if(dist[i][j] == max_len){
                // create a new path to record the path from i to the last one
                int path_len = 0;
                int* path = malloc(sizeof(int)*num);
                for(int k=0;k<num;k++){
                    path[k] = 0;
                }
                path[i] = 1;
                // print ladders
                print_ladders(num, max_len-1, j, words, path, path_len, dist, &id);
                free(path);
            }
        }
        
    }

    // free all the memory space
    free(max_lengths);
    for(int i=0;i<num;i++){
        free(dist[i]);
    }
    free(dist);

    //printf("max %d\n", max_len);
    return max_len;

}

int main(){

    // part 1
    char words[MAX_WORDS_NUM][MAX_WORD_LEN];
    int num = read_words(words);

    if(num == 0){
        return 0;
    }

    Graph g = newGraph(num);
    print_words(num, words);

    // part2
    init_graph(num, words, g);
    showGraph(g);

    // part3
    find_longest_path(num, g, words);
    freeGraph(g);
}

void freeEdges(int** edges, int num){
    int i;
    for(i=0;i<num;i++){
        free(edges[i]);
    }
    free(edges);
}

// init the graph with the words
void init_graph(int num, char words[MAX_WORDS_NUM][MAX_WORD_LEN], Graph g){
    printf("Ordered Word Ladder Graph\n");
    int i=0,j=0;
    for(i=0;i<num;i++){
        for(j=i+1;j<num;j++){
            if(differByOne(words[i], words[j]) == 1){
                insertEdge(newEdge(i, j), g);
            }
        }
    }
}

// print all words
void print_words(int num, char words[MAX_WORDS_NUM][MAX_WORD_LEN]){
    int i=0;
    printf("Dictionary\n");
    for(i=0;i<num;i++){
        printf("%d: %s\n", i, words[i]);
    }
}

// read all words from the stdin
int read_words(char words[MAX_WORDS_NUM][MAX_WORD_LEN]){
    int count = 0;
    char temp[MAX_WORD_LEN];
    while (scanf("%s", temp) != EOF){
        int i, flg=0;
        // check if the word in the words array
        for(i=0;i<count;i++){
            if(strcmp(words[i], temp) == 0){
                flg = 1;
                break;
            }
        }
        // if not in, then add to the array
        if(flg == 0){
            strcpy(words[count], temp);
            count ++;
        }
    }
    return count;
}

int differByOne(char *word, char *other_word){
    int len_word = strlen(word);
    int len_other_word = strlen(other_word);
    // compare that the two words have the same number letters, and just one letter is different betweent the two words
    if(len_word== len_other_word){
        int count=0, i=0;
        for(i=0;i<strlen(word);i++){
            if(word[i] != other_word[i]){
                count ++;
            }
        }
        if(count != 1){
            return 0;
        }else{
            return 1;
        }

        //if the length of word is larger than the length of other word, and the diff is 1
    }else if (len_word-len_other_word==1){
        int count=0, i=0, j=0, pre_i=0;
        
        for(i=0;i<len_other_word;i++){
            if(other_word[i] != word[j+i]){
                j++;
                // record the last position where the two words have the same letter
                i = pre_i-1;
                count ++;
                // means that  2 or more letters are different between the two words
                if(count >= 2){
                    return 0;
                }
            }else{
                // record the last position where the two words have the same letter
                pre_i = i+1;
            }
        }
        return 1;

        // another case
    }else if (len_other_word-len_word==1){
        int count=0, i=0, j=0, pre_i=0;
        for(i=0;i<len_word;i++){
            if(word[i] != other_word[j+i]){
                j++;
                // record the last position where the two words have the same letter
                i = pre_i-1;
                count ++;
                // means that  2 or more letters are different between the two words
                if(count >= 2){
                    return 0;
                }
            }else{
                // record the last position where the two words have the same letter
                pre_i = i+1;
            }
        }
        return 1;
    }else{
        return 0;
    }
}

