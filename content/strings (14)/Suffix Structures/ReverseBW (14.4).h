/**
 * Description: Reverse Burrows-Wheeler
 * Source: ?
 * Verification: https://cses.fi/problemset/task/1113/
 */

string reverseBW(string s) {
	int nex[sz(s)];
	vector<pair<char,int>> v; F0R(i,sz(s)) v.pb({s[i],i});
	sort(all(v)); F0R(i,sz(v)) nex[i] = v[i].s;
	int cur = nex[0]; string ret;
	for (; cur;cur = nex[cur]) ret += v[cur].f;
	return ret;
}