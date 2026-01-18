# Script for reading a filename, and plotting three eigvecs corresponding to the three lowest eigvals

# Importing relevant modules
import numpy as np
import matplotlib.pyplot as plt

# Function: Unpack .txt-files into v (v1, v2, v3) and plot it against a dimensionless x-axis
def plot_data(filename):
    v1, v2, v3 = np.loadtxt(filename, unpack=True)
    v = np.array([v1,v2,v3])
    for i in range(3):
        # Adding boundary points
        vi = np.concatenate(([0], v[i]))
        vi = np.concatenate((vi, [0]))
        x = np.linspace(0, 1, len(vi))
        # Plotting vals
        plt.plot(x, vi, label = f"$v_{i}$ {filename[:-10]}")
    plt.xlabel("$\hat{x}$ [L]", fontsize = 15)
    plt.ylabel("$v$ [L]", fontsize = 15)
    plt.legend()

# Calling function
# n = 10
plot_data("jacobi_data1.txt")
plot_data("analytical_data1.txt")
plt.savefig("eigenvals_10.pdf") 
plt.show()
plt.close()

# n = 100
plot_data("jacobi_data2.txt")
plot_data("analytical_data2.txt")
plt.savefig("eigenvals_100.pdf") 
plt.show()