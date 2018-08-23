/*
* Description: Calculates determinant mod a prime via gaussian elimination
* Verification: SPOJ MIFF
*/

using namespace ModOp;

void elim(mat& m, int col, int a, int b) { // column, todo row
    int x = m.d[b][col];
    FOR(i,col,m.b) SUB(m.d[b][i],mul(x,m.d[a][i]));
}

ll gauss(mat& m) { // determinant of 1000x1000 matrix in ~1s
    int prod = 1, nex = 0;
    
    F0R(i,m.a) {
        int row = -1;
        FOR(j,nex,m.a) if (m.d[j][i] != 0) { row = j; break; }
        if (row == -1) { prod = 0; continue; }
        if (row != nex) MUL(prod,MOD-1), swap(m.d[row],m.d[nex]);
        
        MUL(prod,m.d[nex][i]);
        int x = inv(m.d[nex][i]);
        FOR(k,i,m.b) MUL(m.d[nex][k],x);
        
        F0R(k,m.a) if (k != nex) elim(m,i,nex,k);
        nex ++;
    }
    
    return prod;
}

mat inv(mat m) {
    mat x(m.a,2*m.a);
    F0R(i,m.a) F0R(j,m.a) x.d[i][j] = m.d[i][j];
    F0R(i,m.a) x.d[i][i+m.a] = 1;
    
    if (gauss(x) == 0) return mat(0,0);
    
    mat r(m.a,m.a);
    F0R(i,m.a) F0R(j,m.a) r.d[i][j] = x.d[i][j+m.a];
    return r;
}
