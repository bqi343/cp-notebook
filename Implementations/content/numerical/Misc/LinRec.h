/**
 * Description: Berlekamp-Massey, computes linear recurrence 
	* \texttt{C} of order $N$ for sequence \texttt{s} of $2N$ terms.
 * Time: \texttt{init} $\Rightarrow O(N|C|),$ 
	* \texttt{eval} $\Rightarrow O(|C|^2\log p)$.
 * Usage: LinRec L; L.init({0,1,1,2,3,5,8}); // Fibonacci
 * Source: 
	* http://crypto.stanford.edu/~mironov/cs359/massey.pdf
	* https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm
	* http://codeforces.com/blog/entry/61306
	* MIT ICPC notebook
 * Verification: http://codeforces.com/contest/506/problem/E
 */
 
struct LinRec {
	poly s, C, rC; 
	void BM() {
		int x = 0; T b = 1; // B is fail vector, gives 0,0,...,b
		poly B; B = C = {1}; // invariant: sz(B)+x = M
		F0R(i,sz(s)) { ++x; int L = sz(C), M = i+3-L;
			T d = 0; F0R(j,L) d += C[j]*s[i-j]; 
			if (d == 0) continue; // rec still works
			poly _C = C; T coef = d/b; // invariant: sz(B)+x=_L
			C.rsz(max(L,M)); F0R(j,sz(B)) C[j+x] -= coef*B[j];
			if (L < M) B = _C, b = d, x = 0;
		}
	}
	void init(const poly& _s) { 
		s = _s; BM();
		rC = C; reverse(all(rC)); // poly for getPo
		C.erase(begin(C)); trav(t,C) t *= -1;
	} // now s[i]=sum_{j=0}^{sz(C)-1}C[j]*s[i-j-1]
	poly getPo(ll p) { // get x^p mod rC
		if (p == 0) return {1};
		poly r = getPo(p/2); r = (r*r)%rC;
		return p&1?(r*poly{0,1})%rC:r;
	}
	T dot(poly v) { // dot product with seq
		T ans = 0; F0R(i,sz(v)) ans += v[i]*s[i];
		return ans; } // get p-th term of rec
	T eval(ll p) { assert(p >= 0); return dot(getPo(p)); } 
};