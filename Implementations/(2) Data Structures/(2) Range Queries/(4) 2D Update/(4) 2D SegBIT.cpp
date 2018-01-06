/**
* Source: USACO Mowing the Field
* Description: array of sparse 1D segtrees
*/

const int SZ = 1<<17;

struct SegBit {
    node seg[SZ+1];
    
    SegBit() {
        F0R(i,SZ+1) seg[i] = node();
    }
    
    void upd(int x, int y, int v) { // add v
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