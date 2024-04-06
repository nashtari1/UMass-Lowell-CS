// Copyright 2023 Nika Ashtari
// This file is part of the Checkers program.
// All rights reserved.

#include "Checkers.h"

// Constructor for the Checkers class, initializes the
// board squares and pieces
Checkers::Checkers(const sf::Texture& redPawnTexture,
const sf::Texture& blackPawnTexture) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            m_squares.push_back(createCell(i, j));
        }
    }
    // Create checkers pieces
    m_pieces = createPieces(redPawnTexture, blackPawnTexture);
}

// Load texture from a file
sf::Texture Checkers::loadTexture(const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Error loading texture: " << filename << std::endl;
    }
    return texture;
}

// Create a cell (square) on the board
sf::RectangleShape Checkers::createCell(int i, int j) {
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);
    cell.setFillColor((i + j) % 2 == 0 ? sf::Color::Red : sf::Color::Black);
    return cell;
}

// Create checkers pieces with the given red and black pawn textures
std::vector<Checkers::Piece> Checkers::createPieces(const sf::Texture&
redPawnTexture,
const sf::Texture& blackPawnTexture) {
    std::vector<Piece> pieces;
    sf::Sprite sprite;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if ((i + j) % 2 == 1 && (j < 3 || j > 4)) {
                Piece piece;
                sprite.setTexture(j < 3 ? redPawnTexture : blackPawnTexture);
                piece.sprite = sprite;
                piece.sprite.setScale(CELL_SIZE /
                piece.sprite.getLocalBounds().width,
                CELL_SIZE / piece.sprite.getLocalBounds().height);
                piece.sprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                piece.player = (j < 3 ? 1 : 2);
                piece.isKing = false;
                pieces.push_back(piece);
            }
        }
    }
    return pieces;
}

Checkers::Piece* Checkers::getPieceAt(std::vector<Piece>&
pieces, int x, int y) {
    for (auto& piece : pieces) {
        if (x == piece.sprite.getPosition().x / CELL_SIZE &&
        y == piece.sprite.getPosition().y / CELL_SIZE) {
            return &piece;
        }
    }
    return nullptr;
}

// Check if there is an opponent's piece between the two positions
bool Checkers::hasOpponentBetween(std::vector<Piece>& pieces,
int currentPlayer, int x1, int y1, int x2, int y2) {
    if (abs(x1 - x2) != 2 || abs(y1 - y2) != 2) {
        return false;
    }

    int dx = (x1 + x2) / 2;
    int dy = (y1 + y2) / 2;
    Piece* piece = getPieceAt(pieces, dx, dy);
    return piece != nullptr && piece->player !=
    currentPlayer;
}

