/**
 * Description: Given negation of totally monotone matrix with entries of type \texttt{D}, 
 	* find indices of row maxima (their indices increase for every submatrix). 
 	* If tie, take lesser index. \texttt{f} returns matrix entry at $(r,c)$ in $O(1)$. 
 	* Use in place of divide \& conquer to remove a log factor.
 * Source: maroonrk
 	* https://www.codechef.com/viewsolution/29003911
 	* https://en.wikipedia.org/wiki/SMAWK_algorithm
 	* http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf
 * Time: $O(R+C)$, can be reduced to $O(C(1+\log R/C))$ evaluations of $f$
 * Verification: https://www.codechef.com/viewsolution/32034859
 */

template<class F, class D=ll> vi smawk (F f, vi x, vi y) {
	vi ans(sz(x),-1); // x = rows, y = cols
	#define upd() if (ans[i] == -1 || w > mx) ans[i] = c, mx = w
	if (min(sz(x),sz(y)) <= 8) {
		F0R(i,sz(x)) { int r = x[i]; D mx; 
			each(c,y) { D w = f(r,c); upd(); } }
		return ans; 
	}
	if (sz(x) < sz(y)) { // reduce subset of cols to consider
		vi Y; each(c,y) {
			for (;sz(Y);Y.pop_back()) { int X = x[sz(Y)-1]; 
				if (f(X,Y.bk) >= f(X,c)) break; }
			if (sz(Y) < sz(x)) Y.pb(c);
		} y = Y;
	} // recurse on half the rows
	vi X; for (int i = 1; i < sz(x); i += 2) X.pb(x[i]);
	vi ANS = smawk(f,X,y); F0R(i,sz(ANS)) ans[2*i+1] = ANS[i];
	for (int i = 0, k = 0; i < sz(x); i += 2){
		int to = i+1 < sz(ans) ? ans[i+1] : y.bk; D mx;
		for(int r = x[i];;++k) {
			int c = y[k]; D w = f(r,c); upd();
			if (c == to) break; }
	}
	return ans;
};
