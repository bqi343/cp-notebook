/**
* Description: Similar to 2D segtree, less memory
* For more complex queries use a customized treap
* Verification: http://codeforces.com/contest/785/submission/33953058
*/

template<int SZ> struct mstree { 
    Tree<pi> val[SZ+1]; // for offline queries use vector with binary search instead
    
    void upd(int x, int y, int t = 1) { // x-coordinate between 1 and SZ inclusive
        for (int X = x; X <= SZ; X += X&-X) {
            if (t == 1) val[X].insert({y,x});
            else val[X].erase({y,x});
        }
    }
    
    int query(int x, int y) { 
        int t = 0;    
        for (;x > 0; x -= x&-x) t += val[x].order_of_key({y,MOD});
        return t;
    }
    
    int query(int lox, int hix, int loy, int hiy) { // query number of elements within a rectangle
        return query(hix,hiy)-query(lox-1,hiy)
            -query(hix,loy-1)+query(lox-1,loy-1);
    }
};
