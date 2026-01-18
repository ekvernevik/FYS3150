# Program for plotting results from the Ising Model

import scipy.stats as scs
import numpy as np
import pyarma as pa                 # For reading bin-files with armadillo objects
import matplotlib.pyplot as plt     # For plotting
from matplotlib.ticker import FuncFormatter

# Use paramaters for all figures
# Basic parameters
plt.rcParams.update({'font.size': 9,
                     'axes.grid': True,                 # Set grid
                     'figure.autolayout': True,})        # Set tight_layout})

""" #Latex-like parameters (having Latex installed is required) (NB! Running with this uncommented takes 5 min)

plt.rcParams.update({'text.usetex': True,               # Use Latex fonts
                      'font.family': 'serif',            
                      'font.serif': 'Computer Modern'})  # revtex4-1 font (same font as article) """

# Set figure-size (inches)
figwidth = 3.6
figheight = figwidth / 1.3


# Functions to read data from bin-files 
def get_data_matrix(bin_filename, start=0):
    A = pa.mat()         #Create pa.mat object
    A.load(bin_filename) #Load data
    
    # Asign data
    x = A[start:,0]
    mean_epsilon = A[start:,1]
    mean_m = A[start:,2]
    C_V = A[start:,3]
    chi = A[start:,4]
    return x, mean_epsilon, mean_m, C_V, chi

def get_data_vector(bin_filename):
    A = pa.mat()         #Create pa.mat object
    A.load(bin_filename) #Load data

    # Asign data
    mean_epsilon = A[1]
    mean_m = A[2]
    C_V = A[3]
    chi = A[4]
    return mean_epsilon, mean_m, C_V, chi

        
def get_matrix(bin_filename):
    A = pa.mat()         #Create pa.mat object
    A.load(bin_filename) #Load data
    return A




#-------------------------------- Problem 4b --------------------------------
filename_simulation = "problem_4b.bin" 
filename_analytic = "analytic_problem_4b.bin"

simulation = get_matrix(filename_simulation)
analytic = get_matrix(filename_analytic)

rel_error = pa.abs((analytic-simulation) / analytic)

print("\n------------------ Problem 4b ------------------")
print("Simulation:")
simulation.print()
print("\nAnalytic:")
analytic.print()
print("\nRelative error:")
rel_error.print()


#-------------------------------- Problem 4c --------------------------------
filename_simulation = "problem_4c.bin"
filename_analytical = "analytical_problem_4c.bin"

# Get data
n_cycles, mean_epsilon, mean_m, C_V, chi = get_data_matrix(filename_simulation)
epsilon_analytical, m_analytical, C_V_analytical, chi_analytical = get_data_vector(filename_analytical)

stop = 30
#Expectation value of energy per spin
plt.figure("epsilon_4", figsize=(figwidth, figheight))
plt.plot(n_cycles[0:stop,0], mean_epsilon[0:stop,0], linewidth=0.7, color = "royalblue", marker="o", markersize= 1.0, label="Simulation") 
plt.plot(n_cycles[stop:,0], mean_epsilon[stop:,0], "-", linewidth=2.0, color = "royalblue") 
plt.axhline(epsilon_analytical, linestyle="--", color="r", label="Analytical") 
plt.xscale("log")
plt.xlabel("Number of cycles")
plt.ylabel(r"$\langle\epsilon\rangle$ [J]")
plt.legend()
plt.savefig("../plots/problem4/cycles_epsilon.pdf")         

# Expectation value of magnetisation per spin
plt.figure("m_4", figsize=(figwidth, figheight))
plt.plot(n_cycles[0:stop,0], mean_m[0:stop,0], linewidth=0.7, color = "royalblue", marker="o", markersize= 1.0, label="Simulation") 
plt.plot(n_cycles[stop:,0], mean_m[stop:,0], "-", linewidth=2.0, color = "royalblue") 
plt.axhline(m_analytical, linestyle="--", color="r", label="Analytical") 
plt.xscale("log")                  
plt.xlabel("Number of cycles")
plt.ylabel(r"$\langle|m|\rangle$ ")        
plt.legend()    
plt.savefig("../plots/problem4/cycles_m.pdf")                

