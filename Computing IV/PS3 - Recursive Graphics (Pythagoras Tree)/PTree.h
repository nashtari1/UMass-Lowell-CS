// Copyright 2023 Nika Ashtari
// This file is part of the PTree program.
// All rights reserved.


#ifndef PTREE_H_
#define PTREE_H_

#include <cmath>
#include <SFML/Graphics.hpp>


//  Definition of the PTree class
class PTree {
 public:
    //  Constructor for the PTree class
    PTree(int depth, sf::RectangleShape base,
    sf::RenderTarget& window, sf::Color color);  // NOLINT(runtime/references)

    //  Function that recursively draws the tree
    void pTree();

 private:
    //  Member variables for the class
    int depth;
    sf::RectangleShape base;
    sf::RenderTarget& window;
    sf::Color color;
};  //  End of PTree.h

#endif  // PTREE_H_
