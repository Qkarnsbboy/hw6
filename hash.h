#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        int len = k.size();
        HASH_INDEX_T w[5] = {0, 0, 0, 0, 0};

        // // Compute w values
        // int j = 0; // Index of current character being processed

        // for (int i = 4; i >= 0; i--) { //filling in each w[i]
        //     for (int m = 0; m < 6 && j < len; m++, j++) {
        //         HASH_INDEX_T val = letterDigitToNumber(k[j]);
        //         std::cout << val << std::endl;
        //         w[i] = w[i] * 36 + val;
        //     }
        // }

        int powIndex = 0;
        int wIndex = 4;
        //loop through string backwards
        for(int i = len-1; i >= 0; i--){
            //change pow and w index every 6th letter
            if(powIndex == 6){
                powIndex = 0;
                wIndex--;
            }

            w[wIndex] += pow(36, powIndex) * letterDigitToNumber(k[i]);

            powIndex++;
        }

        //4. compute hash value
        HASH_INDEX_T hashValue = 0;
        for(int i = 0; i < 5; i++){
            hashValue += rValues[i] * w[i];
            // std::cout << w[i] << std::endl;
        }

        return hashValue;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        char c = tolower(letter);

        //if c is a letter
        if(c >= 'a' && c <= 'z'){
            return c - 'a';
        }
        else if (c >= '0' && c <= '9'){
            return c - '0' + 26;
            
        }
        //invalid input
        else {
            return -1;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