// Check if the player has any valid moves
bool Checkers::isValidMove(std::vector<Piece>& pieces,
int currentPlayer,
int x1, int y1, int x2, int y2, bool& isJump) {
    if (x2 < 0 || x2 >= BOARD_SIZE || y2 < 0 ||
    y2 >= BOARD_SIZE) {
        return false;
    }

    Piece* movingPiece = getPieceAt(pieces, x1, y1);
    if (movingPiece->player != currentPlayer) {
        return false;
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    if (!movingPiece->isKing && ((currentPlayer == 1
    && dy < 0)
    || (currentPlayer == 2 && dy > 0))) {
        return false;
    }

    Piece* targetPiece = getPieceAt(pieces, x2, y2);
    if (targetPiece != nullptr) {
        return false;
    }

    if (abs(dx) == 1 && abs(dy) == 1 && !isJump) {
        return true;
    }

    if (abs(dx) == 2 && abs(dy) == 2 &&
    hasOpponentBetween(pieces, currentPlayer, x1,
    y1, x2, y2)) {
        isJump = true;
        return true;
    }

    return false;
}

// Check if the player has any valid moves based on rules
bool Checkers::hasValidMoves(std::vector<Piece>& pieces,
int currentPlayer) {
    for (const auto& piece : pieces) {
        if (piece.player == currentPlayer) {
            int x = piece.sprite.getPosition().x / CELL_SIZE;
            int y = piece.sprite.getPosition().y / CELL_SIZE;
            bool isJump = false;

            if (isValidMove(pieces, currentPlayer, x, y, x -
            1, y - 1, isJump) ||
                isValidMove(pieces, currentPlayer, x, y, x +
                1, y - 1, isJump) ||
                isValidMove(pieces, currentPlayer, x, y, x -
                1, y + 1, isJump) ||
                isValidMove(pieces, currentPlayer, x, y, x +
                1, y + 1, isJump) ||
                isValidMove(pieces, currentPlayer, x, y, x -
                2, y - 2, isJump) ||
                isValidMove(pieces, currentPlayer, x, y, x +
                2, y - 2, isJump) ||
                isValidMove(pieces, currentPlayer, x, y, x -
                2, y + 2, isJump) ||
                isValidMove(pieces, currentPlayer, x, y, x +
                2, y + 2, isJump)) {
                return true;
            }
        }
    }
    return false;
}

// Check if a player can jump based on rules
bool Checkers::canJump(std::vector<Piece>& pieces, int currentPlayer,
const Piece* movingPiece) {
    for (const auto& piece : pieces) {
        if (movingPiece == nullptr ? piece.player == currentPlayer :
        piece == *movingPiece) {
            int x = piece.sprite.getPosition().x / CELL_SIZE;
            int y = piece.sprite.getPosition().y / CELL_SIZE;
            bool isJump = false;

            if (isValidMove(pieces, currentPlayer, x, y,
            x - 2, y - 2, isJump) ||
                isValidMove(pieces, currentPlayer, x, y,
                x + 2, y - 2, isJump) ||
                isValidMove(pieces, currentPlayer, x, y,
                x - 2, y + 2, isJump) ||
                isValidMove(pieces, currentPlayer, x, y,
                x + 2, y + 2, isJump)) {
                return true;
            }
        }
    }
    return false;
}

bool Checkers::isForcedCapture(std::vector<Piece>& pieces,
int currentPlayer) {
    return canJump(pieces, currentPlayer);
}

void Checkers::movePiece(Piece& piece, int x, int y) {
    piece.sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
}

// Select a piece at the specified position if it
// belongs to the current player
Checkers::Piece* Checkers::selectPiece(std::vector<Piece>& pieces,
int currentPlayer, int x, int y) {
    for (auto& piece : pieces) {
        if (x == piece.sprite.getPosition().x / CELL_SIZE &&
        y == piece.sprite.getPosition().y / CELL_SIZE && piece.player ==
        currentPlayer) {
            return &piece;
        }
    }
    return nullptr;
}

// Promote a piece to a king by changing its texture
void Checkers::promoteToKing(Piece& piece, const sf::Texture&
kingTexture) {
    piece.isKing = true;
    piece.sprite.setTexture(kingTexture);
    piece.sprite.setTextureRect(sf::IntRect(0, 0,
    kingTexture.getSize().x,
    kingTexture.getSize().y));
}

int Checkers::checkForWinner(const std::vector<Piece>& pieces) {
    int player1Pieces = 0;
    int player2Pieces = 0;

    for (const auto& piece : pieces) {
        if (piece.player == 1) {
            player1Pieces++;
        } else {
            player2Pieces++;
        }
    }

    if (player1Pieces == 0 || !hasValidMoves
    (const_cast<std::vector<Piece>&>(pieces), 1)) {
        return 2;
    }
    if (player2Pieces == 0 || !hasValidMoves
    (const_cast<std::vector<Piece>&>(pieces), 2)) {
        return 1;
    }

    return 0;
}

// Draw the winning text on the window based on win condition
void Checkers::drawWinnerText(sf::RenderWindow& window,
int winner) {
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    sf::Text winnerText;
    winnerText.setFont(font);
    winnerText.setCharacterSize(50);
    winnerText.setFillColor(sf::Color::White);
    winnerText.setStyle(sf::Text::Bold);
    winnerText.setString(winner == 1 ? "Red Player Wins!" :
    "Black Player Wins!");

    sf::FloatRect textRect = winnerText.getLocalBounds();
    winnerText.setOrigin(textRect.left + textRect.width / 2.0f,
    textRect.top + textRect.height / 2.0f);
    winnerText.setPosition(window.getSize().x / 2.0f,
    window.getSize().y / 2.0f);

    window.draw(winnerText);
}

// Capture the piece between two positions
void Checkers::capturePiece(std::vector<Piece>& pieces, int x1,
int y1, int x2, int y2) {
    int jumpedX = (x1 + x2) / 2;
    int jumpedY = (y1 + y2) / 2;
    Piece* jumpedPiece = getPieceAt(pieces, jumpedX, jumpedY);
    if (jumpedPiece != nullptr) {
        pieces.erase(std::remove_if(pieces.begin(), pieces.end(),
            [=](const Piece &piece) {
                return piece.sprite.getPosition() ==
                jumpedPiece->sprite.getPosition();
            }),
            pieces.end());
    }
}

void Checkers::draw(sf::RenderTarget& target,
sf::RenderStates states) const {
    // Draw the squares
    for (const auto& square : m_squares) {
        target.draw(square, states);
    }

    // Draw the pieces
    for (const auto& piece : m_pieces) {
        target.draw(piece.sprite, states);
    }
}

// Sort the pieces vector by player -
// this is the lambda expression
void Checkers::sortPiecesByPlayer() {
    // Sort the pieces based on player (player 1 first, then player 2)
    std::sort(m_pieces.begin(), m_pieces.end(),
    [](const Piece& a, const Piece& b) {
        return a.player < b.player;
    });
}
