/*
* Description: Calculates determinant mod a prime via gaussian elimination
* Usage: CF Stranger Trees
*/

ll po (ll b, ll p) { return !p?1:po(b*b%MOD,p/2)*(p&1?b:1)%MOD; }
ll inv (ll b) { return po(b,MOD-2); }

int ad(int a, int b) { return (a+b)%MOD; }
int sub(int a, int b) { return (a-b+MOD)%MOD; }
int mul(int a, int b) { return (ll)a*b%MOD; }

void elim(mat& m, int a, int c) { // column, todo row
    ll x = m.d[c][a];
    FOR(i,a,m.b) m.d[c][i] = sub(m.d[c][i],mul(x,m.d[a][i]));
}

int det(mat& x, bool b = 0) { // determinant of 1000x1000 matrix in ~1s
    mat m = x;
    ll prod = 1;
    F0R(i,m.a) {
        bool done = 0;
        FOR(j,i,m.a) if (m.d[j][i] != 0) {
            done = 1; swap(m.d[j],m.d[i]);
            
            if ((j-i)&1) prod = mul(prod,MOD-1);
            prod = mul(prod,m.d[i][i]);
            
            ll x = inv(m.d[i][i]);
            FOR(k,i,m.b) m.d[i][k] = mul(m.d[i][k],x);
            
            if (b) {
                F0R(k,m.a) if (k != i) elim(m,i,k);
            } else {
                FOR(k,i+1,m.a) elim(m,i,k);   
            }
            break;
        }
        if (!done) return 0;
    }
    if (b) x = m;
    return prod;
}

mat inv(mat m) {
    mat x(m.a,2*m.a);
    F0R(i,m.a) F0R(j,m.a) x.d[i][j] = m.d[i][j];
    F0R(i,m.a) x.d[i][i+m.a] = 1;
    
    det(x,1);
    
    mat r(m.a,m.a);
    F0R(i,m.a) F0R(j,m.a) r.d[i][j] = x.d[i][j+m.a];
    return r;
}
