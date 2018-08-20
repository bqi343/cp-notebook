// #include<iostream>
#include<fstream>
#include<set>
#include<unordered_map>
#include<algorithm>
#include<vector>

using namespace std;
 
typedef pair<int, int> pi;
typedef multiset<int> ms;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define pb push_back
#define f first
#define s second

ifstream cin ("grass.in");
ofstream cout ("grass.out");

ms mins;
bool ok = 1;
vector<pair<int,pi>> edge;
int N,M,K,Q;

struct {
    int par, parlen, color, comp;
    ms best;
    unordered_map<int,ms> child;
    vector<pi> adj;
    
    int get() {
        if (best.size()) return *best.begin();
        return 1000000000;
    }
    int changecolor(int y) {
        mins.erase(mins.find(get()));
        if (child.find(color) != child.end()) best.insert(*child[color].begin());
        if (child.find(y) != child.end()) best.erase(best.find(*child[y].begin()));
        mins.insert(get());
        color = y;
    }
    void ins(int len, int c) {
        if (color != c) {
            mins.erase(mins.find(get()));
            if (child[c].size()) best.erase(best.find(*child[c].begin()));
        }
        child[c].insert(len);
        if (color != c) {
            best.insert(*child[c].begin());
            mins.insert(get());
        }
    }
    void change (int len, int c1, int c2) {
        mins.erase(mins.find(get()));
        if (c1 != color) best.erase(best.find(*child[c1].begin()));
        if (c2 != color) if (child.find(c2) != child.end()) best.erase(best.find(*child[c2].begin()));
        
        child[c1].erase(child[c1].find(len));
        if (child[c1].size() == 0) child.erase(c1);
        child[c2].insert(len);
        
        if (c1 != color) if (child.find(c1) != child.end()) best.insert(*child[c1].begin());
        if (c2 != color) best.insert(*child[c2].begin());
        mins.insert(get());
    }
} node[200001];

int getcomp(int cur) {
    if (node[node[cur].comp].comp != node[cur].comp) 
        node[cur].comp = getcomp(node[cur].comp);
    return node[cur].comp;
}

void unite(int n1, int n2) {
    n1 = getcomp(n1), n2 = getcomp(n2);
    node[n2].comp = n1;
} 

void input() {
    cin >> N >> M >> K >> Q;
    F0R(i,M) {
        int A,B,L; cin >> A >> B >> L;
        edge.pb({L,{A,B}});
    }
    sort(edge.begin(),edge.end());
    FOR(i,1,N+1) node[i].comp = i;
    F0R(j,edge.size()) {
        auto a = edge[j];
        if (getcomp(a.s.f) != getcomp(a.s.s)) {
            unite(a.s.f,a.s.s);
            node[a.s.f].adj.pb({a.s.s,a.f});
            node[a.s.s].adj.pb({a.s.f,a.f});
        }
    }
    FOR(i,1,N+1) {
        cin >> node[i].color;
        mins.insert(1000000000);
    }
}

void dfs(int p, int cur) {
    if (node[cur].adj.size() > 10) ok = 0;
    for (auto i: node[cur].adj) if (i.f != p) {
        node[i.f].par = cur, node[i.f].parlen = i.s;
        node[cur].ins(i.s,node[i.f].color);
        dfs(cur,i.f);
    }
}

void naive() {
    ms dist;
    
    FOR(i,1,N+1) for (pi a: node[i].adj) 
        if (i < a.f && node[i].color != node[a.f].color) 
            dist.insert(a.s);
            
    F0R(i,Q) {
        int A,B; cin >> A >> B;
        if (node[A].color != B) {
            for (auto a: node[A].adj) {
                if (node[a.f].color == node[A].color) dist.insert(a.s);
                else if (node[a.f].color == B) dist.erase(dist.find(a.s));
            }
            node[A].color = B;
        }
        cout << *dist.begin() << "\n";
    }
}

int main() { 
    input();
    dfs(0,1);
    if (ok) naive();
    else {
        F0R(i,Q) {
            int A,B; cin >> A >> B;
            if (A != 1) node[node[A].par].change(node[A].parlen,node[A].color,B);
            node[A].changecolor(B);
            cout << *mins.begin() << "\n";
        }
    }
}
