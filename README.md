# HI-SOLVE
## Introduction
HI-SOLVE implements an iterative high-order numerical method for solving nonlinear algebraic equations in the form

  f(x) = 0,
  
which uses higher order derivatives. The method is inspired by (and essentially an attempt at generalizing) the iterative methods for solving cubic equations of state described by Olivera-Fuentes (1993).

The key idea is to truncate the terms in the Taylor expansion of f(x) and approximate the powers in the polynomial. As a consequence, the computation of the update in each iteration of numerical method also becomes iterative.

## Installation
This project uses CMake and the installation is standard:

```
cd <path-to-hi-solve> # open a terminal and go to the hi-solve directory
mkdir build           # create a new folder called build
cd build              # change the directory to the build folder
cmake ..              # create the build system
cmake --build .       # compile the code
```

1. open a terminal and go to the hi-solve directory (`cd <path-to-hi-solve>`)
2. create a new folder called build (`mkdir build`)
3. change the directory to the build folder (`cd build`)
4. create the build system (`cmake ..`)
5. compile the code (`cmake --build .`)

### Test (optional)
In order to test that the installation has been successful

### Create documentation (optional)

# Copyright
MIT License

Copyright (c) 2019 Tobias Kasper Skovborg Ritschel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Bibliography
C. Olivera-Fuentes, 1993. The optimal solution of cubic equations of state, Latin American Applied Research 23, page 243--256. [Link](https://www.researchgate.net/publication/233529753_THE_OPTIMAL_SOLUTION_OF_CUBIC_EQUATIONS_OF_STATE), cached: October 27th, 2019.
