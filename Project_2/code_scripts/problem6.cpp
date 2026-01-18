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

    for (int i = 1; i < 3; i++) {

        // Creating an open filestream
        string filename = "jacobi_data" + to_string(i) + ".txt";
        ofstream ofile;
        ofile.open(filename);

        int width = 12;

        // Defining params
        int n = pow(10, i);     // Number of steps
        int N = n-1;            // Size of matrix
        double h = 1./n;        // Stepsize
        double a = -1/(h*h);    // Super and sub-diagonal
        double d = 2/(h*h);     // Diagonal

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

        // Finding the indices for the eigvals, and rearranging eigvec
        uvec eigval_indices = sort_index(eigenvalues);
        eigenvectors = eigenvectors.cols(eigval_indices);
        

        // Write eigvecs corresponding to three lowest eigvals into filestream
        ofile << setw(width) << scientific << eigenvectors.cols(0,2) << endl;
        
        // Close output file
        ofile.close();



        // Analytical solution
        string filename_analytical = "analytical_data" + to_string(i) + ".txt";
        ofile.open(filename_analytical);
        mat v = tridiag_eigvecs(N);
        v.cols(2,3) = -v.cols(2,3); // Last eigenvector is opposite to calculation
        ofile << setw(width) << scientific << v.cols(0,2) << endl;
        ofile.close();
        }
    

    // The code works *chefs kiss*. Return errorcode 0;
    return 0;
}