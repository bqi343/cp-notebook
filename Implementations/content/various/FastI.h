/**
 * Description: Fast input for chinese contests. For output use 
	* \texttt{fwrite(buf,1,len,stdout)}.
 * Time: $\sim$300ms faster for $10^6$ long longs on CF
 * Source: 
 	* https://codeforces.com/gym/102394/submission/64154785
 	* https://codeforces.com/contest/1254/submission/65420506 (neal)
 	* https://codeforces.com/blog/entry/45835 (AI.Cash)
 * Verification: https://codeforces.com/gym/102394/problem/G 
 */

namespace FastI {
	const int BSZ = 1<<15;
	char nc() { // next char
		static char buf[BSZ]; static int pos = 0, len = 0;
		if (pos == len) {
			pos = 0; len = fread(buf,1,BSZ,stdin);
			if (pos == len) return EOF;
		}
		return buf[pos++];
	}
	template<class T> void ri(T& x) { // read int or ll
		char ch; int sgn = 1;
		while (!isdigit(ch = nc())) if (ch == '-') sgn *= -1;
		x = ch-'0'; while (isdigit(ch = nc())) x = x*10+(ch-'0');
		x *= sgn;
	}
	/// bool blank(char ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'; }
}
/// using namespace FastI;
/// int a,b; ri(a); ri(b); ps(a,b); ps(nc() == EOF);