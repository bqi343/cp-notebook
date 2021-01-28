// solves https://dmoj.ca/problem/ds5
// https://blog.csdn.net/iamzky/article/details/43494481

#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define each(a, x) for (auto& a : x)

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

#define sz(x) (int)x.size()
#define beg(x) x.begin()
#define en(x) x.end()
#define all(x) beg(x), en(x)
#define resz resize

const int MOD = 1000000007; // 998244353
const ll INF = 1e18;
const int MX = 100001;
const ld PI = 4*atan((ld)1);

template<class T> void ckmin(T &a, T b) { a = min(a, b); }
template<class T> void ckmax(T &a, T b) { a = max(a, b); }

namespace input {
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);

    template<class T> void re(T& x) { cin >> x; }
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    template<class Arg, class... Args> void re(Arg& first, Args&... rest) { 
        re(first); re(rest...); 
    }

    template<class T> void re(complex<T>& x) { T a,b; re(a,b); x = cd(a,b); }
    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.f,p.s); }
    template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
}

using namespace input;

namespace output {
    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T, size_t SZ> void pr(const array<T,SZ>& x);
    template<class T> void pr(const vector<T>& x);
    template<class T> void pr(const set<T>& x);
    template<class T1, class T2> void pr(const map<T1,T2>& x);

    template<class T> void pr(const T& x) { cout << x; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) { 
        pr(first); pr(rest...); 
    }

    template<class T1, class T2> void pr(const pair<T1,T2>& x) { 
        pr("{",x.f,", ",x.s,"}"); 
    }
    template<class T> void prContain(const T& x) {
        pr("{");
        bool fst = 1; each(a,x) pr(!fst?", ":"",a), fst = 0; 
        pr("}");
    }
    template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
    template<class T> void pr(const vector<T>& x) { prContain(x); }
    template<class T> void pr(const set<T>& x) { prContain(x); }
    template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }
    
    void ps() { pr("\n"); } 
    template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) { 
        pr(first," "); ps(rest...); // print w/ spaces
    }
}

using namespace output;

namespace io {
    void setIn(string s) { freopen(s.c_str(),"r",stdin); }
    void setOut(string s) { freopen(s.c_str(),"w",stdout); }
    void setIO(string s = "") {
        ios_base::sync_with_stdio(0); cin.tie(0); // fast I/O
        if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
    }
}

using namespace io;

typedef struct snode* sn;

struct info {
    int sz, sum, mn, mx;
    info (int v) {
        if (v == INT_MAX) {
            sz = sum = 0;
            mn = INT_MAX, mx = INT_MAX+1;
        } else {
            sz = 1; sum = mn = mx = v;
        }
    }
    info() : info(INT_MAX) {}
};

void pr(const info& a) {
    vi t = {a.sz,a.sum,a.mn,a.mx};
    pr(t);
}

info& operator+=(info& a, const info& b) {
    a.sz += b.sz, a.sum += b.sum;
    ckmin(a.mn,b.mn); ckmax(a.mx,b.mx);
    return a;
}

bool COOL = 0, FLAG = 0;

void dump(string label = "");

struct snode {
    //////// VARIABLES
    int id, val; // value in node
    sn p, c[5]; // parent, children
    bool flip = 0; 
    info INFO[2]; 
    int nextNum[2], lazy[2];
    
    snode(int ID, int v) {
        id = ID; val = v; 
        p = NULL; F0R(i,5) c[i] = NULL;
        nextNum[0] = nextNum[1] = INT_MAX; lazy[0] = lazy[1] = 0;
        calc();
    }
    
    //////// SPLAY TREE OPERATIONS
    void prop() {
        if (flip) {
            swap(c[0],c[1]); 
            F0R(i,2) if (c[i]) c[i]->flip ^= 1;
            flip = 0; 
        }
        if (nextNum[1] != INT_MAX) { // modify everything in subtree EXCEPT 01 paths 
            if (INFO[1].sz) {
                INFO[1].sum = nextNum[1]*INFO[1].sz; 
                INFO[1].mn = INFO[1].mx = nextNum[1];
            }
            F0R(i,5) if (c[i]) {
                c[i]->nextNum[1] = nextNum[1], c[i]->lazy[1] = 0;
                if (i >= 2) c[i]->nextNum[0] = nextNum[1], c[i]->lazy[0] = 0;
            }
            nextNum[1] = INT_MAX;
        }
        if (lazy[1] != 0) {
            if (INFO[1].sz) {
                INFO[1].sum += lazy[1]*INFO[1].sz;
                INFO[1].mn += lazy[1], INFO[1].mx += lazy[1];
            }
            F0R(i,5) if (c[i]) {
                c[i]->lazy[1] += lazy[1];
                if (i >= 2) c[i]->lazy[0] += lazy[1];
            }
            lazy[1] = 0;
        }
        if (nextNum[0] != INT_MAX) { // modify ONLY 01 paths 
            val = nextNum[0];
            INFO[0].sum = nextNum[0]*INFO[0].sz;
            INFO[0].mn = INFO[0].mx = nextNum[0];
            F0R(i,2) if (c[i]) c[i]->nextNum[0] = nextNum[0], c[i]->lazy[0] = 0;
            nextNum[0] = INT_MAX;
        }
        if (lazy[0] != 0) {
            val += lazy[0];
            INFO[0].sum += lazy[0]*INFO[0].sz;
            INFO[0].mn += lazy[0], INFO[0].mx += lazy[0];
            F0R(i,2) if (c[i]) c[i]->lazy[0] += lazy[0];
            lazy[0] = 0;
        }
    }
    void calc() { 
        F0R(i,5) if (c[i]) c[i]->prop();
        INFO[0] = info(val); INFO[1] = info(INT_MAX); 
        F0R(i,5) if (c[i]) {
            INFO[1] += c[i]->INFO[1];
            if (i >= 2) INFO[1] += c[i]->INFO[0];
            else INFO[0] += c[i]->INFO[0];
        }
    }
    int dir() {
        if (!p) return -2;
        F0R(i,5) if (p->c[i] == this) return i;
        assert(0);
    }
    bool isRoot() { int d = dir(); return d == -2 || d == 4; }
    
