#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;

int p[100001], pp[100001], c[100001][2], sum[100001];

int getDir(int x, int y) {
    return c[x][0] == y ? 0 : 1;
}

void setLink(int x, int y, int d) {
    c[x][d] = y, p[y] = x;
}

void rotate(int y, int d) {
    int x = c[y][d], z = p[y];
    setLink(y,c[x][d^1],d);
    setLink(x,y,d^1);
    setLink(z,x,getDir(z,y));
    
    sum[x] = sum[y];
    sum[y] = sum[c[y][0]]+sum[c[y][1]]+1;
    pp[x] = pp[y]; pp[y] = 0;
}

void splay(int x) {
    while (p[x]) {
        int y = p[x], z = p[y];
        int dy = getDir(y,x), dz = getDir(z,y);
        if (!z) rotate(y,dy);
        else if (dy == dz) rotate(z,dz), rotate(y,dy);
        else rotate(y,dy), rotate(z,dz);
    }
}

void dis(int v, int d) { // fix
    p[c[v][d]] = 0, pp[c[v][d]] = v;
    sum[v] -= sum[c[v][d]];
    c[v][d] = 0; 
}

void con(int v, int d) { // fix
    c[pp[v]][d] = v;
    sum[pp[v]] += sum[v];
    p[v] = pp[v], pp[v] = 0;
}

void access(int v) { 
    // v is brought to the root of auxiliary tree
    // modify preferred paths
    
    splay(v);
    dis(v,1);
    
    while (pp[v]) {
        int w = pp[v]; splay(w);
        dis(w,1), con(v,1);
        splay(v);
    }
}

int find_root(int v) {
    access(v);
    while (c[v][0]) v = c[v][0];
    access(v);
    return v;
}

int find_depth(int v) {
    access(v);
    return sum[c[v][0]];
}

void cut(int v) { 
    // cut link between v and par[v]
    access(v);
    pp[c[v][0]] = p[c[v][0]] = 0; // fix
    sum[v] -= sum[c[v][0]];
    c[v][0] = 0;
}

void link(int v, int w) { 
    // v, which is root of another tree, is now child of w
    access(v), access(w);
    pp[w] = v; con(w,0);
}

int anc(int v, int num) {
    if (find_depth(v) < num) return 0;
    access(v);
    v = c[v][0];
    
    while (1) {
        if (sum[c[v][1]] >= num) v = c[v][1];
        else if (sum[c[v][1]]+1 == num) return v;
        else num -= (sum[c[v][1]]+1), v = c[v][0];
    }
}

int main() {
    FOR(i,1,100001) sum[i] = 1;
    
    link(2,1);
    link(3,1);
    link(4,1);
    link(5,4);
    link(10,4);
    link(7,6);
    link(8,7);
    link(9,8);
    
    FOR(i,1,11) cout << i << " " << find_root(i) << " " << find_depth(i) << " " << anc(i,2) << "\n";
    cout << "\n";
    
    cut(4);
    link(4,8);
    
    FOR(i,1,11) cout << i << " " << find_root(i) << " " << find_depth(i) << " " << anc(i,2) << "\n";
}
