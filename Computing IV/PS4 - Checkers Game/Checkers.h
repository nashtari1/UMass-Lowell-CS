// Copyright 2023 Nika Ashtari
// This file is part of the Checkers program.
// All rights reserved.

// This file contains the Checkers class which inherits from sf::Drawable
// and represents the Checkers game.

// The include guards prevent multiple inclusion of this header file.
#ifndef CHECKERS_H_
#define CHECKERS_H_

// The necessary libraries are included here.

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
// Constants are defined here.

// The size of the game board.
static constexpr int BOARD_SIZE = 8;
// The size of each cell on the board.
static constexpr int CELL_SIZE = 100;
// The Checkers class definition begins here.
class Checkers : public sf::Drawable {
 public:
    // Constructor for the Checkers class.
    Checkers(const sf::Texture& redPawnTexture,
             const sf::Texture& blackPawnTexture);

    // The Piece struct represents a checker piece.
    struct Piece {
        sf::Sprite sprite;  // The sprite for the piece.
        int player;  // The player who owns the piece.
        bool isKing;  // Whether the piece is a king.

        // Overloading the == operator to compare pieces.
        bool operator==(const Piece& other) const {
            return sprite.getPosition() == other.sprite.getPosition() &&
                   player == other.player &&
                   isKing == other.isKing;
        }
    };

    // Public member functions for the Checkers class.
    void movePiece(Piece& piece, int x, int y);
    void sortPiecesByPlayer();  // Sorts pieces by player.
    
    // Public member variables for the Checkers class.
    std::vector<sf::RectangleShape> m_squares;
    // The vector of pieces on the board.
    std::vector<Piece> m_pieces;

    // Helper functions for the Checkers class.
    sf::Texture loadTexture(const std::string& filename);  // Loads a texture.
    sf::RectangleShape createCell(int i, int j);  // Creates a cell.
    std::vector<Piece> createPieces(const sf::Texture& redPawnTexture,
                                    const sf::Texture& blackPawnTexture);  // Creates pieces.

    Piece* getPieceAt(std::vector<Piece>& pieces, int x, int y);  // Gets a piece at a location.
    // Checks if there's an opponent between two positions.
    bool hasOpponentBetween(std::vector<Piece>& pieces, int currentPlayer,
                            int x1, int y1, int x2, int y2);
    bool isValidMove(std::vector<Piece>& pieces, int currentPlayer, int x1,
                     int y1, int x2, int y2, bool& isJump);  // Validates a move.
    // Checks if there are valid moves.
    bool hasValidMoves(std::vector<Piece>& pieces, int currentPlayer);
    bool canJump(std::vector<Piece>& pieces, int currentPlayer,
                 const Piece* movingPiece = nullptr);
    bool isForcedCapture(std::vector<Piece>& pieces, int currentPlayer);

    Piece* selectPiece(std::vector<Piece>& pieces, int currentPlayer,
                       int x, int y);  // Selects a piece.
    void promoteToKing(Piece& piece, const sf::Texture&
    kingTexture);  // Promotes a piece to a king.
    int checkForWinner(const std::vector<Piece>&
    pieces);  // Checks for a winner.
    void drawWinnerText(sf::RenderWindow& window,
    int winner);  // Draws the winner text.
    void capturePiece(std::vector<Piece>& pieces, int x1,
    int y1, int x2, int y2);  // Captures a piece.

 private:
    // Overrides the draw function of sf::Drawable to draw the board and pieces.
    virtual void draw(sf::RenderTarget& target,  // NOLINT
    sf::RenderStates states) const;
};
#endif  // CHECKERS_H
