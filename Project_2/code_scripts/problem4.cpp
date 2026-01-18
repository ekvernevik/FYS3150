// Programme for an eigensolver, with the Jacobi rotation algorithm implemented

// Including relevant libraries
#include <stdio.h>
#include <iostream>
#include <armadillo>
#include "tridiag.hpp"
#include "jacobi_eigensolver.hpp"

using namespace std;
using namespace arma;

// Programme: Applies "jacobi_rotate.hpp" and "jacobi_eigensolver.hpp" to a tridiag-matrix, to solve for eigvecs/vals
int main(){
    // Defining params
    int n = 7;              // Number of steps
    double h = 1./n;        // Stepsize
    double a = -1/(h*h);    // Super and sub-diagonal
    double d = 2/(h*h);     // Diagonal

    int N = n-1;            // Size of matrix

    mat A = tridiag(N, a, d, a); // Creating tridiag-matrix

    // Setting tolerance
    double eps = 1.e-14;

    // Setting initial- and maximum number of iterations
    int maxiter = N*N*N;
    int iterations = 0;

    // Initializing a vector and matrix for the eigvals and eigvecs respectively
    vec eigenvalues = vec(N);
    mat eigenvectors = mat(N,N);

    // Solving for eigvals and eigvecs, and assigning them to the vector and matrix above
    jacobi_eigensolver(A, eps, eigenvalues, eigenvectors, maxiter, iterations);

    // Printing the sorted eigvals and eigvecs
    uvec eigval_indices = sort_index(eigenvalues);
    cout << "Eigenvalues: " << endl << eigenvalues(eigval_indices) << "\n"; 
    eigenvectors = eigenvectors.cols(eigval_indices);
    cout << "Eigenvectors: " << endl << eigenvectors;

    // The code works *chefs kiss*. Return errorcode 0;
    return 0;
}
