//
// Created by Luke on 11/04/2021.
//

#ifndef OTHELLO_STRUCTURES_H
#define OTHELLO_STRUCTURES_H


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

//Structure to be put in the square structure to hold the directions which make it a valid square.
typedef struct directions{
    bool top_left;
    bool up;
    bool top_right;
    bool right;
    bool bottom_right;
    bool down;
    bool bottom_left;
    bool left;

}directions;

//Structure for each square
typedef struct square{
    //Boolean value to store if the square is valid to place in.
    bool valid;

    //Valid directions;
    directions valid_directions;

    //Char to store its colour.
    char colour;
}square;

//Make the board which is a 2D array of squares.
square board[8][8];


#endif //OTHELLO_STRUCTURES_H
