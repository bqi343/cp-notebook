/**
* Source: Dhruv Rohatgi
* Usage: USACO Camp - The Applicant
*/

template<int SZ> struct LCT {
    int p[SZ], pp[SZ], c[SZ][2], sum[SZ];

    LCT () {
        FOR(i,1,SZ) sum[i] = 1;
        memset(p,0,sizeof p);
        memset(pp,0,sizeof pp);
        memset(c,0,sizeof c);
    }

    int getDir(int x, int y) {
        return c[x][0] == y ? 0 : 1;
    }

    void setLink(int x, int y, int d) {
        c[x][d] = y, p[y] = x;
    }

    void rotate(int y, int d) {
        int x = c[y][d], z = p[y];
        setLink(y,c[x][d^1],d);
        setLink(x,y,d^1);
        setLink(z,x,getDir(z,y));
        
        sum[x] = sum[y];
        sum[y] = sum[c[y][0]]+sum[c[y][1]]+1;
        pp[x] = pp[y]; pp[y] = 0;
    }

    void splay(int x) {
        while (p[x]) {
            int y = p[x], z = p[y];
            int dy = getDir(y,x), dz = getDir(z,y);
            if (!z) rotate(y,dy);
            else if (dy == dz) rotate(z,dz), rotate(y,dy);
            else rotate(y,dy), rotate(z,dz);
        }
    }

    void dis(int v, int d) { 
        p[c[v][d]] = 0, pp[c[v][d]] = v;
        sum[v] -= sum[c[v][d]];
        c[v][d] = 0; 
    }

    void con(int v, int d) { 
        c[pp[v]][d] = v;
        sum[pp[v]] += sum[v];
        p[v] = pp[v], pp[v] = 0;
    }

    void access(int v) { 
        // v is brought to the root of auxiliary tree
        // modify preferred paths
        
        splay(v);
        dis(v,1);
        
        while (pp[v]) {
            int w = pp[v]; splay(w);
            dis(w,1), con(v,1);
            splay(v);
        }
    }

    int find_root(int v) {
        access(v);
        while (c[v][0]) v = c[v][0];
        access(v);
        return v;
    }

    int find_depth(int v) {
        access(v);
        return sum[c[v][0]];
    }

    void cut(int v) { 
        // cut link between v and par[v]
        access(v);
        pp[c[v][0]] = p[c[v][0]] = 0; // fix
        sum[v] -= sum[c[v][0]];
        c[v][0] = 0;
    }

    void link(int v, int w) { 
        // v, which is root of another tree, is now child of w
        access(v), access(w);
        pp[w] = v; con(w,0);
    }

    int anc(int v, int num) {
        if (find_depth(v) < num) return 0;
        access(v);
        v = c[v][0];
        
        while (1) {
            if (sum[c[v][1]] >= num) v = c[v][1];
            else if (sum[c[v][1]]+1 == num) return v;
            else num -= (sum[c[v][1]]+1), v = c[v][0];
        }
    }
    
    void print(int x) {
        FOR(i,1,x+1) cout << i << " " << find_root(i) << " " << find_depth(i) << " " << anc(i,2) << "\n";
        cout << "\n";
    }
};

LCT<100001> L;

int main() {
    L.link(2,1); L.link(3,1); L.link(4,1); L.link(5,4);
    L.link(10,4); L.link(7,6); L.link(8,7); L.link(9,8);
    L.print(10);
    
    L.cut(4); L.link(4,8);
    L.print(10);
}