# Spesific heat capacity
plt.figure("C_V_4", figsize=(figwidth, figheight))
plt.plot(n_cycles[0:stop,0], C_V[0:stop,0], linewidth=0.7, color = "royalblue", marker="o", markersize= 1.0, label="Simulation") 
plt.plot(n_cycles[stop:,0], C_V[stop:,0], "-", linewidth=2.0, color = "royalblue") 
plt.axhline(C_V_analytical, linestyle="--", color="r", label="Analytical") 
plt.xscale("log")                   
plt.xlabel("Number of cycles")
plt.ylabel(r"$C_V [k_B]$")            
plt.legend()
plt.savefig("../plots/problem4/cycles_C_V.pdf")        

# Magnetic suceptibility
plt.figure("chi_4", figsize=(figwidth, figheight))
plt.plot(n_cycles[0:stop,0], chi[0:stop,0], linewidth=0.7, color = "royalblue", marker="o", markersize= 1.0,label="Simulation") 
plt.plot(n_cycles[stop:,0], chi[stop:,0], "-", linewidth=2.0, color = "royalblue") 
plt.axhline(chi_analytical, linestyle="--", color="r", label="Analytical") 
plt.xscale("log")
plt.xlabel("Number of cycles")
plt.ylabel(r"$\chi$ [1/J]")            
plt.legend()
plt.savefig("../plots/problem4/cycles_chi.pdf")








#-------------------------------- Problem 5 --------------------------------
filename_10_ordered = "problem_5_10_ordered.bin"
filename_10_random  = "problem_5_10_random.bin"
filename_24_ordered = "problem_5_24_ordered.bin"
filename_24_random  = "problem_5_24_random.bin"

# # Get data
n_cycles, mean_epsilon_10_or, mean_m_10_or, C_V, chi = get_data_matrix(filename_10_ordered)
n_cycles, mean_epsilon_10_ra, mean_m_10_ra, C_V, chi = get_data_matrix(filename_10_random)
n_cycles, mean_epsilon_24_or, mean_m_24_or, C_V, chi = get_data_matrix(filename_24_ordered)
n_cycles, mean_epsilon_24_ra, mean_m_24_ra, C_V, chi = get_data_matrix(filename_24_random)

stop = 10
# Expectation value of energy per spin
plt.figure("epsilon_5", figsize=(figwidth, figheight))
plt.plot(n_cycles[0:stop,0], mean_epsilon_10_or[0:stop,0], linewidth=0.7, color = "r", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], mean_epsilon_10_or[stop:,0], "r-", linewidth=2.0, label="$T=1$ ordered")

plt.plot(n_cycles[0:stop,0], mean_epsilon_10_ra[0:stop,0], linestyle = "--", linewidth=0.7, color = "r", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], mean_epsilon_10_ra[stop:,0], "r--", linewidth=2.0, label="$T=1$ random")

plt.plot(n_cycles[0:stop,0], mean_epsilon_24_or[0:stop,0], linewidth=0.7, color = "k", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], mean_epsilon_24_or[stop:,0], "k-", linewidth=2.0, label="$T=2.4$ ordered")

plt.plot(n_cycles[0:stop,0], mean_epsilon_24_ra[0:stop,0], linestyle = "--", linewidth=0.7, color = "k", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], mean_epsilon_24_ra[stop:,0], "k--", linewidth=2.0, label="$T=2.4$ random")
plt.xscale("log")
plt.xlabel("Number of cycles")
plt.ylabel(r"$\langle\epsilon\rangle$ [J]")
plt.legend(loc="upper right")
plt.savefig("../plots/problem5/epsilon.pdf")     

# Expectation value of magnetisation per spin
plt.figure("m_5", figsize=(figwidth, figheight))
plt.plot(n_cycles[0:stop,0], mean_m_10_or[0:stop,0], linewidth=0.7, color = "r", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], mean_m_10_or[stop:,0], "r-", linewidth=2.0, label="$T=1$ ordered")

