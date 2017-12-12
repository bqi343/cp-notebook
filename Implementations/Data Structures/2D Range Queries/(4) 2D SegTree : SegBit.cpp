// 2D Segment Tree
// Supports 2D Point Update, Range Query
// Implementation time: 9 min

const int SZ = 1<<17;

// Sparse 1D SegTree
struct node {
    int val = 0;
    node* c[2];
    
    void upd(int ind, int v, int L = 0, int R = SZ-1) { // set an element equal to v
        if (L == ind && R == ind) { val = v; return; }
        
        int M = (L+R)/2;
        if (ind <= M) {
            if (!c[0]) c[0] = new node();
            c[0]->upd(ind,v,L,M);
        } else {
            if (!c[1]) c[1] = new node();
            c[1]->upd(ind,v,M+1,R);
        }
        
        val = 0;
        if (c[0]) val += c[0]->val;
        if (c[1]) val += c[1]->val;
    }
    
    int query(int low, int high, int L = 0, int R = SZ-1) { // query sum of segment
        if (low <= L && R <= high) return val;
        if (high < L || R < low) return 0;
        
        int M = (L+R)/2, t = 0;
        if (c[0]) t += c[0]->query(low,high,L,M);
        if (c[1]) t += c[1]->query(low,high,M+1,R);
        return t;
    }
};

// 2D SegTree, sparse segtree of sparse 1D segtrees
struct Node {
    node seg;
    Node* c[2];
    
    void upd(int x, int y, int v, int L = 0, int R = SZ-1) { // set an element equal to v
        seg.upd(y,v);
        if (L == x && R == x) return;
        
        int M = (L+R)/2;
        if (x <= M) {
            if (!c[0]) c[0] = new Node();
            c[0]->upd(x,y,v,L,M);
        } else {
            if (!c[1]) c[1] = new Node();
            c[1]->upd(x,y,v,M+1,R);
        }
    }
    
    int query(int x1, int x2, int y1, int y2, int L = 0, int R = SZ-1) { // query sum of rectangle
        if (x1 <= L && R <= x2) return seg.query(y1,y2);
        if (x2 < L || R < x1) return 0;
        
        int M = (L+R)/2, t = 0;
        if (c[0]) t += c[0]->query(x1,x2,y1,y2,L,M);
        if (c[1]) t += c[1]->query(x1,x2,y1,y2,M+1,R);
        return t;
    }
};

// SegTree + BIT
// Array of Sparse Segtrees
struct SegBit {
    node seg[SZ+1];
    
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

Node n;
SegBit s;

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    
    n.upd(5,7,2);
    n.upd(3,2,20);
    n.upd(5,8,200);
    cout << n.query(3,5,2,7) << "\n"; // 22
    
    s.upd(5,7,2);
    s.upd(3,2,20);
    s.upd(5,8,200);
    cout << s.query(3,5,2,7) << "\n"; // 22
}

// read!
// ll vs. int!
