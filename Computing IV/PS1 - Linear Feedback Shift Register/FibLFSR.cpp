// Written by: Nika Ashtarzadeh

#include "FibLFSR.hpp"
#include <iostream>
//using namespace std;

//constructor
FibLFSR::FibLFSR(std::string seed) {
    tap15 = 0;
    tap13 = 0;
    tap12 = 0;
    tap10 = 0;


    this->seed = seed;
}

//step functions to simulate one step of the LFSR and return the rightmost bit as an integer of 0 or 1. 
int FibLFSR::step() {

    int output = 0;
    tap15 = seed[0];
    tap13 = seed[2];
    tap12 = seed[3];
    tap10 = seed[5];

    output = (((tap15 ^ tap13) ^ (tap12)) ^ tap10); //xor operator
    seed.erase(seed.begin());
    seed.push_back(output);

    return output;
}

// returning number in base 10 instead of binary.
// Member function to call the step k times and return the final integer;
int FibLFSR::generate(int k) {

    int num = 0, bit = 0;

    for(int i = 0; i < k; i++){
        bit = step();
        num = num * 2 + bit; //doubling num variable and add the bit returned from step function 
    }
    return num;
}

//overloading the '<<' operator in order to display current register value in printgable form as per instructions. 
 std::ostream& operator<<(std::ostream& out, FibLFSR& Fib ){
   return out << Fib.seed;
}

//member function to check if inputted string is in binary.
bool FibLFSR::isBinary(std::string seed){

    for(int n= 0; n < (int)seed.length(); n++ ){
        if(isdigit(seed[n]) == false){
            return false;
        }
        else if (seed[n] == '0' || seed[n] == '1') {
            return true;
        }
    }
    return false;
}

//member function to convert seed to integer
int FibLFSR::toInteger(){

    std::string num = seed;
    int value = 0;
    int base = 1;

    for (int i = num.length() - 1; i >= 0; i--) {
        if (num[i] == '1')
            value += base;
        base = base * 2;
    }

    return value;
}
//end of FibLFSR.cpp