// Copyright 2022 Nika Ashtari
// This file is part of the Sokoban game.
// All rights reserved.


#ifndef _HOME_NIKAASH_PS2A_SOKOBAN_H_
#define _HOME_NIKAASH_PS2A_SOKOBAN_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum class Direction { UP, DOWN, RIGHT, LEFT };

class Sokoban : public sf::Drawable {
 public:
    Sokoban();  // constructor
    void loadTextures();  // loads all textures for the game
void movePlayer(Direction direction);
    friend std::istream& operator>>(std::istream& stream, Sokoban& sokoban);

// size of the game level grid (number of tiles per row/column)
int gridSize;
    sf::Sprite& getPlayer();

// used to set the texture of the player according to their direction
const sf::Texture& getTexture(Direction direction) const;

// public object of text to display win text in the main while loop
sf::Text winText;

// function to check if the player has won
    bool isWon() const;

 private:
    void draw
    (sf::RenderTarget& target,  // NOLINT(runtime/references)
    sf::RenderStates states) const override;
    std::vector<sf::Sprite> storageLocations;
    void setStorageLocations();

    sf::Sprite environment;
    sf::Sprite floor;
    sf::Sprite player;
    sf::Sprite storage;
    sf::Sprite box;
    sf::Sprite wall;
    sf::Sprite playerUp;
    sf::Sprite playerRight;
    sf::Sprite playerLeft;

    sf::Texture playerTexture;
    sf::Texture floorTexture;
    sf::Texture wallTexture;
    sf::Texture boxTexture;
    sf::Texture storageTexture;
    sf::Texture environmentTexture;
    sf::Texture playerUpTexture;
    sf::Texture playerRightTexture;
    sf::Texture playerLeftTexture;
    sf::Texture texture;

    sf::Sound winning;
    sf::SoundBuffer buffer;

    sf::Font font;
    sf::Color color = sf::Color::Red;

    char** grid;
    char** originalGrid;
};

#endif  // _HOME_NIKAASH_PS2A_SOKOBAN_H_
