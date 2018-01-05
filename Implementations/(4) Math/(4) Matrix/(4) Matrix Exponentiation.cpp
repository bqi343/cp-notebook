/**
* Source: KACTL
* Verification: https://dmoj.ca/problem/si17c1p5
*/

template<int SZ> struct mat {
    array<array<ll,SZ>,SZ> d;
    
    mat() {
        F0R(i,SZ) F0R(j,SZ) d[i][j] = 0;
    }
    
    mat operator+(const mat& m) {
        mat<SZ> a;
        F0R(i,SZ) F0R(j,SZ) a.d[i][j] = (d[i][j]+m.d[i][j]) % MOD;
        return a;
    }
    
    mat operator*(const mat& m) {
        mat<SZ> a;
        F0R(i,SZ) F0R(j,SZ) F0R(k,SZ) 
            a.d[i][k] = (a.d[i][k]+d[i][j]*m.d[j][k]) % MOD;
        return a;
    }
    
    mat operator^(ll p) {
        mat<SZ> a, b(*this); 
        F0R(i,SZ) a.d[i][i] = 1;
        
        while (p) {
            if (p&1) a = a*b;
            b = b*b;
            p /= 2;
        }
        
        return a;
    }
    
    void print() {
        F0R(i,SZ) {
            F0R(j,SZ) cout << d[i][j] << " ";
            cout << "\n";
        }
        cout << "------------\n";
    }
};

/*
mat<2> x; x.d[0][0] = 1, x.d[1][0] = 2, x.d[1][1] = 1, x.d[0][1] = 3;
mat<2> y = x*x;
mat<2> z = x^5;
x.print(), y.print(), z.print();
*/
