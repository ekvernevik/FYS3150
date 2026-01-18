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

    // Values and params for the first particle
    double q1 = 1.;             // [e]
    double m1 = 40.078;         // [u]
    
    // Values and params for the Penning trap
    double B0 = 9.65*10;            // [u / (s*10^-6) e]
    double V0 = 2.41 * pow(10, 6);  // [u (m*10^-6)^2 / (s*10^-6)^2 e]
    double d = 500;                 // [m*10^-6]

    bool C = false; 
    bool V = true;

    // Adding particles to the Penning trap
    
    // myTrap.add_particle(particle_2);

    // Values and params for the systems time-evolution
    double t_tot = 500.;         // Total simulation-time
    int n_steps = 32000;
    double dt = t_tot/n_steps;  // Timestep size, determined by the two former params

    int width = 12;
    int prec = 4;

    // For-loop to iterate through different vales of omega_v (angular frequency)
    // for (double f = 0.1; f < 0.7; f+=0.3) {
    //     string filename = "counter_f"+to_string(f)+".txt";
    //     ofstream ofile_ctr;
    //     ofile_ctr.open(filename);

    //     for (double w_v = 0.2; w_v < 2.5; w_v += 0.02) {

    //         // "Assembling" the Penning trap
    //         PenningTrap myTrap(B0, V0, d, C, V, f, w_v);

    //         // Adding a particle
    //         for (int i = 0; i < 25; i++) {
    //             vec r = vec(3).randn() * 0.1 * myTrap.d;  // random initial position
    //             vec v = vec(3).randn() * 0.1 * myTrap.d;  // random initial velocity

    //             Particle particle = Particle(q1,m1,r,v);
    //             myTrap.add_particle(particle);
    //         }
            
    //         for (int j = 0; j <n_steps; j++)
    //         {
    //             myTrap.change_time(j*dt);
    //             myTrap.evolve_system("RK4", dt);
    //         }
    //         //cout << myTrap.particles_inside() << endl;

    //         int counter = myTrap.particles_inside();
    //         ofile_ctr << setw(width) << setprecision(prec) << scientific << w_v
    //                   << setw(width) << setprecision(prec) << scientific << counter
    //                   << endl;
    //     }

    //     ofile_ctr.close();
    //     cout << "The wait is over, chooms!" << endl;
    // }

    // Creating a filestream, where we can write values to from our fine grain scan
    string filename2 = "finegrain.txt";
    ofstream ofile_finegrain;
    ofile_finegrain.open(filename2);

    for (double w_v = 2.0; w_v < 2.4; w_v += 0.004) {

            // "Assembling" the Penning trap
            PenningTrap myTrap(B0, V0, d, C, V, 0.7, w_v);

            // Adding a particle
            for (int i = 0; i < 25; i++) {
                vec r = vec(3).randn() * 0.1 * myTrap.d;  // random initial position
                vec v = vec(3).randn() * 0.1 * myTrap.d;  // random initial velocity

                Particle particle = Particle(q1,m1,r,v);
                myTrap.add_particle(particle);
            }
            
            for (int j = 0; j <n_steps; j++)
            {
                myTrap.change_time(j*dt);
                myTrap.evolve_system("RK4", dt);
            }
            //cout << myTrap.particles_inside() << endl;

            int counter = myTrap.particles_inside();
            ofile_finegrain << setw(width) << setprecision(prec) << scientific << w_v
                            << setw(width) << setprecision(prec) << scientific << counter
                            << endl;
        }

        ofile_finegrain.close();
        cout << "The wait is over, chooms!" << endl;

    // All is (hopefully) well. Return with error code 0
    return 0;
}
