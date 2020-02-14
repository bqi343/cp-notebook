/**
 * Description: Polynomial hash for substrings with two bases.
 * Source:
	* KACTL
	* https://codeforces.com/contest/1207/submission/59309672
 * Verification: 
	* USACO Dec 17 Plat 1
	* CF Check Transcription
 */

uniform_int_distribution<int> MULT_DIST(0.1*MOD,0.9*MOD);
typedef array<int,2> T; // bases not too close to ends 
const T base = {MULT_DIST(rng),MULT_DIST(rng)};
T operator+(const T& l, const T& r) { 
	T x; F0R(i,2) x[i] = (l[i]+r[i])%MOD; 
	return x; }
T operator-(const T& l, const T& r) { 
	T x; F0R(i,2) x[i] = (l[i]-r[i]+MOD)%MOD; 
	return x; }
T operator*(const T& l, const T& r) { 
	T x; F0R(i,2) x[i] = (ll)l[i]*r[i]%MOD; 
	return x; }

struct HashRange {
	str S; 
	vector<T> pows, cum;
	void init(str _S) {
		S = _S; pows.rsz(sz(S)), cum.rsz(sz(S)+1);
		pows[0] = {1,1}; FOR(i,1,sz(S)) pows[i] = pows[i-1]*base;
		F0R(i,sz(S)) {
			int c = S[i]-'a'+1;
			cum[i+1] = base*cum[i]+T{c,c};
		}
	}
	T hash(int l, int r) { return cum[r+1]-pows[r+1-l]*cum[l]; }
	/**int lcp(HashRange& b) {
		int lo = 0, hi = min(sz(S),sz(b.S));
		while (lo < hi) {
			int mid = (lo+hi+1)/2;
			if (cum[mid] == b.cum[mid]) lo = mid;
			else hi = mid-1;
		}
		return lo;
	}*/
};
/// HashRange H; H.init("ababab"); F0R(i,6) FOR(j,i,6) ps(i,j,H.hash(i,j));
