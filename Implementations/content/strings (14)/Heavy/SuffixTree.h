/**
 * Description: Used infrequently. Ukkonen's algorithm for suffix tree.
 * Time: O(N\log \sum)
 * Source: 
 	* https://codeforces.com/blog/entry/16780
 	* https://stackoverflow.com/questions/9452701/ukkonens-suffix-tree-algorithm-in-plain-english?rq=1
 * Verification: 
 	* https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1620
 	* https://www.hackerearth.com/practice/data-structures/advanced-data-structures/suffix-trees/practice-problems/algorithm/power-of-string-3/description/
 */

struct SuffixTree {
	str s; int node, pos;
	struct state { // edge to state is s[fpos,fpos+len)
		int fpos, len, link = -1; 
		map<char,int> to;
		state(int fpos, int len) : fpos(fpos), len(len) {}
	};
	vector<state> st;
	int makeNode(int pos, int len) { 
		st.pb(state(pos,len)); return sz(st)-1;
	}
	void goEdge() {
		while (pos>1 && pos>st[st[node].to[s[sz(s)-pos]]].len) {
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
	void init(str _s) {
		makeNode(-1,0); node = pos = 0;
		trav(c,_s) extend(c);
		extend('$'); s.pop_back(); // terminal char
	}
	int maxPre(str x) { // max prefix of x which is substring
		int node = 0, ind = 0;
		while (1) {
			if (ind==sz(x) || !st[node].to.count(x[ind])) return ind;
			node = st[node].to[x[ind]];
			F0R(i,st[node].len) {
				if (ind == sz(x) || x[ind] != s[st[node].fpos+i]) 
					return ind;
				ind ++;
			}
		}
	}
	vi sa; // generate suffix array
	void genSa(int x = 0, int len = 0) {
		if (!sz(st[x].to)) { // terminal node
			sa.pb(st[x].fpos-len);
			if (sa.bk >= sz(s)) sa.pop_back();
		} else {
			len += st[x].len;
			trav(t,st[x].to) genSa(t.s,len);
		}
	}
};
