// Othello Project
// by Luke Connolly 20306416
// GitHub - https://github.com/lukeconnolly2/Othello
// Decisions around implimentation choices etc are found in the README.txt file.
// Ive included brackets at the end of any comments where a new function is used which outline which .h file it is in.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "board.h"
#include "user_input.h"
#include "output.h"


int main() {
    //Initialise player 1 and 2 structs.
    player player1 = {"", 0, 'B'};
    player player2 = {"", 0, 'W'};

    //Make a pointer to the player currently playing which is initialized to player 2.
    player* current_player = &player2;

    //Make a bool to store if the game should continue
    bool game = true;

    //Char to store p when player passes
    char pass;

    //Run this function to set up the board. (Board)
    initialise_board();

    //Get the players names with this function (User Input)
    get_player_names(&player1, &player2);

    //While loop to loop while the game is on
    while(game) {
        //Funtion to reset all the square valid bool at the start of each go (Board)
        reset_squares();

        //If else statement to switch the player each round
        if(current_player == &player1) current_player = &player2;
        else if(current_player == &player2)  current_player = &player1;

        //Function to print the score board (Output)
        print_score(&player1, &player2);

        //Function to print the board itself (Output)
        print_board();

        //If else to check if the player currently playing has any valid moves. (The function print valid returns the number of valid squares.) (Output)
        if(print_valid(current_player->colour) != 0) {
            //Set a bool in the player structure which stores if the player passed last go.
            current_player->passed_last_go = false;
            //Function to get the square the player wants to place in. (User Input)
            get_user_input(current_player->colour);
        }
        else {
            //If the player has no squares they have to pass.
            printf("You have to pass.(Enter p to pass):\n");

            //Had to flush the standard input for a reason I'm not sure about. (Skipped the scanf otherwise)
            fflush(stdin);

            //Makes the player put in p to pass because its in the specification.
            scanf("%c", &pass);

            //Stores the player passed last go in the player structure
            current_player->passed_last_go = true;
        }

        //Checks if the game should continue based on if both players had to pass in the last two rounds or if the board is full
        if((player1.passed_last_go && player2.passed_last_go) || check_if_all_squares_are_full(player1, player2)) game = false;
    }

    //When the game ends it prints this and the scoreboard.
    printf("\nGame Has Ended\n");
    print_score(&player1, &player2);

    //Based on the score it prints whos the winner.
    if(player1.score > player2.score) printf("%s has won.\n", player1.name);
    if(player1.score < player2.score) printf("%s has won.\n", player2.name);
    if(player1.score == player2.score) printf("It has been a draw, no ones a winner.\n");

    //Write the result to a file.
    writetofile(player1, player2);

    exit(1);
}
