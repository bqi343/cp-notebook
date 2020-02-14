/**
 * Description: Used only once. Burrows-Wheeler Transform appends 
 	* \# to a string, sorts the rotations of the string in increasing order, 
	* and constructs a new string that contains the last character 
	* of each rotation. This function reverses the transform.
 * Time: O(N\log N)
 * Source: GeeksForGeeks
 * Verification: https://cses.fi/problemset/task/1113/
 */

str reverseBW(str s) {
	vi nex(sz(s)); vi v(sz(s)); iota(all(v),0);
	stable_sort(all(v),[&s](int a,int b){return s[a]<s[b];});
	F0R(i,sz(v)) nex[i] = v[i];
	int cur = nex[0]; str ret;
	for (; cur; cur = nex[cur]) ret += s[v[cur]];
	return ret;
}