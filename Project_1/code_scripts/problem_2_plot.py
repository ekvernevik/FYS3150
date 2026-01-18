# Importing relevant modules
import numpy as np
import matplotlib.pyplot as plt

# Function to fetch x-and y-vals
def plot_data(filename):
    x_vals = np.loadtxt(filename, usecols=(0))
    y_vals = np.loadtxt(filename, usecols=(1))

    # Plotting values from .txt-file
    plt.figure()
    plt.plot(x_vals, y_vals)
    plt.xlabel("x")
    plt.ylabel("f(x) = $100 e^{-10x}$")
    plt.legend()
    plt.savefig("problem2.pdf")
    plt.show()

# Calling function and plotting vals
plot_data("data.txt")

