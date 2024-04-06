// Copyright 2023 Nika Ashtari
// This file is part of the DNA Sequence program
// All rights reserved.

#include "EDistance.h"
#include <stdint.h>
#include <SFML/System.hpp>  // To use sf::Clock and sf::Time classes for execution time

int main(int argc, const char* argv[]) {
    sf::Clock clock;  // Create a clock object to measure execution time
    sf::Time t;
    std::string s1;
    std::string s2;
    std::cin >> s1;  // Read the first sequence from standard input
    std::cin >> s2;  // Read the second sequence from standard input
    // Create an EDistance object with the two sequences
    EDistance run(s1, s2);
    int distance = run.optDistance();
    // Print results according to instructions
    std::cout << "Edit distance = "<< distance << std::endl;
    std::cout << run.alignment() << std::endl;
    t = clock.getElapsedTime();
    std::cout << "Execution time is " << t.asSeconds() << " seconds \n";
    std::cout << "Edit distance = "<< distance << std::endl;
    return 0;
}
