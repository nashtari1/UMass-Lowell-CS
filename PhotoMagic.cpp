//Written by: Nika Ashtarzadeh

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"

void transform(sf::Image& image, FibLFSR* seed){
    //unisnged integers to store new RGB values
    sf::Uint8 newRed, newGreen, newBlue;

    // using getSize to store width of image
    int width = image.getSize().x;

    // using getSize to store length of image
    int height = image.getSize().y;

    //int variable to hold new 8 bit int for RGB
    int value = 0;

    // for loop to go thru each pixel (x, y) and extract the red, green and blue
    for( int i = 0; i != width; i++){
        for( int k = 0; k != height ; k++ ){

            sf::Color pixel = image.getPixel(i,k);

            // getting red component
            value = seed->generate(30);
            //XOR red value with new 8-bit integer
            newRed = pixel.r ^ ((sf::Uint8)value);

            // getting green component
            value = seed->generate(30);
            // XOR green value with new 8-bit integer
            newGreen = pixel.g ^ ((sf::Uint8)value);

            // getting blue component
            value = seed->generate(30);
            //XOR blue value with new 8-bit integer
            newBlue = pixel.b ^ ((sf::Uint8)value);

            // Create new Color
            sf::Color newColor(newRed, newGreen, newBlue);

            // Setting new color
            image.setPixel(i, k, newColor);
        }
    }
}//end of transform function


int main(int argc, char* argv[]) {

    // source image
    std::string input_file;

    // output image
    std::string output_file;

    // FibLFSR seed for user to input
    std::string inputSeed;

    // Prompts user inputs three arguments, the source image filename, output image filename, and the FibLFSR seed 1011011000110110.
    std::cout << "Please enter input file name including extention: ";
    std::cin >> input_file; 
    std::cout << "\nPlease enter output file name including extention: ";
    std::cin >> output_file;
    std::cout << "\nPlease enter encryption seed: ";
    std::cin >> inputSeed;

    sf::Image inputImage;

    // loading in input file image
    inputImage.loadFromFile(input_file);

    // seed 
    FibLFSR fibLfsr(inputSeed);

    // creating windows, 1 for original image and the other for the encrypted image to be displayed
    sf::RenderWindow window1(sf::VideoMode(600,600), "Original");
    sf::RenderWindow window2(sf::VideoMode(600,600), "Encrypted");

    // Creating original image texture and sprite sfml
    sf::Texture original;

    if (!original.loadFromFile(input_file)) {
        std::cout << "Could not find input file. Please try again...\n";
        std::cout << "Quitting...";
        exit(0);
    }

    sf::Sprite original_image;
    original_image.setTexture(original);

    //encrpyting image..
    transform(inputImage, &fibLfsr);

    // Save new image to file
    if(!inputImage.saveToFile(output_file)){
        std::cout << "Could not save output file. Please try again...\n";
    }

    // Creating encrypted image texture and sprite sfml
    sf::Texture image_encryption;
    image_encryption.loadFromFile(output_file);

    sf::Sprite encrypted;
    encrypted.setTexture(image_encryption);

    // drawing windows
    while (window1.isOpen() && window2.isOpen() ) {

        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window1.close();
        }

        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window2.close();
        }

        window1.clear();
        window1.draw(original_image);
        window1.display();

        window2.clear();
        window2.draw(encrypted);
        window2.display();
    }

    return 0;
} 
// end of PhotoMagic.cpp