/**
 * Description: for each prefix, stores link to max length suffix which is also a prefix
 * Source: https://ideone.com/0cMjZJ
 * Verification: 
	* Kattis stringmultimatching
	* https://codeforces.com/contest/710/problem/F
 */

template<int SZ> struct AhoCorasick {
	int sz = 1, link[SZ]; 
	map<char,int> to[SZ];

	void add(string s) { // add word
		int v = 0;
		trav(c,s) {
			if (!to[v].count(c)) to[v][c] = sz++;
			v = to[v][c];
		}
	}

	int nex(int j, char c) { // state after adding character
		// if alphabet size is limited, speed up with memoization 
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
