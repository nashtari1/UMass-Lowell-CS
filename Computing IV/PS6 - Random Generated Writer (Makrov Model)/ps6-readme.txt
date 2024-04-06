/**********************************************************************
 *  readme.txt template                                                   
 *  Random Writer 
 **********************************************************************/

Name: Nika Ashtarzadeh

Hours to complete assignment: 24+ hours
/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
    In this assignment, I implemented a random writer program that generates 
    text based on a given input text using a Markov model of order k. I successfully 
    implemented the RandWriter class, as well as the client program TextWriter.cpp, 
    and tested the implementation using Boost Unit testing.



  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
 Markov Model: The central algorithm for this assignment was the implementation 
 of a Markov model of order k, which uses k-grams and their frequencies to generate random text.

 Data structures: I used maps to store k-grams and k+1-grams frequencies. 
 I also used set to store the unique characters in the input text.

 OO Design: The RandWriter class encapsulates the Markov model implementation 
 and exposes methods for generating random text and querying frequency information.



/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
 Constructor: Initializes the RandWriter object with the input text and order k.
 orderK(): Returns the order k of the Markov model.
 freq(): Returns the frequency of a given k-gram or k-gram with a specific character appended.
 kRand(): Returns a random character based on the input k-gram's frequency distribution.
 generate(): Generates a random text of length L using the input k-gram as a seed.



/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
 I completed the whole assignment successfully. I believe all the parts of the 
 assignment are working as expected. I tested my implementation using Boost 
 Unit testing and verified the correct behavior for various input cases.



/**********************************************************************
 *  Does your implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/
 Yes, my implementation passes the unit tests. No errors occured 
 when running the tests from ./test command. The output is also accurate
 to the input string.



 /**********************************************************************
 *  Describe where you used exceptions. 
 *  Provide files and lines of the code.
 ***********************************************************************/
 I used exceptions in the these places:

 - RandWriter.cpp, lines 25, 34, 45, 58, 70, and 73: I threw std::runtime_error 
   when the input k-gram was not of the correct length or when there were 
   no valid k-grams for random character generation.

 - test.cpp, lines 29, 37, 42, 44, 48, 50, 54, and 56: I used BOOST_REQUIRE_THROW 
   and BOOST_REQUIRE_NO_THROW to check for the proper throwing of exceptions 
   in various scenarios.



 /**********************************************************************
 *  Describe where you used lambda expression if any
 *  Provide files and lines of the code.
 ***********************************************************************/
 I used a lambda expression in test.cpp, lines 14-16, to print k-grams and their 
 frequencies. I created a new function called 'forEachKgram' in the RandWriter class 
 that accepts a lambda function as an argument. This lambda function takes a k-gram 
 and its frequency as input parameters and prints them. The 'forEachKgram' template 
 function is defined in RandWriter.h header file.

/**********************************************************************
 *  Did you implemented program for extra poits? If yes, describe your 
 *  If yes, describe your implementation.
 ***********************************************************************/
 I did not implement a program for extra points.


/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/



/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/



/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

