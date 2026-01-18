#  Code Contents

#### It's important to note that the guide below for compilation and linking of C++ programmes, is made with a MacOS in mind. Certain parts are negligible as they only apply to Mac-users.

Here you can find some guidelines for running our programmes.

### Guide for Python scripts and C++ programmes

Compiling, linking and running C++ programmes can be a little tricky to begin with, but this guide will ease any attempt at recreating plots or results with instructions for each task where a C++ programme was used. Running python scripts is comparably easier, but all steps are included in this guide for ease of use.

Again, as mentioned in the README.md for the project, all scripts and programmes are named after which task they were used in - the same applies for any plot they may produce (i.e. **problem_7.py** has a plot named **problem7.pdf**).

#### Problem 2
In this task, we compile **problem_2.cpp** and link it to an exectuable **problem2.exe**. Running this executable produces a **.txt**-file with data, named **data.txt**, which can then be plotted with **problem_2_plot.py**.

To do this, download the aformentioned files to a directory; assuming it's a folder on your desktop, you can navigate to it by writing the following line in the terminal:

```bash
cd desktop/directory
```
Onwards, run the following commands in the terminal:

```bash
g++ problem_2.cpp -o problem2.exe

./problem2.exe

python problem_2_plot_py
```

If done correctly, the python script will produce a plot and save it to whichever directory it's currently in.

#### Problem 7

Much like the task above, we compile the corresponding **.cpp**-file and link it to an **.exe**-file, the difference now being that we produce several **.txt**-files, not just one. Additionally, we're now also using *Armadillo*, a linear algebra library for C++ - this adds another component to the compilation/linking-process:

```bash
g++ -larmadillo -std=c++11 programme.cpp -o exectuable.exe
```

To recreate this task, and it's results, you have to once again download the files to a directory, navigate to it using "cd", and write the following in the terminal:

```bash
g++ -larmadillo -std=c++11 problem_7.cpp -o problem7.exe

./problem7.exe

python problem_7.py
```

If done correctly, the python script should produce a graph corresponding to **problem7.pdf**

#### Problem 8

In this task we only run a python script, so no compilation or linking necessary, which makes it comparably easier. Navigate to the directory where you've downloaded the script, and run the following commands in the terminal

```bash
python problem_8.py
```

If done correctly, the python script should produce three plots, corresponding to **problem8_logabserr.pdf**, **proble8_logrelerr.pdfm**, and **problem8_maxrel.pdf**.

#### Problem 9

Same as the tasks above; compile and link, then run. Write the following in the command line:

```bash
g++ -larmadillo -std=c++11 problem_9.cpp -o problem9.exe

./problem9.exe
```

The executable produced from this task is essentially the same as in problem 7, the difference being that it is quicker at larger *n*-steps.
