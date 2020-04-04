/**
 * Description: Product of nimbers is associative, commutative, and distributive 
 	* over addition (xor). Forms finite field of size $2^{2^k}.$ Application: 
 	* Given 1D coin turning games $G_1,G_2$ $G_1\times G_2$ is the 2D coin turning 
 	* game defined as follows. If turning coins at $x_1,x_2,\ldots,x_m$ is legal 
 	* in $G_1$ and $y_1,y_2,\ldots,y_n$ is legal in $G_2$, then turning coins at 
 	* all positions $(x_i,y_j)$ is legal assuming that the coin at $(x_m,y_n)$ 
 	* goes from heads to tails. Then the grundy function $g(x,y)$ of $G_1\times G_2$ 
 	* is $g_1(x)\times g_2(y).$ 
 * Source: Andrew He
 	* also see pg 35 of https://www.fmf.uni-lj.si/~juvan/Seminar1/ferguson.pdf
 	* https://en.wikipedia.org/wiki/Nimber
 * Time: $64^2$ xors per multiplication, memorize to speed up.
 * Verification: https://codeforces.com/gym/102341/problem/L
 	* https://projecteuler.net/problem=459
 */

using ul = uint64_t; 
ul _nimProd[64][64];
ul nimProd(int i, int j) { // nim prod of 2^i, 2^j
	ul& u =_nimProd[i][j]; if (u) return u;
	if (!(i&j)) return u = 1ULL<<(i|j);
	int a = (i&j)&-(i&j); // 2^{2^k}
	return u=nimProd(i^a,j)^nimProd((i^a)|(a-1),(j^a)|(i&(a-1)));
	// 2^{2^k}*2^{2^k} = 2^{2^k}+2^{2^k-1}
} // 2^{2^i}*2^{2^j} = 2^{2^i+2^j} if i<j
struct nb { // nimber
	ul x; nb() { x = 0; }
	nb(ul _x): x(_x) {}
	explicit operator ul() { return x; }
	nb operator+(nb y) { return nb(x^y.x); }
	nb operator*(nb y) {
		ul res = 0;
		F0R(i,64)if(x>>i&1)F0R(j,64)if(y.x>>j&1)res^=nimProd(i,j);
		return nb(res);
	}
	friend nb pow(nb b, ul p) {
		nb res = 1; for (;p;p/=2,b=b*b) if (p&1) res = res*b;
		return res; } // b^{2^{2^A}-1}=1 where 2^{2^A} > b
	friend nb inv(nb b) { return pow(b,-2); }
};