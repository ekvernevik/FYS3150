// Header-file containing a function to find the largest off-diagonal element of a matrix

// Including relevant libraries
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <armadillo>

// Function: finding max off-diagonal element for a symmetric matrix
double max_offdiag_symmetric(const arma::mat& A, int& k, int& l){
    int n_rows = A.n_rows;

    // Setting the maximum value to 0
    double maxval = 0.;
    // Looping through the rows and cols
    for (int i = 0 ; i < n_rows-1 ; i++) {
        for (int j = i+1 ; j < n_rows ; j++){
            // Updating maxval if the abs (fabs for doubles) of the new off-diag element is larger
            if (fabs(A(i,j)) > fabs(maxval)) {
                maxval = A(i,j);
                // Setting the matrix indices to be the two int references, int& k and int& l
                k = i;
                l = j;
            }
            
        }
    }

    // Returning value of largest off-diag element
    return maxval;
}
