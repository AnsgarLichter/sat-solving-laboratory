# SAT Solving Laboratory

This repository contains the exercises for the laboratory of the lecture SAT Solving at the University of Applied Sciences.

## Requirements
* GCC

## Installation
1. Clone the repository
```
git clone git@github.com:AnsgarLichter/sat-solving-laboratory.git
```
2. Clone CaDiCal into the repository's root folder
```
cd satsolving
```
```
git clone https://github.com/arminbiere/cadical.git
```

3. Build CaDiCal library
```
cd cadical
```
```
./configure && make
```

## Use CaDiCal SAT Solver
The CaDiCal library is at the root of the project.

1. Include the ipasir header of the CaDiCal library if you want to use CaDiCal through the ipasir interface
```C++
#include "../cadical/src/ipasir.h"
```


## Laboratory 1

### Graph Coloring
1. Go to the application's folder
```
cd laboratory1
```
2. Compile the program
```
g++ -o graph-coloring graph-coloring.cpp -I../cadical/src -L../cadical/build -l:libcadical.a
```
3. Run the program
```
./graph-coloring ./inputs/<file>
```