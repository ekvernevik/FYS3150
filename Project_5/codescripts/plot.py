# Plotting of the results of the Schrödinger equation using the Crank Nicolson scheme


import pyarma as pa
import numpy as np
import matplotlib
import matplotlib.pyplot as plt

# Use paramaters for all figures
# Basic parameters
plt.rcParams.update({'font.size': 9,
                     'axes.formatter.limits': (-2,2)})

#Latex-like parameters (having Latex installed is required)
plt.rcParams.update({'text.usetex': True,                # Use Latex fonts
                      'font.family': 'serif',            
                      'font.serif': 'Computer Modern'})  # revtex4-1 font (same font as article)


# Functions to extract data
def get_data(filename):
    A = pa.cx_cube()
    A.load(filename)
    u = np.array(A)
    return u

def get_probability(filename):
    u = get_data(filename)
    
    # Calculate probability
    u_conjugate = np.conjugate(u)
    p = np.real(u*u_conjugate)
    return p


#------------------------ Problem 7 ------------------------
p_no_slit = get_probability("problem7_no_slit.bin")
p_double_slit = get_probability("problem7_double_slit.bin")

# Find total probability at each time
P_no_slit = abs(np.sum(p_no_slit, axis=(1,2)))
P_double_slit = abs(np.sum(p_double_slit, axis=(1,2)))

# Time array for plotting
t = np.linspace(0,0.008, len(P_no_slit))

plt.figure(figsize=(3.6, 2.8))
plt.plot(t,P_no_slit-1, label="No slit")
plt.plot(t,P_double_slit-1, label="Double slit")
plt.xlabel(r"$T$")
plt.ylabel(r"$|p(t)-1|$")
plt.legend()
plt.grid()
plt.tight_layout()
plt.savefig("../plots/problem7.pdf")
plt.close()




#------------------------ Problem 8 ------------------------
# Set up a 2D xy grid
h = 0.005
x_points = np.arange(0, 1+h, h)
y_points = np.arange(0, 1+h, h)
x, y = np.meshgrid(x_points, y_points, sparse=True)

# Some settings
x_min, x_max = x_points[0], x_points[-1]
y_min, y_max = y_points[0], y_points[-1]


def plot_frames(p, name):
    fig, ax = plt.subplots(1,3, figsize=(7,2.8), layout='constrained')

    # Create a colour scale normalization according to the max z value
    norm_0 = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=np.max(p[0]))
    norm_1 = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=np.max(p[40]))
    norm_2 = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=np.max(p[80]))

    # Plot frames in figure
    img0 = ax[0].imshow(p[0], extent=[x_min,x_max,y_min,y_max], cmap=plt.get_cmap("hot"), norm=norm_0)
    img1 = ax[1].imshow(p[40], extent=[x_min,x_max,y_min,y_max], cmap=plt.get_cmap("hot"), norm=norm_1)
    img2 = ax[2].imshow(p[80], extent=[x_min,x_max,y_min,y_max], cmap=plt.get_cmap("hot"), norm=norm_2)

    ax[0].set_xlabel("x")
    ax[1].set_xlabel("x")
    ax[2].set_xlabel("x")

    ax[0].set_ylabel("y")
    ax[1].set_ylabel("y")
    ax[2].set_ylabel("y")

    # Add colorbar
    cbar0 = fig.colorbar(img0, ax=ax[0],orientation='horizontal', fraction=0.05)
    cbar1 = fig.colorbar(img1, ax=ax[1],orientation='horizontal', fraction=0.05)
    cbar2 = fig.colorbar(img2, ax=ax[2],orientation='horizontal', fraction=0.05)
    cbar0.set_label(f"{name}$(x;y;t=0)$")
    cbar1.set_label(f"{name}$(x;y;t=0.001)$")
    cbar2.set_label(f"{name}$(x;y;t=0.002)$")
    

filename = "problem8.bin"

p = get_probability(filename)
plot_frames(p, "p")
plt.savefig("../plots/problem8.pdf")
plt.close()

u = get_data(filename)
plot_frames(np.real(u), "Re")
plt.savefig("../plots/problem8_real.pdf")
plt.close()

plot_frames(np.imag(u), "Im")
plt.savefig("../plots/problem8_imag.pdf")
plt.close()




#------------------------ Problem 9 ------------------------
p_single = get_probability("problem9_single_slit.bin")
p_double = get_probability("problem8.bin")
p_triple = get_probability("problem9_triple_slit.bin")

plt.rcParams.update({'axes.grid': True}) # Use grid for all subplots

fig, ax = plt.subplots(1,3, figsize=(7,2.8), sharey=True, layout='constrained')

ax[0].plot(y_points,p_single[-1,:,160]/np.sum(p_single[-1,:,160]))
ax[1].plot(y_points,p_double[-1,:,160]/np.sum(p_double[-1,:,160]))
ax[2].plot(y_points,p_triple[-1,:,160]/np.sum(p_triple[-1,:,160]))


ax[0].set_xlabel("y")
ax[1].set_xlabel("y")
ax[2].set_xlabel("y")

ax[0].set_ylabel(r"$p(y|x=0.8;t=0.002)$")

plt.savefig("../plots/problem9.pdf")
plt.close()
