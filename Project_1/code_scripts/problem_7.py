# Script for plotting the output data from problem_7.cpp

# Importing relevant modules.
import numpy as np
import matplotlib.pyplot as plt

# Loading data from our source term.
x_e = np.loadtxt("data.txt", usecols=0)
u_e = np.loadtxt("data.txt", usecols=1)

# Loading data from our approximations.
# Output data with n = 10
x1 = np.loadtxt("p7_output1.txt", usecols=0)
v1 = np.loadtxt("p7_output1.txt", usecols=1)

# Output data with n = 100
x2 = np.loadtxt("p7_output2.txt", usecols=0)
v2 = np.loadtxt("p7_output2.txt", usecols=1)

# Output data with n = 1000
x3 = np.loadtxt("p7_output3.txt", usecols=0)
v3 = np.loadtxt("p7_output3.txt", usecols=1)

# Output data with n = 10000
x4 = np.loadtxt("p7_output4.txt", usecols=0)
v4 = np.loadtxt("p7_output4.txt", usecols=1)

# Plotting output data
plt.figure()
plt.plot(x_e, u_e, label = "Exact solution")
plt.xlabel("x")
plt.ylabel("u(x)")
plt.plot(x1, v1, "--", label = "n = 10") # Plot of exact sol vs approximate sol, for n = 10.
plt.plot(x2, v2, "--", label = "n = 100") # Plot of exact sol vs approximate sol, for n = 100.
plt.plot(x3, v3, "--", label = "n = 1000") # Plot of exact sol vs approximate sol, for n = 1000.
plt.plot(x4, v4, "--", label = "n = 10000") # Plot of exact sol vs approximate sol, for n = 10000.
plt.legend()
plt.savefig("problem7.pdf")
plt.show()