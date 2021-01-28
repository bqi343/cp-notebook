/**
 * Description: Reeds-Sloane, generalizes Berlekamp-Massey to non-prime moduli
 * Source:
   * https://github.com/zimpha/algorithmic-library/blob/master/cpp/mathematics/linear-recurrence.cc
   * http://neilsloane.com/doc/Me111.pdf
 * Verification:
   * https://www.spoj.com/problems/FINDLR/
 */

#include "CRT.h"

struct LinRec2 {
	vl s, C; ll mod;
	void extend(vl& a, ll b) { if (sz(a) < b) a.rsz(b); }
	vl primePower(ll p, int e) { // generalization of BM
		vector<vl> a(e), an(e), ao(e);
		vl t(e), u(e), r(e), to(e,1), uo(e), pw(e+1);
		pw[0] = 1; FOR(i,1,e+1) pw[i] = pw[i-1]*p;
		ll mod = pw[e];
		auto mul = [mod](ll x, ll y) { return x*y%mod; };
		auto AD = [mod](ll& x, ll y) { x += y; if (x >= mod) x -= mod; };
		auto SUB = [mod](ll& x, ll y) { x -= y; if (x < 0) x += mod; };
		F0R(o,e) {
			a[o] = an[o] = {pw[o]}; t[o] = mul(s[0],pw[o]);
			if (!t[o]) t[o] = 1, u[o] = e;
			else for (an[o].pb(0); t[o]%p == 0; t[o] /= p, ++u[o]);
		}
		FOR(k,1,sz(s)) { // add terms one by one
			F0R(g,e) if (sz(an[g]) > sz(a[g])) { 
				int ind = e-1-u[g]; r[g] = k-1;
				ao[g] = a[ind]; to[g] = t[ind]; uo[g] = u[ind];
			} // recurrence was extended after term k-1 was added
			a = an;
			F0R(o,e) {
				ll d = 0; F0R(i,sz(a[o])) AD(d,mul(a[o][i],s[k-i])); 
				if (d == 0) { t[o] = 1, u[o] = e; continue; } // do nothing
				for (u[o] = 0, t[o] = d; t[o]%p == 0; t[o] /= p, ++u[o]);
				int g = e-1-u[o];
				if (sz(a[g]) == 1) extend(an[o],k+2); // just make it 1,0,0,...
				else { // subtract multiple of previous to get to 0
					ll coef = mul(mul(t[o],invGen(to[g],mod)),pw[u[o]-uo[g]]);
					int m = k-r[g]; extend(an[o],sz(ao[g])+m);
					F0R(i,sz(ao[g])) SUB(an[o][i+m],mul(coef,ao[g][i]));
				}
			}
		}
		return an[0];
	}
	void RS() {
		vector<pair<ll,int>> fac; vl mul;
		for (ll i = 2; i*i <= mod; ++i) if (mod%i == 0) {
			int cnt = 0; ll pw = 1;  // naive factorization
			while (mod%i == 0) mod /= i, ++cnt, pw *= i;
			fac.pb({i,cnt}); mul.pb(pw);
		}
		if (mod > 1) fac.pb({mod,1}), mul.pb(mod);
		vector<vl> as; int n = 0;
		each(x,fac) {
			auto y = primePower(x.f,x.s);
			as.pb(y); ckmax(n,sz(y));
		}
		C.rsz(n);
		F0R(i,n) {
			pl p = {0,1};
			F0R(j,sz(as)) {
				pl tmp = {i < sz(as[j]) ? as[j][i] : 0,mul[j]};
				p = CRT(p,tmp);
			}
			C[i] = p.f;
		}
	}
	void init(vl _s, ll _mod) {
		s = _s; mod = _mod; RS();
	} // can use C in same way as Berlekamp-Massey
};

int main() {
	LinRec2 L;
	L.init({0,0,0,1,1,2,3,5,8,13},20);
	ps(L.C); // {1, 19, 19, 0, 0}
}
