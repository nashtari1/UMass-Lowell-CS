// Copyright 2023 Nika Ashtari
// This file is part of the Random Writer Program
// All rights reserved

#include "RandWriter.h"
#include <stdexcept>
#include <random>
#include <algorithm>
#include <vector>

// Creating a Markov model of order k from given text
// Initializes the RandWriter object with the input text and order k.
RandWriter::RandWriter(std::string text, int k) : k_(k), text_(text) {
    for (const auto& c : text) {
        alphabet_.insert(c);
    }

    // Calculate the k-gram frequencies
    for (size_t i = 0; i < text.size(); ++i) {
        std::string kgram;
        for (int j = 0; j < k; ++j) {
            kgram += text[(i + j) % text.size()];
        }
        kgram_freq_[kgram]++;
    }

    // Calculate the k+1-gram frequencies
    for (size_t i = 0; i < text.size(); ++i) {
        std::string kplus1gram;
        for (int j = 0; j < k + 1; ++j) {
            kplus1gram += text[(i + j) % text.size()];
        }
        kplus1_freq_[kplus1gram]++;
    }
}

// orderK() method: Returns the order k of the Markov model
int RandWriter::orderK() const {
    return k_;
}

//  number of occurrences of kgram in text
int RandWriter::freq(std::string kgram) const {
    if (kgram.size() != static_cast<std::string::size_type>(k_)) {
        throw std::runtime_error("kgram is not of length k");
    }
    auto it = kgram_freq_.find(kgram);
    if (it == kgram_freq_.end()) {
        return 0;
    }
    return it->second;
}

// freq() method (overloaded): Returns the frequency of a given
// k-gram with a specific character appended.
int RandWriter::freq(std::string kgram, char c) const {
    if (kgram.size() != static_cast<std::string::size_type>(k_)) {
        throw std::runtime_error("kgram is not of length k");
    }
    if (alphabet_.find(c) == alphabet_.end()) {
        throw std::runtime_error("Character not in alphabet");
    }
    std::string kplus1gram = kgram + c;
    auto it = kplus1_freq_.find(kplus1gram);
    if (it == kplus1_freq_.end()) {
        return 0;
    }
    return it->second;
}

// Returns random char based on the input k-gram's frequency distribution.
char RandWriter::kRand(std::string kgram) {
    if (kgram.size() != static_cast<std::string::size_type>(k_)) {
        throw std::runtime_error("kgram is not of length k");
    }
    std::vector<char> candidates;
    std::vector<int> weights;

    for (const auto& c : alphabet_) {
        int freq_c = freq(kgram, c);
        if (freq_c > 0) {
            candidates.push_back(c);
            weights.push_back(freq_c);
        }
    }

    if (candidates.empty()) {
        throw std::runtime_error("No such kgram");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> dist(weights.begin(), weights.end());

    return candidates[dist(gen)];
}

// Generates a random text of length L using the input k-gram as a seed.
std::string RandWriter::generate(std::string kgram, int L) {
    if (kgram.size() != static_cast<std::string::size_type>(k_)) {
        throw std::runtime_error("kgram is not of length k");
    }
    if (L < k_) {
        throw std::runtime_error("L is less than k");
    }

    std::string result = kgram;
    std::string current_kgram = kgram;

    for (int i = 0; i < L - k_; ++i) {
        char next_char = kRand(current_kgram);
        result.push_back(next_char);
        current_kgram.erase(0, 1);
        current_kgram.push_back(next_char);
    }

    return result;
}

// overload the stream insertion operator and display
// the internal state of the Markov Model
std::ostream &operator<<(std::ostream &os, const RandWriter &rw) {
    os << "Order: " << rw.k_ << std::endl;
    os << "Alphabet: ";
    for (const auto &c : rw.alphabet_) {
        os << c;
    }
    os << std::endl;

    os << "k-grams:" << std::endl;
    for (const auto &kv : rw.kgram_freq_) {
        os << kv.first << ": " << kv.second << std::endl;
    }

    os << "k+1-grams:" << std::endl;
    for (const auto &kv : rw.kplus1_freq_) {
        os << kv.first << ": " << kv.second << std::endl;
    }

    return os;
}
