/**
 * Description: computes distance between $P$ and line $AB$
 * Source: own
 * Verification: ?
 */

#include "Point.h"

T lineDist(P p, P a, P b) { return abs(cross(p,a,b))/abs(a-b); }