#include<iostream>
// #include<fstream>

using namespace std;

#define ll long long
#define int long long
#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define INF 9223372036854775807;
ll mina[2 << 21], lazym[2 << 21], suma[2 << 21], lazys[2 << 21], bales[200010];

ll qmin(int ind, int low, int high, int L, int R) {
	if (lazym[ind]) {
		mina[ind] += lazym[ind];
		if (low != high) {
			lazym[2*ind] += lazym[ind];
			lazym[2*ind+1] += lazym[ind];
		}
		lazym[ind] = 0;
	}
	if (low > R || high < L) return INF;
	if (L <= low && high <= R) return mina[ind];
	return min(qmin(2*ind,low,(low+high)/2,L,R),qmin(2*ind+1,(low+high)/2+1,high,L,R));
}

ll qsum(int ind, int low, int high, int L, int R) {
	if (lazys[ind]) {
		suma[ind] += (high-low+1)*lazys[ind];
		if (low != high) {
			lazys[2*ind] += lazys[ind];
			lazys[2*ind+1] += lazys[ind];
		}
		lazys[ind] = 0;
	}
	if (low > R || L > high) return 0;
	if (L <= low && high <= R) return suma[ind];
	return qsum(2*ind,low,(low+high)/2,L,R)+qsum(2*ind+1,(low+high)/2+1,high,L,R);
}

void update(int ind, int low, int high, int L, int R, int inc) { // take account for minimum as well
	if (lazys[ind]) {
		suma[ind] += (high-low+1)*lazys[ind];
		if (low != high) lazys[2*ind] += lazys[ind], lazys[2*ind+1] += lazys[ind];
		lazys[ind] = 0;
	}
	if (lazym[ind]) {
		mina[ind] += lazym[ind];
		if (low != high) lazym[2*ind] += lazym[ind], lazym[2*ind+1] += lazym[ind];
		lazym[ind] = 0;
	}
	if (high < L || R < low) return;
	if (L <= low && high <= R) {
		suma[ind] += (high-low+1)*inc;
		if (low != high) lazys[2*ind] += inc, lazys[2*ind+1] += inc;
		mina[ind] += inc;
		if (low != high) lazym[2*ind] += inc, lazym[2*ind+1] += inc;
		return;
	}
	update(2*ind,low,(low+high)/2,L,R,inc);
	update(2*ind+1,(low+high)/2+1,high,L,R,inc);
	suma[ind] = suma[2*ind]+suma[2*ind+1];
	mina[ind] = min(mina[2*ind],mina[2*ind+1]);
}

void build(int ind, int low, int high) {
	if (low == high) suma[ind] = bales[low], mina[ind] = bales[low];
	else {
		build(2*ind,low,(low+high)/2);
		build(2*ind+1,(low+high)/2+1,high);
		suma[ind] = suma[2*ind]+suma[2*ind+1];
		mina[ind] = min(mina[2*ind],mina[2*ind+1]);
	}
}

int main() {
	// ifstream cin ("haybales.in");
	// ofstream cout ("haybales.out");
	ios_base::sync_with_stdio(0);
	int N, Q; cin >> N >> Q;
	FOR(i,1,N+1) cin >> bales[i];
	build(1,1,N);
	F0R(i,Q) {
		char x; cin >> x;
		int A,B,C; cin >> A >> B;
		if (x == 'M') cout << qmin(1,1,N,A,B) << endl;
		else if (x == 'P') {
			cin >> C;
			update(1,1,N,A,B,C);
		} else cout << qsum(1,1,N,A,B) << endl;
	}
	return 0;
}