/**********************************************************************
 *  Checkers ps4b-readme.txt
 **********************************************************************/

Name: Nika Ashtarzadeh
Hours to complete assignment: 24+ hours

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
  In this assignment, the goal was to create a Checkers game that utilizes 
  a checkers game board and its pieces, along with handling user input for 
  selecting the pieces and moving pieces according to the game rules. The 
  implementation uses SFML to draw the game board and the pieces, handle 
  clicks to select pieces, and ensure that only valid pieces are selected. 
  There is also implementation to move pieces, capture other pieces by jumping, 
  promote to king, checking for win conditions, and declaring victory based on 
  the win condtions. These implementations follow the rules outlined in the instructions. 


  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
 The game board representation is a key data structure in the Checkers class. 
 It's a 2D vector of Piece enums, which allows for an efficient way to store 
 the game state. The Piece enum itself represents the different types 
 of pieces on the board (red pawn, red king, black pawn, black king, and empty) 
 and allows for simple logic when processing game state updates.

 I also have the Piece struct is a central part of this program because it represents a 
 single piece on the checkers board. The Piece struct contains three members:

sprite: A sf::Sprite object representing the image of the piece.
player: An integer indicating which player the piece belongs to.
isKing: A boolean indicating whether the piece has been promoted to a king.

The Piece struct is used throughout the program to store information about the 
pieces on the board, such as their position, player, and whether they are kings. 
It is also used to implement functions for moving and capturing pieces. 
The Piece struct is also used to create the initial set of pieces for a new game.


/**********************************************************************
 *  
 **********************************************************************/
 Selecting pieces: The selectPiece() method in the Checkers class updates 
 the selected piece based on the tile coordinates provided. If the clicked 
 tile contains a piece, it is selected; otherwise, the selected piece is deselected.
 The current design of the objects do not require the use of smart pointers.
 The method takes two integer arguments, tileX and tileY, representing the tile 
 coordinates of the user's click on the game board. These coordinates are provided 
 by the CheckersController class after converting the pixel coordinates of the 
 click to tile coordinates.

 Code:
 void Checkers::selectPiece(int tileX, int tileY) {
    if (board[tileX][tileY] != Piece::EMPTY) {
        selectedPiece = sf::Vector2i(tileX, tileY);
    } else {
        // Deselect if an empty space is clicked
        selectedPiece = sf::Vector2i(-1, -1);
    }
}

The central data structure used in the program is the Piece struct, 
which stores information about a game piece, including its sprite, player number, 
and whether it is a king. The Piece struct is used throughout the program to represent 
the game pieces on the board.

The operator== overload in the Piece struct compares two Piece objects for equality. 
It is used to check if two pieces occupy the same position on the game board, have the same player, 
and whether they are kings.

Smart pointers are not used in this program

Piece struct:

struct Piece {
    sf::Sprite sprite;
    int player;
    bool isKing;

    bool operator==(const Piece& other) const {
        return sprite.getPosition() == other.sprite.getPosition() &&
               player == other.player &&
               isKing == other.isKing;
    }
};



/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
I had a very challenging issue where jumping and capturing a piece would sometimes
result in other random pieces being captured on the board along with the intended capture. 
The issue was that my isValidMove function was also handling captures,
so I created a new capturePiece() function so I can just call it when necessary. 





/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
