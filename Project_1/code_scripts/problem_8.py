# Importing relevant modules
import numpy as np
import matplotlib.pyplot as plt
from numba import jit

# Numba throws more deprecation warnings than the Roman army threw spears
import warnings
warnings.filterwarnings("ignore", category=DeprecationWarning) 

# Fetching values from our output files, and assigning them to each their variable
x_1e1, v_1e1, u_1e1 = np.loadtxt("p7_output1.txt", unpack=True)
x_1e2, v_1e2, u_1e2 = np.loadtxt("p7_output2.txt", unpack=True)
x_1e3, v_1e3, u_1e3 = np.loadtxt("p7_output3.txt", unpack=True)
x_1e4, v_1e4, u_1e4 = np.loadtxt("p7_output4.txt", unpack=True)
x_1e5, v_1e5, u_1e5 = np.loadtxt("p7_output5.txt", unpack=True)
x_1e6, v_1e6, u_1e6 = np.loadtxt("p7_output6.txt", unpack=True)
x_1e7, v_1e7, u_1e7 = np.loadtxt("p7_output7.txt", unpack=True)


# Hail, glorious jit
@jit
def err(u, v):
    # Function to calculate the absolute-and relative error for x-and v-vals

    abs_err = np.absolute(u-v)

    rel_err = np.absolute((u - v) / u)

    n_steps = np.linspace(0, 1, len(u))

    return n_steps, abs_err, rel_err


#Calling the function, and assigning more values to each their variable
x_1e1, abs_err_1e1, rel_err_1e1 = err(v_1e1[1:-1], u_1e1[1:-1])
x_1e2, abs_err_1e2, rel_err_1e2 = err(v_1e2[1:-1], u_1e2[1:-1])
x_1e3, abs_err_1e3, rel_err_1e3 = err(v_1e3[1:-1], u_1e3[1:-1])
x_1e4, abs_err_1e4, rel_err_1e4 = err(v_1e4[1:-1], u_1e4[1:-1])
x_1e5, abs_err_1e5, rel_err_1e5 = err(v_1e5[1:-1], u_1e5[1:-1])
x_1e6, abs_err_1e6, rel_err_1e6 = err(v_1e6[1:-1], u_1e6[1:-1])
x_1e7, abs_err_1e7, rel_err_1e7 = err(v_1e7[1:-1], u_1e7[1:-1])

@jit
# Function to add the max_rel for each rel_err-array
def do_stuff():
    max_rel = []
    max_rel.append(np.max(rel_err_1e1))
    max_rel.append(np.max(rel_err_1e2))
    max_rel.append(np.max(rel_err_1e3))
    max_rel.append(np.max(rel_err_1e4))
    max_rel.append(np.max(rel_err_1e5))
    max_rel.append(np.max(rel_err_1e6))
    max_rel.append(np.max(rel_err_1e7))

    x = np.logspace(1, 7, 7)

    return max_rel, x

maxrel, x = do_stuff()

# Plotting the max_rel-list
plt.loglog(x, maxrel, "r+")
plt.xlabel("n_steps")
plt.ylabel("rel_err")
plt.savefig("problem8__maxrel.pdf")
plt.show()

# Plotting the calculated absolute error, using .loglog()
plt.figure(1)
plt.loglog(x_1e1, abs_err_1e1,label="n=10")
plt.loglog(x_1e2, abs_err_1e2,label="n=100")
plt.loglog(x_1e3, abs_err_1e3,label="n=1000")
plt.loglog(x_1e7, abs_err_1e7,label="n=1e7")
plt.title("Plot of $\\log_{10}(\\Delta_i) = \\log_{10} (\\vert u_i - v_i \\vert)$")
plt.xlabel("x")
plt.ylabel("log(abs(u-v))")
plt.legend()
plt.savefig("probem8_logabserr.pdf")
plt.show()

# # Plotting the calculated relative error, using .loglog()
plt.figure(2)
plt.loglog(x_1e1, rel_err_1e1,label="n=10")
plt.loglog(x_1e2, rel_err_1e2,label="n=100")
plt.loglog(x_1e3, rel_err_1e3,label="n=1000")
plt.loglog(x_1e7, rel_err_1e7,label="n=1e7")
plt.title("Plot of $\\log_{10}(\\Delta_i) = \\log_{10} (\\vert \\frac{u_i - v_i}{u_i} \\vert)$")
plt.xlabel("x")
plt.ylabel("log(\\vert (u-v)/u \\vert")
plt.legend()
plt.savefig("problem8_logrelerr.pdf")
plt.show()