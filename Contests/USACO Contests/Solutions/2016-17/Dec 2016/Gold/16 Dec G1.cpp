#include<set>
#include<map>
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef set<int> si;
typedef map<int,int> mii;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = b-1; i >= a; i--)
#define F0Rd(i,a) for (int i = a-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
 
const int MOD = 1000000007;
double PI = 4*atan(1);

// ifstream cin ("moocast.in");
// ofstream cout ("moocast.out");

pi points[1000];
int par[1000], N;

vector<pair<int,pi>> x;

int dist(pi a, pi b) {
	return (a.s-b.s)*(a.s-b.s)+(a.f-b.f)*(a.f-b.f);
}

int getpar(int x) {
	if (par[par[x]] == par[x]) return par[x];
	else return par[x] = getpar(par[x]);
}

void unite(int a, int b) {
	a = getpar(a), b = getpar(b);
	if (a == b) return;
	if (a>b) swap(a,b);
	par[b] = a;
	N--;
}

int main() {
	cin >> N;
	F0R(i,N) {
		cin >> points[i].f >> points[i].s;
		par[i] = i;
	}
	F0R(i,N) FOR(j,i+1,N) x.pb(mp(dist(points[i],points[j]),mp(i,j)));
	sort(x.begin(),x.end());
	F0R(i,x.size()) {
		unite(x[i].s.f,x[i].s.s);
		if (N == 1) {
			cout << x[i].f;
			break;
		}
	}
}
