// Definitions of the methods in the Wave class

#include "wave.hpp"

// Constructor
Wave::Wave(double h_in, double x_c_in, double y_c_in, double sigma_x_in, double sigma_y_in, double p_x_in, double p_y_in, double v_0_in, int n_slits_in)
{
    h = h_in;
    x_c = x_c_in;
    y_c = y_c_in;
    sigma_x = sigma_x_in;
    sigma_y = sigma_y_in;
    p_x = p_x_in;
    p_y = p_y_in;
    v_0 = v_0_in;
    n_slits = n_slits_in;

    M = 1/h+1;  // Number of points along an axis
    d = M-2;    // Number of internal points along an axis


    // Set up initial state 
    u = arma::cx_mat(M,M);
    
    double sigma_x_squared_2 = 2*sigma_x*sigma_x; // Saving some FLOPs
    double sigma_y_squared_2 = 2*sigma_y*sigma_y;

    for (int i = 1; i <= d; i++){
        for (int j = 1; j <= d; j++){
            // real exp
            double real_part = -(((i*h-x_c)*(i*h-x_c))/sigma_x_squared_2) -(((j*h-y_c)*(j*h-y_c))/sigma_y_squared_2); 
           
            // imag exp
            double imag_part = p_x*i*h + p_y*j*h;

            double real = exp(real_part)*cos(imag_part);

            // imag
            double imag = exp(real_part)*sin(imag_part);

            std::complex<double> myComplex(real,imag);
            u(j,i) = myComplex;
        }
    }
    
    // Normalize initial state
    double Z = 0;
    arma::cx_mat u_conj = conj(u);
    for (int i = 0; i < M; i++){
        for (int j = 0; j < M; j++){
            Z += real(u_conj(j, i) * u(j, i));
        }
    }
    u = u/sqrt(Z);


    // Create vector of internal points
    u_vec = arma::cx_vec(d*d);
    for (int i = 1; i <= d; i++)
    {
        for (int j = 1; j <= d; j++)
        {
            u_vec(k_index(j,i)) = u(j,i);
        }
    }



    // Initialize constant potential-barrier
    V = arma::cx_mat(M,M);

    double wall_thickness = 0.02;
    double slit_separation = 0.05;
    double centre = 0.5;

    double x_start = (centre - wall_thickness/2.)/h + 1.;
    double x_stop = (centre + wall_thickness/2.)/h;
    for (int i = round(x_start); i <= round(x_stop); i++){
  
        // Down to first slit
        double y_stop1 = (centre - (n_slits-0.5)*slit_separation)/h;
        for (int j = 1; j < round(y_stop1); j++){
            V(j,i) = v_0;
        }

        // Wall between slits
        for (int n = 1; n < n_slits; n++){
            double y_start2 = y_stop1 + (2.*n-1.)*slit_separation/h + 1.;
            double y_stop2 = y_stop1 + 2.*n*slit_separation/h;
            for (int j = round(y_start2); j < round(y_stop2); j++){
                V(j,i) = v_0;
            }
        }

        // From last slit and down
        double y_start3 = (centre + (n_slits-0.5)*slit_separation)/h + 1.; // Using int or converting from double gives wrong result for n_slit = 2????
        for (int j = round(y_start3); j <= d; j++){
            V(j,i) = v_0;
        }
    }


    // Initialize A and B matrix for Crank Nicolson
    A = arma::sp_cx_mat(d*d, d*d);
    B = arma::sp_cx_mat(d*d, d*d);
}


// Method that converts i-and j-indices into a k-index
int Wave::k_index(int j, int i)
{
    return (j-1) + (i-1) * d;
}


// Mehtod that changes the inner points of the matrix u with values from the vector u_vec
void Wave::vec_to_mat(){
    for (int k = 0; k < d*d; k++){
        int j = k%d + 1;
        int i = k/d + 1;
        u(j,i) = u_vec(k);
    }
}
