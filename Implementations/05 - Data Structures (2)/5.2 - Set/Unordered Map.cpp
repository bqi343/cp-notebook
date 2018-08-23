/**
* Description: faster than standard unordered map
* Source: http://codeforces.com/blog/entry/60737
* Verification: http://codeforces.com/contest/966/problem/E 
    * normal unordered map gets TLE
*/

namespace mapOp {
    const int tmp = chrono::high_resolution_clock::now().time_since_epoch().count();

    template<class T> struct hsh {
        size_t operator()(const T& x) const { 
            return hash<T>{}(x)^tmp; // avoid anti-hash tests?
        }
    };

    template<class a, class b> using um = gp_hash_table<a,b,hsh<a>>;

    template<class a, class b> b get(um<a,b>& u, a x) {
        if (u.find(x) == u.end()) return 0;
        return u[x];
    }
}
