/**
 * Description: lexiographically least matching wrt left vertices
 * Time: $\log |L|$ times sum of complexities of \texttt{gen}, \texttt{maxMatch}
 * Source: https://codeforces.com/blog/entry/76187?#comment-611056
 * Usage: solve(L,R,sz(L))
 * Verification: GP of Moscow 2020 I
 */

vpi maxMatch(vi L, vi R); // return pairs in max matching
pair<vi,vi> gen(vi L, vi R); // return {Lp,Rp}, vertices on 
// left/right that can be reached by alternating path from 
// unmatched node on left after finding max matching

vpi res; // stores answer
void solve(vi L, vi R, int x) { // first |L|-x elements of L
	if (x <= 1) { // are in matching, easy if x <= 1
		vpi v = maxMatch(L,R);
		if (sz(v) != sz(L)) L.pop_back(), v = maxMatch(L,R);
		assert(sz(v) == sz(L)); 
		res.insert(end(res),all(v)); return;
	}
	vi Lp,Rp; tie(Lp,Rp)=gen(L,R); vi Lm=sub(L,Lp),Rm=sub(R,Rp);
	// Lp U Rm is max indep set, Lm U Rp is min vertex cover
	// Lp and Rm independent, edges from Lm to Rp can be ignored
	vpi v = maxMatch(Lm,Rm); assert(sz(v) == sz(Lm)); 
	res.insert(end(res),all(v));
	vi L2(all(L)-x/2); vi Lp2,Rp2; tie(Lp2,Rp2) = gen(L2,R);
	int cnt = 0; each(t,Lp2) cnt += t >= L[sz(L)-x];
	solve(Lp2,Rp2,cnt); // Rp2 covered by best matching
	vi LL = sub(Lp,Lp2), RR = sub(Rp,Rp2); // those in Lp but not 
	// Lp2 that are < L[sz(L)-x/2] must be in answer, not cnt
	cnt = 0; each(t,LL) cnt += t >= L[sz(L)-x/2];
	solve(LL,RR,cnt); // do rest
} // x reduced by factor of at least two
