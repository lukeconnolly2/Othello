Design Decisions:
    How I decided to implement the board:
        I decided to implement the board as an array of my square stucture.
        I was pretty happy with this as it allowed me to store a range of information about each square in a way which was easy to manage.
        I decide to store the squares colour, if it was a valid square on a given turn, and which directions were the valid directions in the square structure.
        This made the filling of the lines when a disk was entered on the board nice and handy as I already had if the square was valid, and in which
        directions were valid.
        This allowed me to skip running the validation code twice which definitely improved the codes run time.
        I stored the board as a global as I found myself passing it to almost every function and I got sick of it.

    How I implemented the players:
        I also implemented the players as structures also.
        This allowed me to store the players name, score, colour and whether they had passed the last turn all in a neat place.
        This came in handy on a good few occasions and I think it makes the code more readable.

    How I implemented the game logic:
        Square Validation:
            I spend most of the time of this project trying to figure out a good way to check if a square was valid.
            I eventually landed on 8 different for loops one for each direction which checks if the requirements for a line to be made in that direction was met.
            I looked a bit into path finding algorithms which led me to recursive solutions which I messed around for a while but I felt the for loops made
            it slightly more readable and found the recursive functions more difficult to work with.

        Filling in the lines made when a disk is entered into the board:
            I left the logic of this pretty easy as I put the valid direction booleans into each squares structure.
            After I checked each direction in my validation function I updated a structure of each bools so that any direction which made a valid line was true.
            So when filling the lines I just had to check if my validation function had found this direction to be valid and if so to fill it incrementally in this direction
            until a disk the same colour as the one just entered was found.

        Swapping players each turn:
            To implement this I decided to make a player pointer called current player.
            This would point to either player 1 or 2 on each turn and swap at the start of each turn.

        Check if the game is over:
            If both players had passed:
                To check if both players had passed in a row I added a bool to the player structure which would store if they passed on their last turn.
                Then I check at the end of each go whether this was true in both player structures, and if so end the game.

            If all the squares were full:
                To check if all the square were full I made a function loop which looped through all the squares and if any of them were free it would return false.
                If this returned true it would mean they were all full and the game would finish.


        Check if a player has to pass:
            To implement this functionality I made my function which printed out the valid squares return an int of how many valid squares there were.
            If this function returned 0 I knew the player had to pass.
            I made the user put in a p for pass anyways just to keep to the specification.
