//
// Created by Luke on 11/04/2021.
//

#ifndef OTHELLO_VALIDATION_H
#define OTHELLO_VALIDATION_H
#include "board.h"


//Function to check if a specific square is a valid choice.
bool is_valid(char colour_playing, int x, int y){
    //Using the colour of the player currently making a move we figure out the colour not playing.
    char colour_against;
    if(colour_playing == 'B') colour_against = 'W';
    else colour_against = 'B';

    //If theres already a colour on this square return false.
    if(board[x][y].colour != ' ') return false;

    //Create a bool to remeber if the square is valid
    bool valid = false;

    //reset all the valid directions on the square.
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
            //Also made sure in for loop we never go outside the board.
            for (int i = x - 1; i > -1; i--) {
                //If its the opposing colour we check in the same direction again.
                if (board[i][y].colour == colour_against) continue;
                //if its a square with no colour the line is broken and its not a valid direction
                if (board[i][y].colour == ' ') break;
                //If it makes a line and gets back to a square with the same colour as the colour playing.
                if (board[i][y].colour == colour_playing){
                    //This direction is a valid direction and its set to true in the structure. (Comes in handy when filling the squares later).
                    board[x][y].valid_directions.up = true;
                    //Valid is set to true.
                    valid = true;
                }
            }
        }
    }
    //rest of the checks use the same logic, just manipulating x, y in different ways.

    //Checks down
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

    //Checks left
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

    //Check right
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

    //Check diagonal top right
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

    //Check diagonal top left.
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

    //Check bottom left.
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

    //Check bottom right.
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

//Fuction to fill in all the lines when a colour is inputted to a square.
void fill_lines(char colour_playing, int x, int y) {
    //Using the colour of the player currently making a move we figure out the colour not playing.
    char colour_against;
    if (colour_playing == 'B') colour_against = 'W';
    else colour_against = 'B';

    //Checks if the up direction is valid
    if (board[x][y].valid_directions.up) {
        //If so fill all the square of the opposing colour in this direction untill a square of the playing colour is found
        for (int i = x - 1; i > -1; i--) {
            if (board[i][y].colour == colour_against) board[i][y].colour = colour_playing;
            else if (board[i][y].colour == colour_playing) break;
        }
    }

    //Again the same logic for each direction, just manipulating x and y in different ways.
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

//Function to input onto a square on the board.
bool input_to_board(char colour, int x, int y){
    //if its a valid square.
    if(board[x][y].valid){
        //Set the board at that position to the playing colour
        board[x][y].colour = colour;
        //Fill all the lines it made.
        fill_lines(colour, x, y);

        return true;
    }
    else return false;
}




#endif //OTHELLO_VALIDATION_H
