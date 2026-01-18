// Programme for numerically solving the one-dimensional Poisson equation using the general algorithm.

// Including relevant libraries
#include <time.h>
#include <armadillo>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <list>

using namespace std;
using namespace arma;

// Implementing our source term as a callable function.
double f(double x) {
    return 100*exp(-10*x);
}

double u(double x) {
    return 1 - (1-exp(-10))*x-exp(-10.*x);
}

// Programme that writes x-and v-vals to a file.
int main() {


    // For loop to compute x-and v-vals for different powers of 10.
    for (int i=1; i<=7; i++) {

        // Start clock
        clock_t t1 = clock();

        // Creating and opening the file we want to funnel the vals into.
        string filename = "p7_output" + to_string(i) + ".txt";
        ofstream ofile;
        ofile.open(filename);

        // Defining known params for our equation.
        double x_min = 0.;
        double x_max = 1.;
        int n = pow(10, i);
        double h = (x_max-x_min) / n;

        // Tridiagonal "matrix", specified by the signature (-1, 2, -1).
        vec a = vec(n).fill(-1.);
        vec b = vec(n).fill(2.);
        vec c = vec(n).fill(-1.);

        // Creating empty vectors of length n+1.
        vec b_tilde = vec(n+1);
        vec g = vec(n+1);
        vec g_tilde = vec(n+1);

        vec v = vec(n+1);
        v(0) = 0;
        v(n) = 0;

        vec x = arma::linspace(x_min, x_max, n+1);

        // Defining g_{1} and g_{n-1}, then solving g_{i} for n = 2, 3, 4, ..., n-2.
        g(1) = h*h*f(x(1)) + v(0);
        g(n-1) = h*h*f(x(n-1)) + v(n); 
        for (int i = 2; i<=n-2; i++) {
                g(i) = f(x(i))*h*h;
            }

        // Forward substitution
        b_tilde(1) = b(1);
        g_tilde(1) = g(1);
        for (int i = 2; i <= n-1; i++) {
            b_tilde(i) = b(i) - (a(i)/b_tilde(i-1))*c(i-1);
            g_tilde(i) = g(i) - (a(i)/b_tilde(i-1))*g_tilde(i-1);
        }

        // Back substitution
        v(n-1) = g_tilde(n-1)/b_tilde(n-1);
        for (int i=n-2; i > 0; i--) {
            v(i) = (g_tilde(i)-c(i)*v(i+1))/b_tilde(i);
        }

        // Defining params for the width and precision, for when we write x-and v-vals to our output file.
        int width = 30;
        int prec = 14;

        // Writing our solutions for v-vals and their corresponding x-val to our output file.
        for (int i=0; i<=n; i++) {
            ofile << setw(width) << setprecision(prec) << scientific << x(i)
                << setw(width) << setprecision(prec) << scientific << v(i)
                << setw(width) << setprecision(prec) << scientific << u(x(i))
                << endl;
        }

        // All the computed data has been funneled into our file. Closing it.
        ofile.close();

        // End clock
        clock_t t2 = clock();

        // Calculate the elapsed time.
        double duration_seconds = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
        
        // Print elapsed time for simulation for 1e+n steps, where n=1, 2, 3, ..., 7
        cout << "Elapsed time for 1e"+to_string(i) + " steps: " << duration_seconds << endl;
    }


    // Mission success. Return with error code 0
    return 0;

}