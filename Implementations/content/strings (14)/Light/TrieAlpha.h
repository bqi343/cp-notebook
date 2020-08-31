/**
 * Description: insert string of lowercase letters
 */

template<int SZ> struct TrieAlpha {
	int nex[SZ][26], sz[SZ], num = 0; // num is last node in trie
	// change 2 to 26 for lowercase letters
	TrieAlpha() { memset(nex,0,sizeof nex); memset(sz,0,sizeof sz); }
	void ins(str x, int a) { // insert or delete
		int cur = 0; sz[cur] += a;
		F0R(i,sz(x)) {
			int t = x[i]-'a';
			if (!nex[cur][t]) nex[cur][t] = ++num;
			sz[cur = nex[cur][t]] += a;
		}
	}
};