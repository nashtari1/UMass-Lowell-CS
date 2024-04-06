// Copyright 2023 Nika Ashtari
// This file is part of the Random Writer Program
// All rights reserved

#define BOOST_TEST_MODULE RandWriterTest
#include "RandWriter.h"
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

// Test case for checking frequency counts of k-grams and k+1-grams
BOOST_AUTO_TEST_CASE(RandWriter_frequency_test) {
    std::string input_text = "gagggagaggcgagaaa";
    int k = 2;

    RandWriter rw(input_text, k);

    // Lambda function to print k-gram and its frequency
    rw.forEachKgram([](const std::string &kgram, int frequency) {
        std::cout << kgram << ": " << frequency << std::endl;
    });
    // Print k-gram frequencies
    for (const auto &entry : rw.kgram_freq_) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }

    std::cout << std::endl;

    // Print k+1-gram frequencies
    for (const auto &entry : rw.kplus1_freq_) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
}

// Test case for testing RandWriter class methods, including error handling.
BOOST_AUTO_TEST_CASE(RandWriter_test) {
    std::string input_text = "gagggagaggcgagaaa";
    int k = 2;

    RandWriter rw(input_text, k);
    // Test orderK() method
    BOOST_REQUIRE_EQUAL(rw.orderK(), k);

    // Test freq() method with single k-gram parameter
    BOOST_REQUIRE_EQUAL(rw.freq("ga"), 5);
    BOOST_REQUIRE_EQUAL(rw.freq("gg"), 3);

    // Test error handling for incorrect k-gram size
    BOOST_REQUIRE_THROW(rw.freq("gaa"), std::runtime_error);
    BOOST_REQUIRE_NO_THROW(rw.freq("ga"));

    // Test freq() method with k-gram and character parameters
    BOOST_REQUIRE_EQUAL(rw.freq("ga", 'g'), 4);
    BOOST_REQUIRE_EQUAL(rw.freq("ga", 'a'), 1);

    // Test error handling for invalid character
    BOOST_REQUIRE_THROW(rw.freq("ga", 'b'), std::runtime_error);
    BOOST_REQUIRE_NO_THROW(rw.freq("ga", 'a'));

    // Test kRand() method
    char random_char = rw.kRand("ga");
    BOOST_REQUIRE(random_char == 'a' || random_char == 'g');
    BOOST_REQUIRE_THROW(rw.kRand("gaa"), std::runtime_error);

    // Test generate() method
    std::string generated_text = rw.generate("ga", 10);
    BOOST_REQUIRE_EQUAL(generated_text.substr(0, k), "ga");
    BOOST_REQUIRE_EQUAL(generated_text.length(), 10);
    BOOST_REQUIRE_THROW(rw.generate("gaa", 10), std::runtime_error);
}
