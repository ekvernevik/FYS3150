// Declarations of mehtods used in the Crank Nicolson scheme

#ifndef __crank_nicolson_hpp__
#define __crank_nicolson_hpp__

#include <armadillo>
#include <complex>
#include "wave.hpp"

// Constructs A- and B-matrices to be used in the Crank-Nicolson method
void initialize_CrankNicolson(Wave& yourWave, double dt);

// Finds the next state
void CrankNicolson(Wave& yourWave);

#endif
