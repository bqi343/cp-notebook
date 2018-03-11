/*
* Description: Calculates determinant mod a prime via gaussian elimination
* Usage: CF Stranger Trees
*/

typedef array<array<int,100>,100> mat;

ll po (ll b, ll p) { return !p?1:po(b*b%MOD,p/2)*(p&1?b:1)%MOD; }
ll inv (ll b) { return po(b,MOD-2); }
    
int SZ;

void elim(mat& m, int a, int c) { // column, todo row
    ll x = m[c][a];
    FOR(i,a,SZ) {
        m[c][i] = (m[c][i]-x*m[a][i])%MOD;
        if (m[c][i] < 0) m[c][i] += MOD;
    }
}

ll det(mat m) {
    ll prod = 1;
    F0R(i,SZ) {
        bool done = 0;
        FOR(j,i,SZ) if (m[j][i] != 0) {
            done = 1; if (j != i) swap(m[j],m[i]);
            if ((j-i)&1) prod *= -1;
            prod = prod*m[i][i]%MOD;
            ll x = inv(m[i][i]);
            FOR(k,i,SZ) m[i][k] = m[i][k]*x%MOD;
            FOR(k,i+1,SZ) elim(m,i,k);
            break;
        }
        if (!done) return 0;
    }
    return (prod%MOD+MOD)%MOD;
}
