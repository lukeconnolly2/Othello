#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "board.h"
#include "user_input.h"
#include "output.h"


int main() {
    //Initialise player 1 and 2 structs.
    player player1 = {"", 0, 'B'};
    player player2 = {"", 0, 'W'};
    player* current_player = &player2;

    bool game = true;

    initialise_board();
    get_player_names(&player1, &player2);


    while(game) {
        if(current_player == &player1) current_player = &player2;
        else if(current_player == &player2)  current_player = &player1;

        print_score(&player1, &player2);
        print_board();

        if(print_valid(current_player->colour) != 0) {
            current_player->passed_last_go = false;
            get_user_input(current_player->colour);
        }
        else {
            printf("You have to pass.\n");
            sleep(5);
            current_player->passed_last_go = true;
        }

        if((player1.passed_last_go && player2.passed_last_go) || check_if_all_squares_are_full()) game = false;
    }

    printf("\nGame Has Ended\n");
    print_score(&player1, &player2);

    if(player1.score > player2.score) printf("%s has won.\n", player1.name);
    if(player1.score < player2.score) printf("%s has won.\n", player2.name);
    if(player1.score == player2.score) printf("It has been a draw, no ones a winner.\n");

    writetofile(player1, player2);

    exit(1);
}
