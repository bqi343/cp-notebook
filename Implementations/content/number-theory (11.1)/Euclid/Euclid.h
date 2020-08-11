/**
 * Description: Generalized Euclidean algorithm. \texttt{euclid} and 
 	* \texttt{invGen} work for $A,B<2^{62}$. \texttt{bet} assumes 
 	* that $0\le L\le R<B$, works for $AB<2^{62}$.
 * Source: KACTL
 	* https://codeforces.com/gym/102411/submission/64315879
 * Time: O(\log AB)
 * Verification: https://codeforces.com/gym/102411/problem/G
 */

pl euclid(ll A, ll B) { // find (x,y) such that $Ax+By=\gcd(A,B)$, $|Ax|,|By|\le \frac{AB}{\gcd(A,B)}$
	if (!B) return {1,0};
	pl p = euclid(B,A%B); return {p.s,p.f-A/B*p.s}; }
ll invGen(ll A, ll B) { // find x in [0,B) such that Ax = 1 mod B
	pl p = euclid(A,B); assert(p.f*A+p.s*B == 1); // gcd must be 1
	return p.f+(p.f<0)*B; }
ll bet(ll A, ll B, ll L, ll R) { // min x s.t. exists y s.t. L <= A*x-B*y <= R
	A %= B; if (A == 0) return L == 0 ? 0 : -1; // try y = 0
	ll k = cdiv(L,A); if (A*k <= R) return k;
	ll x = bet(B,A,A-R%A,A-L%A); // find min x s.t. exists y s.t. -R <= Bx-Ay <= -L
	return x == -1 ? x : cdiv(B*x+L,A); // solve for y
}

/**
ll BET(ll A, ll B, ll L, ll R) {
	F0R(i,B) {
		ll prod = A*i%B;
		if (L <= prod && prod <= R) return i;
	}
	return -1;
}

int main() {
	setIO();
	FOR(i,1,101) FOR(j,1,101) F0R(L,j) FOR(R,L,j) {
		ll a = bet(i,j,L,R);
		ll b = BET(i,j,L,R);
		if (a != b) {
			dbg(i,j,L,R);
			dbg(a);
			dbg(b);
			exit(0);
		}
	}
	dbg("OK");
}
*/