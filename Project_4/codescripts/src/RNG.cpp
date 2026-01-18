// Definitions for the functions in the RNG class

#include "RNG.hpp"

// Generate random int from uniform distribution
int RNG::uniform_int()
{
    my_uniform_int_distribution = std::uniform_int_distribution<int>(0,1);
    return my_uniform_int_distribution(generator);
}

// Generate random double from uniform distribution
double RNG::uniform_double()
{
    my_uniform_real_distribution = std::uniform_real_distribution<double>(0.0 ,1.0);
    return my_uniform_real_distribution(generator);
}
