/**
 * Description: arithmetic + misc polynomial operations with vectors
 * Source: Own
 * Verification: see FFT
 */

namespace VecOp {
	template<class T> vector<T> rev(vector<T> v) { reverse(all(v)); return v; }
	template<class T> vector<T> shift(vector<T> v, int x) { v.insert(v.begin(),x,0); return v; }
	template<class T> vector<T> integ(const vector<T>& v)  {
		vector<T> res(sz(v)+1);
		F0R(i,sz(v)) res[i+1] = v[i]/(i+1);
		return res;
	}
	template<class T> vector<T> dif(const vector<T>& v)	 {
		if (!sz(v)) return v;
		vector<T> res(sz(v)-1); FOR(i,1,sz(v)) res[i-1] = i*v[i];
		return res;
	}
	template<class T> vector<T>& remLead(vector<T>& v) { 
		while (sz(v) && v.back() == 0) v.pop_back();
		return v;
	}
	template<class T> T eval(const vector<T>& v, const T& x) {
		T res = 0; R0F(i,sz(v)) res = x*res+v[i];
		return res;
	}
	
	template<class T> vector<T>& operator+=(vector<T>& l, const vector<T>& r) {
		l.rsz(max(sz(l),sz(r))); F0R(i,sz(r)) l[i] += r[i]; return l;
	}
	template<class T> vector<T>& operator-=(vector<T>& l, const vector<T>& r) {
		l.rsz(max(sz(l),sz(r))); F0R(i,sz(r)) l[i] -= r[i]; return l;
	}
	template<class T> vector<T>& operator*=(vector<T>& l, const T& r) { trav(t,l) t *= r; return l;	 }
	template<class T> vector<T>& operator/=(vector<T>& l, const T& r) { trav(t,l) t /= r; return l; }

	template<class T> vector<T> operator+(vector<T> l, const vector<T>& r) { return l += r; }
	template<class T> vector<T> operator-(vector<T> l, const vector<T>& r) { return l -= r; }
	template<class T> vector<T> operator*(vector<T> l, const T& r) { return l *= r; }
	template<class T> vector<T> operator*(const T& r, const vector<T>& l) { return l*r; }
	template<class T> vector<T> operator/(vector<T> l, const T& r) { return l /= r;	 }

	template<class T> vector<T> operator*(const vector<T>& l, const vector<T>& r) {
		if (min(sz(l),sz(r)) == 0) return {};
		vector<T> x(sz(l)+sz(r)-1); F0R(i,sz(l)) F0R(j,sz(r)) x[i+j] += l[i]*r[j];
		return x;
	}
	template<class T> vector<T>& operator*=(vector<T>& l, const vector<T>& r) { return l = l*r; }
	
	template<class T> pair<vector<T>,vector<T>> qr(vector<T> a, vector<T> b) { // quotient and remainder
		assert(sz(b)); auto B = b.back(); assert(B != 0);
		B = 1/B; trav(t,b) t *= B;
		
		remLead(a); vector<T> q(max(sz(a)-sz(b)+1,0));
		while (sz(a) >= sz(b)) {
			q[sz(a)-sz(b)] = a.back();
			a -= a.back()*shift(b,sz(a)-sz(b));
			remLead(a);
		}
		
		trav(t,q) t *= B;
		return {q,a};
	}
	template<class T> vector<T> quo(const vector<T>& a, const vector<T>& b) { return qr(a,b).f; }
	template<class T> vector<T> rem(const vector<T>& a, const vector<T>& b) { return qr(a,b).s; }
	
	template<class T> vector<T> interpolate(vector<pair<T,T>> v) {
		vector<T> ret, prod = {1};
		F0R(i,sz(v)) prod *= vector<T>({-v[i].f,1});
		F0R(i,sz(v)) {
			T todiv = 1; F0R(j,sz(v)) if (i != j) todiv *= v[i].f-v[j].f;
			ret += qr(prod,{-v[i].f,1}).f*(v[i].s/todiv);
		}
		return ret;
	}
}

using namespace VecOp;