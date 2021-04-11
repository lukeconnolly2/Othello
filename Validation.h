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

    if(board[x][y].colour != ' ') return false;

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



bool input_to_board(char colour, int x, int y){
    if(board[x][y].valid){
        board[x][y].colour = colour;
        fill_lines(colour, x, y);
        return true;
    }
    else return false;
}




#endif //OTHELLO_VALIDATION_H
