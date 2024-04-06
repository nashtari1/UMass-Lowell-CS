// Copyright 2023 Nika Ashtari
// This file is part of the PTree program.
// All rights reserved.


#include <SFML/Graphics.hpp>
#include "PTree.h"

// Main function to draw the Pythagoras Tree
int main(int, char* argv[]) {
    // Get the base and depth of the tree from command line arguments
    int base = std::stoi(argv[1]);
    int depth = std::stoi(argv[2]);

    // Create the render window based on 6L x 4L
    sf::RenderWindow window(sf::VideoMode(base * 6, base * 4),
    "Pythagoras Tree");

    // Create the base rectangle shape
    sf::RectangleShape original{{static_cast<float>(base),
    static_cast<float>(base)}};
    original.setPosition(base * 2.5, base * 3);

    // Set the color of the base rectangle shape
    sf::Color color(sf::Color(50, 153, 204));

    // Loop to handle events and draw the Pythagoras Tree
    while (window.isOpen()) {
        // Poll events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if the close event is triggered
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        // Clear the window
        window.clear();

        // Draw the Pythagoras Tree
        PTree pTree(depth, original, window, color);
        pTree.pTree();

        // Display the window
        window.display();
    }

    // Return 0 when the program ends
    return 0;
}  //  End of main
