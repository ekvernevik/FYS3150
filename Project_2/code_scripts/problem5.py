# Script for plotting iterations against choices of N for an N x N matrix

# Importing relevant modules
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import linregress

# Function to fetch iterations and N-val
def plot_data(filename):
    iterations, N = np.loadtxt(filename, unpack=True)

    # Using regression to find the slope and intercept of the datavals
    slope, intercept, r, p, se = linregress(np.log10(N), np.log10(iterations))

    # Plotting values from .txt-file
    plt.figure(1)
    plt.loglog(N, iterations, "o", color = "r", label = "Datapoints")
    plt.loglog(N, N**slope*10**intercept, label = "Linearly fitted line")
    plt.xlabel("Choice of N",fontsize=15)
    plt.ylabel("Amount of iterations to reach $\epsilon$",fontsize=15)
    plt.legend(fontsize=15)
    plt.savefig("problem5.pdf")
    plt.show()

# Calling function
plot_data("iteration_data.txt")