/**
* Description: Reverse Burrows-Wheeler
* Verification: https://cses.fi/problemset/task/1113/
*/

string reverseBW(string s) {
	vector<pair<char,int>> v;
	int nex[sz(s)];

	F0R(i,sz(s)) v.pb({s[i],i});
	sort(all(v));
	F0R(i,sz(v)) nex[i] = v[i].s;

	int cur = nex[0];
	string ret;
	while (cur != 0) {
		ret += v[cur].f;
		cur = nex[cur];
	}
	return ret;
}
