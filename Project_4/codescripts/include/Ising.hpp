// The Ising class

#ifndef __Ising_hpp__
#define __Ising_hpp__

#include <armadillo>    // For vectors and matrices
#include <math.h>       // For exponential and hyperbolic functions
#include <iostream>

#include "RNG.hpp"        // To generate random numbers


class Ising
{
    public:
        // Input member variables
        double T;           // Temperature [J/k_B]
        int L;              // Lattice length
        bool ordered;       // Option to order or randomize spin-lattice
        unsigned int seed;  // Seed for our random number generator

        // Other member variables
        double beta;        // Inverse T [1/J]
        int N;              // Total number of spins
        double E;           // Energy [J]
        double M;           // Magnetization [unitless]

        arma::mat lattice;  // Matrix containing spins
        arma::vec DeltaE;   // Vector containing ossible energy-changes
        RNG myRNG;          // Our random number generator

        int n_cycles;       // Number of MCMC cycles

            // Total values
        double E_tot;
        double M_tot;
        double E_squared_tot;
        double M_squared_tot;

            // Expectation values
        arma::vec expectation_values_vec;

        // Constructor
        Ising(double T_in, int L_in, bool ordered_in, unsigned int seed_in);

        // Method that returns neighbouring spins with periodic boundary conditions
        int adjacent_spin(int i, int direction);

        // Method that runs a Markov Chain Monte Carlo cycle using the Metropolis algorithm
        void MCMC();

        // Method that starts evaluating energies, magnetisation and cycles to use in calculation
        void counter();

        // Method that calculates expectation values after n_cycles
        void expectation_values();

        // Method that calculates analytical solution for a 2x2 Ising model
        void analytic_2x2();
};

#endif
