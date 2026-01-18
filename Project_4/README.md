# On the compilation, linking and application of our scripts

*In one of our codescripts, namely **main_temperature.cpp**, parallellization has been applied to speed up and shorten the runtime of our executables. In order to parallelize our code, **OpenMP** and an alternative compiler, the **GNU g++** compiler, was employed.*

All of the files that were used in and are necessary to recreate this study can be found in the **codescripts**-folder. The three main cpp-files (pun intended) are listed below, along with an extensive guide on how to apply them.

## main_temperature.cpp

### Building the code:

**For Linux users:**

Linux-users should be able to enable OpenMP easily by adding the compiler flag ```-fopenmp```. This flag should be added to both compilation and linking commands, or for when compilation and linking take place in tandem.

```bash
g++ -O2 main_temperature.cpp -fopenmp src/* -I include/ -o main_temperature.exe -larmadillo
```

**For macOS users:**

Users on macOS have a few more steps. Since macOS does not natively refer to the actual GNU g++ compiler, but rather apples version of it (clang), users will have to download the GNU g++ compiler in order to use the OpenMP-libraries. This can be done rather easily, as:
```bash
brew install gcc@12
```

After successfully installing the GNU g++ compiler, compilation can then be done by adding the following to the standard compilation process: (**I**) using the ```g++-12``` compiler instead of ```g++```, (**II**) adding ```-fopenmp``` to access the *OpenMP*-libraries, and (**III**) adding ```-larmadillo``` and ```std=c++11``` to correctly access the *armadillo*-libraries.
```bash
g++-12 -O2 main_temperature.cpp -fopenmp src/* -I include/ -o main_temperature.exe -larmadillo -std=c++11
```

### Example run:

Running the executable requires additional arguments in the command-line, namely: Lattice size (**L**), a boolean that determines whether the spin-lattice is ordered or random (**ordered**), the number of Monte Carlo Cycles per thread (**n_cycles_per_thread**) during parallellization, minimum temperature (**T_min**), maximum temperature (**T_max**), number of temperature points (**n_T**), and an file to funnel data into (**output_filename**).
```bash
time OMP_NUM_THREADS=<n_threads> ./main_temperature.exe <L> <ordered> <n_cycles> <burn_in> <T_min> <T_max> <n_T> <output_filename>
```

#### Problem 4b
Run:
```bash
time OMP_NUM_THREADS=1 ./main_temperature.exe 2 0 1000000 0 1.0 1.0 1 problem_4b.bin
```
#### Problem 8
##### Large scan over $T = \{2.1,2.4\}$, , with $n_{cycles} = 10^5$, $dT = 0.03$
$L=40$ run:
```bash
time OMP_NUM_THREADS=8 ./main_temperature.exe 40 0 100000 10000 2.1 2.4 11 problem_8_L40_N5.bin
```
$L=60$ run:
```bash
time OMP_NUM_THREADS=8 ./main_temperature.exe 60 0 100000 10000 2.1 2.4 11 problem_8_L60_N5.bin
```
$L=80$ run:
```bash
time OMP_NUM_THREADS=8 ./main_temperature.exe 80 0 100000 10000 2.1 2.4 11 problem_8_L80_N5.bin
```
$L=100$ run:
```bash
time OMP_NUM_THREADS=8 ./main_temperature.exe 100 0 100000 10000 2.1 2.4 11 problem_8_L100_N5.bin
```
#### Fine-grained scan over $T = \{2.26,2.34\}$, , with $n_{cycles} = 10^6$, $dT = 0.005$
$L=40$ run:
```bash
time OMP_NUM_THREADS=8 ./main_temperature.exe 40 0 1000000 10000 2.26 2.34 17 problem_8_L40_N6.bin
```
$L=60$ run:
```bash
time OMP_NUM_THREADS=8 ./main_temperature.exe 60 0 1000000 10000 2.26 2.34 17 problem_8_L60_N6.bin
```
$L=80$ run: (NB! This takes about 20 minutes on my WSL)
```bash
time OMP_NUM_THREADS=8 ./main_temperature.exe 80 0 1000000 10000 2.26 2.34 17 problem_8_L80_N6.bin
```
$L=100$ run: (NB! This takes about 40 minutes on my WSL)
```bash
time OMP_NUM_THREADS=8 ./main_temperature.exe 100 0 1000000 10000 2.26 2.34 17 problem_8_L100_N6.bin
```

## main_cycles.cpp

### Building the code:

Compilation and linking to an executable can be done in the regular manner, as such:
```bash
g++ -O2 main_cycles.cpp src/* -I include/ -o main_cycles.exe -larmadillo -std=c++11
```
### Example run:

Running the executable requires additional arguments in the command-line, namely: Lattice size (**L**), a boolean that determines whether it is ordered or not (**ordered**), the number of Monte Carlo Cycles (**n_cycles**), the estimated burn-in time (**burn_in**), and the temperature (**T**).
```bash
time ./main_cycles.exe <L> <ordered> <n_cycles> <burn_in> <T> <output_filename>
```

#### Problem 4c
Run:
```bash
time ./main_cycles.exe 2 0 1000000 0 1.0 problem_4c.bin
```

#### Problem 5
$T=1$ ordered, run:
```bash
time ./main_cycles.exe 20 1 1000000 0 1.0 problem_5_10_ordered.bin
```
$T=1$ random, run:
```bash
time ./main_cycles.exe 20 0 1000000 0 1.0 problem_5_10_random.bin
```
$T=2.4$ ordered, run:
```bash
time ./main_cycles.exe 20 1 1000000 0 2.4 problem_5_24_ordered.bin
```
$T=2.4$ random, run:
```bash
time ./main_cycles.exe 20 0 1000000 0 2.4 problem_5_24_random.bin
```

## main_epsilon.cpp
### Building the code:

Compilation and linking to an executable can be done in the regular manner, as such:
```bash
g++ -O2 main_epsilon.cpp src/* -I include/ -o main_epsilon.exe -larmadillo -std=c++11
```
### Example run:

Running the executable requires additional arguments in the command-line, namely: Lattice size (**L**), a boolean that determines whether it is ordered or not (**ordered**), the number of Monte Carlo Cycles (**n_cycles**), the estimated burn-in time (**burn_in**), and a file to funnel data into.
```bash
time ./main_epsilon.exe <L> <ordered> <n_cycles> <burn_in> <T> <output_filename>
```
#### Problem 6
$T=1$ run: 
```bash
time ./main_epsilon.exe 20 0 1000000 10000 1.0 problem_6_10.bin
```
$T=2.4$ run: 
```bash
time ./main_epsilon.exe 20 0 1000000 10000 2.4 problem_6_24.bin
```
