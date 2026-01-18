// Main program for evaluating expectation values at different MCMC cycles (problem 4c, 5, 6)

#include <assert.h>     // For aborting if number of command line arguments are incorrect
#include <iostream>     // For writing to terminal

#include "Ising.hpp"    // Our Ising class

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

    // Create matrix to read results to
    arma::mat results = arma::mat(n_cycles, 5);

    // Run MCMC cycles, calculate expectation values and save to file
    for (int j = 0; j < n_cycles; j++){
        myIsing.MCMC();
        myIsing.counter();              // Count cycles and total energy/magnetisation
        myIsing.expectation_values();   // Calculate expectation values

        results.row(j) = myIsing.expectation_values_vec.t();
        results(j,0) = myIsing.n_cycles;
    }   
    // Save results to file
    results.save(filename);

    cout << "\nSimulation results are written to " << filename << endl;
    



    // If 2x2 lattice: calculate the analytical solution as well
    if (L == 2){
        string filename_analytic= "analytical_" + filename;

        // Create matrix to read values to
        arma::mat results_analytic = arma::mat(1, 5);

        // Calculate analytical solution
        myIsing.analytic_2x2();
        results_analytic.row(0) = myIsing.expectation_values_vec.t();
        
        // Save results to file
        results_analytic.save(filename_analytic);

        cout << "Analytical solution is written to " << filename_analytic << endl;
    }

    return 0;
}
