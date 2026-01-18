# Animations made by taking use of the code snippet

import pyarma as pa
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

plt.rcParams.update({'font.size': 12,
                     'axes.formatter.limits': (-2,2)})

""" filename = "problemX_single_slit.bin"
filename_save = '../animations/animation_X_single_slit.mp4' """

""" filename = "problemX_double_slit.bin"
filename_save = '../animations/animation_X_double_slit.mp4' """

filename = "problemX_triple_slit.bin"
filename_save = '../animations/animation_X_triple_slit.mp4'





# Get data
A = pa.cx_cube()
A.load(filename)
u = np.array(A)

# Calculate probability
P = np.real(u*np.conjugate(u))

# Set up a 2D xy grid
h = 0.005
x_points = np.arange(0, 1+h, h)
y_points = np.arange(0, 1+h, h)
x, y = np.meshgrid(x_points, y_points, sparse=True)

# Array of time points
dt = 2.5e-5
T = 0.008
t_points = np.arange(0, 1+dt, dt)

# Fill z_data_list with P(x,y,t)
z_data_list = []
for t in range(len(P)):
    z_data = P[t,:,:]
    z_data_list.append(z_data)


# Some settings
t_min = t_points[0]
x_min, x_max = x_points[0], x_points[-1]
y_min, y_max = y_points[0], y_points[-1]

# Create figure
fig = plt.figure(dpi=150)

ax = plt.gca()

# Create a colour scale normalization according to the max z value in the first frame
norm = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=np.max(z_data_list[0]))

# Plot the first frame
img = ax.imshow(z_data_list[0], extent=[x_min,x_max,y_min,y_max], cmap=plt.get_cmap("hot"), norm=norm)

# Axis labels
plt.xlabel("x")
plt.ylabel("y")

# Add a colourbar
cbar = fig.colorbar(img, ax=ax)
cbar.set_label("p(x,y,t)")

# Add a text element showing the time
time_txt = plt.text(0.95, 0.95, "t = {:.2e}".format(t_min), color="white",
                    horizontalalignment="right", verticalalignment="top")

# Function that takes care of updating the z data and other things for each frame
def animation(i):
    # Update z data
    img.set_data(z_data_list[i])

    # Update the time label
    current_time = t_min + i * dt
    time_txt.set_text("t = {:.2e}".format(current_time))

    return img

# Use matplotlib.animation.FuncAnimation to put it all together
anim = FuncAnimation(fig, animation, interval=1, frames=np.arange(0, len(z_data_list), 2), repeat=False, blit=0)

# # Save the animation
anim.save(filename_save, writer="ffmpeg", bitrate=10000, fps=15)
