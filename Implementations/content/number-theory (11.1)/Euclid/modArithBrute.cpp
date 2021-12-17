ll minBetween_brute(ll A, ll B, ll L, ll R) {
	F0R(i,B) {
		ll prod = A*i%B;
		if (L <= prod && prod <= R) return i;
	}
	return -1;
}

ll minRemainder_brute(ll A, ll B, ll C, ll M) {
	ll ans = B;
	F0R(i,M+1) ckmin(ans,(A*i+C)%B);
	return ans;
}

int main() {
	setIO();
	FOR(i,1,101) FOR(j,1,101) F0R(L,j) FOR(R,L,j) {
		ll a = minBetween(i,j,L,R);
		ll b = BET(i,j,L,R);
		if (a != b) {
			dbg(i,j,L,R);
			dbg(a);
			dbg(b);
			exit(0);
		}
	}
	dbg("OK");
}