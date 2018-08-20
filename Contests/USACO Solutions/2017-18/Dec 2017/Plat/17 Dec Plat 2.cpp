#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;
const int MX = 1500;

int xdir[4] = {1,0,-1,0}, ydir[4] = {0,1,0,-1};

char g[MX][MX];
bool ok[MX][MX][4];
int N,M,Q;
pi A,B;

queue<vi> todo;

int hsh(pi x) {
    return M*x.f+x.s;
}

bool valid(pi x) {
    if (x.f < 0 || x.f >= N || x.s < 0 || x.s >= M) return 0;
    if (g[x.f][x.s] == '#') return 0;
    return 1;
}

void input() {
    freopen("pushabox.in","r",stdin);
    freopen("pushabox.out","w",stdout);
    cin >> N >> M >> Q;
    F0R(i,N) F0R(j,M) {
        cin >> g[i][j];
        if (g[i][j] == 'A') A = {i,j};
        if (g[i][j] == 'B') B = {i,j};
    }
}

bool visit[MX][MX];

bool dfs(pi a, pi b, pi c) {
    if (a == b) return 1;
    if (a == c || !valid(a) || visit[a.f][a.s]) return 0;
    
    visit[a.f][a.s] = 1;
    F0R(i,4) if (dfs({a.f+xdir[i],a.s+ydir[i]},b,c)) return 1;
    return 0;
}

int cor[MX][MX][4], nex = 1, ind = 1;
bool used[MX][MX][4];
int disc[MX][MX], lo[MX][MX];
vector<pair<pi,pi>> cedge;

int getdir(pi a, pi b) {
    b.f -= a.f, b.s -= a.s;
    if (b == mp(1,0)) return 0;
    if (b == mp(0,1)) return 1;
    if (b == mp(-1,0)) return 2;
    return 3;
}

void gen(pi pre, pi cur) {
    lo[cur.f][cur.s] = disc[cur.f][cur.s] = nex++;
    int child = 0;
    
    F0R(i,4) {
        pi CUR = {cur.f+xdir[i], cur.s+ydir[i]};
        if (!valid(CUR) || CUR == pre) continue;
        
        if (!used[cur.f][cur.s][i]) {
            used[cur.f][cur.s][i] = used[CUR.f][CUR.s][i^2] = 1;
            cedge.pb({cur,CUR});
        }
        
        if (disc[CUR.f][CUR.s]) {
            lo[cur.f][cur.s] = min(lo[cur.f][cur.s],disc[CUR.f][CUR.s]);
        } else {
            gen(cur,CUR);
            lo[cur.f][cur.s] = min(lo[cur.f][cur.s],lo[CUR.f][CUR.s]);
            
            if (lo[CUR.f][CUR.s] >= disc[cur.f][cur.s] && (pre != mp(-1,-1) || child > 0)) {
                ind++;
                cor[cur.f][cur.s][getdir(cur,CUR)] = ind;
                cor[CUR.f][CUR.s][getdir(CUR,cur)] = ind;
                
                while (cedge.back() != mp(cur,CUR)) {
                    auto a = cedge.back().f, b = cedge.back().s;
                    cor[a.f][a.s][getdir(a,b)] = ind;
                    cor[b.f][b.s][getdir(b,a)] = ind;
                    cedge.pop_back();
                }
                cedge.pop_back();
            }
        }
        child ++;
    }
}

bool existsnaive(pi a, pi b, pi c) {
    if (!valid(b)) return 0;
    F0R(i,N) F0R(j,M) visit[i][j] = 0;
    return dfs(a,b,c);
}

bool existspath(pi cur, int d1, int d2) {
    pi p1 = {cur.f+xdir[d1], cur.s+ydir[d1]};
    pi p2 = {cur.f+xdir[d2], cur.s+ydir[d2]};
    
    if (!valid(p1) || !valid(p2)) return 0;
    return cor[cur.f][cur.s][d1] == cor[cur.f][cur.s][d2];
}

void process(vi x) {
    F0R(i,4) if (!ok[x[0]][x[1]][i] && existspath({x[0],x[1]},x[2],i)) {
        ok[x[0]][x[1]][i] = 1;
        todo.push({x[0],x[1],i});
    }
    pi X = {x[0]-xdir[x[2]],x[1]-ydir[x[2]]};
    if (valid(X) && !ok[X.f][X.s][x[2]]) {
        ok[X.f][X.s][x[2]] = 1;
        todo.push({X.f,X.s,x[2]});
    }
}

int main() {
    input();
    F0R(i,4) if (existsnaive(A,{B.f+xdir[i],B.s+ydir[i]},B)) {
        ok[B.f][B.s][i] = 1;
        todo.push({B.f,B.s,i});
    }
    gen({-1,-1},A);
    while (sz(todo)) {
        process(todo.front());
        todo.pop();
    }
    F0R(i,Q) {
        int R,C; cin >> R >> C; R--, C--;
        if (mp(R,C) == B) {
            cout << "YES\n";
            continue;
        }
        bool f = 0;
        F0R(i,4) f |= ok[R][C][i];
        if (f) cout << "YES\n";
        else cout << "NO\n";
    }
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
