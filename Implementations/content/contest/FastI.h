/**
 * Description: fast input for chinese contests
 * Time: $\sim$300ms faster for $10^6$ long longs on CF
 * Source: 
 	* https://codeforces.com/gym/102394/submission/64154785
 	* maybe also see https://codeforces.com/blog/entry/45835 ?
 * Verification: https://codeforces.com/gym/102394/problem/G 
 */

namespace fastI {
	const int BSZ = 100000;
	char nc() { // get next char
		static char buf[BSZ], *p1 = buf, *p2 = p1;
		if (p1 == p2) {
			p1 = buf; p2 = buf+fread(buf,1,BSZ,stdin);
			if (p1 == p2) return EOF;
		}
		return *p1++;
	}
	bool blank(char ch) { return ch == ' ' || ch == '\n' 
							|| ch == '\r' || ch == '\t'; }
	template<class T> void ri(T& x) { // read int or ll
		char ch; int sgn = 1;
		while ((ch = nc()) > '9' || ch < '0') 
			if (ch == '-') sgn *= -1;
		x = ch-'0'; 
		while ((ch = nc()) >= '0' && ch <= '9') x = x*10+ch-'0';
		x *= sgn;
	}
}
using namespace fastI;