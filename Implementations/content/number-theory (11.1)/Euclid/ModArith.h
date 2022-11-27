/**
 * Description: Statistics on mod'ed arithmetic series.
   * \texttt{minBetween} and \texttt{minRemainder} both assume that 
   * $0\le L\le R<B$, $AB<2^{62}$
 * Source: https://codeforces.com/gym/102411/submission/64315879
 	* also https://codeforces.com/blog/entry/90690
 * Verification: https://codeforces.com/gym/102411/problem/G
 */

ll minBetween(ll A, ll B, ll L, ll R) {
	// min x s.t. exists y s.t. L <= A*x-B*y <= R
	A %= B;
	if (L == 0) return 0;
	if (A == 0) return -1;
	ll k = cdiv(L,A); if (A*k <= R) return k;
	ll x = minBetween(B,A,A-R%A,A-L%A); // min x s.t. exists y 
	// s.t. -R <= Bx-Ay <= -L
	return x == -1 ? x : cdiv(B*x+L,A); // solve for y
}

// find min((Ax+C)%B) for 0 <= x <= M
// aka find minimum non-negative value of A*x-B*y+C
// where 0 <= x <= M, 0 <= y
ll minRemainder(ll A, ll B, ll C, ll M) {
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
	return minRemainder(A,new_B,C,max_X);
}
