// The RNG (Random Number Generator) class

#ifndef __RNG_hpp__
#define __RNG_hpp__

#include <random>

class RNG
{
    public:
        // Mersenne Twister 19937 random number generator
        std::mt19937 generator; 

        // Distribution objects transforming generator samples to random numbers in the range (0,1)
        std::uniform_int_distribution<int> my_uniform_int_distribution;
        std::uniform_real_distribution<double> my_uniform_real_distribution;
        // (Other distributions can be added)


    // Constructor, takes no arguments
    RNG() { };

    // Method for generating a random int from uniform distribution
    int uniform_int();

    // Method for generating a random double from uniform distribution
    double uniform_double();
};

#endif
