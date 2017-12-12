// https://open.kattis.com/problems/closestpair2
// Nlog^2N

pair<double,pair<pdd,pdd>> MN = {INF,{{0,0},{0,0}}};

int n;

bool cmp(pdd a, pdd b) {
    return a.s < b.s;
}

double dist(pdd a, pdd b) {
    b.f -= a.f, b.s -= a.s;
    return sqrt(b.f*b.f+b.s*b.s);
}

pair<double,pair<pdd,pdd>> strip(vector<pdd> v, double di) {
    pair<double,pair<pdd,pdd>> ans = MN;
    F0R(i,v.size()) FOR(j,i+1,v.size()) {
        if (v[i].s+di <= v[j].s) break;
        ans = min(ans,{dist(v[i],v[j]),{v[i],v[j]}});
    }
    return ans;
}

pair<double,pair<pdd,pdd>> bes (vector<pdd> v) {
    if (v.size() == 1) return MN;
    int M = v.size()/2;
    vector<pdd> v1(v.begin(),v.begin()+M), v2(v.begin()+M,v.end());
    auto a = bes(v1), b = bes(v2);
    double di = min(a.f,b.f);
    
    vector<pdd> V;
    F0R(i,v.size()) if (v[i].f > v[M].f-di && v[i].f < v[M].f+di) V.pb(v[i]);
    sort(V.begin(),V.end(),cmp);
    
    auto z = strip(V,di);
    return min(min(a,b),z);
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cout << fixed << setprecision(2);
	while (cin >> n) {
	    if (n == 0) break;
	    vector<pdd> v(n);
	    F0R(i,n) cin >> v[i].f >> v[i].s;
	    sort(v.begin(),v.end());
	    auto a = bes(v);
	    cout << a.s.f.f << " " << a.s.f.s << " " << a.s.s.f << " " << a.s.s.s << "\n";
	}
}