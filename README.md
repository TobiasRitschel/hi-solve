# HI-SOLVE
## Introduction
HI-SOLVE implements an iterative high-order numerical method for solving nonlinear algebraic equations in the form

  f(x) = 0,
  
which uses higher order derivatives. The method is inspired by (and essentially an attempt at generalizing) the iterative methods for solving cubic equations of state described by Olivera-Fuentes (1993).

The key idea is to truncate the terms in the Taylor expansion of f(x) and approximate the powers in the polynomial. As a consequence, the computation of the update in each iteration of numerical method also becomes iterative.

## Installation
This project uses CMake and the installation is standard:

1. open a terminal and go to the hi-solve directory (`cd <path-to-hi-solve>`)
2. create a new folder called build (`mkdir build`)
3. change the directory to the build folder (`cd build`)
4. create the build system (`cmake build`)
5. compile the code (`cmake --build .`)

### Test (optional)
In order to test that the installation has been successful

### Create documentation (optional)

## Bibliography
C. Olivera-Fuentes, 1993. The optimal solution of cubic equations of state, Latin American Applied Research 23, page 243--256. Link: https://www.researchgate.net/publication/233529753_THE_OPTIMAL_SOLUTION_OF_CUBIC_EQUATIONS_OF_STATE, cached: October 27th, 2019.
