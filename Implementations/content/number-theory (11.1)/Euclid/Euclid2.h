/**
 * Description: finds smallest $x\ge 0$ such that $L\le Ax\pmod{P}\le R$
 * Source: https://codeforces.com/gym/102411/submission/64315879
 * Verification: https://codeforces.com/gym/102411/problem/G
 */

ll cdiv(ll x, ll y) { return (x+y-1)/y; }
ll bet(ll P, ll A, ll L, ll R) { 
	if (A == 0) return L == 0 ? 0 : -1;
	ll c = cdiv(L,A); if (A*c <= R) return c;
	ll B = P%A; // P = k*A+B, L <= A(x-Ky)-By <= R 
	// => -R <= By % A <= -L
	auto y = bet(A,B,A-R%A,A-L%A); 
	return y == -1 ? y : cdiv(L+B*y,A)+P/A*y;
}
