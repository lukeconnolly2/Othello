#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "board.h"



//Structure for player
typedef struct player {
    //Hold players name
    char name[50];
    //Int to hold each players score.
    int score;
    //Char to store each players colour.
    char colour;

    //To store if player passed last round.
    bool passed_last_go;
}player;




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

//Function to check if a specific square is a valid choice.
bool is_valid(char colour_playing, int x, int y){
    //Using the colour of the player currently making a move we figure out the colour not playing.
    char colour_against;
    if(colour_playing == 'B') colour_against = 'W';
    else colour_against = 'B';

    bool valid = false;

    board[x][y].valid_directions.top_left = false;
    board[x][y].valid_directions.up = false;
    board[x][y].valid_directions.top_right = false;
    board[x][y].valid_directions.right = false;
    board[x][y].valid_directions.bottom_right = false;
    board[x][y].valid_directions.down = false;
    board[x][y].valid_directions.bottom_left = false;
    board[x][y].valid_directions.left = false;

    //check upwards on the grid from the x y position piped in.
    if(x != 0){
        //if the colour above said square is the opposing colour
        if(board[x-1][y].colour == colour_against) {
            //if its the case we check the squares after in the same direction for another one of the same colour as
            //currently playing to make a line.
            for (int i = x - 1; i > -1; i--) {
                if (board[i][y].colour == colour_against) continue;
                if (board[i][y].colour == ' ') break;
                if (board[i][y].colour == colour_playing){
                    board[x][y].valid_directions.up = true;
                    valid = true;
                }
            }
        }
    }
    //rest of the checks use the same logic, just manipulating x, y in different ways.


    //check down
    if(x != 7){
        if(board[x+1][y].colour == colour_against) {
            for (int i = x + 2; i < 8; i++) {
                if (board[i][y].colour == colour_against) continue;
                if (board[i][y].colour == ' ') break;
                if (board[i][y].colour == colour_playing) {
                    board[x][y].valid_directions.down = true;
                    valid = true;
                }
            }
        }
    }

    //check left
    if(y != 0){
        if(board[x][y-1].colour == colour_against) {
            for (int i = y - 2; i > -1; i--) {
                if (board[x][i].colour == colour_against) continue;
                if (board[x][i].colour == ' ') break;
                if (board[x][i].colour == colour_playing) {
                    board[x][y].valid_directions.left = true;
                    valid = true;
                }
            }
        }
    }

    //check right
    if(y != 7){
        if(board[x][y+1].colour == colour_against) {
            for (int i = y + 2; i < 8; i++) {
                if (board[x][i].colour == colour_against) continue;
                if (board[x][i].colour == ' ') break;
                if (board[x][i].colour == colour_playing) {
                    board[x][y].valid_directions.right = true;
                    valid = true;
                }
            }
        }
    }

    //check diagonal top right
    if(x!=0 && y!= 7){
        if(board[x-1][y+1].colour == colour_against){
            for(int i = 2; x-i > -1 && y+i < 8; i++){
                if(board[x-i][y+i].colour == colour_against) continue;
                if(board[x-i][y+i].colour == ' ')  break;
                if(board[x-i][y+i].colour == colour_playing){
                    board[x][y].valid_directions.top_right = true;
                    valid = true;
                }
            }
        }
    }

    //check diagonal top left.
    if(x!=0 && y!=0){
        if(board[x-1][y-1].colour == colour_against){
            for(int i = 2; x-i > -1 && y-i > -1; i++){
                if(board[x-i][y-i].colour == colour_against) continue;
                if(board[x-i][y-i].colour == ' ')  break;
                if(board[x-i][y-i].colour == colour_playing){
                    board[x][y].valid_directions.top_left = true;
                    valid = true;
                }
            }
        }
    }

    //check bottom left.
    if(x!=7 && y!=0){
        if(board[x+1][y-1].colour == colour_against){
            for(int i = 2; x+i < 8  && y-i > -1; i++){
                if(board[x+i][y-i].colour == colour_against) continue;
                if(board[x+i][y-i].colour == ' ')  break;
                if(board[x+i][y-i].colour == colour_playing) {
                    board[x][y].valid_directions.bottom_left = true;
                    valid = true;
                }
            }
        }
    }

    //check bottom right.
    if(x!=7 && y!=7){
        if(board[x+1][y+1].colour == colour_against){
            for(int i = 2; x+i < 8  && y+i < 8; i++){
                if(board[x+i][y+i].colour == colour_against) continue;
                if(board[x+i][y+i].colour == ' ')  break;
                if(board[x+i][y+i].colour == colour_playing){
                    board[x][y].valid_directions.bottom_right = true;
                    valid = true;
                }
            }
        }
    }
    return valid;
}
void fill_lines(char colour_playing, int x, int y) {
    //Using the colour of the player currently making a move we figure out the colour not playing.
    char colour_against;
    if (colour_playing == 'B') colour_against = 'W';
    else colour_against = 'B';

    if (board[x][y].valid_directions.up) {
        for (int i = x - 1; i > -1; i--) {
            if (board[i][y].colour == colour_against) board[i][y].colour = colour_playing;
            else if (board[i][y].colour == colour_playing) break;
        }
    }

    if(board[x][y].valid_directions.down){
        for (int i = x+1; i < 8; i++) {
            if (board[i][y].colour == colour_against) board[i][y].colour = colour_playing;
            else if(board[i][y].colour == colour_playing)  break;
        }
    }

    if(board[x][y].valid_directions.left){
        for (int i = y-1; i > -1; i--) {
            if (board[x][i].colour == colour_against) board[x][i].colour = colour_playing;
            else if(board[x][i].colour == colour_playing)  break;
        }
    }

    if(board[x][y].valid_directions.right){
        for (int i = y+1; i < 8; i++) {
            if (board[x][i].colour == colour_against) board[x][i].colour = colour_playing;
            else if(board[x][i].colour == colour_playing)  break;
        }
    }

    if(board[x][y].valid_directions.top_left){
        for(int i = 1; x-i > -1 && y-i > -1; i++) {
            if (board[x-i][y-i].colour == colour_against) board[x-i][y-i].colour = colour_playing;
            else if(board[x-i][y-i].colour == colour_playing)  break;
        }
    }

    if(board[x][y].valid_directions.top_right){
        for(int i = 1; x-i > -1 && y+i < 8; i++) {
            if (board[x-i][y+i].colour == colour_against) board[x-i][y+i].colour = colour_playing;
            else if(board[x-i][y+i].colour == colour_playing)  break;
        }
    }

    if(board[x][y].valid_directions.bottom_left){
        for(int i = 1; x+i < 8 && y-i > -1; i++) {
            if (board[x+i][y-i].colour == colour_against) board[x+i][y-i].colour = colour_playing;
            else if(board[x+i][y-i].colour == colour_playing)  break;
        }
    }

    if(board[x][y].valid_directions.bottom_right){
        for(int i = 1; x+i < 8 && y+i < 8; i++) {
            if (board[x+i][y+i].colour == colour_against) board[x+i][y+i].colour = colour_playing;
            else if(board[x+i][y+i].colour == colour_playing)  break;
        }
    }
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
                    printf("%c%d ", y + 65, x + 1);
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

int decode_user_choice_y(char userchoice[]){
    return (int) userchoice[0] - 65;
}
int decode_user_choice_x(char userchoice[]){
    return (int) userchoice[1] - 49;
}

bool input_to_board(char colour, int x, int y){
    if(board[x][y].valid){
        board[x][y].colour = colour;
        fill_lines(colour, x, y);
        return true;
    }
    else return false;
}

void get_user_input(char colour){
    char  userchoice[3];
    do{
        printf("\nEnter square:\n");
        scanf("%s", userchoice);
    }
    while(!input_to_board(colour, decode_user_choice_x(userchoice), decode_user_choice_y(userchoice)));
}

void writetofile(player player1, player player2) {

    FILE *fp;

    fp = fopen("othello-results.txt", "a");
    if(fp == NULL)   fopen("othello-results.txt", "W");

    char line[2000];
    if(player1.score > player2.score) fprintf(fp, "%s has a score of %d and %s has a score of %d meaning %s has won\n", player1.name, player1.score, player2.name, player2.score, player1.name);
    if(player1.score < player2.score) fprintf(fp, "%s has a score of %d and %s has a score of %d meaning %s has won\n", player1.name, player1.score, player2.name, player2.score, player2.name);
    if(player1.score == player2.score) fprintf(fp, "%s has a score of %d and %s has a score of %d meaning its a draw\n", player1.name, player1.score, player2.name, player2.score);


    fclose(fp);

    printf("This has been written to othello-results.txt\n");
}

int main() {
    //Initialise player 1 and 2 structs.
    player player1 = {"", 0, 'B'};
    player player2 = {"", 0, 'W'};
    player* current_player = &player2;

    bool game = true;
    char colours[3] = {'B', 'W'};
    int i=1;

    fflush(stdout);
    initialise_board();
    get_player_names(&player1, &player2);
    fflush(stdout);
    while(game) {
        if(current_player == &player1) current_player = &player2;
        else if(current_player == &player2)  current_player = &player1;

        print_score(&player1, &player2);
        fflush(stdout);
        print_board();
        fflush(stdout);

        if(print_valid(current_player->colour) != 0) {
            current_player->passed_last_go = false;
            get_user_input(current_player->colour);
            fflush(stdout);
        }
        else {
            printf("You have to pass.\n");
            sleep(5);
            current_player->passed_last_go = true;
            fflush(stdout);
        }

        if(player1.passed_last_go && player2.passed_last_go) game = false;
        fflush(stdout);
    }

    printf("\nGame Has Ended\n");
    print_score(&player1, &player2);

    if(player1.score > player2.score) printf("%s has won.\n", player1.name);
    if(player1.score < player2.score) printf("%s has won.\n", player2.name);
    if(player1.score == player2.score) printf("It has been a draw, no ones a winner.\n");

    writetofile(player1, player2);

    exit(69);
    return 0;
}