    friend void setLink(sn x, sn y, int d) {
        if (y) y->p = x;
        if (d >= 0) x->c[d] = y;
    }
    void rot() { // assume p and p->p propagated
        assert(!isRoot()); int x = dir(); sn pa = p;
        setLink(pa->p, this, pa->dir());
        setLink(pa, c[x^1], x);
        setLink(this, pa, x^1);
        pa->calc(); calc();
    }
    bool ok0() {
        int d = dir(); return d == 0 || d == 1;
    }
    void splay() {
        while (ok0() && p->ok0() && p->p->ok0()) {
            p->p->prop(), p->prop(), prop();
            dir() == p->dir() ? p->rot() : rot();
            rot();
        }
        if (ok0() && p->ok0()) p->prop(), prop(), rot();
        if (ok0()) {
            p->prop(), prop();
            auto a = p->p, b = p->c[2], c = p->c[3]; int d = p->dir();
            p->p = p->c[2] = p->c[3] = NULL; p->calc(); rot(); 
            setLink(this,b,2); setLink(this,c,3); setLink(a,this,d); calc();
        }
        while (!isRoot() && !p->isRoot()) {
            p->p->prop(), p->prop(), prop();
            dir() == p->dir() ? p->rot() : rot();
            rot();
        }
        if (!isRoot()) p->prop(), prop(), rot();
        prop();
    }

    sn splayRight() {
        prop();
        if (!c[3]) { splay(); return this; }
        return c[3]->splayRight();
    }
    
    friend sn join(sn a, sn b) {
        if (!a) return b;
        a->splay(); a = a->splayRight();
        setLink(a,b,3); a->calc(); return a;
    }
    
    //////// LINK CUT TREE BASE OPERATIONS
    void access() { // bring this to top of tree, left subtree of this is now path to root
        int it = 0;
        // if (FLAG) ps("WAT",LCT[1]->nextNum[1],LCT[1]->nextNum[0]);
        for (sn v = this, pre = NULL; v; v = v->p) {
            /*if (FLAG && v->id != 8) {
                ps("HA",v->id,v->dir()); exit(0);
            }
            if (FLAG && v->id == 7) {
                ps("WAT",v->nextNum[1]); exit(0);
            }*/
            it ++;
            v->splay(); auto c = v->c[1]; 
            /*if (c->c[2]) {
                ps("??");
                //dump();
                exit(0);
            }*/
            if (c) assert(!c->c[2] && !c->c[3]);
            if (pre) pre->prop();
            if (pre) {
                assert(v->c[4] == pre);
                auto a = pre->c[2], b = pre->c[3]; 
                if (a) a->p = NULL;
                if (b) b->p = NULL;
                pre->c[2] = pre->c[3] = NULL; pre->calc();
                if (c) c->p = NULL;
                setLink(v,join(join(a,b),c),4); 
            } else {
                if (c) c->p = NULL;
                if (v->c[4]) v->c[4]->p = NULL;
                setLink(v,join(c,v->c[4]),4);
            }
            v->c[1] = pre; v->calc(); pre = v;
        }
        // if (COOL) ps("HA",id,mn,mx,sum,sz,lazy);
        splay(); assert(!c[1]);
    }
    void makeRoot() { access(); flip ^= 1; }
    
    //////// LINK CUT TREE QUERIES
    friend sn lca(sn x, sn y) {
        if (x == y) return x;
        x->access(); y->access(); 
        /*if (FLAG) {
            dump(); exit(0);
        }
        if (FLAG) {
            ps(x->id,y->id);
            ps(x->dir());
            dump();
        }*/
        if (!x->p) return NULL;
        x->splay(); return x->p ? x->p : x;
    }
    friend bool connected(sn x, sn y) { return lca(x,y); }
    
