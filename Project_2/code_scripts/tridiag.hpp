// Header-file for creating a tridiagonal matrix, and finding its eigenvalues and eigenvectors

// Including relevant libraries
#include <stdio.h>
#include <iostream>
#include <armadillo>
#include <math.h>

// Function: takes in arguments for N, the diagonal, and the sub- and super diagonal, and creates a tridiag matrix.
arma::mat tridiag(int N, double a, double b, double c) {

    // Creating a matrix of N x N dimensions
    arma::mat A = arma::mat(N, N);
    A(0, 0) = b; // First diagonal element

    // For-loop the initialize the diagonal, sub- and super diagonal with values
    for (int i = 0; i<N-1; i++) {
        A(i, i+1) = a;      // Super diagonal
        A(i+1, i+1) = b;    // Diagonal
        A(i+1, i) = c;      // Sub diagonal
    }

    // Returns tridiagonal matrix
    return A;
}

// Function: takes in arguments for N, the super- and subdiagonal (here both are a), and the diagonal, and finds eigvals
arma::vec tridiag_eigvals(int N, double a, double d) {

    // Creating a vector that is N-elements long
    arma::vec eigval = arma::vec(N);

    // For-loop to assign an eigenval to each index in eigval
    for (int i=0; i<N; i++) {
        eigval(i) = d + 2*a*cos(((i+1)*M_PI)/(N+1));
        }

    // Returns a vector of eigenvals
    return eigval;
}

// Function: takes in arguments for N, and finds eigvecs
arma::mat tridiag_eigvecs(int N) {

    // Creating a matrix of N x N dimensions
    arma::mat v_eig = arma::mat(N, N);

    // For-loop to assign each column with an eigenvector
    for (int i = 0; i < N; i++) {
        arma::vec vi = arma::vec(N);
        
        for (int j = 0; j < N; j++) {
            vi(j) = sin((j+1)*(i+1)*M_PI/(N+1));
        }

        v_eig.col(i) = arma::normalise(vi);
    }

    // Returns a matrix of eigenvectors
    return v_eig;

}
