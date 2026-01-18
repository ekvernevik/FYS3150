// Programme for finding the largest off-diagonal element of a symmetric matrix

// Including relevant libraries
#include <stdio.h>
#include <iostream>
#include <armadillo>
#include "max_offdiag_symmetric.hpp"

using namespace std;
using namespace arma;

// Function: Applies "max_offdiag_symmetric.hpp" on a defined matrix, and finds the largest offdiag value
int main() {

    // Making our matrix, and printing it
    mat A = mat("1 0 0 0.5 ; 0 1 -0.7 0 ; 0 -0.7 1 0 ; 0.5 0 0 1");
    cout << "Finding the maxval of the matrix:" << endl << A;

    // Creating variables for the matrix indices
    int k, l;

    // Assigning the value of the absolute value of the largest off-diag element to maxval
    double maxval = max_offdiag_symmetric(A, k, l);

    // Printing maxval, and the matrix indices for the element
    cout << "\n";
    cout << "Value of maxval: " << maxval << endl;
    cout << "Row index: " << k << endl;
    cout << "Col index: " << l << endl;

    // Alles ist gut, return error-code 0
    return 0;
}
