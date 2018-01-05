/**
* Description: persistent segtree node without lazy updates
* Verification: Codeforces Problem 893F - Subtree Minimum Query
* Implementation: http://codeforces.com/contest/893/submission/32652140
*/ 

struct Node { 
    int val = 0;
    Node* c[2];
    
    Node* copy() {
        Node* x = new Node(); *x = *this;
        return x;
    }
    
    int query(int low, int high, int L, int R) {  
        if (low <= L && R <= high) return val;
        if (R < low || high < L) return MOD;
        int M = (L+R)/2;
        return min(c[0]->query(low,high,L,M),
                   c[1]->query(low,high,M+1,R));
    }
    
    Node* upd(int ind, int v, int L, int R) {
        if (R < ind || ind < L) return this;
        Node* x = copy();
        
        if (ind <= L && R <= ind) {
            x->val += v;
            return x;
        }
        
        int M = (L+R)/2;
        x->c[0] = x->c[0]->upd(ind,v,L,M);
        x->c[1] = x->c[1]->upd(ind,v,M+1,R);
        x->val = min(x->c[0]->val,x->c[1]->val);
        
        return x;
    }
    
    void build(vi& arr, int L, int R) {
        if (L == R) {
            if (L < (int)arr.size()) val = arr[L];
            else val = 0;
            return;
        }
        int M = (L+R)/2;
        c[0] = new Node();
        c[0]->build(arr,L,M);
        c[1] = new Node();
        c[1]->build(arr,M+1,R);
        val = min(c[0]->val,c[1]->val);
    }
};
