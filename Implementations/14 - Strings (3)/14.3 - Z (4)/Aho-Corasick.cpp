/**
 * Description: for each prefix, stores link to max length suffix which is also a prefix
 * Source: https://ideone.com/0cMjZJ
 * Verification: 
	* Kattis stringmultimatching
	* https://codeforces.com/contest/710/problem/F
	* https://codeforces.com/contest/1207/problem/G
 */

template<int SZ> struct AhoCorasick { // arbitrary alphabet
	int sz = 1, link[SZ]; 
	map<char,int> to[SZ];

	int add(string s) { // add word
		int v = 0;
		trav(c,s) {
			if (!to[v].count(c)) to[v][c] = sz++;
			v = to[v][c];
		}
		return v;
	}

	int nex(int j, char c) { // state after adding character
		while (j != -1 && !to[j].count(c)) j = link[j];
		return j == -1 ? 0 : to[j][c]; 
	}
	
	void init() { // generate links
		link[0] = -1;
		queue<int> q; q.push(0);
		while (sz(q)) {
			int v = q.front(); q.pop();
			trav(it,to[v]) {
				char c = it.f; int u = it.s;
				link[u] = nex(link[v],c); 
				q.push(u); 
			}
		}
	}
};

template<int SZ> struct AhoCorasick { // fixed alphabet
	int sz = 1, link[SZ]; 
	array<int,26> to[SZ];

	AhoCorasick() {
		F0R(i,SZ) to[i] = array<int,26>();
	}
    
	int add(string s) { // add word
		int v = 0;
		trav(C,s) {
			int c = C-'a';
			if (!to[v][c]) to[v][c] = sz++;
			v = to[v][c];
		}
		return v;
	}
	
	void init() { // generate links
		link[0] = -1;
		queue<int> q; q.push(0);
		while (sz(q)) {
			int v = q.front(); q.pop();
			F0R(c,26) if (to[v][c]) {
				int u = to[v][c];
				link[u] = link[v] == -1 ? 0 : to[link[v]][c];
				q.push(u); 
			}
			if (v) F0R(c,26) if (!to[v][c]) to[v][c] = to[link[v]][c];
			// to[v][c] is equivalent to nex(v,c) in above
		}
	}
};
