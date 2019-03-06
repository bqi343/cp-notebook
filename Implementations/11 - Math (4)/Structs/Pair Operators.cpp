/**
 * Description: modular arithmetic with pairs
 	* use for hashing
 * Source: Own
 * Verification: see hashing
 */

namespace pairOp {
    template<class A, class B> A operator+=(A& l, const B& r) { return l = l+r; }
    template<class A, class B> A operator-=(A& l, const B& r) { return l = l-r; }
    template<class A, class B> A operator*=(A& l, const B& r) { return l = l*r; }

	template<class A, class B> pair<A,B> operator+(const pair<A,B>& l, const pair<A,B>& r) { 
		return {l.f+r.f,l.s+r.s};
	}
	template<class A, class B> pair<A,B> operator-(const pair<A,B>& l, const pair<A,B>& r) { 
		return {l.f-r.f,l.s-r.s};
	}
	template<class A, class B> pair<A,B> operator*(const pair<A,B>& l, const pair<A,B>& r) { 
		return {l.f*r.f,l.s*r.s};
	}
	template<class A, class B, class C> pair<A,B> operator*(const pair<A,B>& l, const C& r) { 
		return {l.f*r,l.s*r};
	}
}

using namespace pairOp;