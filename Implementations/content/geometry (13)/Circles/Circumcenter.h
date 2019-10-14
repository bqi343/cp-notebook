/**
 * Description: circumcenter
 * Source: EGMO
 * Verification: see MEC
 */

pair<P,T> ccCenter(P a, P b, P c) { // circumcenter, radius
	b -= a; c -= a;
	P res = b*c*(conj(c)-conj(b))/(b*conj(c)-conj(b)*c);
	return {a+res,abs(res)};
}