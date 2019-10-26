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

#ifndef HI_SOLVE_FUN_H
#define HI_SOLVE_FUN_H

/// An abstract class representing a scalar-valued function

/**
This class is used by the HiSolve class for function evaluations as well as evaluating up to the N'th order derivative. You need to implement a class deriving from this abstract base class to represent the specific function that you want to solve (i.e. that you want to find the roots of).

@see HiSolve
*/

class Fun {
  /**
  Evaluate the function and up to (and including) its N'th order derivative

  @param[in]  x   the scalar value to evaluate the function at
  @param[in]  N   the highest-order derivative to be evaluated
  @param[out] df  the values of the function and its derivatives
  */
  public:
  virtual void eval(const double x, const size_t N, std::vector<double> &df) const = 0;
};

#endif