plt.plot(n_cycles[0:stop,0], mean_m_10_ra[0:stop,0], linestyle = "--", linewidth=0.7, color = "r", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], mean_m_10_ra[stop:,0], "r--", linewidth=2.0, label="$T=1$ random")

plt.plot(n_cycles[0:stop,0], mean_m_24_or[0:stop,0], linewidth=0.7, color = "k", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], mean_m_24_or[stop:,0], "k-", linewidth=2.0, label="$T=2.4$ ordered")

plt.plot(n_cycles[0:stop,0], mean_m_24_ra[0:stop,0], linestyle = "--", linewidth=0.7, color = "k", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], mean_m_24_ra[stop:,0], "k--", linewidth=2.0, label="$T=2.4$ random")
plt.xscale("log")                  
plt.xlabel("Number of cycles")
plt.ylabel(r"$\langle|m|\rangle$ ")        
plt.legend(loc="upper left")    
plt.savefig("../plots/problem5/m.pdf")



#-------------------------------- Problem 6 --------------------------------
#Burn-in 40000
filename_10 = "problem_6_10.bin"
filename_24 = "problem_6_24.bin"

# Load data
A_10 = get_matrix(filename_10)
A_24 = get_matrix(filename_24)

# Make histograms
plt.figure(figsize=(figwidth, figheight))
""" We set bins = 2*len(set(A))-1 do distinguish between the non-continuous values of epsilon.
    set(A) returns the unique values of A, and len(set(A)) returns the number of unique values  """
plt.hist(A_10, bins=2*len(set(A_10))-1, density=True, color="orange",  label="$T=1$", edgecolor='black', linewidth=0.1)
plt.hist(A_24, bins=2*len(set(A_24))-1, density=True, label="$T=2.4$")
plt.xlabel("$\epsilon$ [J]")
plt.ylabel("$p_{\epsilon}(\epsilon ; T)$")
plt.yscale("log")
plt.legend()
plt.grid(False)
plt.savefig("../plots/problem6/problem6.pdf")


# Burn-in 600 and 1
filename_10_600 = "problem_6_10_600.bin"
filename_24_1 = "problem_6_24_1.bin"

# Load data
A_10 = get_matrix(filename_10_600)
A_24 = get_matrix(filename_24_1)

# Make histograms
plt.figure(figsize=(figwidth, figheight))
""" We set bins = 2*len(set(A))-1 do distinguish between the non-continuous values of epsilon.
    set(A) returns the unique values of A, and len(set(A)) returns the number of unique values  """
plt.hist(A_10, bins=2*len(set(A_10))-1, density=True, color="orange",  label="$T=1$", edgecolor='black', linewidth=0.1)
plt.hist(A_24, bins=2*len(set(A_24))-1, density=True, label="$T=2.4$")
plt.xlabel("$\epsilon$ [J]")
plt.ylabel("$p_{\epsilon}(\epsilon ; T)$")
plt.yscale("log")
plt.legend()
plt.grid(False)
plt.savefig("../plots/problem6/problem6_600_1.pdf")


# Burn-in 0
filename_10_0 = "problem_6_10_0.bin"
filename_24_0 = "problem_6_24_0.bin"

# Load data
A_10 = get_matrix(filename_10_0)
A_24 = get_matrix(filename_24_0)

# Make histograms
plt.figure(figsize=(figwidth, figheight))
""" We set bins = 2*len(set(A))-1 do distinguish between the non-continuous values of epsilon.
    set(A) returns the unique values of A, and len(set(A)) returns the number of unique values  """
plt.hist(A_10, bins=2*len(set(A_10))-1, density=True, color="orange",  label="$T=1$", edgecolor='black', linewidth=0.1)
plt.hist(A_24, bins=2*len(set(A_24))-1, density=True, label="$T=2.4$")
plt.xlabel("$\epsilon$ [J]")
plt.ylabel("$p_{\epsilon}(\epsilon ; T)$")
plt.yscale("log")
plt.legend()
plt.grid(False)
plt.savefig("../plots/problem6/problem6_0.pdf")






