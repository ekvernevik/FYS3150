import numpy as np

n_list = np.array([4000, 8000, 16000, 32000])

def plot_thing(method, n_step):

    data_pos = np.loadtxt(f"{method}_pos_{n_step}.txt")
    data_a = np.loadtxt(f"analytical_{n_step}_result.txt")

    x1 = data_pos[:,1][::3]
    y1 = data_pos[:,1][1::3]
    z1 = data_pos[:,1][2::3]

    x_a = data_a[:,1]
    y_a = data_a[:,2]
    z_a = data_a[:,3]

    r_a = np.zeros((n_step, 3))
    for i in range(n_step):
        r_a[i] = np.array([x_a[i], y_a[i], z_a[i]])

    r_num = np.zeros((n_step, 3))
    for i in range(n_step):
        r_num[i] = np.array([x1[i], y1[i], z1[i]])

    r_ = np.zeros(n_step)
    dmax_err = np.zeros(n_step)

    for i in range(n_step):
        r_num = np.array([x1[i], y1[i], z1[i]])
        r_a = np.array([x_a[i], y_a[i], z_a[i]])
        max_err = np.linalg.norm(r_a-r_num)
        r_[i] = max_err/np.linalg.norm(r_a)
        dmax_err[i] = np.linalg.norm(r_a - r_num)
    
    return np.amax(dmax_err)


dmax_err_array = np.zeros(4)
for i in range(len(n_list)):
    dmax_err_array[i] = plot_thing("RK4", n_list[i])

print(dmax_err_array)

sum = 0
for i in range(1, 4):
    sum += ( np.log10(dmax_err_array[i]/dmax_err_array[i-1]) ) / np.log10( 50/n_list[i] / 50/n_list[i-1] )

r_err = (1/3)*sum
print(r_err)