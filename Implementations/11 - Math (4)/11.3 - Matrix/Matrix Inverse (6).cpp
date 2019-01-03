/*
* Description: Calculates determinant mod a prime via gaussian elimination
    * only slight adjustments needed to use doubles
* Source: Own?
* Verification: SPOJ MIFF
*/

namespace matInv {
    template<class T> void elim(Mat<T>& m, int col, int a, int b) { // column, todo row
        auto x = m.d[b][col];
        FOR(i,col,m.b) SUB(m.d[b][i],mul(x,m.d[a][i]));
    }
    
    template<class T> T gauss(Mat<T>& m) { // determinant of 1000x1000 Matrix in ~1s
        T prod = 1;
        int nex = 0;
        
        F0R(i,m.a) {
            int row = -1;
            FOR(j,nex,m.a) if (m.d[j][i] != 0) { row = j; break; }
            if (row == -1) { prod = 0; continue; }
            if (row != nex) MUL(prod,-1), swap(m.d[row],m.d[nex]);
            
            MUL(prod,m.d[nex][i]);
            auto x = inv(m.d[nex][i]);
            FOR(k,i,m.b) MUL(m.d[nex][k],x);
            
            F0R(k,m.a) if (k != nex) elim(m,i,nex,k);
            nex ++;
        }
        
        prod = (prod%MOD+MOD)%MOD;
        return prod;
    }

    int numSpan(Mat<int> m) { // Kirchhoff's theorem
        Mat<int> res(m.a-1,m.a-1);
        F0R(i,m.a) FOR(j,i+1,m.a) {
            if (i) {
                AD(res.d[i-1][i-1],m.d[i][j]);
                SUB(res.d[i-1][j-1],m.d[i][j]);
                SUB(res.d[j-1][i-1],m.d[i][j]);
            }
            AD(res.d[j-1][j-1],m.d[i][j]);
        }
        return gauss(res);
    }
    
    template<class T> Mat<T> inv(Mat<T> m) {
        Mat<T> x(m.a,2*m.a);
        F0R(i,m.a) F0R(j,m.a) x.d[i][j] = m.d[i][j];
        F0R(i,m.a) x.d[i][i+m.a] = 1;
        
        if (gauss(x) == 0) return Mat<T>(0,0);
        
        Mat<T> r(m.a,m.a);
        F0R(i,m.a) F0R(j,m.a) r.d[i][j] = x.d[i][j+m.a];
        return r;
    }
}

using namespace matInv;