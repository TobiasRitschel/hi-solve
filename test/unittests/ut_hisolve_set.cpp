/*
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
*/

// Standard libraries
#include <cstdlib> // For EXIT_SUCCESS and EXIT_FAILURE
#include <cmath> // For fabs

// The library being tested
#include <hi-solve.h>

/// Test the set functions in HiSolve

int main(int argc, char **argv){
  // Small number used for testing equality
  const double eps = 1.0e-14;

  // Options (REMARK: these MUST be different from the default values)
  const double  tol         = 1.0e-10;
  const size_t  maxit       = 17;
  const size_t  Nmaxinit    = 5;
  const size_t  Nmaxfinal   = 2*Nmaxinit + 1;
  const bool    UseMaxOrder = false;

  // Simply create an object given the highest order number of derivatives to be evaluated
  HiSolve solver(Nmaxinit);

  // Set the algorithmic parameters
  solver.setTol         (tol        );
  solver.setMaxIt       (maxit      );
  solver.setNmax        (Nmaxfinal  );
  solver.setUseMaxOrder (UseMaxOrder);

  // Check that the getters return the correct result
  if(fabs(solver.getTol()      - tol) > eps ){ return EXIT_FAILURE; }
  if(solver.getMaxIt()        != maxit      ){ return EXIT_FAILURE; }
  if(solver.getNmax()         != Nmaxfinal  ){ return EXIT_FAILURE; }
  if(solver.getUseMaxOrder()  != UseMaxOrder){ return EXIT_FAILURE; }

  return EXIT_SUCCESS;
}
