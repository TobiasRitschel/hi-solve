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

// The library being tested
#include <hi-solve.h>

/// Basic class for testing the solve function in HiSolve

class Sine : public Fun {
  public:
  void eval(const double x, const size_t N, std::vector<double> &df) const override {
    // Evaluate sine and its derivatives
    for(int k = 0; k != N; ++k){
      switch(k%2){
        case 0: df[k] = sin(x); break;
        case 1: df[k] = cos(x); break;
      } // End switch k%2

      // Negate if necessary
      if(k%4 > 1){ df[k] *= -1.0; }
    } // End for k
  }
};

/// Test the solve function in HiSolve

int main(int argc, char **argv){
  // Create function object
  const Sine f;

  // Highest order derivative to be used and tolerance
  const size_t Nmax = 5;
  const double tol  = 1.0e-12;

  // Initial guess (the answer is l*pi for any integer l)
  const double x0 = 0.17;

  // Simply create an object given the highest order number of derivatives to be evaluated
  HiSolve solver(Nmax);

  // Set the tolerance
  solver.setTol(tol);

  // Solve the algebraic equation
  const double x = solver.solve(f, x0);

  // Check that the result is correct
  if(fabs(x) > tol){ return EXIT_FAILURE; }

  return EXIT_SUCCESS;
}
