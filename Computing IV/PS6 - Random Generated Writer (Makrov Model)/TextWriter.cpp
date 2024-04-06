// Copyright 2023 Nika Ashtari
// This file is part of the Random Writer Program
// All rights reserved

#include "RandWriter.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Input validation: checking if correct number of command-line arg is given
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " k L" << std::endl;
        return 1;
    }

    // Parse command-line arguments for k and L values
    int k = std::stoi(argv[1]);
    int L = std::stoi(argv[2]);

    // Read input text from standard input
    std::string input_text((std::istreambuf_iterator<char>
    (std::cin)), std::istreambuf_iterator<char>());

    // Create a RandWriter object using the input text and k value
    RandWriter rand_writer(input_text, k);

    // Generate a random text using the RandWriter object
    std::string kgram = input_text.substr(0, k);
    std::string generated_text = rand_writer.generate(kgram, L);

    // Output the generated text
    std::cout << generated_text << std::endl;

    return 0;
}
