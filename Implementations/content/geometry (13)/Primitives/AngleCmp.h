/**
 * Description: sorts points according to atan2
 * Verification: ?
 */

#include "Point.h"

template<class T> int half(pair<T,T> x) { return mp(x.s,x.f) > mp((T)0,(T)0); }
bool angleCmp(P a, P b) { 
	int A = half(a), B = half(b);
	return A == B ? cross(a,b) > 0 : A < B;
}
