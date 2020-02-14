/**
 * Description: represent circle as \{center,radius\}
 * Source: Own
 * Verification: see circle intersection
 */

#include "../Primitives/Point.h"

typedef pair<P,T> circ;
bool on(circ x, P y) { return abs(y-x.f) == x.s; }
bool in(circ x, P y) {	return abs(y-x.f) <= x.s; }
T arcLen(circ x, P a, P b) {
	P d = (a-x.f)/(b-x.f); return x.s*acos(d.f); }