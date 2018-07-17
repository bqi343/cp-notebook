/**
* Source: GeeksForGeeks
* Description: Nlog^2N, can be improved
* Usage: https://open.kattis.com/problems/closestpair2
*/

pair<double,pair<pd,pd>> MN = {INF,{{0,0},{0,0}}};

int n;

bool cmp(pd a, pd b) {
    return a.s < b.s;
}

double dist(pd a, pd b) {
    b.f -= a.f, b.s -= a.s;
    return sqrt(b.f*b.f+b.s*b.s);
}

pair<double,pair<pd,pd>> strip(vector<pd> v, double di) {
    pair<double,pair<pd,pd>> ans = MN;
    F0R(i,sz(v)) FOR(j,i+1,sz(v)) {
        if (v[i].s+di <= v[j].s) break;
        ans = min(ans,{dist(v[i],v[j]),{v[i],v[j]}});
    }
    return ans;
}

pair<double,pair<pd,pd>> bes (vector<pd> v) {
    if (v.size() == 1) return MN;
    int M = v.size()/2;
    vector<pd> v1(v.begin(),v.begin()+M), v2(v.begin()+M,v.end());
    auto a = bes(v1), b = bes(v2);
    double di = min(a.f,b.f);
    
    vector<pd> V;
    F0R(i,v.size()) if (v[i].f > v[M].f-di && v[i].f < v[M].f+di) V.pb(v[i]);
    sort(V.begin(),V.end(),cmp);
    
    auto z = strip(V,di);
    return min(min(a,b),z);
}

int main() {
	cout << fixed << setprecision(2);
	while (cin >> n) {
	    if (n == 0) break;
	    vector<pd> v(n);
	    F0R(i,n) cin >> v[i].f >> v[i].s;
	    sort(all(v));
	    auto a = bes(v);
	    cout << a.s.f.f << " " << a.s.f.s << " " << a.s.s.f << " " << a.s.s.s << "\n";
	}
}
