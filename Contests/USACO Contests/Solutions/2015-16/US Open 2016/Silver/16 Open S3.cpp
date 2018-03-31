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

set<int> adj[3001];

int N,M,visit[3001];
vi permute;

void rem(int vert) {
    for (int a: adj[vert]) adj[a].erase(vert);
}

int get(int vert) {
    queue<int> todo;
    todo.push(vert);
    F0R(i,3001) visit[i] = 0;
    int cur = 0;
    while (todo.size()) {
        int a = todo.front();
        todo.pop();
        visit[a] = 1; cur++;
        for (int b: adj[a]) if (visit[b] == 0) {
            visit[b] = -1;
            todo.push(b);
        }
    }
    return cur;
}

int main() {
    ifstream cin ("closing.in");
    ofstream cout ("closing.out");
    cin >> N >> M; permute.resize(N);
    F0R(i,M) {
        pi x; cin >> x.f >> x.s;
        adj[x.f].insert(x.s);
        adj[x.s].insert(x.f);
    }
    F0R(i,N) cin >> permute[i];
    F0R(i,N) {
        if (get(permute[N-1]) == N-i) cout << "YES\n";
        else cout << "NO\n";
        rem(permute[i]);
    }
}
