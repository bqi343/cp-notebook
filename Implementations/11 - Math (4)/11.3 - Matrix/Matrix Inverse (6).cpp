/*
 * Description: calculates determinant via gaussian elimination
 * Source: various
 * Verification: SPOJ MIFF
 */

namespace matInv {
    template<class T> void elim(Mat<T>& m, int col, int a, int b) { // eliminate row a from row b
        auto x = m.d[b][col];
        FOR(i,col,m.c) m.d[b][i] -= x*m.d[a][i];
    }
    template<class T> T gauss(Mat<T>& m) { // determinant of 1000x1000 Matrix in ~1s
        T prod = 1; int nex = 0;

        F0R(i,m.r) {
            int row = -1;
            FOR(j,nex,m.r) if (m.d[j][i] != 0) { row = j; break; } // for ld use EPS
            if (row == -1) { prod = 0; continue; }
            if (row != nex) prod *= -1, swap(m.d[row],m.d[nex]);

            prod *= m.d[nex][i];
            auto x = 1/m.d[nex][i]; FOR(k,i,m.c) m.d[nex][k] *= x;

            F0R(k,m.r) if (k != nex) elim(m,i,nex,k);
            nex ++;
        }

        return prod;
    }

    mi numSpan(Mat<mi> m) { // Kirchhoff's theorem
        Mat<mi> res(m.r-1,m.r-1);
        F0R(i,m.r) FOR(j,i+1,m.r) {
            if (i) {
                res.d[i-1][i-1] += m.d[i][j];
                res.d[i-1][j-1] -= m.d[i][j];
                res.d[j-1][i-1] -= m.d[i][j];
            }
            res.d[j-1][j-1] += m.d[i][j];
        }
        return gauss(res);
    }

    template<class T> Mat<T> inv(Mat<T> m) {
        Mat<T> x(m.r,2*m.r);
        F0R(i,m.r) F0R(j,m.r) x.d[i][j] = m.d[i][j];
        F0R(i,m.r) x.d[i][i+m.r] = 1;

        if (gauss(x) == 0) return Mat<T>(0,0);

        Mat<T> r(m.r,m.r);
        F0R(i,m.r) F0R(j,m.r) r.d[i][j] = x.d[i][j+m.r];
        return r;
    }
}

using namespace matInv;