// Declarations of the methods in the Wave class

#ifndef __wave_hpp__
#define __wave_hpp__

#include <armadillo>    // For vectors and matrices
#include <cmath>        // For exp and round
#include <iostream>     // For extensive debugging

class Wave
{
    public:

        // Member variables
        int M;              // Number of points along each axis (including boundary points)
        double h;           // Distance between points
        int d;              // Number of internal points
        
        double x_c;         // x-coordinate for center of wave-packet
        double y_c;         // y-coordinate for center of wave-packet
        double sigma_x;     // Initial wave packet width in x-direction
        double sigma_y;     // Initial wave packet width in y-direction
        double p_x;         // Wave packet momentum in x-direction
        double p_y;         // Wave packet momentum in y-direction

        double v_0;         // Potential-barrier constant
        int n_slits;        // Number of slits

        arma::cx_mat u;     // Matrix that contains all the points
        arma::cx_vec u_vec; // Vector that contains the internal points

        arma::cx_mat V;     // Matrix that contains the potential-barrier

        arma::sp_cx_mat A;  // Sparse-complex-type matrix for A
        arma::sp_cx_mat B;  // Sparse-complex-type matrix for B
    

        // Constructor
        Wave(double h_in, double x_c_in, double y_c_in, double sigma_x_in, double sigma_y_in, double p_x_in, double p_y_in, double v_0_in, int n_slits_in);

        // Method that returns the k-value in a column vector from i- and j-coordinates from a matrix
        int k_index(int j, int i);

        // Mehtod that changes the inner points of the matrix u with values from the vector u_vec
        void vec_to_mat();
};


#endif
