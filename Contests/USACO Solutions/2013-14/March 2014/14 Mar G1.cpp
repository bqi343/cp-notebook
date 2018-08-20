// #include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second

ifstream cin ("lazy.in");
ofstream cout ("lazy.out");

const int M = 1000000, SZ = 1<<22;
int N,K, mx[SZ], lazy[SZ], ans = 0;
vector<pair<int,pi>> p, p1;
 
void push(int ind, int low, int high) {
	mx[ind] += lazy[ind];
    if (low != high) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind];
    lazy[ind] = 0;
}
 
void pull(int ind) {
    mx[ind] = max(mx[2*ind],mx[2*ind+1]);
}
 
void upd(int ind, int low, int high, int L, int R, int inc) {
    push(ind,low,high);
    if (high < L || R < low) return;
    if (L <= low && high <= R) {
        mx[ind] += inc;
        if (low != high) lazy[2*ind] += inc, lazy[2*ind+1] += inc;
        return;
    }
    upd(2*ind,low,(low+high)/2,L,R,inc);
    upd(2*ind+1,(low+high)/2+1,high,L,R,inc);
    pull(ind);
}

int solve() {
	F0R(i,SZ) mx[i] = lazy[i] = 0;
	vector<pair<pi,int>> temp;
	F0R(i,p.size()) {
		temp.pb({{p[i].s.f+p[i].s.s-K,1},i});
		temp.pb({{p[i].s.f+p[i].s.s+K+1,-1},i});
	}
	sort(temp.begin(),temp.end());
	for (auto a: temp) {
		int dif = p[a.s].s.s-p[a.s].s.f+M;
		if (a.f.s == 1) upd(1,0,2*M,dif,min(dif+2*K,2*M),p[a.s].f);
		else upd(1,0,2*M,dif,min(dif+2*K,2*M),-p[a.s].f);
		ans = max(ans,mx[1]);
	}
}

int main() {
	cin >> N >> K; p.resize(N);
	F0R(i,N) cin >> p[i].f >> p[i].s.f >> p[i].s.s;
	solve();
	
	for (auto a: p) p1.pb({a.f,{M-a.s.f,a.s.s}});
	p = p1;
	solve();
	
	cout << ans;
}
