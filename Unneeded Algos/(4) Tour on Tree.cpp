// useful for segtree queries

const int MX = 100001;

int n, r, st[MX], en[MX], depth[MX];
vi adj[MX], z;

void euler(int pre, int cur) {
    st[cur] = z.size();
    depth[cur] = depth[pre]+1;
    z.pb(cur);
    
    for (int i: adj[cur]) if (i != pre) euler(cur,i);
    
    en[cur] = z.size();
    z.pb(cur);
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n >> r;
	F0R(i,n-1) {
	    int a,b; cin >> a >> b;
	    adj[a].pb(b), adj[b].pb(a);
	}
	euler(0,r);
	FOR(i,1,n+1) cout << i << " " << st[i] << " " << en[i] << "\n";
}