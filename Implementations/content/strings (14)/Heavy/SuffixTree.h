/**
 * Description: Ukkonen's algorithm for suffix tree
 * Time: O(N\log \sum)
 * Source: 
 	* https://codeforces.com/blog/entry/16780
 	* https://stackoverflow.com/questions/9452701/ukkonens-suffix-tree-algorithm-in-plain-english?rq=1
 * Verification: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1620
 */

 struct SuffixTree {
	string s; int node, pos;
	struct state {
		int fpos, len, link = -1;
		map<char,int> to;
		state(int fpos, int len) : fpos(fpos), len(len) {}
	};
	vector<state> st;
	int makeNode(int pos, int len) { 
		st.pb(state(pos,len)); return sz(st)-1;
	}
	void goEdge() {
		while (pos > 1 && pos > st[st[node].to[s[sz(s)-pos]]].len) {
			node = st[node].to[s[sz(s)-pos]];
			pos -= st[node].len;
		}
	}
	void extend(char c) {
		s += c; pos ++; int last = 0;
		while (pos) {
			goEdge();
			char edge = s[sz(s)-pos];
			int& v = st[node].to[edge];
			char t = s[st[v].fpos+pos-1];
			if (v == 0) {
				v = makeNode(sz(s)-pos,MOD);
				st[last].link = node; last = 0;
			} else if (t == c) {
				st[last].link = node;
				return;
			} else {
				int u = makeNode(st[v].fpos,pos-1);
				st[u].to[c] = makeNode(sz(s)-1,MOD); st[u].to[t] = v;
				st[v].fpos += pos-1; st[v].len -= pos-1;
				v = u; st[last].link = u; last = u;
			}
			if (node == 0) pos --;
			else node = st[node].link;
		}
	}
	void init(string _s) {
		makeNode(0,MOD); node = pos = 0;
		trav(c,_s) extend(c);
	}
	bool isSubstr(string _x) {
		string x; int node = 0, pos = 0;
		trav(c,_x) {
			x += c; pos ++; 
			while (pos > 1 && pos > st[st[node].to[x[sz(x)-pos]]].len) {
				node = st[node].to[x[sz(x)-pos]];
				pos -= st[node].len;
			}
			char edge = x[sz(x)-pos];
			if (pos == 1 && !st[node].to.count(edge)) return 0;
			int& v = st[node].to[edge];
			char t = s[st[v].fpos+pos-1];
			if (c != t) return 0;
		}
		return 1;
	}
};