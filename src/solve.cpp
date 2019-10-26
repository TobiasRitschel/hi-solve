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

// Class header
#include <hi-solve.h>

double HiSolve::solve(const Fun &f, const double x0){
  // Copy the initial guess
  double x = x0;

  // Evaluate the function and derivatives
  f.eval(x, N(0), df);

  // Iterate until convergence or maximum number of iterations is reached
  size_t  it = 0;
  bool    Converged     = fabs(df[0]) < tol_;
  bool    MaxItReached  = false;
  while(!Converged && !MaxItReached){
    // Increment the iteration counter
    ++it;

    // Compute update
    const double dx = (this->*updateStrategy)(N(it));

    // Update approximation of solution
    x += dx;

    // Evaluate the function and its derivatives
    f.eval(x, Order(N(it)), df);

    // Check for convergence and whether the maximum number of iterations has been reached
    Converged     = fabs(df[0]) < tol_;
    MaxItReached  = it == maxit_;
  } // End while not Converged and not MaxItReached

  return x;
}