    //////// LINK CUT TREE MODIFICATIONS
    friend bool link(sn x, sn y) { // make y parent of x
        if (connected(x,y)) exit(2);
        /*if (FLAG) {
            ps("??",x->id,y->id);
            exit(0);
        }*/
        x->makeRoot(); setLink(y,join(x,y->c[4]),4); y->calc();
        return 1;
    }
    friend bool cut(sn x, sn y) {
        x->makeRoot(); y->access(); 
        if (y->c[0] != x || x->c[0] || x->c[1]) exit(3);
        x->p = y->c[0] = NULL; y->calc(); 
        return 1;// ??
    }
    
    void propAll() {
        prop();
        F0R(i,5) if (c[i]) c[i]->propAll();
    }
};

sn getPar(sn x) {
    x->access(); x = x->c[0];
    while (1) {
        x->prop();
        if (!x->c[1]) return x;
        x = x->c[1];
    }
    return x;
}

int N,M,root;
sn LCT[MX];

void printInfo(int a) {
    ps("LABEL",a,"PARENT",LCT[a]->p?LCT[a]->p->id:-1,"FLIP",LCT[a]->flip,LCT[a]->INFO[0],LCT[a]->INFO[1]);
    F0R(b,5) if (LCT[a]->c[b]) ps("CHILD","DIR",b,"LABEL",LCT[a]->c[b]->id);
    ps("-----");
}

void dump(string label) {
    ps("DUMP",label);
    //FOR(i,1,N+1) ps("WAT",i,LCT[i]->nextNum[0],LCT[i]->val,LCT[i]->INFO[0].sz,LCT[i]->INFO[1].mx,LCT[i]->INFO[0].mn,LCT[i]->INFO[1].mn);
    FOR(a,1,N+1) {
        F0R(b,5) if (LCT[a]->c[b]) {
            ps(a,LCT[a]->c[b]->id,b);
            // ps("CHILD","DIR",b,"LABEL",LCT[a]->c[b]->id);
        }
        //printInfo(a);
    }
    FOR(a,1,N+1) ps(a,LCT[a]->flip);
    ps("----");
    // exit(0);
}

void pathInc(int y, int z) {
    LCT[y]->access(); LCT[y]->lazy[0] = z;
}

void pathMod(int y, int z) {
    LCT[y]->access(); LCT[y]->nextNum[0] = z;
    /*if (y == 4) {
        ps("??",y,z);
        dump();
        LCT[5]->access();
        dump();
        exit(0);
    }*/
}

void init() {
    setIO(); re(N,M);
    vpi ed(N-1); re(ed);
    FOR(i,1,N+1) {
        int x; re(x);
        LCT[i] = new snode(i,x);
    }
    F0R(i,N-1) {
        int x = ed[i].f, y = ed[i].s;
        // if (i == 3) FLAG = 1;
        link(LCT[x],LCT[y]);
        // if (i == 3) dump();
        // dump();
    }
    re(root); 
}

int co = 0;

void PS(int x) { cout << x << "\n"; co ++; }

int main() {
    init();
    // FLAG = 1;
    int co = 0;
    F0R(i,M) {
        int K; re(K);
        if (K == 0 || K == 5) {
            int x,y; re(x,y); LCT[root]->makeRoot(); LCT[x]->access();
            auto c = LCT[x]->c[4];
            if (K == 0) {
                if (c) c->prop(), c->nextNum[0] = c->nextNum[1] = y;
                LCT[x]->val = y; 
                
            } else {
                if (c) c->prop(), c->lazy[0] = c->lazy[1] = y;
                LCT[x]->val += y;
            }
            LCT[x]->calc();
        } else if (K == 1) {
            int x; re(x); root = x;
        } else if (K == 2 || K == 6) {
            int x,y,z; re(x,y,z); LCT[x]->makeRoot(); 
            if (K == 2) pathMod(y,z);
            else pathInc(y,z);
        } else if (K == 3 || K == 4 || K == 11) {
            int x; re(x); LCT[root]->makeRoot(); LCT[x]->access();
            auto ans = info(LCT[x]->val); sn c = LCT[x]->c[4];
            if (c) c->prop(), ans += c->INFO[0], ans += c->INFO[1];
            co ++;
            /*if (co == 1068) {
                ps("AA",K,ans,12+i);
                LCT[x]->propAll();
                dump();
                exit(0);
            }*/
            if (K == 3) PS(ans.mn);
            else if (K == 4) PS(ans.mx);
            else if (K == 11) PS(ans.sum);
        } else if (K == 7 || K == 8 || K == 10) {
            int x,y; re(x,y); LCT[x]->makeRoot(); LCT[y]->access();
            auto ans = LCT[y]->INFO[0];
            co ++;
            /*if (co == 1067) {
                ps("BB",K,ans);
                LCT[y]->propAll();
                dump();
                exit(0);
            }*/
            if (K == 7) PS(ans.mn);
            else if (K == 8) PS(ans.mx);
            else PS(ans.sum);
        } else if (K == 9) {
            int x,y; re(x,y);
            LCT[root]->makeRoot();
            if (lca(LCT[x],LCT[y]) == LCT[x]) {
                // ps("OOPSNO",root,x,y);
                // if (i == 20) ps("HI");
                continue;
            }
            cut(getPar(LCT[x]),LCT[x]);
            link(LCT[x],LCT[y]);
        } else exit(5);
    }
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/
