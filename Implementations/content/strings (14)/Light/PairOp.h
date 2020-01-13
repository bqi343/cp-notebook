/**
 * Description: operations with pairs
 * Source: own
 * Verification: see HashRange
 */

namespace pairOp {
	template<class A, class B> pair<A,B> operator+(const pair<A,B>& l, const pair<A,B>& r) { return {l.f+r.f,l.s+r.s}; }
	template<class A, class B> pair<A,B> operator-(const pair<A,B>& l, const pair<A,B>& r) { return {l.f-r.f,l.s-r.s}; }
	template<class A, class B> pair<A,B> operator*(const pair<A,B>& l, const pair<A,B>& r) { return {l.f*r.f,l.s*r.s}; }
	template<class A, class B, class C> pair<A,B> operator*(const pair<A,B>& l, const C& r) { return {l.f*r,l.s*r}; }
	template<class A, class B, class C> pair<A,B> operator*(const C& r, const pair<A,B>& l) { return l*r; }
	template<class A, class B, class C> pair<A,B> operator/(const pair<A,B>& l, const C& r) { return {l.f/r,l.s/r}; }
	
	template<class A, class B> pair<A,B>& operator+=(pair<A,B>& l, const pair<A,B>& r) { return l = l+r; }
	template<class A, class B> pair<A,B>& operator-=(pair<A,B>& l, const pair<A,B>& r) { return l = l-r; }
	template<class A, class B> pair<A,B>& operator*=(pair<A,B>& l, const pair<A,B>& r) { return l = l*r; }
	template<class A, class B, class C> pair<A,B>& operator*=(pair<A,B>& l, const C& r) { return l = {l.f*r,l.s*r}; }
	template<class A, class B, class C> pair<A,B>& operator/=(pair<A,B>& l, const C& r) { return l = {l.f/r,l.s/r}; }
}

using namespace pairOp;
