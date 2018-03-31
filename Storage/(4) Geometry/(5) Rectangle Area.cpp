// Rectangle Union 
// Use Lazy SegTree with min + # query

const ll INF = 1e18;

template<int SZ> struct LazySegTree {
    pi mn[2*SZ];
    int lazy[2*SZ]; // set SZ to a power of 2
    
    LazySegTree() {
        FOR(i,SZ,2*SZ) mn[i] = {0,1};
        memset (lazy,0,sizeof lazy);
        build();
    }
    
    void push(int ind, int L, int R) {
        mn[ind].f += lazy[ind];
        if (L != R) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind];
        lazy[ind] = 0;
    }
    
    pi comb(pi a, pi b) {
        if (a.f != b.f) return min(a,b);
        return {a.f,a.s+b.s};
    }
    
    void pull(int ind) {
        mn[ind] = comb(mn[2*ind],mn[2*ind+1]);
    }
    
    void build() {
        for (int i = SZ-1; i > 0; --i) pull(i);
    }

    pi qmin(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
        push(ind,L,R);
        if (lo > R || L > hi) return {MOD,0};
        if (lo <= L && R <= hi) return mn[ind];
        
        int M = (L+R)/2;
        return comb(qmin(lo,hi,2*ind,L,M),qmin(lo,hi,2*ind+1,M+1,R));
    }
    
    void upd(int lo, int hi, int inc, int ind = 1, int L = 0, int R = SZ-1) {
        push(ind,L,R);
        if (hi < L || R < lo) return;
        if (lo <= L && R <= hi) {
            lazy[ind] = inc;
            push(ind,L,R);
            return;
        }
        
        int M = (L+R)/2;
        upd(lo,hi,inc,2*ind,L,M); upd(lo,hi,inc,2*ind+1,M+1,R);
        pull(ind);
    }
};

int N;
LazySegTree<1<<17> seg;
vector<vi> to;
ll ans = 0;

int main() {
    cin >> N;
    F0R(i,N) {
        int x1, x2, y1, y2; cin >> x1 >> x2 >> y1 >> y2;
        to.pb({y1,1,x1,x2-1});
        to.pb({y2,-1,x1,x2-1});
    }
    sort(to.begin(),to.end());
    F0R(i,to.size()-1) {
        seg.upd(to[i][2],to[i][3],to[i][1]);
        ans += (to[i+1][0]-to[i][0])*((1LL<<17)-seg.qmin(0,(1<<17)-1).s);
    }
    cout << ans;
}

/*
2
1 3 1 3
2 4 2 4
*/

/*
7
*/
