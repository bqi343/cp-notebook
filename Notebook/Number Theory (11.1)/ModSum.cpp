/**
 * Description: Sums of mod'ed arithmetic progressions
 * Source: KACTL
 * Verification: ?
 */

typedef unsigned long long ul;

ul sumsq(ul to) { return (to-1)*to/2; } // sum of 0..to-1

ul divsum(ul to, ul c, ul k, ul m) { // sum_{i=0}^{to-1}floor((ki+c)/m)
	ul res = k/m*sumsq(to)+c/m*to;
	k %= m; c %= m; if (!k) return res;
	ul to2 = (to*k+c)/m;
	return res+(to-1)*to2-divsum(to2,m-1-c,m,k); 
}

ll modsum(ul to, ll c, ll k, ll m) {
	c = (c%m+m)%m, k = (k%m+m)%m;
	return to*c+k*sumsq(to)-m*divsum(to,c,k,m);
}

/*
Explanation:
$$\sum_{i=0}^{to-1}\left\lfloor \frac{ki+c}{m}\right\rfloor=\sum_{x=1}^{to}\left\lfloor \frac{k(to-x)+c}{m}\right\rfloor$$
This is equal the number of lattice points $(x,y)$ such that $x,y>0$ and
$$y\le \left\lfloor \frac{k(to-x)+c}{m}\right\rfloor\implies my+kx\le k\cdot to+c.$$
If we swap $x,y$ then the sum is equal to
\begin{align*}
\sum_{y=1}^{to2}\left\lfloor \frac{k\cdot to+c-my}{k}\right\rfloor&=\sum_{y=1}^{to2}\left\lfloor \frac{k\cdot to+c-my}{k}\right\rfloor\\
&=\sum_{y=1}^{to2}to+\left\lfloor \frac{c-my}{k}\right\rfloor\\
&=to\cdot to2-\sum_{y=1}^{to2}\left\lceil \frac{my-c}{k}\right\rceil\\
&=to\cdot to2-\sum_{y=1}^{to2}\left\lfloor \frac{my-c+k-1}{k}\right\rfloor\\
&=to\cdot to2-\sum_{y=0}^{to2-1}\left\lfloor \frac{my+m-c+k-1}{k}\right\rfloor\\
&=(to-1)\cdot to2-\sum_{y=0}^{to2-1}\left\lfloor \frac{my+m-c-1}{k}\right\rfloor
\end{align*}
as desired.
*/