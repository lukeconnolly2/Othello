//
// Created by Luke on 11/04/2021.
//

#ifndef OTHELLO_USER_INPUT_H
#define OTHELLO_USER_INPUT_H

#include <string.h>

#include "Validation.h"
#include "board.h"
#include "structures.h"

//Function to decode player input to then output the y array index.
int decode_user_choice_y(char userchoice[]){
    //if statement for uppercase letters. Decodes via ascii table.
    if(userchoice[1] > 64 && userchoice[1] < 73)  return (int) userchoice[1] - 65;
    //if statement for lowercase letters. Also decodes via ascii table.
    if(userchoice[1] > 96 && userchoice[1] < 106) return (int) userchoice[1] - 97;
    //Otherwise the user has inputed an invalid character and we then exit.
    else exit(-1);
}
//Function to decode player input to then output the x array index.
int decode_user_choice_x(char userchoice[]){
    //If its not a digit on the ascii table, we exit.
    if(userchoice[0] < 48 || userchoice[0] > 57) exit(-1);
    //if it is use ascii table to decode it.
    return (int) userchoice[0] - 49;
}

//Function to get user input.
void get_user_input(char colour){
    //Bool to store if input is good
    bool good_input = true;
    //Char array to store this input.
    char userchoice[3];
    do{
        //Prompt user and scan in there input.
        printf("\nEnter square:\n");
        scanf("%s", userchoice);
        //If it cant be put in the board, ask user again, otherwise it gets put in.
        if(!input_to_board(colour, decode_user_choice_x(userchoice), decode_user_choice_y(userchoice))) {
            good_input = false;
            printf("Enter a Valid square.");
        }
    }
    while(!good_input);
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
