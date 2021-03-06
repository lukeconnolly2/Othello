//
// Created by Luke on 11/04/2021.
//

#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H

#include "structures.h"

//Function to check if theres any squares left on the board.
bool check_if_all_squares_are_full(player player1, player player2){
    if(player1.score + player2.score == 64) return true;
    else return false;
}

//Function to get the board ready before the game.
void initialise_board(){
    //Print the title.
    printf("   *** Welcome to Othello ***   \n");

    //Initialise all squares to default.
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            board[x][y].colour = ' ';
            board[x][y].valid = false;
        }
    }

    //Set the colour of the starting arrangement.
    board[4][4].colour = 'W';
    board[3][3].colour = 'W';
    board[3][4].colour = 'B';
    board[4][3].colour = 'B';
}

//Function to print the board.
void print_board(){

    //Print the top line of the board.
    printf("  ");
    for(int x=0;x<8;x++)printf(" ---");
    printf("\n");

    //For loop to iterate through rows
    for(int x=0;x<8;x++){
        //Print the number of each row
        printf("%d ", x+1);

        //Iterate over cols.
        for(int y=0;y<8;y++){
            //Print the contents of the row
            printf("| %c ", board[x][y].colour);
        }
        printf("|\n  ");

        //Print separating lines.
        for(int z=0;z<8;z++)printf(" ---");
        printf("\n");
    }

    //Print letters at the bottom.
    printf("    ");
    for(int x = 65;x<73;x++)printf("%c   ", x);
    printf("\n");
}

void reset_squares(){
    for(int x=0; x<8;x++){
        for(int y=0;y<8;y++){
            board[x][y].valid = false;
        }
    }
}


#endif //OTHELLO_BOARD_H
