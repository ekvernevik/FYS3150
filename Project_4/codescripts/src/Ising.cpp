// Definitions for the functions in the Ising class

#include "Ising.hpp"

// Constructor
Ising::Ising(double T_in, int L_in, bool ordered_in, unsigned int seed_in)
{
    // Asign input member variables
    T = T_in;
    L = L_in;
    ordered = ordered_in;
    seed = seed_in;

    // Asign other member variables
    beta = 1./T;
    N = L*L;
    n_cycles = 0;
    myRNG.generator.seed(seed); // Set the seed

    E_tot = 0;
    M_tot = 0;
    E_squared_tot = 0;
    M_squared_tot = 0;

    expectation_values_vec = arma::vec(5);

    // Create lattice (spin-matrix)
    lattice = arma::mat(L, L);

    if (ordered == true){
        lattice.fill(1);     // All spins are -1
    } 
    else {  // Randomize spin-lattice
        for (int x = 0; x < L; x++){
            for (int y = 0; y < L; y++){
                lattice(x,y) = 2*myRNG.uniform_int() - 1; // Asign random number (-1 or 1) to spin
            }
        }
    }


    // Calculate initial energy (without double-counting)
    E = 0;
    for (int x = 0; x < L; x++){
        for (int y = 0; y < L; y++){
            E -= lattice(x,y) * 
                (lattice(x, adjacent_spin(y,1))      // Spin to the right
                +lattice(adjacent_spin(x,1), y));    // Spin below
        }
    }
    
    // Calculate intial magnetization 
    M = arma::accu(lattice);       // arma::accu sums over all elements in matrix

    // Calculate possible energy changes
    DeltaE = arma::vec(5);
    for (int i = 0; i < 5; i++){
        double DeltaE_i = i*4 - 8;
        DeltaE(i) = exp(-beta*DeltaE_i); // Boltzmann factor
    }
}


// Find neighbouring spins with periodic boundary conditions
int Ising::adjacent_spin(int i, int direction) // above or left: dircetion = -1
{                                              // below or right: direction = 1
    return (i + L + direction) % (L);
}


// Run a Markov Chain Monte Carlo cycle using the Metropolis algorithm
void Ising::MCMC()
{
    // Loop N = L*L times
    for (int i = 0; i < N; i++){
        // Choose random spin to possibly flip
        int x = myRNG.uniform_double() * L;
        int y = myRNG.uniform_double() * L;

        // Compute possible energy change
        int DeltaE_possible = 2 * lattice(x,y) * 
                            (lattice(adjacent_spin(x,-1), y)   // Above
                            +lattice(adjacent_spin(x, 1), y)   // Below
                            +lattice(x, adjacent_spin(y,-1))   // Left
                            +lattice(x, adjacent_spin(y, 1))); // Right 

        // Metropolis accept/reject test
        if (myRNG.uniform_double() <= DeltaE(DeltaE_possible/4 + 2)){ // if random number is less than Boltzmann factor
            // Change the state
            lattice(x,y) *= -1;    // Flip the spin
            E += DeltaE_possible;  // Update energy
            M += 2*lattice(x,y);   // Update Magnetization
        }
    }
}


// Count energies, magnetisation and number of cycles (this could be an if statement in MCMC?)
void Ising::counter()
{
    // Count number of cycles to use in calculation
    n_cycles += 1;

    // Add current state to total values
    E_tot += E;
    M_tot += abs(M);
    E_squared_tot += E*E;
    M_squared_tot += M*M;
}


// Calculates expectation values
void Ising::expectation_values()
{
    // Saving some FLOPs
    int N_n = N * n_cycles;
    double N_T_n = 1/(N * T * n_cycles);


    // Energy and Magnetisation per spin
    double mean_epsilon = E_tot/N_n;
    double mean_m = M_tot/N_n;

    // Spesific heat capacity per spin
    double C_V = (N_T_n/T) * (E_squared_tot - (E_tot*E_tot)/n_cycles);


    // Susceptibility per spin
    double chi = (N_T_n) * (M_squared_tot - (M_tot*M_tot)/n_cycles);

    expectation_values_vec  = {0, mean_epsilon, mean_m, C_V, chi};
}


void Ising::analytic_2x2()
{
    double Z = 4*cosh(8*beta) + 12;

    double mean_epsilon = -8*sinh(8*beta) / Z;
    double mean_m = (2*exp(8*beta) + 4) / Z;
    double C_V = (768*cosh(8*beta) + 256) / (Z*Z*T*T);
    double chi = (16*exp(-8*beta) + 48*exp(8*beta) + 48) / (Z*Z*T);

    expectation_values_vec  = {0, mean_epsilon, mean_m, C_V, chi};
}
