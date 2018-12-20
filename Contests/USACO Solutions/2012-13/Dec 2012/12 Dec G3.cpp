// #include<iostream>
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

using namespace std;
//using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

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

const int MOD = 1000000007;
double PI = 4*atan(1);

ifstream cin ("runaway.in");
ofstream cout ("runaway.out");

ll N,L, ad[200001];
int loc[200001], ans[200001];
multiset<ll> val[200001];
map<int,ll> child[200001];

void dfs(int node) {
    int mx = node;
    for (auto a: child[node]) {
        dfs(a.f);
        ad[loc[a.f]] += child[node][a.f];
        if (val[loc[a.f]].size() > val[loc[mx]].size()) mx = a.f;
    }
    loc[node] = loc[mx];
    for (auto a: child[node]) if (a.f != mx)
        for (ll i: val[loc[a.f]]) val[loc[node]].insert(i+ad[loc[a.f]]-ad[loc[node]]);
    
    val[loc[node]].insert(-ad[loc[node]]);
    while ((*prev(val[loc[node]].end()))+ad[loc[node]] > L)
        val[loc[node]].erase(prev(val[loc[node]].end()));
    
    ans[node] = val[loc[node]].size();
}

void init() {
    cin >> N >> L;
    FOR(i,1,N+1) loc[i] = i;
    FOR(i,2,N+1) {
        ll p,l; cin >> p >> l;
        child[p][i] = l;
    }
}

int main() {
    init();
    dfs(1);
    FOR(i,1,N+1) cout << ans[i] << "\n";
}
