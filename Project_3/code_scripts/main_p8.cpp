// Programme for simulating the time-evolution of a (or several) particles motion in a Penning trap, using either the Forward-Euler-method,
// or, the RungeKutta4-method.

// Including relevant libraries
#include <iostream>
#include <fstream>
#include <iomanip>
#include <armadillo>
#include <cmath>
#include <list>

// Including our header-files for our two classes
#include "Particle.hpp"
#include "PenningTrap.hpp"

using namespace std;
using namespace arma;

// Function: Initialize one (or more) particles with values, and simulate their motion in a Penning trap
int main() {
    
    // Defining a variable for the Coulomb-constant
    double k_e = 1.38935333 * std::pow(10, 5); // [u (m*10^-6)^3 / (s*10^-6)^2 e^2]

    // Values and params for the first particle
    double q1 = 1.;             // [e]
    double m1 = 40.078;         // [u]
    vec r1 = vec("20. 0. 20."); // [m*10^-6]
    vec v1 = vec("0. 25. 0.");  // [m*10^-6 / s*10^-6] 

    // "Assembling" the particle
    Particle particle_1 = Particle(q1,m1,r1,v1);

    // Values and params for the second particle
    double q2 = 1.;             // [e]
    double m2 = 40.078;         // [u]
    vec r2 = vec("25. 25. 0."); // [m*10^-6]
    vec v2 = vec("0. 40. 5.");  // [m*10^-6 / s*10^-6] 

    // "Assembling the particle"
    Particle particle_2 = Particle(q2,m2,r2,v2);
    
    // Values and params for the Penning trap
    double B0 = 9.65*10;            // [u / (s*10^-6) e]
    double V0 = 2.41 * pow(10, 6);  // [u (m*10^-6)^2 / (s*10^-6)^2 e]
    double d = 500;                 // [m*10^-6]
    
    std::vector<int> n = {4000, 8000, 16000, 32000};

    bool C = false;
    bool V = false;
    double f = 0;
    double omega_V = 0;

    for (int i = 0; i < n.size(); i++) {

        // "Assembling" the Penning trap
        PenningTrap myTrap(B0,V0,d,C,V,f,omega_V);

        // Adding particles to the Penning trap
        myTrap.add_particle(particle_1);
        myTrap.add_particle(particle_2);

        // Values and params for the systems time-evolution
        double t_tot = 50.;         // Total simulation-time
        int n_steps = n.at(i);

        //myTrap.write_to_file(myTrap, "FE", t_tot, n_steps);
        myTrap.write_to_file("RK4", t_tot, n_steps);
        //myTrap.write_to_file(myTrap, "analytical", t_tot, n_steps);

    }
    

    // All is (hopefully) well. Return with error code 0
    return 0;
}
