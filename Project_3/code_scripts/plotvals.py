import numpy as np
import matplotlib.pyplot as plt

n_list = [4000, 8000, 16000, 32000]

def z_t_plots():
    # Comparing FE, RK4, and analytical res for one particle
    data_1p_FE = np.loadtxt("FE_pos_4000.txt")
    data_1p_RK4 = np.loadtxt("RK4_pos_4000.txt")

    # Fetching timesteps for FE-and RK4-methods
    t_p1_FE = data_1p_FE[:,0][::3]
    t_p1_RK4 = data_1p_RK4[:,0][::3]

    # Fethching timesteps for analytical res
    t_a, x_a, y_a, z_a = np.loadtxt("analytical_4000_result.txt", unpack=True)

    # Fetching components from position vector, for FE-and RK4-methods
    x_p1_FE = data_1p_FE[:,1][::3]
    z_p1_FE = data_1p_FE[:,1][2::3]

    x_p1_RK4 = data_1p_RK4[:,1][::3]
    z_p1_RK4 = data_1p_RK4[:,1][2::3]

    plt.plot(t_p1_FE, z_p1_FE, label="Forward Euler")
    plt.plot(t_p1_RK4, z_p1_RK4, label="RK4")
    plt.plot(t_a, z_a, label="Analytical sol")
    plt.ylabel("z-direction [$\mu m$]", fontsize=12)
    plt.xlabel("Time, [$\mu s$]", fontsize=12)
    plt.legend(fontsize=12)
    plt.savefig("z_t_comparison.pdf")
    plt.show()

    plt.plot(t_p1_FE, x_p1_FE, label="Forward Euler")
    plt.plot(t_p1_RK4, x_p1_RK4, label="RK4")
    plt.plot(t_a, x_a, label="Analytical sol")
    plt.ylabel("x-direction [$\mu m$]", fontsize=12)
    plt.xlabel("Time, [$\mu s$]", fontsize=12)
    plt.legend(fontsize=12)
    plt.savefig("x_t_comparison.pdf")
    plt.show()

def circ_plots():
    data_pos = np.loadtxt("RK4_pos_32000.txt")
    # data_vel = np.loadtxt("RK4_vel_32000.txt")

    # t1 = data_pos[:,0][::3]

    x1 = data_pos[:,1][::3]
    y1 = data_pos[:,1][1::3]
    z1 = data_pos[:,1][2::3]

    # v1_x = data_vel[:,1][::3]
    # v1_y = data_vel[:,1][1::3]
    # v1_z = data_vel[:,1][2::3]

    x2 = data_pos[:,2][::3]
    y2 = data_pos[:,2][1::3]
    # z2 = data_pos[:,2][2::3]

    # v2_x = data_vel[:,2][::3]
    # v2_y = data_vel[:,2][1::3]
    # v2_z = data_vel[:,2][2::3]

    # plt.plot(x1, y1, label="Particle 1")
    # plt.plot(x2, y2, label="Particle 2")
    # plt.xlabel("x-direction [$\mu m$]", fontsize=12)
    # plt.ylabel("y-direction [$\mu m$]", fontsize=12)
    # plt.axis("equal")
    # plt.legend(fontsize=12)
    # plt.savefig("x_y_comparison_1.pdf")
    # plt.show()

    plt.figure()
    plt.plot(x1, y1, label="Particle 1")
    plt.plot(x2, y2, label="Particle 2")
    plt.xlabel("x-direction [$\mu m$]", fontsize=12)
    plt.ylabel("y-direction [$\mu m$]", fontsize=12)
    plt.axis("equal")
    plt.legend(fontsize=12)
    plt.savefig("x_y_faulty_comparison_2.pdf")
    plt.show()
    # plt.xlabel("x-direction [$\mu m$]", fontsize=12)
    # plt.ylabel("$v_x$, velocity in x-direction [$\mu m /s$]", fontsize=12)
    # plt.axis("equal")
    # plt.legend(fontsize=12)
    # plt.savefig("x_vx_comparison.pdf")

    # plt.plot(z1, v1_z, label="Particle 1")
    # plt.plot(z2, v2_z, label="Particle 2")
    # plt.xlabel("z-direction [$\mu m$]", fontsize=12)
    # plt.ylabel("$v_z$, velocity in z-direction [$\mu m /s$]", fontsize=12)
    # plt.axis("equal")
    # plt.legend(fontsize=12)
    # plt.savefig("z_vz_comparison.pdf")
    # plt.show()

