/**
* Description: Segment tree on values instead of indices
* Verification: http://www.spoj.com/problems/MKTHNUM/
*/

int N,Q, A[100000];
map<int,int> m;
vi revm;

void input() {
	cin >> N >> Q;
	F0R(i,N) cin >> A[i];
}

void compress() {
    F0R(i,N) m[A[i]] = 0;
    int nex = 0;
    for (auto& a: m) {
        a.s = nex++;
        revm.pb(a.f);
    }
    F0R(i,N) A[i] = m[A[i]];
}

template<int SZ> struct wavelet {
    vi mapl[2*SZ], mapr[2*SZ], val[2*SZ];
    
    void build(int ind = 1, int L = 0, int R = SZ-1) { // build a wavelet tree
        if (ind == 1) { F0R(i,N) val[ind].pb(i); }
        
        if (L < R) {
            int M = (L+R)/2;
            for (int i: val[ind]) {
                val[2*ind+(A[i] > M)].pb(i);
                mapl[ind].pb(sz(val[2*ind])-1);
                mapr[ind].pb(sz(val[2*ind+1])-1);
            }
            build(2*ind,L,M);
            build(2*ind+1,M+1,R);
        }
    }
    
    int getl(int ind, int x) { return x < 0 ? -1 : mapl[ind][x]; }
    
    int getr(int ind, int x) { return x < 0 ? -1 : mapr[ind][x]; }
    
    int query(int lind, int rind, int k, int ind = 1, int L = 0, int R = SZ-1) { // how many <= mid with index <= r
        if (L == R) return L;
        
        int M = (L+R)/2;
        int t = getl(ind,rind)-getl(ind,lind-1);
        if (t >= k) return query(getl(ind,lind-1)+1,getl(ind,rind),k,2*ind,L,M);
        return query(getr(ind,lind-1)+1,getr(ind,rind),k-t,2*ind+1,M+1,R);
    }
};

wavelet<1<<17> w;

int main() {
    input();
    compress();
    w.build();
    
    F0R(i,Q) {
        int l,r,k; cin >> l >> r >> k;
        cout << revm[w.query(l-1,r-1,k)] << "\n";
    }
}