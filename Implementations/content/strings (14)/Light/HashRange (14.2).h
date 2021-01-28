/**
 * Description: Polynomial hash for substrings with two bases.
 * Source:
	* KACTL
	* https://codeforces.com/contest/1207/submission/59309672
 * Verification: 
	* USACO Dec 17 Plat 1 (LCP :o)
	* CF Check Transcription
 */

typedef array<int,2> H; // bases not too close to ends 
uniform_int_distribution<int> BDIST(0.1*MOD,0.9*MOD);
const H base = {BDIST(rng),BDIST(rng)};
/// const T ibase = {(int)inv(mi(base[0])),(int)inv(mi(base[1]))};
H operator+(H l, H r) { 
	F0R(i,2) if ((l[i] += r[i]) >= MOD) l[i] -= MOD;
	return l; }
H operator-(H l, H r) { 
	F0R(i,2) if ((l[i] -= r[i]) < 0) l[i] += MOD;
	return l; }
H operator*(H l, H r) { 
	F0R(i,2) l[i] = (ll)l[i]*r[i]%MOD;
	return l; }
H makeH(char c) { return {c,c}; }
/// H& operator+=(H& l, H r) { return l = l+r; }
/// H& operator-=(H& l, H r) { return l = l-r; }
/// H& operator*=(H& l, H r) { return l = l*r; }

vector<H> pows = {{1,1}};
struct HashRange {
	str S; vector<H> cum = {{0,0}};
	void add(char c) { S += c; cum.pb(base*cum.bk+makeH(c)); }
	void add(str s) { each(c,s) add(c); }
	void extend(int len) { while (sz(pows) <= len) pows.pb(base*pows.bk); }
	H hash(int l, int r) { int len = r+1-l; extend(len);
		return cum[r+1]-pows[len]*cum[l]; }
	/**int lcp(HashRange& b) { return first_true([&](int x) { 
		return cum[x] != b.cum[x]; },0,min(sz(S),sz(b.S)))-1; }*/
};
/// HashRange HR; HR.add("ababab"); F0R(i,6) FOR(j,i,6) ps(i,j,HR.hash(i,j));
