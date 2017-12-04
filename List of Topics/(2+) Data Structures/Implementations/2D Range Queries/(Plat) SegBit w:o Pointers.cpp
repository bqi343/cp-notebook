const int SZ = 100000;

// Sparse SegTree
struct node {
    int val, c[2];
    
    node() {
        val = 0;
        c[0] = c[1] = -1;
    }
    
    void upd(int ind, int v, int L, int R); 
    int query(int low, int high, int L, int R);
};

node seg[20000000]; // pre-allocated memory
int nex = 100001;

void node::upd(int ind, int v, int L = 0, int R = SZ-1) { // set an element equal to v
    if (L == ind && R == ind) { val = v; return; }
    
    int M = (L+R)/2;
    if (ind <= M) {
        if (c[0] == -1) {
            c[0] = nex++;
        }
        seg[c[0]].upd(ind,v,L,M);
    } else {
        if (c[1] == -1) {
            c[1] = nex++;
        }
        seg[c[1]].upd(ind,v,M+1,R);
    }
    
    val = 0;
    if (c[0] != -1) val += seg[c[0]].val;
    if (c[1] != -1) val += seg[c[1]].val;
}

int node::query(int low, int high, int L = 0, int R = SZ-1) { // query sum of segment
    if (low <= L && R <= high) return val;
    if (high < L || R < low) return 0;
    
    int M = (L+R)/2, t = 0;
    if (c[0] != -1) t += seg[c[0]].query(low,high,L,M);
    if (c[1] != -1) t += seg[c[1]].query(low,high,M+1,R);
    return t;
}

// SegTree + BIT
struct SegBit {
    void upd(int x, int y, int v) { // set an element equal to v
        for (x++;x <= SZ; x += (x&-x)) seg[x].upd(y,v);
    }
    
    int query(int x, int y1, int y2) {
        int ret = 0;
        for (;x > 0; x -= (x&-x)) ret += seg[x].query(y1,y2);
        return ret;
    }
    
    int query(int x1, int x2, int y1, int y2) { // query sum of rectangle
        return query(x2+1,y1,y2)-query(x1,y1,y2);
    }
};

SegBit s;

int main() {
    
}

// read!
// ll vs. int!