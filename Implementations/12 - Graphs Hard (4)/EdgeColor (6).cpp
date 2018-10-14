/**
 * Description: https://en.m.wikipedia.org/wiki/Vizing%27s_theorem 
 * Source: Own (not very optimized)
 * Usage: https://open.kattis.com/problems/gamescheduling
 */
 
template<int SZ> struct EdgeColor {
    int n, adjVert[SZ][SZ], adjCol[SZ][SZ];
    int deg[SZ], maxDeg;
    
    EdgeColor(int _n) {
        n = _n; maxDeg = 0;
        F0R(i,n) {
            deg[i] = 0;
            F0R(j,n) adjVert[i][j] = adjCol[i][j] = -1;
        }
    }
    
    void delEdge(int x, int y) { 
        if (adjVert[x][y] == -1) return; 
        int C = adjVert[x][y];
        adjCol[x][C] = adjCol[y][C] = adjVert[x][y] = adjVert[y][x] = -1;
    }
    
    void setEdge(int x, int y, int c) { // delete previous value if it had one 
        delEdge(x,y); assert(adjCol[x][c] == -1 && adjCol[y][c] == -1);
        adjVert[x][y] = adjVert[y][x] = c, adjCol[x][c] = y, adjCol[y][c] = x;
    }
    
    void shiftPath(int x, vi p) {
        F0Rd(i,sz(p)) setEdge(x,p[i],notAdj[p[i]]);
    }
    
    vi getPath(int st, int c0, int c1) {
        vi res = {st};
        for (int nex = 0; ; nex ^= 1) {
            int c = (nex == 0 ? c0 : c1);
            if (adjCol[res.back()][c] == -1) return res;
            res.pb(adjCol[res.back()][c]);
        }
    }
    
    void flipPath(vi p, int c0, int c1) {
        F0R(i,sz(p)-1) delEdge(p[i],p[i+1]);
        F0R(i,sz(p)-1) {
            if (i&1) setEdge(p[i],p[i+1],c0);
            else setEdge(p[i],p[i+1],c1);
        }
    }
    
    int notAdj[SZ];
    
    void addEdge(int x, int y) {
        maxDeg = max(maxDeg,max(++deg[x],++deg[y]));
        
        // generate a color which is not adjacent to each vertex
        F0R(i,n) {
            F0R(j,maxDeg+1) if (adjCol[i][j] == -1) {
                notAdj[i] = j;
                break;
            }
        }
        
        vi nex(n);
        F0R(i,n) if (adjVert[x][i] != -1) nex[i] = adjCol[x][notAdj[i]];
        nex[y] = adjCol[x][notAdj[y]];
        
        // generate sequence of neighbors
        vi vis(n), seq = {y};
        while (seq.back() != -1 && !vis[seq.back()]) {
            vis[seq.back()] = 1; 
            seq.pb(nex[seq.back()]);
        }
        
        // case 1: easy
        if (seq.back() == -1) {
            seq.pop_back(), shiftPath(x,seq);
            return;
        } 
        
        // separate into path and cycle
        int ind = 0; while (seq[ind] != seq.back()) ind ++;
        seq.pop_back();
        vi path = vi(seq.begin(),seq.begin()+ind);
        vi cyc = vi(seq.begin()+ind,seq.end());
        int c0 = notAdj[x], c1 = notAdj[cyc.back()];
            
        // case based on a/b path 
        vi p = getPath(cyc.back(),c0,c1);
        if (p.back() != path.back()) {
            if (p.back() == x) { p.pop_back(), delEdge(x,p.back()); }
            flipPath(p,c0,c1); 
            notAdj[seq.back()] = c0; shiftPath(x,seq);
        } else {
            reverse(all(p));
            flipPath(p,c0,c1); 
            notAdj[path.back()] = c0; shiftPath(x,path);
        }
    }
};
