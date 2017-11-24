// DSU Template

int ans = 0;
vector<pair<int,pii>> edge;

DSU<100> D;

void kruskal() {
	sort(edge.begin(),edge.end());
	for (auto a: edge) if (D.unite(a.s.f,a.s.s)) ans += a.f;	
}

int main() {
	F0R(i,100) FOR(j,i+1,100) if (rand() % 5 == 0) edge.pb({rand() % 100+1,{i,j}});
	kruskal();
	cout << D.sz[D.get(5)] << " " << ans;
}
