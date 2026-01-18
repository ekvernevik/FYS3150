// Header-file containing a function to do solve an eigenfunction

// Including relevant libraries
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <armadillo>
#include "max_offdiag_symmetric.hpp"
#include "jacobi_rotate.hpp"

// Function: Eigensolver
void jacobi_eigensolver(const arma::mat& A, double eps, arma::vec& eigenvalues, arma::mat& eigenvectors, 
                        const int maxiter, int& iterations){
    // Defining params
    int k, l;   // Matrix indices
    int n_rows = A.n_rows;  // Setting n to be N-rows in A
    arma::mat R = arma::mat(n_rows,n_rows,arma::fill::eye); // Creating an n x n identity matrix

    // Finding max offdiag value, and assigning its idices to k and l
    double maxval = max_offdiag_symmetric(A,k,l);
    arma::mat temp = A; // A non-const copy of A, so that we can update elements in A

    // While-loop to rotate temp and find its max offdiag value, until abs(maxval) is greater than our tolerance
    while (fabs(maxval) > eps){
        jacobi_rotate(temp,R,k,l);  // Jacobi rotation algorithm
        iterations++;               // Increasing the iteration count
        maxval = max_offdiag_symmetric(temp,k,l);   // Finding max offdiag val
        
        // If-statement, that stops the programme if the number of iterations goes beyond maxiter
        if (iterations > maxiter){
            std::cout << "Reached max number of iterations = " << maxiter << std::endl;
            break;
        }
    }

    // Assigning the eigvals along the diagonal in temp, to the eigenvalues-vector
    for (int i=0 ; i < n_rows; i++){
        eigenvalues(i) = temp(i,i);
    }

    // Assigning the eigvecs in R to the eigenvectors-matrix
    eigenvectors = R;
}
