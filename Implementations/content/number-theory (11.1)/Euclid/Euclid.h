/**
 * Description: Generalized Euclidean algorithm. \texttt{euclid} and 
 	* \texttt{invGen} work for $A,B<2^{62}$. \texttt{bet} assumes 
 	* that $0\le L\le R<B$, works for $AB<2^{62}$ (same for \texttt{min\_rem})
 * Source: KACTL
 	* https://codeforces.com/gym/102411/submission/64315879
 	* also https://codeforces.com/blog/entry/90690
 * Time: O(\log AB)
 * Verification: https://codeforces.com/gym/102411/problem/G
 */

// ceil(a/b)
// ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); }
pl euclid(ll A, ll B) { // For A,B>=0, finds (x,y) s.t.
	// Ax+By=gcd(A,B), |Ax|,|By|<=AB/gcd(A,B)
	if (!B) return {1,0};
	pl p = euclid(B,A%B); return {p.s,p.f-A/B*p.s}; }
ll invGen(ll A, ll B) { // find x in [0,B) such that Ax=1 mod B
	pl p = euclid(A,B); assert(p.f*A+p.s*B == 1);
	return p.f+(p.f<0)*B; } // must have gcd(A,B)=1
ll bet(ll A, ll B, ll L, ll R) { // min x s.t.
	// exists y s.t. L <= A*x-B*y <= R
	A %= B;
	if (L == 0) return 0;
	if (A == 0) return -1;
	ll k = cdiv(L,A); if (A*k <= R) return k;
	ll x = bet(B,A,A-R%A,A-L%A); // min x s.t. exists y 
	// s.t. -R <= Bx-Ay <= -L
	return x == -1 ? x : cdiv(B*x+L,A); // solve for y
}

// find min((Ax+C)%B) for 0 <= x <= M
// aka minimize A*x-B*y+C where 0 <= x <= M, 0 <= y

ll min_rem(ll A, ll B, ll C, ll M) {
	assert(A >= 0 && B > 0 && C >= 0 && M >= 0);
	A %= B, C %= B; ckmin(M,B-1);
	if (A == 0) return C;
	if (C >= A) { // make sure C<A
		ll ad = cdiv(B-C,A);
		M -= ad; if (M < 0) return C;
		C += ad*A-B;
	}
	ll q = B/A, new_B = B%A; // new_B < A
	if (new_B == 0) return C; // B-q*A

	// now minimize A*x-new_B*y+C
	// where 0 <= x,y and x+q*y <= M, 0 <= C < new_B < A
	// q*y -> C-new_B*y
	if (C/new_B > M/q) return C-M/q*new_B;
	M -= C/new_B*q; C %= new_B; // now C < new_B

	// given y, we can compute x = ceil[((B-q*A)*y-C)/A]
	// so x+q*y = ceil((B*y-C)/A) <= M
	ll max_Y = (M*A+C)/B; // must have y <= max_Y
	ll max_X = cdiv(new_B*max_Y-C,A); // must have x <= max_X
	if (max_X*A-new_B*max_Y+C >= new_B) --max_X; 
	// now we can remove upper bound on y
	return min_rem(A,new_B,C,max_X);
}

/**
ll bet_brute(ll A, ll B, ll L, ll R) {
	F0R(i,B) {
		ll prod = A*i%B;
		if (L <= prod && prod <= R) return i;
	}
	return -1;
}

ll min_rem_brute(ll A, ll B, ll C, ll M) {
	ll ans = B;
	F0R(i,M+1) ckmin(ans,(A*i+C)%B);
	return ans;
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