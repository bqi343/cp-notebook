/**
 * Description: The Burrows-Wheeler Transform appends \# to a string, 
	 * sorts the rotations of the string in increasing order, 
	 * and constructs a new string that contains the last character 
	 * of each rotation. This function reverses the transform.
 * Time: O(N\log N)
 * Source: ?
 * Verification: https://cses.fi/problemset/task/1113/
 */

string reverseBW(string s) {
	vi nex(sz(s));
	vector<pair<char,int>> v; F0R(i,sz(s)) v.pb({s[i],i});
	sort(all(v)); F0R(i,sz(v)) nex[i] = v[i].s;
	int cur = nex[0]; string ret;
	for (; cur;cur = nex[cur]) ret += v[cur].f;
	return ret;
}