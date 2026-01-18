#  Code Contents

#### It's important to note that the guide below for compilation and linking of C++ programmes, is made with a MacOS in mind. Certain parts are negligible as they only apply to Mac-users.

Here you can find some guidelines for running our programmes.

### Guide for Python scripts and C++ programmes

Compiling, linking and running C++ programmes can be a little tricky to begin with, but this guide will ease any attempt at recreating plots or results with instructions for each task where a C++ programme was used. Running python scripts is comparably easier, but all steps are included in this guide for ease of use.

Again, as mentioned in the README.md for the project, all scripts and programmes are named after which task they were used in - the same applies for any plot they may produce (i.e. **problem_6.py** has a plot named **problem6.pdf**).

#### Running and compiling code

Each **.cpp**-file needs to be compiled and linked to an executable, and then the executable needs to be run in order to get the wanted output/plots. These two things can be done by downloading the files, navigating to the directory they're in, and writing the following:

*(Note: Use an appropriate flag, either -O2 or -O3, to enable compiler optimization. Several of the scripts run simulations that are computationally demanding, and adding the aforementioned flags will shorten the runtime)*

```bash
$ g++ filename.cpp -o executablename.exe -larmadillo -std=c++11 -O2
$ ./executablename.exe
```

