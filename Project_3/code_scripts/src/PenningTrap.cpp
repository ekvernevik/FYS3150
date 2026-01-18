// Definitions for the functions in the PenningTrap class

// Including relevant libraries
#include <armadillo>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

// Including our header-files for our two classes
#include "PenningTrap.hpp"
#include "Particle.hpp"

// Defining a variable for the Coulomb-constant
double k_e = 1.38935333 * std::pow(10, 5); // [u (m*10^-6)^3 / (s*10^-6)^2 e^2]

// Constructor for the PenningTrap-class
PenningTrap::PenningTrap(double B0_in, double V0_in, double d_in, bool Coulomb_interactions_in, bool time_dependent_V0_in, double f_in, double omega_V_in) 
{
    B0 = B0_in;     // Magnetic field strength
    V0 = V0_in;     // Applied electric potential
    d = d_in;       // Characteristic dimension

    time_dependent_V0 = time_dependent_V0_in;
    Coulomb_interactions = Coulomb_interactions_in;

    f = f_in;
    omega_V = omega_V_in;
}

// Method: add a particle to the trap
void PenningTrap::add_particle(Particle particle_in)
{
    particle_collection.push_back(particle_in);
}

// Method: Initialize an external electric field at point r=(x,y,z)
arma::vec PenningTrap::external_E_field(arma::vec r)
{
    if (time_dependent_V0)
    {
        //std::cout << time << std::endl;
        double V = V0*(1+f*cos(omega_V*time));
        return V/(d*d) * arma::vec(" 1 1 -2") % r;
    }
    else{
        return V0/(d*d) * arma::vec(" 1 1 -2") % r;
    }
    //return V0/(d*d) * arma::vec(" 1 1 -2") % r;
    
}

// Method: Initialize an external magnetic field at point r=(x,y,z)
arma::vec PenningTrap::external_B_field(arma::vec r)
{
    return B0*arma::vec("0 0 1");
}

// Method: Calculate the force on particle_i from particle_j
arma::vec PenningTrap::force_particle(int i, int j)
{
    double q1 = particle_collection.at(i).q;        // Charge of particle_i
    double q2 = particle_collection.at(j).q;        // Charge of particle_j
    arma::vec r1 = particle_collection.at(i).r;     // Pos of particle_i
    arma::vec r2 = particle_collection.at(j).r;     // Pos of particle_j

    return k_e * q1*q2 / ( (r1-r2)%(r1-r2) ) % ( (r1-r2)/abs(r1-r2) ); // Coulomb's law

}

// Method: Calculate the total force on particle_i from the external fields
arma::vec PenningTrap::total_force_external(int i)
{
    double q = particle_collection.at(i).q;     // Charge of particle_i
    arma::vec r = particle_collection.at(i).r;  // Pos of particle_i
    arma::vec v = particle_collection.at(i).v;  // Vel of particle_i
    if (arma::norm(r) > d){
        return arma::zeros(3); // Returns zero-vector
    }
    else {
        return q*(external_E_field(r) + arma::cross(v, external_B_field(r))); // Lorentz force
    }
    
}

// Method: Calculate the total force on particle_i from the other particles
arma::vec PenningTrap::total_force_particles(int i)
{
    double q = particle_collection.at(i).q;     // Charge of particle_i
    arma::vec r = particle_collection.at(i).r;  // Pos of particle_i
    arma::vec force = arma::vec(3);             // Empty force vector
    
    // For-loop, to iterate through each particle
    for (int j = 0; j < particle_collection.size(); j++) {
        if (j != i) {
            force += force_particle(i,j);
        }
    }
    return force; // Force of Coulomb interactions
}

// Method: Calculate the total force on particle_i from both external fields and other particles
arma::vec PenningTrap::total_force(int i)
{
    if (Coulomb_interactions)
    {
        return total_force_external(i) + total_force_particles(i);  // Sum of all forces
    }
    else
    {
        return total_force_external(i); // Only force from external field
    }
}

