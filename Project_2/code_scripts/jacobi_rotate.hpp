// Header-file containing a function to do a jacobi rotation
//  - Calculations below were found in a lecture note from 2022;
//    All of the calculations are labeled after their respective steps

// Including relevant libraries
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <armadillo>

// Function: Jacobi rotation algorithm
void jacobi_rotate(arma::mat& A, arma::mat& R, int k, int l){
    
    int n_rows = A.n_rows; // Setting n_rows to be N-rows in A
    
    // 3.1, Computing tau
    double tau = (A(l,l) - A(k,k)) / (2*A(k,l));


    // 3.2, Computing tan, cos, sin (t, c, s)
    double t;
    if (tau>0) {
        t = 1 / (tau + sqrt(1+tau*tau));
    }
    else {
        t = -1 / (-tau + sqrt(1+tau*tau));
    }
    double c = 1/sqrt(1+t*t);
    double s = c*t;


    // 3.3, Transforming the current matrix
    double A_kk = A(k,k); // Copy of A(k,k)
    A(k,k) = A_kk*c*c - 2*A(k,l)*c*s + A(l,l)*s*s;
    A(l,l) = A(l,l)*c*c + 2*A(k,l)*c*s + A_kk*s*s;
    A(k,l) = 0;
    A(l,k) = 0;
    
    // For-loop to iterate through matrix elements
    for (int i = 0; i < n_rows; i++) {
        if (i != k & i != l) {
            double A_ik = A(i,k); // Copy of A(i,k)
            A(i,k) = A_ik*c - A(i,l)*s;
            A(k,i) = A(i,k);
            A(i,l) = A(i,l)*c + A_ik*s;
            A(l,i) = A(i,l);

        }
    }

    // 3.4, Updating the rotation matrix
    for (int i = 0; i < n_rows; i++){
        double R_ik = R(i,k); // Copy of R(i,k)
        R(i,k) = R_ik*c - R(i,l)*s;
        R(i,l) = R(i,l)*c + R_ik*s;
    }
}
