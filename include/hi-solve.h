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

#ifndef HI_SOLVE_H
#define HI_SOLVE_H

// Standard library headers
#include <vector> // For std::vector
#include <cmath> // For pow
#include <algorithm> // For min

// Abstract function base class
#include <fun.h>

/// A class for solving scalar nonlinear algebraic equations using high-order methods

/**
This class provides functionality for approximating the solution to scalar-valued nonlinear algebraic equations by using a high-order numerical method, i.e. a method which exploits the information from high-order derivative of the algebraic function.

You need to provide a function object which allows the return of these high-order derivatives; this class does not compute them (e.g. using finite-difference approximations or automatic differentiation techniques).
*/

class HiSolve {
  // Internal data members
  private:
    double  tol_;             // Tolerance used to terminate the iterations
    size_t  maxit_;           // Maximum number of iterations
    size_t  Nmax_;            // Maximum order used
    bool    UseMaxOrder_;     // Whether or not to use the maximum-order variant of the algorithm
    std::vector<double> df;   // Function value and derivatives
    double (HiSolve::*updateStrategy)(const size_t) const;  // Which update strategy to use (1, 2, or 3)

  /**
  Constructor with default values for tolerance (1e-6), maximum number of iterations (20), and variant of the algorithm (maximum-order variant).

  @param[in] Nmax highest-order derivative used
  */
  public:
  HiSolve(const size_t Nmax) : tol_(1.0e-6), maxit_(20), Nmax_(Nmax), UseMaxOrder_(true), df(Nmax) { setUpdateStrategy(1); }

  /**
  Constructor with user-specified tolerance, maximum number of iterations, and variant of the algorithm.

  @param[in] tol          tolerance for terminating the iterations
  @param[in] maxit        maximum number of iterations
  @param[in] Nmax         highest-order derivative used
  @param[in] UseMaxOrder  whether or not to use the maximum-order variant of the algorithm
  @param[in] UpdateStrategy which update strategy to use (must be 1, 2, or 3)
  */
  public:
  HiSolve(const double tol, const size_t maxit, const size_t Nmax, const bool UseMaxOrder, const size_t UpdateStrategy) : tol_(tol), maxit_(maxit), Nmax_(Nmax), UseMaxOrder_(UseMaxOrder), df(Nmax) { setUpdateStrategy(UpdateStrategy); }

  /**
  Set the tolerance for terminating the iterations

  @param[in] tol tolerance for terminating the iterations
  */
  public:
  void setTol(const double tol){ tol_ = tol; }

  /**
  Get the tolerance for terminating the iterations

  @returns the tolerance for terminating the iterations
  */
  public:
  double getTol() const { return tol_; }

  /**
  Set the maximum number of iterations

  @param[in] maxit maximum number of iterations
  */
  public:
  void setMaxIt(const size_t maxit){ maxit_ = maxit; }

  /**
  Get the maximum number of iterations

  @returns the maximum number of iterations
  */
  public:
  size_t getMaxIt() const { return maxit_; }

  /**
  Set the highest order of derivatives used

  @param[in] Nmax the highest order of derivatives used
  */
  public:
  void setNmax(const size_t Nmax){ Nmax_ = Nmax; }

  /**
  Get tthe highest order of derivatives used

  @returns the highest order of derivatives used
  */
  public:
  size_t getNmax() const { return Nmax_; }

  /**
  Set whether or not to use the maximum-order variant

  @param[in] UseMaxOrder if true, the maximum-order variant of the algorithm is used
  */
  public:
  void setUseMaxOrder(const bool UseMaxOrder){ UseMaxOrder_ = UseMaxOrder; }

  /**
  Get whether or not the maximum-order variant is used

  @returns whether or not the maximum-order variant of the algorithm is used
  */
  public:
  bool getUseMaxOrder() const { return UseMaxOrder_; }

  /**
  Set the update strategy (1, 2, or 3)

  @param UpdateStrategy the update strategy number (1, 2, or 3)
  */
  public:
  void setUpdateStrategy(const size_t UpdateStrategy){
    if(UpdateStrategy == 0 || UpdateStrategy > 3){
      throw "Unknown value of UpdateStrategy. Please use 1, 2, or 3.";
    } // End if UpdateStrategy != 1, 2, or 3

    // Set the update strategy
    switch(UpdateStrategy){
      case 1: updateStrategy = &HiSolve::updateStrategy1; break;
      case 2: updateStrategy = &HiSolve::updateStrategy2; break;
      case 3: updateStrategy = &HiSolve::updateStrategy3; break;
    } // End switch UpdateStrategy
  }

  /**
  Solve a set of nonlinear algebraic equations

  @param[in] f  function object
  @param[in] x0 initial guess
  */
  public:
  double solve(const Fun &f, const double x0);

  /**
  Strategy 1 for computing a approximate high-order update

  @param[in] N number of terms to include in the approximation
  */
  private:
  double updateStrategy1(const size_t N) const;

  /**
  Strategy 2 for computing a approximate high-order update

  @param[in] N number of terms to include in the approximation
  */
  private:
  double updateStrategy2(const size_t N) const;

  /**
  Strategy 3 for computing an approximate high-order update

  @param[in] N number of terms to include in the approximation
  */
  private:
  double updateStrategy3(const size_t N) const;

  /**
  Internal function returning the number of terms used in a given iteration

  @param[in] it the iteration number

  @returns the number of terms to use
  */
  size_t N(const size_t it) const { return UseMaxOrder_ ? Nmax_ : std::min(it, Nmax_); }

  /**
  Internal function returning the order of the highest-order derivative to be used

  @param[in] N the number of terms to be used

  @returns the order of the highest-order derivative to be used
  */
  size_t Order(const size_t N) const { return UseMaxOrder_ ? N : N+1; }
};

#endif
