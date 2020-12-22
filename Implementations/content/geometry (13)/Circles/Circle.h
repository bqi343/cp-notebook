/**
 * Description: represent circle as \{center,radius\}
 * Source: Own
 * Verification: see circle intersection
 */

#include "../Primitives/Point.h"

using Circ = pair<P,T>;
int in(const Circ& x, const P& y) { // -1 if inside, 0, 1
	return sgn(abs(y-x.f)-x.s); }
T arc_length(const Circ& x, P a, P b) { // precondition: a and b on x
	P d = (a-x.f)/(b-x.f); return x.s*acos(d.f); }