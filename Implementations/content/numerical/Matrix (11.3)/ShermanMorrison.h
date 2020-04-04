/**
 * Description: Calculates $(A+uv^T)^{-1}$ given $A^{-1}$. 
 	* Not invertible if \texttt{sum=0}.
 * Source: https://en.wikipedia.org/wiki/Sherman%E2%80%93Morrison_formula
 * Verification: F from https://codeforces.com/gym/101981
 */

#include "MatrixInv.h"

template<class T> void ad(Mat<T>& A,vector<T> u,vector<T> v) {
	int n = A.r; vector<T> x(n), y(n); 
	F0R(i,n) F0R(j,n)
		x[i] += A.d[i][j]*u[j], y[j] += v[i]*A.d[i][j];
	T sum = 1; F0R(i,n) F0R(j,n) sum += v[i]*A.d[i][j]*u[j];
	F0R(i,n) F0R(j,n) A.d[i][j] -= x[i]*y[j]/sum;
}