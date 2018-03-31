/*
* Description: Calculates determinant mod a prime via gaussian elimination
* Usage: CF Stranger Trees
*/

ll po (ll b, ll p) { return !p?1:po(b*b%MOD,p/2)*(p&1?b:1)%MOD; }
ll inv (ll b) { return po(b,MOD-2); }

int mul(ll a, ll b) { return a*b%MOD; }
int sub(ll a, ll b) { return ((a-b)%MOD+MOD)%MOD; }

void elim(mat& m, int a, int c) { // column, todo row
    ll x = m.d[c][a];
    FOR(i,a,m.a) m.d[c][i] = sub(m.d[c][i],x*m.d[a][i]);
}

int det(mat m) {
    ll prod = 1;
    F0R(i,m.a) {
        bool done = 0;
        FOR(j,i,m.a) if (m.d[j][i] != 0) {
            done = 1; swap(m.d[j],m.d[i]);
            
            if ((j-i)&1) prod = mul(prod,MOD-1);
            prod = mul(prod,m.d[i][i]);
            
            ll x = inv(m.d[i][i]);
            FOR(k,i,m.a) m.d[i][k] = mul(m.d[i][k],x);
            FOR(k,i+1,m.a) elim(m,i,k);
            break;
        }
        if (!done) return 0;
    }
    return prod;
}