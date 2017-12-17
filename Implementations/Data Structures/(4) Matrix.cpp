/**
* Source: KACTL
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

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	mat<2> x; 
	x.d[0][0] = 1, x.d[1][0] = 2, x.d[1][1] = 1, x.d[0][1] = 3;
	x.print();
	
	mat<2> y = x*x;
	y.print();
	
	mat<2> z = x^5;
	z.print();
}