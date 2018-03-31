// #include<iostream>
#include<fstream>
#include<vector>
#include<map>

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
 
int N, ad[100001], loc[100001];
map<int,int> dist[100001], pos[100001], neg[100001];
ll a1, a2;
vector<pi> adj[100001];

void init() {
    FOR(i,1,N+1) ad[i] = 0, loc[i] = i;
}

void comb(int x1, int y1) {
    int x = loc[x1], y = loc[y1];
    for (pi a: dist[x]) 
        if (dist[y].find(-a.f-ad[x]-ad[y]) != dist[y].end())
            a1 += (ll)a.s*dist[y][-a.f-ad[x]-ad[y]];
            
    for (pi a: dist[x]) dist[y][a.f+ad[x]-ad[y]] += a.s;
    
    dist[x].clear();
    loc[x1] = y;
}

void prep(int y1) {
    int y = loc[y1];
    
    pos[y].erase(-ad[y]-1);
    a2 += pos[y][-ad[y]];
    pos[y].erase(-ad[y]);
    
    neg[y].erase(-ad[y]+1);
    a2 += neg[y][-ad[y]];
    neg[y].erase(-ad[y]);
}

void comb1(int x1, int y1) {
    int x = loc[x1], y = loc[y1];
    //if (x1 == 2 && y1 == 3) cout << a2 << " " << pos[y].size() << " " << neg[x].size() << "\n";
    /*if (x1 == 4 && y1 == 5) {
        for (auto a: pos[loc[x1]]) cout << "POS " << x1 << " " << a.f+ad[loc[x1]] << " " << a.s << "\n";
        for (auto a: neg[loc[x1]]) cout << "NEG " << x1 << " " << a.f+ad[loc[x1]] << " " << a.s << "\n";
        for (auto a: pos[loc[y1]]) cout << "POS " << y1 << " " << a.f+ad[loc[y1]] << " " << a.s << "\n";
        for (auto a: neg[loc[y1]]) cout << "NEG " << y1 << " " << a.f+ad[loc[y1]] << " " << a.s << "\n";
    }*/
    
    for (pi a: pos[x]) 
        if (neg[y].find(-a.f-ad[x]-ad[y]) != neg[y].end())
            a2 += (ll)a.s*neg[y][-a.f-ad[x]-ad[y]];
    
    for (pi a: neg[x]) {
        if (pos[y].find(-a.f-ad[x]-ad[y]) != pos[y].end())
            a2 += (ll)a.s*pos[y][-a.f-ad[x]-ad[y]];
        //if (x1 == 2 && y1 == 3) cout << "HI " << a.f << " " << a.s << "\n";
    }
    
    for (pi a: pos[x]) pos[y][a.f+ad[x]-ad[y]] += a.s;
    for (pi a: neg[x]) neg[y][a.f+ad[x]-ad[y]] += a.s;
    
    //if (x1 == 4 && y1 == 5) for (auto a: neg[loc[y1]]) cout << "NEGG " << y1 << " " << a.f+ad[loc[y1]] << " " << a.s << "\n";
    pos[x].clear();
    neg[x].clear();
    loc[x1] = y;
}

void dfs1(int par, int node) {
    pi mx = {1,node};
    dist[node][0] = 1;
    
    for (pi a: adj[node]) if (a.f != par) {
        dfs1(node,a.f);
        ad[loc[a.f]] += a.s;
        mx = max(mx,{dist[loc[a.f]].size(),a.f});
    }
    for (pi a: adj[node]) if (a.f != par && a.f != mx.s) comb(a.f,mx.s);
    if (node != mx.s) comb(node,mx.s);
}

void dfs2(int par, int node) {
    pi mx = {0,node};
    
    for (pi a: adj[node]) if (a.f != par) {
        dfs2(node,a.f);
        ad[loc[a.f]] += a.s; 
        prep(a.f);
        mx = max(mx,{pos[loc[a.f]].size()+neg[loc[a.f]].size(),a.f});
    }
    
    for (pi a: adj[node]) if (a.f != par && a.f != mx.s) {
        comb1(a.f,mx.s);
        //if (node == 2) cout << "AAA " << neg[loc[5]].size() << "\n";
    }
    loc[node] = loc[mx.s];
    /*if (node == 2) {
        cout << loc[node] << " " << neg[loc[node]].size() << "\n";
        for (auto a: neg[loc[node]]) cout << node << " " << a.f+ad[loc[node]] << " " << a.s << "\n";
    }*/
    pos[loc[node]][-ad[loc[node]]] = 1;
    neg[loc[node]][-ad[loc[node]]] = 1;
}

int main() {
    ifstream cin ("yinyang.in");
    ofstream cout ("yinyang.out");
    cin >> N;
    F0R(i,N-1) {
        int x,y,t; cin >> x >> y >> t;
        t = 2*t-1;
        adj[x].pb({y,t});
        adj[y].pb({x,t});
    }
    init();
    dfs1(0,1);
    init();
    dfs2(0,1);
    cout << a1-a2;
}
