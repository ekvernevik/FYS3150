### Building the code:

Compilation and linking to an executable can be done in the regular manner, as such:
```bash
g++ -O2 main.cpp src/* -I include/ -o main.exe -larmadillo -std=c++11
```
### Example run:

Running the executable requires additional arguments in the command-line, namely: 
```bash
time ./main.exe <T> <x_c> <sigma_x> <p_x> <y_c> <sigma_y> <p_y> <n_slits> <filename>
```

#### Problem 7
No slit:
```bash
time ./main.exe 0.008 0.25 0.05 200 0.5 0.05 0 0 problem7_no_slit.bin
```
Double slit:
```bash
time ./main.exe 0.008 0.25 0.05 200 0.5 0.10 0 2 problem7_double_slit.bin
```


#### Problem 8
Run:
```bash
time ./main.exe 0.002 0.25 0.05 200 0.5 0.20 0 2 problem8.bin
```

#### Problem 9
Single slit:
```bash
time ./main.exe 0.002 0.25 0.05 200 0.5 0.20 0 1 problem9_single_slit.bin
```
Triple slit:
```bash
time ./main.exe 0.002 0.25 0.05 200 0.5 0.20 0 3 problem9_triple_slit.bin
```

#### Problem X
(same parameters as problem 8 and 9, but with $T = 0.008$)

Single slit:
```bash
time ./main.exe 0.008 0.25 0.05 200 0.5 0.20 0 1 problemX_single_slit.bin
```
Double slit:
```bash
time ./main.exe 0.008 0.25 0.05 200 0.5 0.20 0 2 problemX_double_slit.bin
```
Triple slit:
```bash
time ./main.exe 0.008 0.25 0.05 200 0.5 0.20 0 3 problemX_triple_slit.bin
```
