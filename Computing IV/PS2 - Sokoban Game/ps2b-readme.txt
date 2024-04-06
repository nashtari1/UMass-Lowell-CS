/**********************************************************************
 *                                                  
 *  PS2b: Sokoban
 **********************************************************************/

Name: Nika Ashtarzadeh

Hours to complete assignment : 10 hours

/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
 Yes, I have completed the whole assignment successfully. 

 I created the movePlayer which first finds the player's location '@' by 
 looping through the game level.The new position of the player is calculated 
 based on the direction provided as the argument to the function.
 The function then checks if the new position of the player is valid. 
 If it is not valid, then the function returns and does nothing.
 If the new position is a storage location, the function moves the 
 player to that location and sets the 'leavingStorageLocation' flag to true. 
 If the player is leaving a storage location, then the function sets the 
'leavingStorageLocation' flag to true and stores the location of all storage locations.
 If the new position of the player is a box, then the function checks if 
 the new position of the box is valid. If it is not valid, then the function 
 returns and does nothing. If the new position is valid, then the function 
 moves the box to the new position and moves the player to the new position.

 The isWon function keeps track of the number of boxes in addition to the number of storage 
 areas and boxes on storage areas. If there are more boxes than storage 
 areas, it returns true if boxesOnStorage equals storageAreas. If 
 there are more storage areas than boxes, the function still returns 
 true if all storage areas have a box on them.

 I have updated the loadTextures function to  uses a lambda function called setTexture to set the texture for each sprite object.
 The setTexture lambda function takes three arguments:

 A reference to a sf::Sprite object representing the sprite to which the texture will be assigned.
 A reference to a sf::Texture object that will store the texture data.
 A constant reference to a std::string object that specifies the name of the texture file to load.
 The lambda function loads the texture data from the file specified by the filename argument
 using the loadFromFile() function of the sf::Texture class. If the texture data is loaded successfully,
 the function assigns the texture to the sprite using the setTexture() function of the sf::Sprite class.

 The Sokoban program uses uses complex algorithms and data structures to create the game. 
 It uses a dynamic memory allocation technique to create a grid of characters that represents the game level, 
 which is read in from an input stream using a custom overloaded operator. The program also utilizes the SFML 
 library to load and display textures for various game elements, including the player sprite, 
 storage locations, and environmental objects such as walls and floors. A sound buffer is also used to 
 play an audio cue when the player wins the game. Additionally, the program uses a Direction enumeration 
 to manage the movement of the player character, and it uses a vector of sprite objects to represent the 
 various storage locations within the game level. To check for a winning game condition, the program compares 
 the game level grid to an original grid solution, which prevents the storage tile from being overwritten 
 when the player moves over it.
/**********************************************************************
 *  Did you attempt the extra credit parts? Which one(s)?
 *  Successfully or not?  
 **********************************************************************/
 Yes I have attempted the extra credit part successfully. I implemented a
 getTexture const function that takes in the Direction enum. This is used
 to set the player's direction based on the corresponding texture.
 I have also implemented a victory sound using sf::Sound and sf::SoundBuffer objects
 that will play based on the isWon() function. The isWon() function would then
 be called in the movePlayer function at the beggining and end within an if statement.
 I have also implemented a Text object that will display on screen that the user has won the game. 


/**********************************************************************
 *  Did your code pass cpplint?
 *  Indicate yes or no, and explain how you did it.
 **********************************************************************/
  Yes it has passed cpplint. 

/**********************************************************************
 *  List whatever help (if any) you received from TAs,
 *  classmates, or anyone else.
 **********************************************************************/



/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
  I had a serious issue that took most of my time for this assignment which was
  the storage location tile would be overwritten if the box or player walked over it.
  The storage tile would become a floor tile. I had to use multiple debug functions
  to help solve the problem such as printing the grid and printing the player position.
  To solve the issue, i had to create a copy of the initial game grid called originalGrid and
  a new function called setStorageLocations which would set the storage locations to 'a' any
  time the player moved off of a storage tile. It would use the 'originalGrid' array copy to do this and 
  set the value to the current 'grid' array. 

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
 Victory sound effect: "Success Fanfare Trumpets" by
 FunWithSound (https://pixabay.com/sound-effects/success-fanfare-trumpets-6185/)