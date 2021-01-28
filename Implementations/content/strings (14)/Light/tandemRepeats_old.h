/**
 * Description: Used only once. Main-Lorentz algorithm
	* finds all $(x,y)$ such that \texttt{s.substr(x,y-1) == s.substr(x+y,y-1)}.
 * Time: O(N\log N)
 * Source: https://cp-algorithms.com/string/main_lorentz.html
 * Verification: http://codeforces.com/contest/1043/problem/G
 */

#include "../Light/Z (14.3).h"

struct TandemRepeats {
	str S; vector<array<int,3>> al; 
	// (t[0],t[1],t[2]) -> exists repeating substr starting 
	// at x with length t[0]/2 for all t[1] <= x <= t[2]
	vector<array<int,3>> solveLeft(str s, int m) {
		vector<array<int,3>> v;
		vi v2 = getPrefix(str(begin(s)+m+1,end(s)),
						str(begin(s),begin(s)+m+1));
		str V = str(begin(s),begin(s)+m+2); reverse(all(V)); 
		vi v1 = z(V); reverse(all(v1));
		F0R(i,m+1) if (v1[i]+v2[i] >= m+2-i) {
			int lo = max(1,m+2-i-v2[i]), hi = min(v1[i],m+1-i);
			lo = i-lo+1, hi = i-hi+1; swap(lo,hi);
			v.pb({2*(m+1-i),lo,hi});
		}
		return v;
	}
	void divi(int l, int r) {
		if (l == r) return;
		int m = (l+r)/2; divi(l,m); divi(m+1,r);
		str t(begin(S)+l,begin(S)+r+1);
		m = (sz(t)-1)/2;
		auto a = solveLeft(t,m);
		reverse(all(t));
		auto b = solveLeft(t,sz(t)-2-m);
		each(x,a) al.pb({x[0],x[1]+l,x[2]+l});
		each(x,b) {
			int ad = r-x[0]+1;
			al.pb({x[0],ad-x[2],ad-x[1]});
		}
	}
	void init(str _S) { S = _S; divi(0,sz(S)-1); }
	vi genLen() { 
		// min length of repeating substr starting at each index
		priority_queue<pi,vpi,greater<pi>> m; m.push({MOD,MOD});
		vpi ins[sz(S)]; each(a,al) ins[a[1]].pb({a[0],a[2]});
		vi len(sz(S));
		F0R(i,sz(S)) {
			each(j,ins[i]) m.push(j);
			while (m.top().s < i) m.pop();
			len[i] = m.top().f;
		}
		return len;
	}
};
