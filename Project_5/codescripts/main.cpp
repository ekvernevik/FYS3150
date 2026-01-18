#include <iostream>
#include <cmath>        // For pow
#include <assert.h>     // For aborting if number of command line arguments are incorrect

#include "wave.hpp"
#include "crank_nicolson.hpp"

using namespace std;

int main(int argc, const char* argv[])
{
    // Constant parameters for all runs
    double h = 0.005;                       // Point step size
    double dt = 2.5 * pow(10,-5);           // Time step size
    
    // Check number of command line arguments
    assert(argc == 10);

    // Read command line arguments
    const double T = atof(argv[1]);         // Total time
    const double x_c = atof(argv[2]);       // Centre of wave-packet, x-direction
    const double sigma_x = atof(argv[3]);   // Width of wave-paceket, x-direction 
    const double p_x = atof(argv[4]);       // Momentum of wave packet, x-direction
    const double y_c = atof(argv[5]);       // Centre of wave-packet, y-direction
    const double sigma_y = atof(argv[6]);   // Width of wave-paceket, y-direction
    const double p_y = atof(argv[7]);       // Momentum of wave packet, y-direction
    const int n_slits = atof(argv[8]);      // Number of slits
    const string filename = argv[9];

    double v_0;               // Potential-barrier constant
    if (n_slits > 0){
        v_0 = pow(10,10);
    }
    else{
        v_0 = 0;
    }


    // Create wave
    Wave myWave(h, x_c, y_c, sigma_x, sigma_y, p_x, p_y, v_0, n_slits);

    // Create cube to save results to
    arma::cx_cube results = arma::cx_cube(myWave.M, myWave.M, T/dt+1 );

    // Store initial state
    results.slice(0) = myWave.u;
    
    // Initialize the Crank Nicolson method
    initialize_CrankNicolson(myWave, dt);

    // Evolve and store new states
    for (int i = 0; i < T/dt; i++){
        CrankNicolson(myWave);
        results.slice(i+1) = myWave.u;
    }

    // Save results 
    results.save(filename);


    return 0;
}
