// Copyright 2023 Nika Ashtari
// This file is part of the Random Writer Program
// All rights reserved

#ifndef RANDWRITER_H
#define RANDWRITER_H

#include <iostream>
#include <map>
#include <set>
#include <string>

// Represents a Markov model of order k for text generation
class RandWriter {
 public:
    // Initializing contructor and functions of class
    RandWriter(std::string text, int k);
    int orderK() const;
    int freq(std::string kgram) const;
    int freq(std::string kgram, char c) const;
    char kRand(std::string kgram);
    std::string generate(std::string kgram, int L);

    // Displays the internal state of the Markov Model.
    friend std::ostream &operator<<(std::ostream &os,
    const RandWriter &rw);

    // Member variables
    int k_;
    std::string text_;
    std::set<char> alphabet_;
    std::map<std::string, int> kgram_freq_;
    std::map<std::string, int> kplus1_freq_;

    // Calls lambda function for each k-gram frequency in the model.
    template <typename Func>
      void forEachKgram(Func func) const {
         for (const auto &entry : kgram_freq_) {
        func(entry.first, entry.second);
      }
}

 private:
};
#endif  // RANDWRITER_H
