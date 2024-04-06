// Copyright 2023 Nika Ashtari
// This file is part of the PTree program.
// All rights reserved.


#include "PTree.h"

//  PTree class constructor, sets the initial values for the depth,
//  base rectangle, render target, and color
//  Creating squares by deriving from RectangleShape class
PTree::PTree(int depth, sf::RectangleShape base,
sf::RenderTarget& window, sf::Color color)
    : depth(depth), base(base), window(window), color(color)
{}

void PTree::pTree() {
    // Set the fill color of the base rectangle
    base.setFillColor(color);
    // Draw the base rectangle
    window.draw(base);

    // If the depth is greater than 0, then create the left and right rectangles
    if (depth > 0) {
        // Create a copy of the base rectangle for the left and right rectangles
        sf::RectangleShape left = base;
        sf::RectangleShape right = base;

        // Get the size of the base rectangle
        auto size = base.getSize();
        auto offset = base.getTransform();

        //  Resize the left and right rectangles
        //  to be smaller than the base rectangle
        //  Also used static cast to float to avoid errors
        left.setSize(size * static_cast<float>((std::sqrt(2.0) / 2.0)));
        right.setSize(size * static_cast<float>((std::sqrt(2.0) / 2.0)));

        // Set the origin of the left rectangle to be at the bottom left corner
        left.setOrigin(0, left.getSize().y);
        //  Set the origin of the right rectangle
        //  to be at the bottom right corner
        right.setOrigin(right.getSize());

        //  Set the position of the left rectangle
        //  to be at the bottom left corner
        left.setPosition(offset.transformPoint({ 0, 0 }));
        //  Set the position of the right rectangle
        //  to be at the bottom right corner
        right.setPosition(offset.transformPoint({ size.x, 0 }));

        // Rotate the left rectangle by -45 degrees
        left.rotate(-45);
        // Rotate the right rectangle by 45 degrees
        right.rotate(45);

        // Change the color based on the depth of the current iteration
        switch (depth) {
        case 4:
            color = sf::Color::Green;
            break;
        case 3:
            color = sf::Color::Yellow;
            break;
        case 2:
            color = sf::Color(255, 165, 0);
            break;
        case 1:
            color = sf::Color(255, 0, 0, 128);
            break;
        default:
            break;
        }

        //  Recursively call the pTree function for the
        //  left rectangle with a decreased depth
        PTree leftTree(depth - 1, left, window, color);
        leftTree.pTree();
        //  Recursively call the pTree function for the
        //  right rectangle with a decreased depth
        PTree rightTree(depth - 1, right, window, color);
        rightTree.pTree();
    }
}  //  End of PTree.cpp
