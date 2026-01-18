import numpy as np
import matplotlib.pyplot as plt

# P7
p7_steps_1e1 = np.array([0.000245, 0.000265, 0.000343])
p7_steps_1e2 = np.array([0.000692, 0.000696, 0.000752])
p7_steps_1e3 = np.array([0.004612, 0.004573, 0.004832])
p7_steps_1e4 = np.array([0.04513, 0.044171, 0.045286])
p7_steps_1e5 = np.array([0.44069, 0.447383, 0.441587])
p7_steps_1e6 = np.array([4.80513, 4.66821, 4.73012])


# P9
p9_steps_1e1 = np.array([0.000137, 0.000189, 0.000187])
p9_steps_1e2 = np.array([7.5e-05, 0.000103, 0.00012])
p9_steps_1e3 = np.array([0.000188, 0.000139, 0.000166])
p9_steps_1e4 = np.array([0.00082, 0.000873, 0.000877])
p9_steps_1e5 = np.array([0.007683, 0.007972, 0.007952])
p9_steps_1e6 = np.array([0.077526, 0.078507, 0.078003])



a1 = np.mean(p7_steps_1e1)
a2 = np.mean(p7_steps_1e2)
a3 = np.mean(p7_steps_1e3)
a4 = np.mean(p7_steps_1e4)
a5 = np.mean(p7_steps_1e5)
a6 = np.mean(p7_steps_1e6)

b1 = np.mean(p9_steps_1e1)
b2 = np.mean(p9_steps_1e2)
b3 = np.mean(p9_steps_1e3)
b4 = np.mean(p9_steps_1e4)
b5 = np.mean(p9_steps_1e5)
b6 = np.mean(p9_steps_1e6)

a = np.array([a1, a2, a3, a4, a5, a6])
b = np.array([b1, b2, b3, b4, b5, b6])
x = np.linspace(10, 1e6, 6)

# plt.plot(x, a, label="General algorithm")
# plt.plot(x, b, label="Special algorithm")
# plt.legend()
# plt.show()

print("Avg. time for problem 7 \n")
print(f"Avg_time for 1e1 steps: {a1:.6f}")
print(f"Avg_time for 1e2 steps: {a2:.6f}")
print(f"Avg_time for 1e3 steps: {a3:.6f}")
print(f"Avg_time for 1e4 steps: {a4:.6f}")
print(f"Avg_time for 1e5 steps: {a5:.6f}")
print(f"Avg_time for 1e6 steps: {a6:.6f}")
print("\n")

print("Avg. time for problem 9 \n")
print(f"Avg_time for 1e1 steps: {b1:.6f}")
print(f"Avg_time for 1e2 steps: {b2:.6f}")
print(f"Avg_time for 1e3 steps: {b3:.6f}")
print(f"Avg_time for 1e4 steps: {b4:.6f}")
print(f"Avg_time for 1e5 steps: {b5:.6f}")
print(f"Avg_time for 1e6 steps: {b6:.6f}")
print("\n")