// Method: Evolves the Penning trap system, using one of two numerical approaches (FE or RK4), or an analytical solution
void PenningTrap::evolve_system(const std::string& method, double dt)
{
    if (method == "RK4") {
        std::vector<Particle> initial_particle_collection = particle_collection; // Temporary collection of particles to store initial position and velocity

        // Initialise matrices containing k_v-vectors for all particles
        arma::mat k_v1 = arma::mat(3,particle_collection.size()); 
        arma::mat k_v2 = arma::mat(3,particle_collection.size());
        arma::mat k_v3 = arma::mat(3,particle_collection.size());
        arma::mat k_v4 = arma::mat(3,particle_collection.size());

        arma::mat k_r1 = arma::mat(3,particle_collection.size());
        arma::mat k_r2 = arma::mat(3,particle_collection.size());
        arma::mat k_r3 = arma::mat(3,particle_collection.size());
        arma::mat k_r4 = arma::mat(3,particle_collection.size());
        
        // Evaluate k1
        for (int i = 0; i < particle_collection.size(); i++){ // for every particle
            Particle& particle = particle_collection.at(i);
            arma::vec a = total_force(i)/particle.m;    // Evaluate acceleration
            
            k_v1.col(i) = dt*a;            // Fill k_v1 value for particle i
            k_r1.col(i) = dt*particle.v;   // Fill k_x1 value for particle i
        }

        // Update position and velocity to use in k2
        for (int i = 0; i < particle_collection.size(); i++){ // for every particle
            Particle& particle = particle_collection.at(i);
            Particle initial_particle = initial_particle_collection.at(i);
            particle.v = initial_particle.v + 0.5*k_v1.col(i); // Update velocity
            particle.r = initial_particle.r + 0.5*k_r1.col(i); // Update position
         }

        // Evaluate k2
        for (int i = 0; i < particle_collection.size(); i++){ // for every particle
            Particle& particle = particle_collection.at(i);
            arma::vec a = total_force(i)/particle.m;    // Force in acceleration is now calculated at position r + 0.5k_r1
            
            k_v2.col(i) = dt*a;            // Fill k_v2 value for particle i
            k_r2.col(i) = dt*particle.v;   // Fill k_x2 value for particle i 
        }

        // Update position and velocity to use in k3
        for (int i = 0; i < particle_collection.size(); i++){ // for every particle
            Particle& particle = particle_collection.at(i);
            Particle initial_particle = initial_particle_collection.at(i);
            particle.v = initial_particle.v + 0.5*k_v2.col(i); // Update velocity
            particle.r = initial_particle.r + 0.5*k_r2.col(i); // Update position
         }

        // k3
        for (int i = 0; i < particle_collection.size(); i++){ // for every particle
            Particle& particle = particle_collection.at(i);
            arma::vec a = total_force(i)/particle.m;    // Force in acceleration is now calculated at position r + 0.5k_r2
            
            k_v3.col(i) = dt*a;            // Fill k_v3 value for particle i
            k_r3.col(i) = dt*particle.v;   // Fill k_x3 value for particle i 
        }

        // Update position and velocity to use in k4
        for (int i = 0; i < particle_collection.size(); i++){ // for every particle
            Particle& particle = particle_collection.at(i);
            Particle initial_particle = initial_particle_collection.at(i);
            particle.v = initial_particle.v + k_v3.col(i); // Update velocity
            particle.r = initial_particle.r + k_r3.col(i); // Update position
        }

        // k4
        for (int i = 0; i < particle_collection.size(); i++){ // for every particle
            Particle& particle = particle_collection.at(i);
            arma::vec a = total_force(i)/particle.m;    // Force in acceleration is now calculated at position r + k_r3
            
            k_v4.col(i) = dt*a;            // Fill k_v4 value for particle i
            k_r4.col(i) = dt*particle.v;   // Fill k_x4 value for particle i 
        }

        // Update position and velocity with k-values
        for (int i = 0; i < particle_collection.size(); i++){ // for every particle
            Particle initial_particle = initial_particle_collection.at(i); // Initial particle
            Particle& particle = particle_collection.at(i);                // Reference to particle to change

            particle.v = initial_particle.v + (k_v1.col(i) + 2.*k_v2.col(i) + 2.*k_v3.col(i) + k_v4.col(i))/6.;
            particle.r = initial_particle.r + (k_r1.col(i) + 2.*k_r2.col(i) + 2.*k_r3.col(i) + k_r4.col(i))/6.;
        }

    } else if (method == "FE") {

        arma::mat force = arma::mat(3, particle_collection.size());

        for (int i= 0; i < particle_collection.size(); i++) {
            force.col(i) = total_force(i);
        }

        for (int i = 0; i < particle_collection.size(); i++){ // for every particle
            Particle& particle = particle_collection.at(i);

            arma::vec v0 = particle.v; // Store original velocity (else: Euler Cromer)
            // Forward Euler method
            arma::vec a = force/particle.m;
            particle.v = particle.v + dt*a;     // Update velocity
            particle.r = particle.r + dt*v0;    // Update position
        }

    } else {

        std::cout << "Unsupported method: " << method << std::endl;
        return;
    }
}

