/**
 * Description: returns \{circumcenter,circumradius\}
 * Source: EGMO
 * Verification: see MEC
 */

#include "Circle.h"

circ ccCenter(P a, P b, P c) { 
	b -= a; c -= a;
	P res = b*c*(conj(c)-conj(b))/(b*conj(c)-conj(b)*c);
	return {a+res,abs(res)};
}
