// Definitions of mehtods used in the Crank Nicolson scheme

#include "crank_nicolson.hpp"

// Constructs A- and B-matrices to be used in the Crank-Nicolson method
void initialize_CrankNicolson(Wave& yourWave, double dt)
{
   // Defining parameters
    int d = yourWave.d;                     // Number of internal points
    double h = yourWave.h;                  // Distance between points

    std::complex<double> r(0, dt/(2*h*h));  // Variable for r = i*dt / 2*h^2
    std::complex<double> r_v(0, dt/2);      // Variable for r_v = i*dt / 2
    
    // Creating vectors
    arma::cx_vec a = arma::cx_vec(d*d);     // Complex vector for a_k
    arma::cx_vec b = arma::cx_vec(d*d);     // Complex vector for b_k

    // Filling the vectors
    for (int i = 1; i <= d; i++)
    {
        for (int j = 1; j <= d; j++)
        {
            a(yourWave.k_index(j,i)) = 1.+(4.*r)+r_v*yourWave.V(j,i);
            b(yourWave.k_index(j,i)) = 1.-(4.*r)-r_v*yourWave.V(j,i);
        }
    }
    

    // Filling the matrices A and B with values
    for (int s = 0; s < d; s++){    // For every sub-matrix

        // main diagonal
        for (int i = 0; i < d; i++){
            int k = i + s*d;
            yourWave.A(k, k) = a(k);
            yourWave.B(k, k) = b(k);
        }

        // sub/super diagonal
        for (int i = 0; i < d-1; i++){
            int k = i + s*d;
            yourWave.A(k + 1, k) = -r; // sub
            yourWave.A(k, k + 1) = -r; // super
            yourWave.B(k + 1, k) = r;  // sub
            yourWave.B(k, k + 1) = r;  // super
        }
    }
    
    // band diagonals
    yourWave.A.diag(d).fill(-r);
    yourWave.A.diag(-d).fill(-r);
    yourWave.B.diag(d).fill(r);
    yourWave.B.diag(-d).fill(r);

}


// Calculates next state
void CrankNicolson(Wave& yourWave){
    // Matrix multiplication
    arma::cx_vec b_vec = yourWave.B*yourWave.u_vec;
    
    // Solve matrix equation
    yourWave.u_vec = arma::spsolve(yourWave.A, b_vec);

    // Change the inner points of the u-matrix with the new u_vec
    yourWave.vec_to_mat();
}
