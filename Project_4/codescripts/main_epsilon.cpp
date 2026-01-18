// Main program for generating eps samples, to approximate probability function p_eps

#include <assert.h> // For aborting if number of command line arguments are incorrect
#include <iostream> // For writing to terminal

#include "Ising.hpp"

using namespace std;

int main(int argc, const char* argv[])
{
    // Seed
    const int seed = 666;     // Seed for the random simulation
    
    // Check number of command line arguments
    assert(argc == 7);

    // Read command line arguments
    const int L = atoi(argv[1]);        // Lattice length
    const bool ordered = atoi(argv[2]); // Orderd or random initial spin lattice
    const int n_cycles = atoi(argv[3]); // Number of MCMC cycles
    const int burn_in = atoi(argv[4]);  // Number of burn-in MCMC cycles
    const double T = atof(argv[5]);
    const string filename = argv[6];    // Output filename for the simulation

    // Create Ising model
    Ising myIsing(T, L, ordered, seed);

    // Run MCMC cycles without counting during the burn-in time
    for (int i = 0; i < burn_in; i++){
        myIsing.MCMC();
    }

    // Create vector to read results to
    arma::vec results = arma::vec(n_cycles);

    // Run MCMC cycles, calculate expectation values and save to file
    int N = L*L;
    for (int j = 0; j < n_cycles; j++){
        myIsing.MCMC();
        results.row(j) = myIsing.E/N;
    }   

    // Save results to file
    results.save(filename);

    cout << "\nSimulation results are written to " << filename << endl;

    return 0;
}