#---------------------------------- Problem 7 ---------------------------------
# Function for calculating averages of timing tests for parallellization, and different choices of threads
def get_avg(measured_runtimes):
    avg_runtime = []
    for runtime in measured_runtimes:
        avg = np.mean(runtime)
        print(f"Avg: {avg}")
        avg_runtime.append(avg)

    return avg_runtime

# Measurements are from M1 mac
n_t_1 = [31.726,
         31.063,
         31.030]

n_t_2 = [16.446,
         16.396,
         16.448]

n_t_4 = [9.724,
         9.707,
         9.942]

n_t_6 = [7.427,
         7.236,
         7.553]

n_t_8 = [7.022,
         6.889,
         7.714]

n_t_10 = [7.432,
          7.509,
          7.403]

data    = [n_t_1, n_t_2, n_t_4, n_t_6, n_t_8, n_t_10]
threads = [1, 2, 4, 6, 8, 10]

t_1 = 31.273


data_average = get_avg(measured_runtimes=data)

f_speedfac = []
for i in range(len(data_average)):
    res = t_1*(1/data_average[i])
    f_speedfac.append(res)
    print(f"Speed-up factor for {threads[i]}-threads: {f_speedfac[i]}")

plt.figure("timing_test",figsize=(figwidth, figheight))
plt.plot(threads, data_average, "o", label="Elapsed run-time")
plt.plot(threads, data_average, "--")
plt.xlabel("n-threads")
plt.ylabel("Elapsed time in seconds [s]")
plt.legend()
plt.savefig("../plots/problem7/timing_test.pdf")





#-------------------------------- Problem 8 --------------------------------
# Function for plotting expectation values versus temperature
def plot_expectation(folder, name, xlabel, filenames, labels, start=0):
    figures = [name + "_epsilon", name + "_m", name + "_C_V", name + "_chi"]
    ylabels = [r"$\langle \epsilon \rangle$ [J]", r"$\langle |m| \rangle$", r"$C_V [k_{B}]$", r"$\chi$ [1/J]"]
    colors = ["orange","green","red","royalblue"]

    # Create figures
    for name in figures:
        plt.figure(name, figsize=(figwidth, figheight))

    # Get data and plot
    for i in range(len(filenames)):
        T, mean_epsilon, mean_m, C_V, chi = get_data_matrix(filenames[i], start)
        variables = [mean_epsilon, mean_m, C_V, chi]

        # Make plots in figures
        for j in range(len(variables)):
            plt.figure(figures[j])
            plt.plot(T, variables[j], linewidth=0.7, color = colors[i], marker="o", markersize= 1.0, label=labels[i])

    # Finish and save figures 
    for i in range(len(figures)):
        plt.figure(figures[i])
        plt.xlabel(xlabel)
        plt.ylabel(ylabels[i])
        plt.legend()
        plt.savefig("../plots/" + folder + figures[i] + ".pdf")


# Large scan
folder = "problem8/"
name = "large_scan_N5"
xlabel = r"T [J/$k_B$]"
filenames = ["problem_8_L40_N5.bin", "problem_8_L60_N5.bin", "problem_8_L80_N5.bin", "problem_8_L100_N5.bin"]
labels = ["L = 40","L = 60","L = 80","L = 100"]
plot_expectation(folder, name, xlabel, filenames, labels)

# Fine-grained scan
name = "fine_grained_scan_N6"
filenames = ["problem_8_L40_N6.bin", "problem_8_L60_N6.bin", "problem_8_L80_N6.bin", "problem_8_L100_N6.bin"]
plot_expectation(folder, name, xlabel, filenames, labels)



#--------------------------------- Problem 9 --------------------------#
print("\n------------------ Problem 9 ------------------")


T_c = [2.28, 2.29, 2.31, 2.32]
L = 1/np.array([100, 80, 60, 40])
T_c_Onsager = 2.269 # J/k_B

# Function to format axes in the plot below to have less decimals
def format_func1(value, _):
    return f'{value:.3f}'  # Adjust the decimal precision as needed

# Function to format axes in the plot below to have less decimals
def format_func2(value, _):
    return f'{value:.2f}'  # Adjust the decimal precision as needed

x_maxs = [0.025, 0.016]
plt.figure("N=4",figsize=(figwidth, figheight))
plt.plot(L, T_c, "--")
plt.plot(L, T_c, "o", label="Estimated $T_c(L)$")

