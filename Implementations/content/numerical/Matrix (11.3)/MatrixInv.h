/**
 * Description: Uses gaussian elimination to convert into reduced row echelon form
	* and calculates determinant. For determinant via arbitrary modulos, 
	* use a modified form of the Euclidean algorithm because modular inverse 
	* may not exist. If you have computed $A^{-1}\pmod{p^k},$ then the inverse 
	* $\pmod{p^{2k}}$ is $A^{-1}(2I-AA^{-1}).$
 * Time: O(N^3), determinant of $1000\times 1000$ matrix of modints in 
	* 1 second if you reduce \# of operations by half
 * Source: various
 * Verification: 
	* SPOJ MIFF (matrix inverse modulo prime)
	* https://open.kattis.com/problems/equationsolver
 */

#include "Matrix.h"

const ld EPS = 1e-12;
int getRow(vector<vector<ld>>& m, int R, int i, int nex) {
    pair<ld,int> bes = {0,-1}; // find row with max absolute value
    FOR(j,nex,R) ckmax(bes,{abs(m[j][i]),j}); 
    return bes.f < EPS ? -1 : bes.s; }
int getRow(vector<vector<mi>>& m, int R, int i, int nex) {
    FOR(j,nex,R) if (m[j][i] != 0) return j;
    return -1; }
pair<T,int> gauss(Mat& m) { 
    int R = sz(m), C = sz(m[0]), rank = 0, nex = 0;
    T prod = 1; // determinant
    F0R(i,R) {
        int row = getRow(m,R,i,nex);
        if (row == -1) { prod = 0; continue; }
        if (row != nex) prod *= -1, swap(m[row],m[nex]);
        prod *= m[nex][i]; rank ++;
        T x = 1/m[nex][i]; FOR(k,i,C) m[nex][k] *= x;
        F0R(j,R) if (j != nex) {
            T v = m[j][i]; if (v == 0) continue;
            FOR(k,i,C) m[j][k] -= v*m[nex][k];
        }
        nex ++;
    }
    return {prod,rank};
}
Mat inv(Mat m) {
    int R = sz(m); assert(R == sz(m[0]));
    Mat x = makeMat(R,2*R);
    F0R(i,R) {
        x[i][i+R] = 1;
        F0R(j,R) x[i][j] = m[i][j];
    }
    if (gauss(x).s != R) return Mat();
    Mat res = makeMat(R,R);
    F0R(i,R) F0R(j,R) res[i][j] = x[i][j+R];
    return res;
}