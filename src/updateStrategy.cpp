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

double HiSolve::updateStrategy1(const size_t N) const {
  // Newton-step
  double dx = -df[0]/df[1];

  // Modify Newton-step using higher-order derivatives
  for(int k = 1; k != N; ++k){
    // Auxiliary variables
    double den = 0.0;
    double aux = 1.0;
    double fac = 1.0;

    // Update Newton-step
    for(int l = 0; l != k; l++){
      fac *= l;
      den += aux*df[l+1]/fac;
      aux *= dx;
    } // End for l
  } // End for k

  return dx;
}

double HiSolve::updateStrategy2(const size_t N) const {
  // Auxiliary variables
  double fac = 1.0;

  // Newton-step
  double dx = -df[0]/df[1];

  // Modify Newton-step using higher-order derivatives
  for(int k = 1; k != N; ++k){
    // Update auxiliary factors
    const double aux = std::pow(dx, k);
    fac *= k+1;

    // Update Newton-step
    dx = 1.0/(1.0/dx - aux*df[k+1]/(fac*df[0]));
  } // End for k

  return dx;
}

double HiSolve::updateStrategy3(const size_t N) const {
  // Auxiliary variables
  double aux = 1.0;
  double fac = 1.0;

  // Newton-step
  double dx = -df[0]/df[1];

  // Modify Newton-step using higher-order derivatives
  for(int k = 1; k != N; ++k){
    // Update auxiliary factors
    aux *= dx;
    fac *= k+1;

    // Update Newton-step
    dx = 1.0/(1.0/dx - aux*df[k+1]/(fac*df[0]));
  } // End for k

  return dx;
}
