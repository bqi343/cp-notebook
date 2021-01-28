/**
 * Description: Stable Roommates problem. Exits with -1 if no solution.
 * Time: O(N^2)
 * Source:
 	* https://en.wikipedia.org/wiki/Stable_roommates_problem
 	* probably better to check https://codeforces.com/contest/1423/submission/94783878
 * Verification: https://codeforces.com/contest/1423/problem/A
 */

/**
 * Description: Stable Roommates problem. Exists with -1 if no solution.
 * Time: O(N^3) (idk if this worst case is achievable tho) Can make O(N^2) if needed ...
 * Source:
 	* https://en.wikipedia.org/wiki/Stable_roommates_problem
 	* probably better to check https://codeforces.com/contest/1423/submission/94783878
 * Verification: https://codeforces.com/contest/1423/problem/A
 */

int N,A[1000][1000];
bool active[1000][1000];
deque<int> pref[1000];
int propose[1000], proposed[1000];
 
void fin() { // no solution
	ps(-1);
	exit(0);
}
 
void rem(int x, int y) { active[x][y] = active[y][x] = 0; }
 
void clip(int x) {
	while (sz(pref[x]) && !active[x][pref[x].ft]) pref[x].pop_front();
	while (sz(pref[x]) && !active[x][pref[x].bk]) pref[x].pop_back();
	if (!sz(pref[x])) fin();
}
 
void ad(int x, int y) {
	assert(x != y && propose[x] == -1 && proposed[y] == -1);
	propose[x] = y, proposed[y] = x;
	while (1) {
		clip(y);
		if (pref[y].bk != x) rem(y,pref[y].bk);
		else break;
	}
	assert(pref[y].bk == x);
}
 
int nex(int x) {
	assert(sz(pref[x]) > 1);
	clip(x); int y = pref[x].ft; pref[x].pop_front();
	clip(x); pref[x].push_front(y);
	return proposed[pref[x][1]];
}
 
int main() {
	setIO(); re(N);
	if (N&1) fin();
	F0R(i,N) {
		F0R(j,N) if (i != j) {
			re(A[i][j]);
			pref[i].pb(j); active[i][j] = 1;
		}
		sort(all(pref[i]),[&](int x, int y) { return A[i][x] < A[i][y]; });
	}
	F0R(i,N) propose[i] = proposed[i] = -1;
	queue<int> q; F0R(i,N) q.push(i);
	while (sz(q)) {
		int x = q.ft; q.pop(); assert(propose[x] == -1);
		while (1) {
			clip(x); int y = pref[x].ft, X = proposed[y];
			if (X != -1 && A[y][X] < A[y][x]) { rem(x,y); continue; }
			if (X != -1) propose[X] = -1, proposed[y] = -1, q.push(X);
			ad(x,y); break;
		}
	}
	F0R(i,N) assert(propose[i] != -1);
	int cur = 0;
	while (1) { // rotation elimination
		for (;cur<N;++cur) {
			clip(cur); assert(proposed[cur] != -1 && pref[cur].bk == proposed[cur]);
			if (sz(pref[cur]) > 1) break;
		}
		F0R(i,N) {
			vi tmp;
			each(j,pref[i]) if (active[i][j]) tmp.pb(j);
		}
		if (cur == N) {
			F0R(i,N) {
				assert(proposed[propose[i]] == i);
				ps(propose[i]+1);
			}
			exit(0);
		}
		vi cyc, CYC;
		{
			int x = cur, y = cur;
			do { x = nex(x), y = nex(nex(y)); } while (x != y);
			do { cyc.pb(y); y = nex(y); } while (x != y);
		}
		each(x,cyc) { // if there exists a solution,
			// then there also exists a solution after deleting these edges
			int y = propose[x]; CYC.pb(y); assert(y != -1);
			propose[x] = -1, proposed[y] = -1, rem(x,y);
		}
		F0R(i,sz(cyc)) ad(cyc[i],CYC[(i+1)%sz(cyc)]);
	}
}
