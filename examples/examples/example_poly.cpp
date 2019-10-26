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
#include <iostream> // For cout, endl, etc.
#include <iomanip> // For setprecision

// The library being tested
#include <hi-solve.h>

/// A class implementing a polynomial

class Poly : public Fun {
  private:
  const int m_;
  const std::vector<double> a_;

  public:
  Poly(const std::vector<double> a, const int m) : a_(a), m_(m) {};

  public:
  void eval(const double x, const size_t N, std::vector<double> &dq) const override {
    // Evaluate sine and its derivatives
    for(int l = 0; l != N; ++l){
      // Base value of the function value/derivative
      dq[l] = 0.0;

      for(int i = l+1; i != m_+1; ++i){
        double fac = 1.0;

        for(int k = 1; k != l+1; ++k){
          fac *= i - k;
        } // End for i

        dq[l] += fac*a_[i-1]*pow(x, i-l-1);
      } // End for l
    } // End for k
  }
};

/// Test the solve function in HiSolve

int main(int argc, char **argv){
  // Order of the polynomial
  const int m = 31;

  // Polynomial coefficients
  std::vector<double> a(m, 0.0);

  a[0] = 0.0;
  for(int i = 1; i != m+1; ++i){
    a[i] = pow(10.0, -i);
  } // End for i

  // Create function object and vector for function evaluations
  const Poly q(a, m);
  std::vector<double> dq_mo(1);
  std::vector<double> dq_vo(1);

  // Highest order derivative to be used and tolerance
  const size_t Nmax   = 5;
  const double tol    = 1.0e-14;
  const size_t maxit  = 4e1;

  // Simply create an object given the highest order number of derivatives to be evaluated
  HiSolve solver(Nmax);

  // Set the tolerance and the maximum number of iterations
  solver.setTol   (tol  );
  solver.setMaxIt (maxit);

  // Minimum and maximum initial guesses and increment
  const double xmax =  2.0e1;
  const double xmin = -2.0e1;
  const double xinc =  2.0e0;

  // For each strategy
  for(size_t strat = 1; strat != 4; ++strat){
    // Set the strategy
    solver.setUpdateStrategy(strat);

    std::cout << "Update strategy " << strat << ":" << std::endl;
    for(int j = 0; j != m; ++j){
      // Maximum order used
      const size_t N = j;

      for(int i = 0; i != (int)((xmax - xmin)/xinc) + 1; ++i){
        // Initial guess
        const double x0 = xmin + i*xinc;

        // Solve for root using the maximum-order variant of the algorithm
        solver.setUseMaxOrder(true);
        const double xsol_mo = solver.solve(q, x0);
        q.eval(xsol_mo, 0, dq_mo);

        // Solve for root using the variable-order variant of the algorithm
        solver.setUseMaxOrder(false);
        const double xsol_vo = solver.solve(q, x0);
        q.eval(xsol_vo, 0, dq_vo);

        // Report results
        std::cout << std::setprecision(2);
        std::cout << dq_mo[0] << "/" << dq_vo[0] << " ";
      } // End for i
      std::cout << std::endl;
    } // End for j
    std::cout << std::endl;
  } // End for strat

  return EXIT_SUCCESS;
}
