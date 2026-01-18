// Main program for evaluating expectation values at different temperatures (problem 4b, 8)

#include <assert.h>     // For aborting if number of command line arguments are incorrect
#include <iostream>     // For writing to terminal

#include "omp.h"        // OpenMP header

#include "Ising.hpp"    // Our Ising class

using namespace std;

int main(int argc, const char* argv[])
{
    // Seed
    const int seed = 666;     // Seed for the random simulation
    
    // Check number of command line arguments
    assert(argc == 9);

    // Read command line arguments
    const int L = atoi(argv[1]);        // Lattice length
    const bool ordered = atoi(argv[2]); // Orderd or random initial spin lattice
    const int n_cycles = atoi(argv[3]); // Number of temperature steps
    const int burn_in = atoi(argv[4]);  // Number of burn-in MCMC cycles
    const double T_min = atof(argv[5]); 
    const double T_max = atof(argv[6]);
    const int n_T = atoi(argv[7]);      // Number of measurements
    const string filename = argv[8];    // Output filename for the simulation

    // Avoid NaN when only one temperature
    double dT; // Temperature step
    if (n_T > 1){
        dT = (T_max-T_min)/(n_T-1.); 
    }
    else{
        dT = 0;
    }

    // Create matrix to read results to
    arma::mat results = arma::mat(n_T, 5);

    // Start parallel region
    #pragma omp parallel
    {
        // Start parallel loop
        #pragma omp for
        // For every temperature
        for (int j = 0; j < n_T; j ++){
            double T = T_min + j*dT;

            // Create Ising model
            Ising myIsing(T, L, ordered, seed);

            // Run MCMC cycles without counting during the burn-in time
            for (int i = 0; i < burn_in; i++){
                myIsing.MCMC();
            }

            // Run MCMC cycles and count total values
            for (int i = 1; i <= n_cycles; i++){
                myIsing.MCMC();
                myIsing.counter();
            }

            myIsing.expectation_values();                           // Calculate final expectation values
            results.row(j) = myIsing.expectation_values_vec.t();    // Add expectation values to results
            results(j,0) = T;                                       // Add temperature to results
        
        } // End of parallelized loop

    } // End of parallelized region
    
    // Save results to file
    results.save(filename);

    cout << "Simulation results are written to " << filename << endl;

    
    
    // If 2x2 lattice: calculate the analytical solution as well
    if (L == 2){
        string filename_analytic = "analytic_" + filename ;

        // Create matrix to read values to
        arma::mat results_analytic = arma::mat(n_T,5);

        // For every temperature
        for (int j = 0; j < n_T; j ++){
            double T = T_min + j*dT;

            // Create Ising model
            Ising myIsing(T, L, ordered, seed);

            // Calculate analytic expectation values and write to file
            myIsing.analytic_2x2();
            results_analytic.row(j) = myIsing.expectation_values_vec.t();
            results_analytic(j,0) = T;
        }
        // Save results to file
        results_analytic.save(filename_analytic);
        
        cout << "Analytical solution is written to " << filename_analytic << endl;
    }


    return 0;
}
