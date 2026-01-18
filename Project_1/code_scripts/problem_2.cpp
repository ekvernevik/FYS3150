
// Including relevant libraries
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Programme that calculates and writes the y-vals and corresponding x-vals for the 1D Poisson distribution to an output file
int main() {

    string filename = "data.txt";
    ofstream ofile;
    ofile.open(filename);

    // Defining known params
    double x_min = 0.0;
    double x_max = 1.0;
    int n = 100;

    // Setting a stepsize
    double h = (x_max-x_min) / n;

    // Initializing x-and y-vals
    double x = x_min;
    double y =  0;

    int width = 12;
    int prec = 4;

    for (int i=0; i <= n; i++) {
        // Write a line with the current x and y values (nicely formatted!) to file
        ofile << setw(width) << setprecision(prec) << scientific << x
              << setw(width) << setprecision(prec) << scientific << y
              << endl;
        // Update x and y values
        x += h;
        y = 1 - (1-exp(-10))*x-exp(-10.*x);
    }

    // Close the output file
    ofile.close();

    
    // All is well. Exit program with return code 0.
    return 0;
}