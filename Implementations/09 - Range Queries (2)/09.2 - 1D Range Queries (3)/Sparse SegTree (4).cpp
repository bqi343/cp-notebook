/**
* Description: Does not allocate storage for nodes with no data
* Source: Own
* Verification: USACO Mowing the Field?
*/ 

const int SZ = 1<<20;

template<class T> struct node {
    T val;
    node<T>* c[2];
    
    node() {
        val = 0;
        c[0] = c[1] = NULL;    
    }
    
    void upd(int ind, T v, int L = 0, int R = SZ-1) { // add v
        if (L == ind && R == ind) { val += v; return; }
        
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
    
    T query(int low, int high, int L = 0, int R = SZ-1) { // query sum of segment
        if (low <= L && R <= high) return val;
        if (high < L || R < low) return 0;
        
        int M = (L+R)/2;
        T t = 0;
        if (c[0]) t += c[0]->query(low,high,L,M);
        if (c[1]) t += c[1]->query(low,high,M+1,R);
        return t;
    }
    
    void UPD(int ind, node* c0, node* c1, int L = 0, int R = SZ-1) { // for 2D segtree
        if (L != R) {
            int M = (L+R)/2;
            if (ind <= M) {
                if (!c[0]) c[0] = new node();
                c[0]->UPD(ind,c0 ? c0->c[0] : NULL,c1 ? c1->c[0] : NULL,L,M);
            } else {
                if (!c[1]) c[1] = new node();
                c[1]->UPD(ind,c0 ? c0->c[1] : NULL,c1 ? c1->c[1] : NULL,M+1,R);
            }
        } 
        val = 0;
        if (c0) val += c0->val;
        if (c1) val += c1->val;
    }
};
