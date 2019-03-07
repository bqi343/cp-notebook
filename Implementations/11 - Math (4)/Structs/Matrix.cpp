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