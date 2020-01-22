#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int MOD = 1e9+7; // 998244353; // = (119<<23)+1
const int MX = 5e4+5; 

void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
 
struct mi {
	int v; explicit operator int() const { return v; }
	mi(ll _v) : v(_v%MOD) { v += (v<0)*MOD; }
	mi() : mi(0) {}
};
mi operator+(mi a, mi b) { return mi(a.v+b.v); }
mi operator-(mi a, mi b) { return mi(a.v-b.v); }
mi operator*(mi a, mi b) { return mi((ll)a.v*b.v); }
typedef array<array<mi,20>,20> T;
 
int N,K,Q;
vector<int> A;
array<mi,20> sto[MX], isto[MX];
mi i2 = (MOD+1)/2;
 
void prin(T& t) { // print a matrix for debug purposes
	for (int i = 0; i < K; ++i) {
		for (int j = 0; j < K; ++j) 
			cout << t[i][j].v << ' ';
		cout << "\n";
	}
	cout << "-------\n";
}
 
int main() {
	setIO("nondec");
	cin >> N >> K; A.resize(N); 
	for (int i = 0; i < N; ++i) cin >> A[i];
	T STO, ISTO;
	for (int i = 0; i < K; ++i) 
		STO[i][i] = ISTO[i][i] = 1;
	for (int i = 0; i <= N; ++i) {
		for (int j = 0; j < K; ++j) 
			for (int k = j; k < K; ++k) 
				sto[i][j] = sto[i][j]+STO[j][k];
		for (int k = 0; k < K; ++k) 
			isto[i][k] = ISTO[0][k];
		if (i == N) break;
		int x = A[i]-1;
		// STO goes from pre[i] to pre[i+1]
		// set STO = STO*M_{A[i]}
		for (int j = 0; j <= x; ++j) 
			for (int k = x; k >= j; --k) 
				STO[j][x] = STO[j][x]+STO[j][k];
		// ISTO goes from ipre[i] to ipre[i+1]
		// set ISTO=M_{A[i]}^{-1}*ISTO
		for (int j = 0; j < x; ++j) 
			for (int k = x; k < K; ++k)
				ISTO[j][k] = ISTO[j][k]-i2*ISTO[x][k];
		for (int k = x; k < K; ++k) 
			ISTO[x][k] = ISTO[x][k]*i2;
	}
	cin >> Q;
	for (int i = 0; i < Q; ++i) {
		int L,R; cin >> L >> R;
		mi ans = 0; 
		for (int j = 0; j < K; ++j) 
			ans = ans+isto[L-1][j]*sto[R][j];
		cout << ans.v << "\n";
	}
}