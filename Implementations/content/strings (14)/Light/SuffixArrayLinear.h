/**
 * Description: Linear Time Suffix Array
 * Source: 
	* https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp
 	* https://www.researchgate.net/publication/224176324_Two_Efficient_Algorithms_for_Linear_Time_Suffix_Array_Construction
 * Verification:
 	* https://judge.yosupo.jp/problem/suffixarray
 */

vi sa_is(const vi& s, int upper) {
	int n = sz(s); if (!n) return {};
	vi sa(n); vb ls(n); // is suffix starting at i < suffix starting at i+1
	R0F(i,n-1) ls[i] = s[i] == s[i+1] ? ls[i+1] : s[i] < s[i+1]; 
	// s-type: less than next suffix -> ls[i] = 1 
	// l-type: greater than next suffix -> ls[i] = 0
	vi sum_l(upper), sum_s(upper);
	F0R(i,n) (ls[i] ? sum_l[s[i]+1] : sum_s[s[i]]) ++; // note that s[i] = upper-1 -> !ls[i]
	F0R(i,upper) { 
		if (i) sum_l[i] += sum_s[i-1]; // sum_l[i] = sum_{j=0}^{i-1}(s_j+l_j)
		sum_s[i] += sum_l[i]; // sum_s[i] = sum_{j=0}^{i-1}s_j+sum_{j=0}^{i}l_j
	}
	auto induce = [&](const vi& lms) {
		fill(all(sa),-1);
		vi buf = sum_s;
		for (int d: lms) if (d != n) sa[buf[s[d]]++] = d; // lms is s-type, first few ...
		buf = sum_l; sa[buf[s[n-1]]++] = n-1;
		F0R(i,n) { // do l-type in increasing order, suf[v] > suf[v+1]
			int v = sa[i]-1;
			if (v >= 0 && !ls[v]) sa[buf[s[v]]++] = v;
		}
		buf = sum_l;
		R0F(i,n) { // do s-type in decreasing order, suf[v] < suf[v+1]
			int v = sa[i]-1;
			if (v >= 0 && ls[v]) sa[--buf[s[v]+1]] = v; // lms is s-type, last few ...
		}
	};
	vi lms_map(n+1,-1), lms; int m = 0;
	FOR(i,1,n) if (!ls[i-1] && ls[i]) lms_map[i] = m++, lms.pb(i);
	induce(lms); // sorts LMS prefixes
	vi sorted_lms; each(v,sa) if (lms_map[v] != -1) sorted_lms.pb(v);
	vi rec_s(m); int rec_upper = 0; // smaller subproblem
	FOR(i,1,m) { // compare two lms substrings in sorted order
		int l = sorted_lms[i-1], r = sorted_lms[i];
		int end_l = lms_map[l]+1 < m ? lms[lms_map[l]+1] : n;
		int end_r = lms_map[r]+1 < m ? lms[lms_map[r]+1] : n;
		bool same = 0; // whether lms substrings are same
		if (end_l-l == end_r-r) {
			for (;l < end_l && s[l] == s[r]; ++l,++r);
			if (l != n && s[l] == s[r]) same = 1;
		}
		rec_s[lms_map[sorted_lms[i]]] = (rec_upper += !same);
	}
	vi rec_sa = sa_is(rec_s,rec_upper+1);
	F0R(i,m) sorted_lms[i] = lms[rec_sa[i]];
	induce(sorted_lms); // sorts LMS suffixes
	return sa;
}
