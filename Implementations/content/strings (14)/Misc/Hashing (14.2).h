/**
 * Description: polynomial double-hash substrings
 * Sources:
	* KACTL
	* https://codeforces.com/contest/1207/submission/59309672
 * Verification: 
	* USACO Dec 17 Plat 1
	* CF Check Transcription
 */

#include "Modular.h"

namespace pairOp {
	template<class A, class B> pair<A,B> operator+(const pair<A,B>& l, const pair<A,B>& r) { return {l.f+r.f,l.s+r.s}; }
	template<class A, class B> pair<A,B> operator-(const pair<A,B>& l, const pair<A,B>& r) { return {l.f-r.f,l.s-r.s}; }
	template<class A, class B> pair<A,B> operator*(const pair<A,B>& l, const pair<A,B>& r) { return {l.f*r.f,l.s*r.s}; }
	template<class A, class B, class C> pair<A,B> operator*(const pair<A,B>& l, const C& r) { return {l.f*r,l.s*r}; }
	template<class A, class B, class C> pair<A,B> operator*(const C& r, const pair<A,B>& l) { return l*r; }
	template<class A, class B, class C> pair<A,B> operator/(const pair<A,B>& l, const C& r) { return {l.f/r,l.s/r}; }
	
	template<class A, class B> pair<A,B>& operator+=(pair<A,B>& l, const pair<A,B>& r) { return l = l+r; }
	template<class A, class B> pair<A,B>& operator-=(pair<A,B>& l, const pair<A,B>& r) { return l = l-r; }
	template<class A, class B> pair<A,B>& operator*=(pair<A,B>& l, const pair<A,B>& r) { return l = l*r; }
	template<class A, class B, class C> pair<A,B>& operator*=(pair<A,B>& l, const C& r) { return l = {l.f*r,l.s*r}; }
	template<class A, class B, class C> pair<A,B>& operator/=(pair<A,B>& l, const C& r) { return l = {l.f/r,l.s/r}; }
}

using namespace pairOp;

uniform_int_distribution<int> MULT_DIST(0.1 * MOD, 0.9 * MOD); // not too close to ends
const pmi base = {MULT_DIST(rng),MULT_DIST(rng)};

struct hsh {
	string S; 
	vpmi pows, cum;
	
	void init(string _S) {
		S = _S; pows.rsz(sz(S)), cum.rsz(sz(S)+1);
		pows[0] = {1,1}; FOR(i,1,sz(S)) pows[i] = pows[i-1]*base;
		F0R(i,sz(S)) {
			int c = S[i]-'a'+1;
			cum[i+1] = base*cum[i]+pmi(c,c);
		}
	}
	
	pmi get(int l, int r) {	 return cum[r+1]-pows[r+1-l]*cum[l]; }
	
	int lcp(hsh& b) {
		int lo = 0, hi = min(sz(S),sz(b.S));
		while (lo < hi) {
			int mid = (lo+hi+1)/2;
			if (cum[mid] == b.cum[mid]) lo = mid;
			else hi = mid-1;
		}
		return lo;
	}
};

// hsh H; H.init("ababab"); F0R(i,6) FOR(j,i,6) ps(i,j,H.get(i,j));