res = scs.linregress(L, T_c)
a = res[0] # Slope of linear fit
T_c_simulation = res[1]
print(f"T_c_simulation: {T_c_simulation}")

r_err = abs((T_c_simulation - T_c_Onsager)/T_c_Onsager)
print(f"r_err: {r_err}")
print(f"std: {res[4]}")

x = np.linspace(0.01, x_maxs[0],100)
plt.plot(x,a*x + T_c_simulation, label="Linearly fitted line")
plt.ylabel("$T_c$ [$J/k_B$]")
plt.xlabel("1/L")
plt.legend()
plt.gca().xaxis.set_major_formatter(FuncFormatter(format_func1))
plt.gca().yaxis.set_major_formatter(FuncFormatter(format_func2))
plt.savefig("../plots/problem9/T_c.pdf")



plt.figure("N=3",figsize=(figwidth, figheight))
plt.plot(L[:3], T_c[:3], "--")
plt.plot(L[:3], T_c[:3], "o", label="Estimated $T_c(L)$")

res = scs.linregress(L[:3], T_c[:3])
a = res[0] # Slope of linear fit
T_c_simulation = res[1]
print(f"T_c_simulation: {T_c_simulation}")

r_err = abs((T_c_simulation - T_c_Onsager)/T_c_Onsager)
print(f"r_err: {r_err}")
print(f"std: {res[4]}")

x = np.linspace(0.01, x_maxs[1],100)
plt.plot(x,a*x + T_c_simulation, label="Linearly fitted line")
plt.ylabel("$T_c$ [$J/k_B$]")
plt.xlabel("1/L")
plt.legend()
plt.gca().xaxis.set_major_formatter(FuncFormatter(format_func1))
plt.gca().yaxis.set_major_formatter(FuncFormatter(format_func2))
plt.savefig("../plots/problem9/T_c_short.pdf")






#-------------------------------- Burn-in(vestigation) --------------------------------
# Burn-in 0
filename_10_0 = "problem_6_10_0.bin"
filename_24_0 = "problem_6_24_0.bin"

# Load data
A_10 = get_matrix(filename_10_0)
A_24 = get_matrix(filename_24_0)

stop = 10

# Plot of energy per spin and expectation value versus n_cycles 
#T = 1
plt.figure(figsize=(figwidth, figheight))

plt.plot(n_cycles[0:stop,0], A_10[0:stop,0], linewidth=0.7, color = "b", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], A_10[stop:,0], "b-", linewidth=2.0, label="$\epsilon$")

plt.plot(n_cycles[0:stop,0], mean_epsilon_10_ra[0:stop,0], linewidth=0.7, color = "k", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], mean_epsilon_10_ra[stop:,0], "k-", linewidth=2.0, label=r"$\langle\epsilon\rangle$")

plt.xscale("log")
plt.xlabel("Number of cycles")
plt.ylabel("J")
plt.axvline(600, color="gray", label=r"$n_{cycles} = 600$")
plt.legend()
plt.savefig("../plots/burn_T10.pdf")

#T = 2.4
plt.figure(figsize=(figwidth, figheight))
# plt.plot(n_cycles,A_24, label="$\epsilon$")
# plt.plot(n_cycles,mean_epsilon_24_ra, "k--", label=r"$\langle\epsilon\rangle$")

plt.plot(n_cycles[0:stop,0], A_24[0:stop,0], linewidth=0.7, color = "b", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], A_24[stop:,0], "b-", linewidth=2.0, label="$\epsilon$")

plt.plot(n_cycles[0:stop,0], mean_epsilon_24_ra[0:stop,0], linewidth=0.7, color = "k", marker="o", markersize= 1.0)
plt.plot(n_cycles[stop:,0], mean_epsilon_24_ra[stop:,0], "k-", linewidth=2.0, label=r"$\langle\epsilon\rangle$")

plt.xscale("log")
plt.xlabel("Number of cycles")
plt.ylabel("J")

plt.legend()
plt.savefig("../plots/burn_T24.pdf")
