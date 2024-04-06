// Copyright 2022 Nika Ashtari
// This file is part of the Sokoban game.
// All rights reserved.


#include "Sokoban.h"
#include <iostream>

float scale = 50.0;  // Define the scale factor


/*Sokoban constructor that calls loadTexture 
when an object of sokoban is created*/ 
Sokoban::Sokoban() {
    loadTextures();
}


/*movePlayer function that first finds location of player based on game level 
  symbols. Uses Direction enum to calculate player position. Keeps player within
  bounds of the game level.*/

void Sokoban::movePlayer(Direction dir) {
    if (isWon()) {
        return;
    }
    // Get player position


    int playerX = -1, playerY = -1;
    bool foundPlayer = false;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == '@') {
                playerX = j;
                playerY = i;
                foundPlayer = true;
                break;
            }
        }
        if (foundPlayer) {
            break;
        }
    }


    // Calculate new player position based on direction


    int newPlayerX = playerX;
    int newPlayerY = playerY;
    switch (dir) {
        case Direction::UP:
            newPlayerY--;
            break;
        case Direction::DOWN:
            newPlayerY++;
            break;
        case Direction::LEFT:
            newPlayerX--;
            break;
        case Direction::RIGHT:
            newPlayerX++;
            break;
    }

    // Check if new player position is valid

    if (newPlayerX < 0 || newPlayerX >= gridSize || newPlayerY < 0
    || newPlayerY >= gridSize || grid[newPlayerY][newPlayerX] == '#') {
        // Invalid move - do nothing
        return;
    }

    // Check if new player position is a storage location
    bool leavingStorageLocation = false;
    if (grid[newPlayerY][newPlayerX] == '.') {
        // Player is moving onto a storage location
        grid[newPlayerY][newPlayerX] = '@';
        grid[playerY][playerX] = '.';
    } else if (grid[newPlayerY][newPlayerX] == 'a') {
        // Player is moving onto a storage location
        grid[newPlayerY][newPlayerX] = '@';
        grid[playerY][playerX] = '.';
        leavingStorageLocation = true;
    } else if (leavingStorageLocation) {
        grid[playerY][playerX] = 'a';
        setStorageLocations();
     } else if (grid[newPlayerY][newPlayerX] == 'A') {
        // Player is moving a box onto a storage location
        // Check if the new position of the box is valid
        int newBoxX = newPlayerX + (newPlayerX - playerX);
        int newBoxY = newPlayerY + (newPlayerY - playerY);
        if (newBoxX < 0 || newBoxX >= gridSize ||
        newBoxY < 0 || newBoxY >= gridSize ||
        grid[newBoxY][newBoxX] == '#' || grid[newBoxY][newBoxX] == 'A'
        || grid[newBoxY][newBoxX] == '1') {
            // Invalid move - do nothing
            return;
        }
        // Move the box to the new position
        grid[newBoxY][newBoxX] = 'A';
        grid[newPlayerY][newPlayerX] = '@';
        if (grid[playerY][playerX] == '+') {
            grid[playerY][playerX] = 'a';
        } else {
            grid[playerY][playerX] = '.';
        }
    } else if (grid[playerY][playerX] == '+') {
        // Player is leaving a storage location
        grid[playerY][playerX] = 'a';
        leavingStorageLocation = true;
    }

    setStorageLocations();

    // Update player sprite
    player.setPosition(newPlayerX * 50, newPlayerY * 50);

    // Update player texture based on direction
    player.setTexture(getTexture(dir));
     if (isWon()) {
        winning.play();
    }
}

