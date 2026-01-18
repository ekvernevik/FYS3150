// Programme for an eigensolver, with the Jacobi rotation algorithm implemented

// Including relevant libraries
#include <stdio.h>
#include <iostream>
#include <armadillo>
#include <fstream>
#include "tridiag.hpp"
#include "jacobi_eigensolver.hpp"

using namespace std;
using namespace arma;

// Programme: Applies "jacobi_rotate.hpp" and "jacobi_eigensolver.hpp" to a tridiag-matrix, to solve for eigvecs/vals
int main(){

    // Creating an open filestream
    string filename = "iteration_data.txt";
    ofstream ofile;
    ofile.open(filename);

    int width = 12;

    for (int i = 1; i <= 15; i++) {
        
        int N = i * 10;            // Size of matrix

        // Defining params
        int n = N+1;              // Number of steps
        double h = 1./n;        // Stepsize
        double a = -1/(h*h);    // Super and sub-diagonal
        double d = 2/(h*h);     // Diagonal

        mat A = tridiag(N, a, d, a); // Creating tridiag-matrix
        
        // Segment for testing in task b)
        // mat A = mat(N, N).randn();
        // A = symmatu(A);

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

        // Write a line with the current x and y values (nicely formatted!) to file
        ofile << setw(width) << scientific << iterations
              << setw(width) << scientific << N
              << endl;

    }

    // The code works *chefs kiss*. Return errorcode 0;
    return 0;
}