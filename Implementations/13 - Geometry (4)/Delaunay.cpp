/*
* Bowyer-Watson O(n^2logn)
* Untested
*/

namespace Delaunay {
    ld cross(cd b, cd c) {
        return (conj(b)*c).imag();
    }

    ld cross(cd a, cd b, cd c) { return cross(b-a,c-a); }
    
    bool collinear(cd a, cd b, cd c) { return cross(a,b,c) == 0; }
    
    bool ccw (cd a, cd b, cd c) { return cross(a,b,c) > 0; }
    
    bool inCircle (cd a, cd b, cd c, cd d) {
        a -= d, b -= d, c -= d;
        ld x = norm(a)*cross(b,c)+norm(b)*cross(c,a)+norm(c)*cross(a,b);
        if (!ccw(a,b,c)) x *= -1;
        return x > 0;
    }
    
    vector<array<int,3>> triangulate(vcd v) {
        v.pb(cd(-50,-50)); v.pb(cd(50,0)); v.pb(cd(0,50)); 
        // super-triangle, adjust as necessary
        
        vector<array<int,3>> ret;
        ret.pb({sz(v)-3,sz(v)-2,sz(v)-1});
        
        F0R(i,sz(v)-3) {
            map<pi,int> m;
            vector<array<int,3>> tmp;
            for (auto a: ret) {
                if (inCircle(v[a[0]],v[a[1]],v[a[2]],v[i])) 
                    m[{a[0],a[1]}] ++, m[{a[1],a[2]}] ++, m[{a[0],a[2]}] ++;
                else tmp.pb(a);
            }
            for (auto a: m) if (a.s == 1) {
                array<int,3> x = {a.f.f,a.f.s,i}; sort(all(x));
                tmp.pb(x);
            }
            swap(ret,tmp);
        }
        vector<array<int,3>> tmp;
        for (auto a: ret) if (a[2] < sz(v)-3) tmp.pb(a);
        return tmp;
    }
};