// Method: Calculate analytical solution of the z-component of the particles position vector
void PenningTrap::analytical_sol(double t) 
{
    double x_0 = 20.;   // How do i get these values directly?
    double z_0 = 20.;
    double v_0 = 25.;
     
    Particle& particle = particle_collection.at(0); // Reference to particle at each time

    double omega_0 = (particle.q*B0)/particle.m;
    double omega_z = sqrt((2*particle.q*V0)/(particle.m*d*d));

    double omega_pluss = (omega_0 + sqrt(omega_0*omega_0 - 2.*omega_z*omega_z))/2.;
    double omega_minus = (omega_0 - sqrt(omega_0*omega_0 - 2.*omega_z*omega_z))/2.;

    double A_pluss =  (v_0 + omega_minus*x_0)/(omega_minus-omega_pluss);
    double A_minus = -(v_0 + omega_pluss*x_0)/(omega_minus-omega_pluss);

    particle.r(0) =  A_pluss*cos(omega_pluss*t) + A_minus*cos(omega_minus*t); // Update x-position
    particle.r(1) = -A_pluss*sin(omega_pluss*t) - A_minus*sin(omega_minus*t); // Update y-position
    particle.r(2) = z_0*cos(omega_z*t);                                       // Update z-position
}

// Method: Write results of FE, RK4, and analytical solution to a file
void PenningTrap::write_to_file(std::string method, double t_tot, int n_steps)
{
    double dt = t_tot/n_steps;
    if (method == "RK4" || method == "FE") {

        std::string filename = method + "_pos_" + std::to_string(n_steps) + ".txt";
        std::ofstream ofile(filename);

        std::string filename2 = method + "_vel_" + std::to_string(n_steps) + ".txt";
        std::ofstream ofile2(filename2);


        if (ofile.is_open()) {

            // Params for our filestream
            int width = 12;
            int prec = 4;

            // For-loop, to iterate through each timestep
            for (int i = 0; i < n_steps; i++) {
                change_time(i*dt);
                // For-loop, to iterate through each component (i.e. x, y, z) in the position vector, r
                for (int j = 0; j < 3; j++ ) {
                    
                    // Adding the timestep, for each component in r = (x, y, z)
                    ofile << i*dt;
                    ofile2 << i*dt;

                    // For-loop, to iterate through each particle in the Penning trap
                    for (int k = 0; k < particle_collection.size(); k++) {
                        
                        // Adding each component in r = (x, y, z) for each particle in the Penning trap
                        ofile << std::setw(width) << std::setprecision(prec) << std::scientific << particle_collection.at(k).r(j);
                        ofile2 << std::setw(width) << std::setprecision(prec) << std::scientific << particle_collection.at(k).v(j);
                    }
                    ofile << std::endl;
                    ofile2 << std::endl;
                }

                // Advancing the time-evolution of the Penning trao, using the Forward-Euler-method
                evolve_system(method, dt);
            }

            // Closing our filestream
            ofile.close();
            ofile2.close();

            std::cout << "\n" << "Simulated " << particle_collection.size() << " particle(s) using the " << method << "-method" 
                      << ", for a total runtime: " << t_tot << " [micro-s], with n_steps = "<< n_steps << std::endl;

            std::cout << "Simulated datavals are written to: " << filename << " and " << filename2 << std::endl;
        }

    }  else if (method == "analytical") {

        std::string filename = "analytical_" + std::to_string(n_steps) + "_result.txt";   
        std::ofstream ofile(filename);

        if (ofile.is_open()) {
            // Params for our filestream
            int width = 12;
            int prec = 4;

            // For-loop, to iterate through each timestep
            for (int i = 0; i < n_steps; i++) {
                
                ofile << std::setw(width) << std::setprecision(prec) << std::scientific << i*dt
                      << std::setw(width) << std::setprecision(prec) << std::scientific << particle_collection.at(0).r(0)
                      << std::endl;
                ofile << std::setw(width) << std::setprecision(prec) << std::scientific << i*dt
                      << std::setw(width) << std::setprecision(prec) << std::scientific << particle_collection.at(0).r(1)
                      << std::endl;
                ofile << std::setw(width) << std::setprecision(prec) << std::scientific << i*dt
                      << std::setw(width) << std::setprecision(prec) << std::scientific << particle_collection.at(0).r(2)
                      << std::endl;
                analytical_sol(i*dt);
            }

            // Closing our filestream
            ofile.close();

            std::cout << "\n" << "Simulated " << particle_collection.size() << " particle(s) using the " << method << "-method" 
                      << ", for a total runtime: " << t_tot << " [micro-s], with n_steps = "<< n_steps << std::endl;

            std::cout << "Simulated datavals are written to: " << filename << std::endl;
        }
    } else {
        std::cout << "Unsupported method: " << method << std::endl;
    }
}

void PenningTrap::change_time(double t)
{
    time = t;
}

int PenningTrap::particles_inside() 
{
    int counter = 0;
    for (int i = 0; i < particle_collection.size(); i++){
        arma::vec r = particle_collection.at(i).r;
        
        if (arma::norm(r) <= d){
            counter++;
        }
    }
    return counter;
}