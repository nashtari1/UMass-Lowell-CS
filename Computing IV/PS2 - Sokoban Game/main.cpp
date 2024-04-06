// Copyright 2022 Nika Ashtari
// This file is part of the Sokoban game.
// All rights reserved.

#include <SFML/Graphics.hpp>
#include "Sokoban.h"

int main(int argc, char* argv[]) {
     /* Check that the program was executed with the correct number of 
     arguments. Can use any .lvl file for the Sokoban levels*/ 
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
  // Extract the filename from the command line arguments
  std::string filename(argv[1]);

    // Check that the file has the correct extension
    if (filename.substr(filename.size() - 4) != ".lvl") {
        std::cout <<
        "Error: Invalid file extension. Please specify a .lvl file.";
        std::cout << std::endl;
        return 1;
    }

    // Open the level file
    std::ifstream levelFile(filename);

    // Check that the file was successfully opened
    if (!levelFile) {
        std::cout << "Error: Failed to open level file "
        << filename << std::endl;
        return 1;
    }

    // Create a Sokoban game object and load textures
    Sokoban sokoban;
    sokoban.loadTextures();

    // Load the level file into the game object using the stream operator
    levelFile >> sokoban;

    // Create a window with the correct size and title


    sf::RenderWindow window
    (sf::VideoMode
    (sokoban.gridSize * 50,
    sokoban.gridSize * 50), "Sokoban");
    // Get a reference to the player sprite
    sf::Sprite& player = sokoban.getPlayer();
while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            // Move the player in response to keyboard events
            switch (event.key.code) {
                case sf::Keyboard::W:
                sokoban.movePlayer(Direction::UP);
                player.setTexture(sokoban.getTexture(Direction::UP));
                break;
                case sf::Keyboard::S:
                    sokoban.movePlayer(Direction::DOWN);
                    player.setTexture
                    (sokoban.getTexture(Direction:: DOWN));
                    break;
                case sf::Keyboard::A:
                    sokoban.movePlayer
                    (Direction::LEFT);
                    player.setTexture
                    (sokoban.getTexture(Direction::LEFT));
                    break;
                case sf::Keyboard::D:
                    sokoban.movePlayer(Direction::RIGHT);
                    player.setTexture(sokoban.getTexture(Direction::RIGHT));
                    break;
                case sf::Keyboard::R:
                    std::cout << "restarting..."<< std::endl;
                    levelFile.clear();
                levelFile.seekg(0);
                    levelFile >> sokoban;
                    player.setTexture
                    (sokoban.getTexture(Direction:: DOWN));
                    break;
                default:
                    break;}

                /*Clear the window, draw the game object, 
                and display the updated frame*/ 
                window.clear();
                window.draw(sokoban);
                window.display();
            }
        }

        window.clear();
        window.draw(sokoban);  // draw the grid at the start of the while loop
        // check to display win message if player has won
        if (sokoban.isWon()) {
        // Draw the win text
        window.draw(sokoban.winText);
        }
        window.display();
    }
    return 0;
}

// end of main
