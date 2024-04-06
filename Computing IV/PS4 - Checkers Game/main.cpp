// Copyright 2023 Nika Ashtari
// This file is part of the Checkers program.
// All rights reserved.

#include "Checkers.h"
#include <SFML/Graphics.hpp>

int main() {
sf::RenderWindow window(sf::VideoMode(BOARD_SIZE *CELL_SIZE,
BOARD_SIZE * CELL_SIZE), "Checkers");

// Loading textures
sf::Texture redPawnTexture;
if (!redPawnTexture.loadFromFile("redpawn.png")) {
    std::cerr << "Could not locate file! Quitting...";
    exit(0);
}

sf::Texture redKingTexture;
if (!redKingTexture.loadFromFile("redking.png")) {
    std::cerr << "Could not locate file! Quitting...";
    exit(0);
}

sf::Texture blackPawnTexture;
if (!blackPawnTexture.loadFromFile("blackpawn.png")) {
    std::cerr << "Could not locate file! Quitting...";
    exit(0);
}

sf::Texture blackKingTexture;
if (!blackKingTexture.loadFromFile("blackking.png")) {
    std::cerr << "Could not locate file! Quitting...";
    exit(0);
}

// Create checkers object
Checkers checkers(redPawnTexture, blackPawnTexture);

checkers.sortPiecesByPlayer();

    std::vector<sf::RectangleShape> cells;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cells.push_back(checkers.createCell(i, j));
        }
    }

    // Create the initial checkers pieces using the
    // textures for red and black pawns
    std::vector<Checkers::Piece> pieces = checkers.createPieces(redPawnTexture,
    blackPawnTexture);

    // Set the starting player as player 2 (Black)
    int currentPlayer = 2;

    // Initialize a pointer to store the selected piece,
    // initially set to nullptr
    Checkers::Piece* selectedPiece = nullptr;

    // Create a rectangle shape to indicate the selected piece on the board
    sf::RectangleShape selectedRect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    // Set the fill color to semi-transparent yellow
    selectedRect.setFillColor(sf::Color(255, 255, 0, 100));

    // Initialize a boolean variable to control the
    // visibility of the selected rectangle
    bool showSelectedRect = false;


    int winner = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
                int x = event.mouseButton.x / CELL_SIZE;
                int y = event.mouseButton.y / CELL_SIZE;

                if (selectedPiece == nullptr) {
                    selectedPiece = checkers.selectPiece(pieces,
                    currentPlayer, x, y);
                    if (selectedPiece != nullptr) {
                        selectedRect.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                        showSelectedRect = true;
                    }
                } else {
                    int x1 = selectedPiece->sprite.getPosition().x / CELL_SIZE;
                    int y1 = selectedPiece->sprite.getPosition().y / CELL_SIZE;
                    bool isJump = false;

                    if (checkers.isValidMove(pieces, currentPlayer,
                    x1, y1, x, y, isJump)) {
                        checkers.movePiece(*selectedPiece, x, y);
                        if (isJump) {
                            checkers.capturePiece(pieces, x1, y1, x, y);
                        }

                        if (!selectedPiece->isKing && ((currentPlayer == 1
                        && y == BOARD_SIZE - 1)
                        || (currentPlayer == 2 && y == 0))) {
                            if (currentPlayer == 1 && y == BOARD_SIZE - 1 &&
                            selectedPiece->sprite.getPosition().x /
                            CELL_SIZE == x) {
                                checkers.promoteToKing(*selectedPiece,
                                currentPlayer == 1 ?
                                redKingTexture : blackKingTexture);
                            } else if (currentPlayer == 2 && y == 0 &&
                            selectedPiece->sprite.getPosition().x /
                            CELL_SIZE == x) {
                                checkers.promoteToKing(*selectedPiece,
                                currentPlayer == 1 ?
                                redKingTexture : blackKingTexture);
                            }
                        }

                        if (isJump) {
                            // Check if the piece can jump again
                            if (checkers.canJump(pieces, currentPlayer,
                            selectedPiece)) {
                                // If yes, keep piece and highlight it
                                showSelectedRect = true;
                            } else {
                                // If not, switch to the other player
                                currentPlayer = 3 - currentPlayer;
                                selectedPiece = nullptr;
                                showSelectedRect = false;
                            }
                        } else {
                            // If it's not a jump, switch to the other player
                            currentPlayer = 3 - currentPlayer;
                            selectedPiece = nullptr;
                            showSelectedRect = false;
                        }
                    } else {
                        selectedPiece = nullptr;
                        showSelectedRect = false;
                    }
                }
            }
        }

        window.clear();
        for (const auto& cell : cells) {
            window.draw(cell);
        }
        if (showSelectedRect) {
            window.draw(selectedRect);
        }


        window.clear();
        for (const auto& cell : cells) {
            window.draw(cell);
        }
        if (showSelectedRect) {
            window.draw(selectedRect);
        }
        for (const auto& piece : pieces) {
            window.draw(piece.sprite);
        }
        window.display();

        // Check for a winner after updating the window
        winner = checkers.checkForWinner(pieces);
        if (winner != 0) {
            window.clear();
            for (const auto& cell : cells) {
                window.draw(cell);
            }
            for (const auto& piece : pieces) {
                window.draw(piece.sprite);
            }
            checkers.drawWinnerText(window, winner);
            window.display();
                       sf::sleep(sf::seconds(5));
            window.close();
        }
    }

    return 0;
}
