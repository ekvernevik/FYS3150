// The PenningTrap class

#ifndef __PenningTrap_hpp__
#define __PenningTrap_hpp__

#include <armadillo>

#include "Particle.hpp"

class PenningTrap
{
    public:
        // Member variables
        double B0;
        double V0;
        double d;
        std::vector<Particle> particle_collection;

        bool Coulomb_interactions;
        bool time_dependent_V0; 
        double time; // Holds the time
        double f;
        double omega_V;

        // Constructor
        PenningTrap(double B0_in, double V0_in, double d_in, bool Coulomb_interactions_in, bool time_dependent_V0_in, double f_in, double omega_V_in);

        // Add a particle to the trap
        void add_particle(Particle particle_in);

        // External electric field at point r=(x,y,z)
        arma::vec external_E_field(arma::vec r); 

        // External magnetic field at point r=(x,y,z)
        arma::vec external_B_field(arma::vec r);

        // Force on particle_i from particle_j
        arma::vec force_particle(int i, int j);

        // The total force on particle_i from the external fields
        arma::vec total_force_external(int i);

        // The total force on particle_i from the other particles
        arma::vec total_force_particles(int i);

        // The total force on particle_i from both external fields and other particles
        arma::vec total_force(int i);

        // Evolve the system using one of two methods, Forward Euler or RK4
        void evolve_system(const std::string& method, double dt);

        // Analyical solution for the motion of the Calcium-ion
        void analytical_sol(double t);

        // Writes solutions found using a numerical method, to their respective files
        void write_to_file(std::string method, double t_tot, int n_steps);

        void change_time(double t);
        
        // Counts particles inside
        int particles_inside();
};

#endif