// Overload the >> operator to read in a Sokoban level from a stream
std::istream& operator>>(std::istream& stream, Sokoban& sokoban) {
    int width, height;
    stream >> width >> height;
    sokoban.gridSize = width;
    sokoban.grid = new char*[sokoban.gridSize];
    sokoban.originalGrid = new char*[sokoban.gridSize];

    for (int i = 0; i < sokoban.gridSize; i++) {
        sokoban.grid[i] = new char[sokoban.gridSize];
        sokoban.originalGrid[i] = new char[sokoban.gridSize];

        for (int j = 0; j < sokoban.gridSize; j++) {
            stream >> sokoban.grid[i][j];
            sokoban.originalGrid[i][j] = sokoban.grid[i][j];
        }
    }
    return stream;
}

  void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states)const  {
    // creating copies of each sprite in order to be modified by setPosition
    sf::Sprite environment = this->environment;
    sf::Sprite wall = this->wall;
    sf::Sprite player = this->player;
    sf::Sprite box = this->box;
    sf::Sprite storage = this->storage;
    sf::Sprite floor = this->floor;
    // Draw background
    target.draw(environment, states);


    // Draw floors
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == '.') {
                floor.setPosition(j * 50, i * 50);
                target.draw(floor, states);
            }
        }
    }

  for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == 'a') {
                storage.setPosition(j * scale, i * scale);
                target.draw(storage, states);
            } else if (grid[i][j] == '1') {
                box.setPosition(j * scale, i * scale);
                target.draw(box, states);
            }
        }
    }


    // Draw boxes
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == 'A') {
                box.setPosition(j * 50, i * 50);
                target.draw(box, states);
            } else if (grid[i][j] == '1') {
                box.setPosition(j * 50, i * 50);
                target.draw(box, states);
            }
        }
    }

    // Draw player
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == '@') {
                player.setPosition(j * 50, i * 50);
                target.draw(player, states);
            }
        }
    }


  // Draw walls
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == '#') {
                wall.setPosition(j * 50, i * 50);
                target.draw(wall, states);
            }
        }
    }
  }

  // getter function for player sprite with default texture
  sf::Sprite& Sokoban:: getPlayer() {
        return player;
    }

/* Loads the textures, sounds, text, etc for the game
and sets them for the corresponding sprites.*/
// Uses lambda expression
void Sokoban::loadTextures() {
    // lambda function to load textures and set them for a given sprite
    auto setTexture = [](sf::Sprite& sprite,
    sf::Texture& texture, const std::string& filename) {
    if (texture.loadFromFile(filename)) {
        sprite.setTexture(texture);
    }
};

    // Load textures and set them for each sprite
    setTexture(environment, environmentTexture, "environment_03.png");
    setTexture(floor, floorTexture, "ground_01.png");
    setTexture(wall, wallTexture, "block_06.png");
    setTexture(box, boxTexture, "crate_03.png");
    setTexture(player, playerTexture, "player_05.png");
    setTexture(storage, storageTexture, "ground_04.png");
    setTexture(playerUp, playerUpTexture, "player_08.png");
    setTexture(playerRight, playerRightTexture, "player_17.png");
    setTexture(playerLeft, playerLeftTexture, "player_20.png");

    // Load sound buffer
    if (buffer.loadFromFile("winning.wav")) {
        winning.setBuffer(buffer);
    }

    // Load font
    if (font.loadFromFile("arial.ttf")) {
        winText.setFont(font);
    }

    // Set properties for winText
    winText.setString("You win! Press R to Restart.");
    winText.setCharacterSize(24);
    winText.setFillColor(color);
    winText.setPosition(10, 10);
}


// function to set the player texture based on direction
const sf::Texture& Sokoban::getTexture(Direction direction) const {
    switch (direction) {
        case Direction::UP:
            return playerUpTexture;
        case Direction::LEFT:
            return playerLeftTexture;
            break;
        case Direction::RIGHT:
            return playerRightTexture;
            break;
        default:
            return playerTexture;
            break;
    }
}

/* function to help solve a bug where storage tile would 
disappear when player steps off of it*/ 
void Sokoban::setStorageLocations() {
    // Clear storage locations
    storageLocations.clear();

    // Update storage locations based on original grid
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (originalGrid[i][j] == 'a') {
                if (grid[i][j] == '.') {
                    grid[i][j] = 'a';
                    storage.setTexture(storageTexture);
                    storage.setPosition(j * 50, i * 50);
                    storageLocations.push_back(storage);
                } else if (grid[i][j] == 'a') {
                    storage.setTexture(storageTexture);
                    storage.setPosition(j * 50, i * 50);
                    storageLocations.push_back(storage);
                }
            }
        }
    }
}

/* checks to see if the player has won based on 
the conditions outlined in instructions*/ 
bool Sokoban::isWon() const {
    int boxesOnStorage = 0;
    int storageAreas = 0;
    int boxes = 0;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (originalGrid[i][j] == 'a') {
                storageAreas++;
                if (grid[i][j] == 'A') {
                    boxesOnStorage++;
                }
            }
            if (grid[i][j] == 'A') {
                boxes++;
            }
        }
    }

    if (boxes > storageAreas) {
        return boxesOnStorage == storageAreas;
    } else {
        return boxesOnStorage == boxes;
    }
}
// end of Sokoban.cpp
