/**
* Source: CF (link no longer available)
* Description: Node + lazy updates
*/

struct node { 
    int val = 0, lazy = 0;
    node* c[2];
    
    node* copy() {
        node* x = new node(); *x = *this;
        return x;
    }
    
    void push() {
        if (!lazy) return;
        F0R(i,2) if (c[i]) {
            c[i] = new node(*c[i]);
            c[i]->val += lazy; // lazy value is included in value
            c[i]->lazy += lazy;
        }
        lazy = 0;
    }
    
    int query(int low, int high, int L, int R) {  
        if (low <= L && R <= high) return val;
        if (R < low || high < L) return MOD;
        int M = (L+R)/2;
        return lazy+min(c[0]->query(low,high,L,M), 
                        c[1]->query(low,high,M+1,R));
    }
    
    node* upd(int low, int high, int v, int L, int R) {
        if (R < low || high < L) return this;
        node* x = copy();
        if (low <= L && R <= high) {
            x->lazy += v, x->val += v;
            return x;
        }
        x->push();
        
        int M = (L+R)/2;
        x->c[0] = x->c[0]->upd(low,high,v,L,M);
        x->c[1] = x->c[1]->upd(low,high,v,M+1,R);
        x->val = min(x->c[0]->val,x->c[1]->val);
        
        return x;
    }
    
    void build(vi& arr, int L, int R) {
        if (L == R) {
            if (L < sz(arr)) val = arr[L];
            else val = 0;
            return;
        }
        int M = (L+R)/2;
        c[0] = new node(); c[0]->build(arr,L,M);
        c[1] = new node(); c[1]->build(arr,M+1,R);
        val = min(c[0]->val,c[1]->val);
    }
};

template<int SZ> struct pers {
    node* loc[MX]; // stores location of root after ith update
    int nex = 1;
    
    pers() { loc[0] = new node(); }
    
    void upd(int low, int high, int val) {
        loc[nex] = loc[nex-1]->upd(low,high,val,0,SZ-1);
        nex++;
    }
    void build(vi& arr) { 
        loc[0]->build(arr,0,SZ-1);
    }
    int query(int ti, int low, int high) { 
        return loc[ti]->query(low,high,0,SZ-1);
    }
};

pers<8> p;
vi arr = {1,7,2,3,5,9,4,6};

int query(int l, int r) {
    int mn = MOD;
    FOR(i,l,r+1) mn = min(mn,arr[i]);
    return mn;
}

void upd(int l, int r, int k) { FOR(i,l,r+1) arr[i] += k; }

int tmp[101][8][8];

int main() {
    p = pers<8>();
    p.build(arr);
    
    FOR(i,1,101) {
        int l = rand() % 8, r = rand() % 8; if (l > r) swap(l,r);
        int k = rand()%20-10;
        p.upd(l,r,k);
        upd(l,r,k);
        F0R(j1,8) FOR(j2,j1,8) tmp[i][j1][j2] = query(j1,j2);
        int z = rand() % i+1;
        F0R(j1,8) FOR(j2,j1,8) assert(tmp[z][j1][j2] == p.query(z,j1,j2)); // verification
    }
}