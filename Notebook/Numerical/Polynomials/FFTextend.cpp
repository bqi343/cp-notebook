/**
 * Description: Polynomial division and sqrt
 * Source: CF, http://people.csail.mit.edu/madhu/ST12/scribe/lect06.pdf
 * Verification: https://codeforces.com/contest/438/problem/E
 */

using namespace FFT;

template<class T> vector<T> inv(vector<T> v, int p) { // compute inverse of v mod x^p, where v[0] = 1 
    v.rsz(p);  vector<T> a = {T(1)/v[0]};
    for (int i = 1; i < p; i *= 2) {
        if (2*i > p) v.rsz(2*i);
        auto l = vector<T>(begin(v),begin(v)+i), r = vector<T>(begin(v)+i,begin(v)+2*i);
        auto c = conv(a,l); c = vector<T>(begin(c)+i,end(c));
        auto b = conv(a*T(-1),conv(a,r)+c); b.rsz(i);
        a.insert(end(a),all(b));
    }
    a.rsz(p); return a;
}

template<class T> pair<vector<T>,vector<T>> divi(const vector<T>& f, const vector<T>& g) { // f = q*g+r
    if (sz(f) < sz(g)) return {{},f};
    auto q = conv(inv(rev(g),sz(f)-sz(g)+1),rev(f));
    q.rsz(sz(f)-sz(g)+1); q = rev(q);
    auto r = f-conv(q,g); r.rsz(sz(g)-1);
    return {q,r};
}

template<class T> vector<T> sqrt(vector<T> v, int p) { // S*S = v mod x^p, p is power of 2
    assert(v[0] == 1); if (p == 1) return {1};
    v.rsz(p); 
    auto S = sqrt(v,p/2);
    auto ans = S+conv(v,inv(S,p)); 
    ans.rsz(p); ans *= T(1)/T(2);
    return ans;
}