def plot_3d():

    data_pos = np.loadtxt("RK4_pos_4000.txt")
    data_vel = np.loadtxt("RK4_vel_4000.txt")

    x1 = data_pos[:,1][::3]
    y1 = data_pos[:,1][1::3]
    z1 = data_pos[:,1][2::3]

    x2 = data_pos[:,2][::3]
    y2 = data_pos[:,2][1::3]
    z2 = data_pos[:,2][2::3]

    ax = plt.figure().add_subplot(projection="3d")
    ax.plot(x1, y1, z1, label="Particle 1")
    ax.plot(x2, y2, z2, label="Particle 2")
    ax.set_xlabel("x-direction [$\mu m$]")
    ax.set_ylabel("y-direction [$\mu m$]")
    ax.set_zlabel("z-direction [$\mu m$]")
    plt.legend(fontsize=12)
    plt.savefig("3d_plot.pdf")
    plt.show()

def err(method, n_list):

    plt.figure()

    h = []
    dmax_err = []
    for n_steps in n_list:
        
        data_pos = np.loadtxt(f"{method}_pos_{n_steps}.txt")
        data_a = np.loadtxt(f"analytical_{n_steps}_result.txt")

        x1 = data_pos[:,1][::3]
        y1 = data_pos[:,1][1::3]
        z1 = data_pos[:,1][2::3]

        x_a = data_a[:,1]
        y_a = data_a[:,2]
        z_a = data_a[:,3]

        r_a = np.zeros((n_steps, 3))
        for i in range(n_steps):
            r_a[i] = np.array([x_a[i], y_a[i], z_a[i]])

        r_num = np.zeros((n_steps, 3))
        for i in range(n_steps):
            r_num[i] = np.array([x1[i], y1[i], z1[i]])

        r_ = np.zeros(n_steps)
        t = np.linspace(0,50,n_steps)
        d_err = np.zeros(n_steps)

        for i in range(n_steps):
            r_num = np.array([x1[i], y1[i], z1[i]])
            r_a = np.array([x_a[i], y_a[i], z_a[i]])
            abs_err = np.linalg.norm(r_a-r_num)
            r_[i] = abs_err/np.linalg.norm(r_a)
            d_err[i] = np.linalg.norm(r_a - r_num)

        plt.plot(t[1:], r_[1:], "o", markersize=1, label =f"n = {n_steps}")
        plt.yscale("log")
        plt.xlabel("Time, [$\mu s$]")
        plt.ylabel("${r_i}$, relative error")
    
        plt.legend(fontsize=12)
        plt.savefig(f"{method}_error_t_plot.pdf")

        dmax_err.append(np.max(d_err[1:]))
        h.append(50/n_steps)

    plt.show()

    sum = 0
    for i in range(1,4):
        sum += np.log10(dmax_err[i]/dmax_err[i-1])/np.log10(h[i]/h[i-1])

    r_err = sum/3

    print(r_err)

def plot_loss_1():
    
    data1 = np.loadtxt("counter_f0.1.txt")
    data2 = np.loadtxt("counter_f0.4.txt")
    data3 = np.loadtxt("counter_f0.7.txt")
    omega_0 = 0.71

    omega1 = data1[:,0]
    frac_p1 = data1[:,1]

    omega2 = data2[:,0]
    frac_p2 = data2[:,1]

    omega3 = data3[:,0]
    frac_p3 = data3[:,1]

    fig, axs = plt.subplots(3,1, figsize=(8,8))
    fig.set_tight_layout(True)
    axs[0].plot(omega1, frac_p1)
    axs[0].set_xlabel("Angular frequency, $\omega_V$ [MHz]")
    axs[0].set_ylabel("Particle loss, for $f = 0.1$")

    axs[1].plot(omega2, frac_p2)
    axs[1].set_xlabel("Angular frequency, $\omega_V$ [MHz]")
    axs[1].set_ylabel("Particle loss, for $f = 0.4$")

    axs[2].plot(omega3, frac_p3)
    axs[2].set_xlabel("Angular frequency, $\omega_V$ [MHz]")
    axs[2].set_ylabel("Particle loss, for $f = 0.7$")

    plt.xlabel("Angular frequency, $\omega_V$ [MHz]")
    plt.ylabel("Particle loss, for $f = 0.7$")
    plt.legend(fontsize=12)
    plt.show()

def plot_loss_2():
    data = np.loadtxt("finegrain.txt")

    omega = data[:,0]
    frac  = data[:,1]

    plt.plot(omega, frac)
    plt.xlabel("Angular frequency, $\omega_V$ [MHz]")
    plt.ylabel("Particle loss, for $f = 0.7$")
    plt.legend(fontsize=12)
    plt.savefig("finegrain.pdf")
    plt.show()

circ_plots()