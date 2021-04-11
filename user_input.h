//
// Created by Luke on 11/04/2021.
//

#ifndef OTHELLO_USER_INPUT_H
#define OTHELLO_USER_INPUT_H

#include <string.h>

#include "Validation.h"
#include "board.h"
#include "structures.h"

int decode_user_choice_y(char userchoice[]){
    if(userchoice[1] > 64 && userchoice[1] < 73)  return (int) userchoice[1] - 65;
    if(userchoice[1] > 96 && userchoice[1] < 106) return (int) userchoice[1] - 97;
    else exit(-1);
}
int decode_user_choice_x(char userchoice[]){
    if(userchoice[0] < 48 || userchoice[0] > 57) exit(-1);
    return (int) userchoice[0] - 49;
}

void get_user_input(char colour){
    char userchoice[3];
    do{
        printf("\nEnter square:\n");
        scanf("%s", userchoice);
    }
    while(!input_to_board(colour, decode_user_choice_x(userchoice), decode_user_choice_y(userchoice)));
}

//Function to get the names of the two players
void get_player_names(player *player1, player *player2){
    //Var to store the name.
    char name[50];
    //Get user input.
    printf("Enter the name for player 1 (Black):");
    scanf("%s", name);
    //Copy it into struct in the main function with pointers
    strcpy(player1->name, name);
    //User input
    printf("Enter the name for player 2 (White):");
    scanf("%s", name);
    //Copy it in again
    strcpy(player2->name, name);
}


#endif //OTHELLO_USER_INPUT_H
