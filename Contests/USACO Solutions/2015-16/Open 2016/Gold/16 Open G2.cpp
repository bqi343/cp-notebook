//#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<unordered_map>
#include<cmath>
#include<cstring>
#include<string>
#include<bitset>
#include<algorithm>
#include<vector>
#include <queue>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

vi a1[200001], a2[200001], per;
vector<string> ans;

int N,M, par[200001], permute[200001], numpar = 0;

int getpar(int node) {
	if (par[node] != par[par[node]]) par[node] = getpar(par[node]);
	return par[node];
}

void unite(int a, int b) {
	b = getpar(b);
	if (a == b) return;
	numpar--;
	par[b] = a;
}
int main() {
    ifstream cin ("closing.in");
    ofstream cout ("closing.out");
    cin >> N >> M; 
    FOR(i,1,N+1) par[i] = i;
    F0R(i,M) {
        pi x; cin >> x.f >> x.s;
        a1[x.f].pb(x.s);
        a1[x.s].pb(x.f);
    }
    F0R(i,N) {
    	int x; cin >> x;
    	per.pb(x);
    	permute[x] = N-i;
    }
    FOR(i,1,N+1) for (int j: a1[i]) if (permute[i]>permute[j]) a2[i].pb(j);
    reverse(per.begin(),per.end());
    for (int i: per) {
    	numpar++;
    	for (int j: a2[i]) unite(i,j);
    	if (numpar == 1) ans.pb("YES\n");
    	else ans.pb("NO\n");
    }
    reverse (ans.begin(),ans.end());
    for (auto a: ans) cout << a;
}
