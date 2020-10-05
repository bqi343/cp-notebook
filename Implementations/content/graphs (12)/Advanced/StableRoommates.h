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
 
void fin() {
	ps(-1);
	exit(0);
}
 
void rem(int x, int y) {
	active[x][y] = active[y][x] = 0;
}
 
void clip(int x) {
	while (sz(pref[x]) && !active[x][pref[x].ft]) pref[x].pop_front();
	while (sz(pref[x]) && !active[x][pref[x].bk]) pref[x].pop_back();
	if (!sz(pref[x])) fin();
}
 
void ad(int x, int y) {
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
	int y = pref[x].ft; pref[x].pop_front();
	clip(x); pref[x].push_front(y);
	return proposed[pref[x][1]];
}
 
int main() {
	setIO(); re(N);
	if (N&1) fin();
	F0R(i,N) {
		F0R(j,N) if (i != j) {
			re(A[i][j]);
			pref[i].pb(j);
			active[i][j] = 1;
		}
		sort(all(pref[i]),[&](int x, int y) { return A[i][x] < A[i][y]; });
		dbg(i,pref[i]);
	}
	F0R(i,N) propose[i] = proposed[i] = -1;
	queue<int> q; F0R(i,N) q.push(i);
	while (1) {
		while (sz(q)) {
			int x = q.ft; q.pop(); if (propose[x] != -1) continue;
			while (1) {
				clip(x);
				int y = pref[x].ft;
				if (proposed[y] != -1 && A[y][proposed[y]] < A[y][x]) {
					assert(active[y][x]); rem(x,y); assert(!active[y][x]);
					continue;
				}
				if (proposed[y] != -1) {
					q.push(proposed[y]);
					propose[proposed[y]] = -1; proposed[y] = -1;
				}
				ad(x,y);
				break;
			}
		}
		int st = -1;
		F0R(i,N) {
			clip(i); assert(proposed[i] != -1);
			assert(pref[i].bk == proposed[i]);
			if (sz(pref[i]) > 1) {
				st = i;
				break;
			}
		}
		if (st == -1) {
			F0R(i,N) assert(proposed[propose[i]] == i);
			F0R(i,N) ps(propose[i]+1);
			exit(0);
		}
		vi cyc;
		{
			int x = st, y = st;
			do {
				x = nex(x), y = nex(nex(y));
			} while (x != y);
			do {
				cyc.pb(y);
				y = nex(y);
			} while (x != y);
		}
		trav(x,cyc) {
			int y = propose[x];
			proposed[y] = -1, propose[x] = -1;
			rem(x,y); q.push(x), q.push(y);
		}
	}
}