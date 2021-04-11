//
// Created by Luke on 11/04/2021.
//

#ifndef OTHELLO_OUTPUT_H
#define OTHELLO_OUTPUT_H

#include <stdio.h>
#include <string.h>
#include "structures.h"

//Function to calc and print each players score.
void print_score(player *player1, player *player2){
    //Vars to store the scores
    int black_score = 0;
    int white_score = 0;

    //Loop through lines and cols
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            //For each W add one to whites score
            if(board[x][y].colour == 'W')   white_score++;
            //For each B add one to blacks score.
            if(board[x][y].colour == 'B')   black_score++;
        }
    }

    //Set the scores in the structs in main function.
    player1->score = black_score;
    player2->score = white_score;

    //Print the scores.
    printf("Score: %s (Black) %d:%d %s (White)\n", player1->name, player1->score, player2->score, player2->name);
}




int print_valid(char colour_playing){
    //Int to store the number of squares which it is valid to place a piece on.
    int number_of_valid_squares = 0;
    //Output
    printf("Valid Choices (%c):\n",colour_playing);
    //Loop through all the squares
    for(int x=0; x<8;x++){
        for(int y=0;y<8;y++){
            //if its an open square
            if(board[x][y].colour == ' ') {
                //Check can it be placed on with is_valid function.
                if (is_valid(colour_playing, x, y)) {
                    //if so set the square to valid.
                    board[x][y].valid = true;
                    //Print it
                    printf("%d%c ", x + 1, y + 65);
                    //increment the number of valid squares
                    number_of_valid_squares++;
                }
                    //else set the square to false.
                else{
                    board[x][y].valid = false;
                }
            }
        }
    }

    //return  the number of squares which are valid so we can keep track of if a user needs to pass or not.
    return number_of_valid_squares;
}


void writetofile(player player1, player player2) {

    FILE *fp;

    fp = fopen("othello-results.txt", "a");
    if(fp == NULL)   fopen("othello-results.txt", "W");

    if(player1.score > player2.score) fprintf(fp, "%s has a score of %d and %s has a score of %d meaning %s has won\n", player1.name, player1.score, player2.name, player2.score, player1.name);
    if(player1.score < player2.score) fprintf(fp, "%s has a score of %d and %s has a score of %d meaning %s has won\n", player1.name, player1.score, player2.name, player2.score, player2.name);
    if(player1.score == player2.score) fprintf(fp, "%s has a score of %d and %s has a score of %d meaning its a draw\n", player1.name, player1.score, player2.name, player2.score);


    fclose(fp);

    printf("This has been written to othello-results.txt\n");
}


#endif //OTHELLO_OUTPUT_H
