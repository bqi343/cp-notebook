/**
 * Description: Unused. Convert permutation of $\{0,1,...,N-1\}$ to integer in $[0,N!)$ and back.
 * Source: http://antoinecomeau.blogspot.com/2014/07/mapping-between-permutations-and.html
 * Verification: ?
 * Time: O(N)
 * Usage: assert(encode(decode(5,37)) == 37);
 */

vi decode(int n, int a) {
	vi el(n), b; iota(all(el),0);
	F0R(i,n) {
		int z = a%sz(el);
		b.pb(el[z]); a /= sz(el);
		swap(el[z],el.bk); el.pop_back();
	}
	return b;
}
int encode(vi b) {
	int n = sz(b), a = 0, mul = 1;
	vi pos(n); iota(all(pos),0); vi el = pos;
	F0R(i,n) {
		int z = pos[b[i]]; a += mul*z; mul *= sz(el);
		swap(pos[el[z]],pos[el.bk]); 
		swap(el[z],el.bk); el.pop_back();
	}
	return a;
}
