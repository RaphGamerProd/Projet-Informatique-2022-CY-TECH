#ifndef _MASTERLIB_H
#define _MASTERLIB_H

// Libraries importation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Defining constants
#define SIZE 10
#define color(param) printf("\033[%sm",param)


// Structures declration
typedef struct 
{
    int px;
    int py;
    int piecetype[4][4];
    int maxrot;
}tetromino;

typedef struct masterlib
{
    int bLoose;
    int difficulty_setting;
    int party_score;
    int answer_time;
}gamestatus;


// Functions declaration
void add_color(int gridlocation[SIZE][SIZE], int difficulty, int i, int j);
void calculate_newrotation(int nb_rotation, int curr_row, int curr_col, int* rotated_row, int* rotated_collumns);
void create_grid(int anchor_piece, int gridlocation[SIZE][SIZE], int difficulty);
void forcecrash(char message[200]);
void has_loose(int gridlocation[SIZE][SIZE], gamestatus *gamestat);
void initialise_score(FILE *my_file);
void reset_grid(int gridlocation[SIZE][SIZE]);
void rotate_matrix(int nb_rotation, tetromino *currentpiece);
void remove_lines(int gridlocation[SIZE][SIZE], gamestatus *gamestat);
void selectpiecearray(int arr1[4][4], int arr2[4][4]);
void set_score(FILE *myfile, gamestatus *gamestat);
void snap_piece(int gridlocation[SIZE][SIZE], tetromino *currentpiece, gamestatus *gamestat);
void spawn_piece(tetromino *currentpiece);

char gridskin(int value);

int null_matrix(int arr[4][4]);
int retrieve_time();





#endif