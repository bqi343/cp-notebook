#include <bits/stdc++.h>
 
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

int N, sub[40001], ans=0;
char n[40001];
bool done[40001];
vi adj[40001];
pi bes;
map<int,int> t[2];
vector<pair<char,pi>> todo; // store depth, max depth

void dfs1(int p, int z) {
    sub[z] = 1;
    for (int i: adj[z]) if (i != p && !done[i]) {
        dfs1(z,i);
        sub[z] += sub[i];
    }
}

void dfs2(int x, int p, int z) {
    int cur = sub[x]-sub[z];
    for (int i: adj[z]) if (i != p && !done[i]) {
        dfs2(x,z,i);
        cur = max(cur,sub[i]);
    }
    bes = min(bes,{cur,z});
}

void dfs3(int p, int z, int mn, int mx, int cur) {
    cur += (n[z] == '(' ? 1 : -1);
    
    mn = min(mn,cur), mx = max(mx,cur);
    for (int i: adj[z]) if (i != p && !done[i]) dfs3(z,i,mn,mx,cur);
    
    if (cur == mn) todo.pb({')',{cur,mx-mn}});
    else if (cur == mx) todo.pb({'(',{cur,mx-mn}}); 
}

void test(int x) {
    F0R(i,2) t[i].clear();
    t[0][0] = t[1][0] = 0;
    
    for (int i: adj[x]) if (!done[i]) {
        dfs3(x,i,0,0,0);
        for (pair<char,pi> a: todo) 
            if (a.f == '(') {
                int z = a.s.f+(n[x] == '(' ? 1 : -1);
                if (t[1].count(-z)) ans = max(ans,max(a.s.s,t[1][-z]));
            } else {
                int z = a.s.f+(n[x] == '(' ? 1 : -1);
                if (t[0].count(-z)) ans = max(ans,max(a.s.s,t[0][-z]));
            }
            
        for (pair<char,pi> a: todo) 
            if (a.f == '(') t[0][a.s.f] = max(t[0][a.s.f],a.s.s);
            else t[1][a.s.f] = max(t[1][a.s.f],a.s.s);
            
        todo.clear();
    }
}

int get_centroid(int x) {
    dfs1(0,x); 
    bes = {MOD,0};
    dfs2(x,0,x);
    return bes.s;
}

void solve(int x) {
    x = get_centroid(x);  
    test(x); done[x] = 1;
    for (int i: adj[x]) if (!done[i]) solve(i);
}

int main() {
    freopen("btree.in","r",stdin);
    freopen("btree.out","w",stdout);
    
    cin >> N;
    FOR(i,2,N+1) {
        int x; cin >> x;
        adj[i].pb(x);
        adj[x].pb(i);
    }
    FOR(i,1,N+1) cin >> n[i];
    solve(1);
    cout << ans;
}
