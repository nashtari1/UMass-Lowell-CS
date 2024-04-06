// Copyright 2023 Nika Ashtari
// This file is part of the DNA Sequence program
// All rights reserved.

#ifndef EDISTANCE_H
#define EDISTANCE_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class EDistance {
 public:
    // Constructor to initialize the EDistance class with two strings as inputs
    EDistance(std::string x, std::string y);
    // Static function to compute penalty of two characters
    static int penalty(char a, char b);
    // Static function to find the min of three integers using lambda function
    static int min(int a, int b, int c);
    // Function to find the optimal edit distance using dynamic programming
    int optDistance();
    // Function to get the optimal alignment
    std::string alignment();
    // 2D vector to store the optimal edit distances of the two strings
    std::vector<std::vector<int>> opt;
    // Two input strings
    std::string s1;
    std::string s2;
 private:
};
#endif  // EDISTANCE_H
