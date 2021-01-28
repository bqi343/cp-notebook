/**
 * Description: for each prefix, stores link to max length suffix which is also a prefix
 * Source: https://ideone.com/0cMjZJ
 * Verification: 
	* Kattis stringmultimatching
 */

struct ACunfixed { 
	struct node {
		map<char,int> to;
		int link;
	};
	vector<node> d;
	ACunfixed() { d.eb(); }
	int add(str s) { // add word
		int v = 0;
		each(c,s) {
			if (!d[v].to.count(c)) {
				d[v].to[c] = sz(d);
				d.eb();
			}
			v = d[v].to[c];
		}
		return v;
	}
	int nex(int j, char c) { // state after adding character
		while (j != -1 && !d[j].to.count(c)) j = d[j].link;
		return j == -1 ? 0 : d[j].to[c]; 
	}
	void init() { // generate links
		d[0].link = -1;
		queue<int> q; q.push(0);
		while (sz(q)) {
			int v = q.ft; q.pop();
			each(it,d[v].to) {
				int u = it.s; d[u].link = nex(d[v].link,it.f); 
				q.push(u); 
			}
		}
	}
};
