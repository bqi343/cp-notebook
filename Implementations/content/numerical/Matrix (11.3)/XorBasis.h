/**
 * Description: XOR basis. If \texttt{x} is in basis \texttt{b} 
 	* then returns 0, otherwise returns adds it to 1. Equivalent
 	* to Gaussian Elimination.
 * Source: Own
 * Verification: GP of Nanjing 2020 A
 	* https://atcoder.jp/contests/agc045/tasks/agc045_a (first solve :D)
 */

ll red(vl& b, ll x) { each(t,b) ckmin(x,x^t);
	return x; }
bool add(vl& b, ll x) {
	if (!(x = red(b,x))) return 0;
	int ind=0; while (ind<sz(b)&&b[ind]>x) ind ++;
	b.insert(begin(b)+ind,x); return 1;
}

/**
ps(add(a,1)); // true
ps(add(a,2)); // true
ps(add(a,3)); // false
ps(add(a,7)); // true
ps(add(a,4)); // false
*/
