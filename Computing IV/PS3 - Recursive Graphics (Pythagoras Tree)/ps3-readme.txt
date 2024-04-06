/**********************************************************************
 *  Recursive Graphics (Pythagoras Tree) ps3-readme.txt template
 **********************************************************************/

Name: Nika Ashtarzadeh
Hours to complete assignment: 10 Hours

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
The assignment was to develop a program that generates a Pythagoras Tree 
using recursion and the SFML library. The user can specify the base and 
depth of the tree as command line arguments.

The program is divided into three parts: the main file, PTree.cpp, and 
PTree.h. The main file sets up the window and creates instances of the 
PTree class. The PTree class is responsible for most of the program including
drawing the tree, using recursion to generate the squares at each level of the tree,
setting the colors of the squares, and ensuring the orientation and position of the
squares are correct.

Overall, the program successfully generates a Pythagoras Tree with 
the specified base and depth. The program uses SFML graphics capabilities to draw the tree 
and handle user events.

  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
The recursion algorithm function, pTree(), was a key aspect of the Pythagoras Tree assignment. 
Recursion is a technique in computer programming where a function calls itself 
repeatedly until a certain condition is met. In this assignment, the 
recursion algorithm was used to build the Pythagoras Tree by breaking down each 
square into two smaller squares and then repeating the process until the desired 
depth was reached.

Each time the function was called, it would create two new squares, modify their 
size, orientation, and color, and then call the function again with the new squares. 
This process was repeated until the desired depth was reached, at which point the 
squares were drawn to the screen. The use of recursion replaced the need for complex loops 
or conditional statements.

/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Describe if and how do you used the smart pointers 
 *  Include code excerpts.
 **********************************************************************/
In this program, the main feature implemented was the Pythagoras tree 
pattern created through recursive calls to a pTree() function, which is 
responsible for drawing each square and calling itself on two smaller 
squares derived from the original square.

The PTree class was defined with the following member variables:

- depth which represents the depth of recursion and determines the number of 
squares to be drawn
- base which is a sf::RectangleShape object representing the base square
- window which is a reference to the sf::RenderTarget object where the squares will be drawn
- color which is a sf::Color object representing the color of the squares
The main algorithm behind the creation of the Pythagoras Tree is the recursive 
call to the pTree() function. The function starts by drawing the base square, and 
then checks if the depth is greater than 0. If depth is greater than 0, it 
creates two smaller squares derived from the base square and calls the 
pTree() function on each of these squares, reducing the depth by 1 each time. 
This process continues until the depth becomes 0, at which point the recursive 
calls stop and the final pattern is drawn on the sf::RenderTarget window.

Smart pointers were not used in this assignment, instead I used raw pointers and 
references since it was sufficient for managing the dynamically created objects.

The following code excerpt shows the important part of the recursion algorithm:

    base.setFillColor(color);
    window.draw(base);

    if (depth > 0)
    {
        sf::RectangleShape left = base;
        sf::RectangleShape right = base;
        auto size = base.getSize();
        auto offset = base.getTransform();

        left.setSize(size * static_cast<float>((std::sqrt(2.0) / 2.0)));
        right.setSize(size * static_cast<float>((std::sqrt(2.0) / 2.0)));

        left.setOrigin(0, left.getSize().y);
        right.setOrigin(right.getSize());

        left.setPosition(offset.transformPoint({ 0, 0 }));
        right.setPosition(offset.transformPoint({ size.x, 0 }));

        left.rotate(-45);
        right.rotate(45);

        ... rest of code ...
    }

/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
 No partner.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
 Had a lot of trouble trying to place the squares in the correct position and 
 rotation in order for it to match the Pythagoras tree examples shown in the instructions.
 It involved a lot of trial and error to overcome this issue in PTree.cpp 

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/