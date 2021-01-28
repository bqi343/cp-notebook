/**
 * Description: Aho-Corasick for fixed alphabet. For each prefix, 
 	* stores link to max length suffix which is also a prefix.
 * Time: O(N\sum)
 * Source: https://ideone.com/0cMjZJ
	* https://codeforces.com/contest/710/problem/F
	* https://codeforces.com/contest/1207/problem/G
 */

struct ACfixed { // fixed alphabet
	static const int ASZ = 26;
	struct node { array<int,ASZ> to; int link; };
	vector<node> d = {{}};
	int add(str s) { // add word
		int v = 0;
		each(C,s) {
			int c = C-'a';
			if (!d[v].to[c]) d[v].to[c] = sz(d), d.eb();
			v = d[v].to[c];
		}
		return v;
	}
	void init() { // generate links
		d[0].link = -1; 
		queue<int> q; q.push(0);
		while (sz(q)) {
			int v = q.ft; q.pop();
			F0R(c,ASZ) {
				int u = d[v].to[c]; if (!u) continue;
				d[u].link = d[v].link == -1 ? 0 : d[d[v].link].to[c];
				q.push(u); 
			}
			if (v) F0R(c,ASZ) if (!d[v].to[c]) 
				d[v].to[c] = d[d[v].link].to[c];
		}
	}
};
