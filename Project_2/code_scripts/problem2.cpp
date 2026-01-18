// Programme for setting up a tridiagonal matrix A, and checking that the results from armadillo::eig_sym()
// agrees with analytical results.

// Including relevant libraries
#include <stdio.h>
#include <iostream>
#include <armadillo>
#include <math.h>
#include "tridiag.hpp"

using namespace std;
using namespace arma;

// Function: Applies the tridiag_eigvals()- and tridiag_eigvecs()-methods from "tridiag.hpp" on a tridiagonal matrix
int main() {
    // Creating tridiagonal matrix
    int n = 7;              // Number of steps
    double h = 1./n;        // Stepsize
    double a = -1/(h*h);    // Super and sub-diagonal
    double d = 2/(h*h);     // Diagonal

    int N = n-1;            // Size of matrix

    mat A = tridiag(N, a, d, a);
    cout << "Tridiagonal matrix" << endl << A;

    // Armadillo solution
    vec eigval;
    mat eigvec;
    eig_sym(eigval, eigvec, A);

    // Analytical solution
    vec lmbda = tridiag_eigvals(N, a, d);
    mat v = tridiag_eigvecs(N);

    // Comparing eig-solutions for arma and analytical
    cout << "\n";
    cout << "Eigenvalues armadillo" << endl <<  eigval;
    cout << "\n";
    cout << "Eigenvalues analytical" << endl << lmbda;

    cout << "\n";
    cout << "\n";

    cout << "Eigenvectors armadillo" << endl << eigvec;
    cout << "\n";
    cout << "Eigenvectors analytical" << endl << v;
    
    // All is well. Return with errorcode 0
    return 0;
}
