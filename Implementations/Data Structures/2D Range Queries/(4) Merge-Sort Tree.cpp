template<int SZ> struct mstree { 
    Tree<pii> val[SZ+1]; // for offline queries use vector with binary search instead
    
    void upd(int x, int y, int t = 1) { // x-coordinate between 1 and SZ inclusive
        for (int X = x; X <= SZ; X += X&-X) {
            if (t) val[X].insert({y,x});
            else val[X].erase({y,x});
        }
    }
    
    int query(int x, int y) {
        int t = 0;    
        for (;x > 0; x -= x&-x) t += val[x].order_of_key({y,MOD});
        return t;
    }
    
    int query(int lox, int hix, int loy, int hiy) { // query number of elements within a rectangle
        return query(hix,hiy)-query(lox-1,hiy)-query(hix,loy-1)+query(lox-1,loy-1);
    }
};

int main() {
	mstree<100000> m;
	m.upd(3,6); m.upd(4,5);
	cout << m.query(3,5,4,6) << " " << m.query(3,5,4,5); // 2, 1
}
