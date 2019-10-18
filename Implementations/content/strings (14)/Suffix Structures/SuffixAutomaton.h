/**
 * Description: constructs minimal DFA that recognizes all suffixes of a string
 * Time: O(N\log \sum)
 * Source: https://cp-algorithms.com/string/suffix-automaton.html
 * Verification: 
	* https://www.spoj.com/problems/SUBLEX/
	* https://open.kattis.com/problems/stringmultimatching
 */
 
struct SuffixAutomaton {
	struct state {
		int len = 0, firstPos = -1, link = -1;
		bool isClone = 0;
		map<char, int> next;
		vi invLink;
	};
	
	vector<state> st;
	int last = 0;
	void extend(char c) {
		int cur = sz(st); st.eb();
		st[cur].len = st[last].len+1, st[cur].firstPos = st[cur].len-1;
		int p = last;
		while (p != -1 && !st[p].next.count(c)) {
			st[p].next[c] = cur;
			p = st[p].link;
		}
		if (p == -1) {
			st[cur].link = 0;
		} else {
			int q = st[p].next[c];
			if (st[p].len+1 == st[q].len) {
				st[cur].link = q;
			} else {
				int clone = sz(st); st.pb(st[q]);
				st[clone].len = st[p].len+1, st[clone].isClone = 1;
				while (p != -1 && st[p].next[c] == q) {
					st[p].next[c] = clone;
					p = st[p].link;
				}
				st[q].link = st[cur].link = clone;
			}
		}
		last = cur;
	}
	void init(string s) { 
		st.eb(); trav(x,s) extend(x); 
		FOR(v,1,sz(st)) st[st[v].link].invLink.pb(v);
	}
	
	// APPLICATIONS
	void getAllOccur(vi& oc, int v) {
		if (!st[v].isClone) oc.pb(st[v].firstPos);
		trav(u,st[v].invLink) getAllOccur(oc,u);
	}
	vi allOccur(string s) {
		int cur = 0;
		trav(x,s) {
			if (!st[cur].next.count(x)) return {};
			cur = st[cur].next[x];
		}
		vi oc; getAllOccur(oc,cur); trav(t,oc) t += 1-sz(s);
		sort(all(oc)); return oc;
	}
	
	vl distinct;
	ll getDistinct(int x) {
		if (distinct[x]) return distinct[x];
		distinct[x] = 1; 
		trav(y,st[x].next) distinct[x] += getDistinct(y.s);
		return distinct[x];
	}
	ll numDistinct() { // # of distinct substrings, including empty
		distinct.rsz(sz(st));
		return getDistinct(0);
	}
	ll numDistinct2() { // another way to get # of distinct substrings
		ll ans = 1;
		FOR(i,1,sz(st)) ans += st[i].len-st[st[i].link].len;
		return ans;
	}
};