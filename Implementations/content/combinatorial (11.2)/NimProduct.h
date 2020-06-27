/**
 * Description: Product of nimbers is associative, commutative, and distributive 
 	* over addition (xor). Forms finite field of size $2^{2^k}.$ 
 	* Defined by $ab=\text{mex}(\{a'b+ab'+a'b':a'<a,b'<b\}).$ Application: 
 	* Given 1D coin turning games $G_1,G_2$ $G_1\times G_2$ is the 2D coin turning 
 	* game defined as follows. If turning coins at $x_1,x_2,\ldots,x_m$ is legal 
 	* in $G_1$ and $y_1,y_2,\ldots,y_n$ is legal in $G_2$, then turning coins at 
 	* all positions $(x_i,y_j)$ is legal assuming that the coin at $(x_m,y_n)$ 
 	* goes from heads to tails. Then the grundy function $g(x,y)$ of $G_1\times G_2$ 
 	* is $g_1(x)\times g_2(y).$ 
 * Source: Andrew He
 	* also see pg 35 of https://www.fmf.uni-lj.si/~juvan/Seminar1/ferguson.pdf
 	* https://en.wikipedia.org/wiki/Nimber
 	* https://judge.yosupo.jp/submission/6485
 * Time: $64^2$ xors per multiplication, memorize to speed up.
 * Verification: https://codeforces.com/gym/102341/problem/L
 	* https://projecteuler.net/problem=459
 	* https://judge.yosupo.jp/problem/nim_product_64
 */

using ul = uint64_t; 

struct Precalc {
	ul tmp[64][64], y[8][8][256];
	unsigned char x[256][256];
	Precalc() { // small nim products, all < 256
		F0R(i,256) F0R(j,256) x[i][j] = mult<8>(i,j); 
		F0R(i,8) F0R(j,i+1) F0R(k,256)
			y[i][j][k] = mult<64>(prod2(8*i,8*j),k);
	}
	ul prod2(int i, int j) { // nim prod of 2^i, 2^j
		ul& u = tmp[i][j]; if (u) return u;
		if (!(i&j)) return u = 1ULL<<(i|j);
		int a = (i&j)&-(i&j); // a=2^k, consider 2^{2^k}
		return u=prod2(i^a,j)^prod2((i^a)|(a-1),(j^a)|(i&(a-1)));
		// 2^{2^k}*2^{2^k} = 2^{2^k}+2^{2^k-1}
	} // 2^{2^i}*2^{2^j} = 2^{2^i+2^j} if i<j
	template<int L> ul mult(ul a, ul b) {
		ul c = 0; F0R(i,L) if (a>>i&1) 
			F0R(j,L) if (b>>j&1) c ^= prod2(i,j);
		return c;
	}
	// 2^{8*i}*(a>>(8*i)&255) * 2^{8*j}*(b>>(8*j)&255)
	// -> (2^{8*i}*2^{8*j})*((a>>(8*i)&255)*(b>>(8*j)&255))
	ul multFast(ul a, ul b) const { // faster nim product
		ul res = 0; auto f = [](ul c, int d) { return c>>(8*d)&255; };
		F0R(i,8) {
			F0R(j,i) res ^= y[i][j][x[f(a,i)][f(b,j)]^x[f(a,j)][f(b,i)]];
			res ^= y[i][i][x[f(a,i)][f(b,i)]];
		}
		return res;
	}
};
const Precalc P;

struct nb { // nimber
	ul x; nb() { x = 0; }
	nb(ul _x): x(_x) {}
	explicit operator ul() { return x; }
	nb operator+(nb y) { return nb(x^y.x); }
	nb operator*(nb y) { return nb(P.multFast(x,y.x)); }
	friend nb pow(nb b, ul p) {
		nb res = 1; for (;p;p/=2,b=b*b) if (p&1) res = res*b;
		return res; } // b^{2^{2^A}-1}=1 where 2^{2^A} > b
	friend nb inv(nb b) { return pow(b,-2); }
};