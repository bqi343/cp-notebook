/**
 * Description: 2D matrix operations
 * Source: KACTL
 * Verification: ? https://dmoj.ca/problem/si17c1p5, SPOJ MIFF
 */

template<class T> struct Mat {
    T** d;
    int a, b;
    
    Mat() { a = b = 0; }

    Mat(int _a, int _b) {
        a = _a, b = _b;
        d = new T*[a];
        F0R(i,a) {
            d[i] = new T[b];
            F0R(j,b) d[i][j] = 0;
        }
    }
    
    Mat (const vector<vector<T>>& v) : Mat(sz(v),sz(v[0])) {
        F0R(i,a) F0R(j,b) d[i][j] = v[i][j];
    }

    operator vector<vector<T>> () {
        auto ret = vector<vector<T>>(a,vector<T>(b));
        F0R(i,a) F0R(j,b) ret[i][j] = d[i][j];
        return ret;
    }
    
    Mat operator+(const Mat& m) {
        Mat r(a,b);
        F0R(i,a) F0R(j,b) r.d[i][j] = d[i][j]+m.d[i][j];
        return r;
    }
    Mat operator-(const Mat& m) {
        Mat r(a,b);
        F0R(i,a) F0R(j,b) r.d[i][j] = d[i][j]-m.d[i][j];
        return r;
    }
    Mat operator*(const Mat& m) {
        Mat r(a,m.b);
        F0R(i,a) F0R(j,b) F0R(k,m.b) r.d[i][k] += d[i][j]*m.d[j][k];
        return r;
    }

    friend Mat exp(const Mat& m, ll p) {
        assert(a == b);
        Mat r(a,a), base(*this); 
        F0R(i,a) r.d[i][i] = 1;
        for (; p; p /= 2, base *= base) if (p&1) r *= base;
        return r;
    }
};

namespace matInv {
    template<class T> void elim(Mat<T>& m, int col, int a, int b) { // eliminate row a from row b
        auto x = m.d[b][col];
        FOR(i,col,m.b) m.d[b][i] -= x*m.d[a][i];
    }
    
    template<class T> T gauss(Mat<T>& m) { // determinant of 1000x1000 Matrix in ~1s
        T prod = 1; int nex = 0;
        
        F0R(i,m.a) {
            int row = -1;
            FOR(j,nex,m.a) if (m.d[j][i] != 0) { row = j; break; }
            if (row == -1) { prod = 0; continue; }
            if (row != nex) prod *= -1, swap(m.d[row],m.d[nex]);
            
            prod *= m.d[nex][i];
            auto x = inv(m.d[nex][i]);
            FOR(k,i,m.b) m.d[nex][k] *= x;
            
            F0R(k,m.a) if (k != nex) elim(m,i,nex,k);
            nex ++;
        }
        
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