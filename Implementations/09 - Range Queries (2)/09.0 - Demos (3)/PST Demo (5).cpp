vl arr = {1,7,2,3,5,9,4,6};

ll query(int l, int r) {
    ll mn = MOD;
    FOR(i,l,r+1) mn = min(mn,arr[i]);
    return mn;
}

void upd(int l, int r, int k) { FOR(i,l,r+1) arr[i] += k; }

int tmp[101][8][8];

int main() {
    pseg<ll,8> p = pseg<ll,8>();
    p.build(arr);
    
    /*p.upd(4,5,10LL*MOD);
    cout << p.query(1,4,5) << "\n";
    p.upd(4,4,10LL*MOD);
    cout << p.query(2,4,5) << "\n";
    cout << p.query(2,4,4) << "\n";*/
    
    FOR(i,1,101) {
        int l = rand() % 8, r = rand() % 8; if (l > r) swap(l,r);
        int k = rand()%20-10;
        p.upd(l,r,k);
        upd(l,r,k);
        F0R(j1,8) FOR(j2,j1,8) tmp[i][j1][j2] = query(j1,j2);
        int z = rand() % i+1;
        F0R(j1,8) FOR(j2,j1,8) if (tmp[z][j1][j2] != p.query(z,j1,j2)) {
            cout << "BAD " << i << " " << z << " " << j1 << " " << j2 << " " << tmp[z][j1][j2] << " " << p.query(z,j1,j2) << "\n";
            exit(0);
        }
    }
}