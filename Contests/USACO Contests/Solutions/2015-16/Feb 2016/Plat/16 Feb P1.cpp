#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
 
#define pb push_back
#define pi pair <int, int>
#define vi vector<int>
#define f first
#define s second

#define F0R(i, a) for (int i=0; i<a; i++)

int N,M = 999999, code[1000000], t[2][1 << 18],c1;
vi ya;
vector<pi> cows;

void insert(int ind, int low, int high, int y, int inc, bool z) {
	if (low > y || high < y) return;
	if (low == high) {
		t[z][ind] += inc;
		return;
	}
	insert(2*ind,low,(low+high)/2,y,inc,z);
	insert(2*ind+1,(low+high)/2+1,high,y,inc,z);
 	t[z][ind] = t[z][2*ind] + t[z][2*ind+1];
}

int query(int ind, int low, int high, int L, int R, bool z) {
	if (low > R || high < L) return 0;
	if (L <= low && high <= R) return t[z][ind];
	return query(2*ind,low,(low+high)/2,L,R,z)+query(2*ind+1,(low+high)/2+1,high,L,R,z);
}

int compute(int v) {
	int a = query(1,1,c1,1,v,1), b = query(1,1,c1,1,v,0);
	return max(max(a,t[1][1]-a),max(b,t[0][1]-b));
}

int solve(int low, int high) {
	if (high-low<2) return min(compute(low),compute(high));
	int s = (low+high)/2;
	int a = query(1,1,c1,1,s,0), b = query(1,1,c1,1,s,1);
	int c = t[0][1]-a, d = t[1][1]-b;
	if (a>c) {
		if (b>d) return solve(low,s);
		else {
			if (a>d) return solve(low,s);
			else return solve(s,high);
		}
	} else {
		if (b>d) {
			if (b>c) solve(low,s);
			else return solve(s,high);
		} else return solve(s,high);
	}
}

int main() {
	ifstream cin ("balancing.in"); ofstream cout ("balancing.out");
	ios_base::sync_with_stdio(0); cin >> N;
	F0R(i,N) {
		pi k; cin >> k.f >> k.s;
		ya.pb(k.s), cows.pb(k);
	}
	sort(cows.begin(),cows.end()); sort(ya.begin(), ya.end());
	ya.erase( unique(ya.begin(), ya.end() ), ya.end() );
	F0R(i,ya.size()) c1++, code[ya[i]] = c1;
	F0R(i,N) insert(1,1,c1,code[cows[i].s],1,1);
	M = min(M,solve(0,c1));
	int i = 0;
	while (i<N) {
		int curx = cows[i].f;
		while (cows[i].f == curx && i < N) {
			insert(1,1,c1,code[cows[i].s],1,0);
			insert(1,1,c1,code[cows[i].s],-1,1);
			i++;
		}
		M = min(M,solve(0,c1));
	}
	cout << M;
}
