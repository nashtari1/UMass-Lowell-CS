// Copyright 2023 Nika Ashtari
// This file is part of the DNA Sequence program
// All rights reserved.

#include "EDistance.h"

//  Using vector of columns each containing a row vector
EDistance::EDistance(std::string a, std::string b) {
    s1 = a;
    s2 = b;
    std::vector<int> MatrixVec(s1.size() + 1, 0);
    for (int x = 0; x < s2.size() + 1; x++) {
        opt.push_back(MatrixVec);
    }
}

// Returns the minimum of three integers using a lambda function
int EDistance::min(int a, int b, int c) {
    auto min_lambda = [](int x, int y) { return x < y ? x : y; };
    return min_lambda(min_lambda(a, b), c);
}

// Returns the penalty for two mismatching characters
int EDistance::penalty(char a, char b) {
    if (a == b) {
        return 0;
    } else {
        return 1;
    }
}

// Returns a string representing the alignment of the two input strings
std::string EDistance::alignment() {
    std::stringstream align;
    int i = 0;
    int j = 0;
    while (i < s2.length() || j < s1.length()) {
        if (i < s2.length() && j < s1.length() &&
        opt[i][j] == opt[i+1][j+1] + penalty(s1[j], s2[i])) {
            align << s1[j] << " " <<  s2[i] << " "
            << penalty(s1[j], s2[i]) << std::endl;
            i++;
            j++;
        } else if (i < s2.length() && opt[i][j] == opt[i+1][j] + 2) {
            align << "- " << s2[i] << " " <<
                penalty(s1[j], s2[i])+1 << std::endl;
                i++;
        } else {
            align << s1[j] << " - " <<
            penalty(s1[j], s2[i])+1 << std::endl;
            j++;
        }
    }
    return align.str();
}

// Calculates the optimal edit distance using dynamic programming
int EDistance::optDistance() {
    for (int i = 0; i < s1.length() + 1; i++) {
    opt[s2.length()][i] = 2 * (s1.length() - i);
  }
  for (int j = 0; j < s2.length() + 1; j++) {
    opt[j][s1.length()] = 2 * (s2.length() - j);
  }
  for (int i = s2.length()- 1; i >= 0; i--) {
    for (int j = s1.length()- 1; j >= 0; j--) {
      opt[i][j] = min(opt[i+1][j+1] + penalty(s1[j], s2[i]),
      opt[i+1][j] + 2, opt[i][j+1] + 2);
    }
  }
  return opt[0][0];
}
