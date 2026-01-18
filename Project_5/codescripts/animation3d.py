import pyarma as pa
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np


# Get data
A = pa.cx_cube()
A.load("problemX_double_slit.bin")
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


fig = plt.figure(figsize = (12, 6), dpi = 100)     
ax = fig.add_subplot(projection = '3d')

plt.xlabel("x")
plt.ylabel("y")


def update(i):
    Z = P[i,:,:]
    ax.clear()
    ax.plot_surface(x, y, Z, cmap = mpl.cm.hot)

    plt.title(f"t = {i*dt:.2e}")


anim = animation.FuncAnimation(fig, update, np.arange(int(T/dt)), interval = 10, repeat = False)

# Save the animation
anim.save('../animations/3d.mp4', writer="ffmpeg", bitrate=10000, fps=15)
