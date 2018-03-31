/*
ID: bqi3431
PROG: picture
LANG: C++11 
*/

#include <fstream>
#include <vector>
#include <map>

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

int N, ans;
map<int,int> cur;
vector<pair<pi,pi>> rect;

void solve() {
    vector<pi> todo[20003];
    for (auto a: rect) {
        todo[a.s.f+10001].pb({a.f.f,1});
        todo[a.s.f+10001].pb({a.f.s,-1});
        todo[a.s.s+10001].pb({a.f.f,-1});
        todo[a.s.s+10001].pb({a.f.s,1});
    }
    F0R(i,20003) {
        for (pi a: todo[i]) {
            cur[a.f] += a.s;
            if (cur[a.f] == 0) cur.erase(a.f);
        }
        int z = 0;
        for (pi a: cur) {
            int z1 = z+a.s;
            if (z == 0 || z1 == 0) {
                ans++;
                //cout << i-10001 << "\n";
            }
            z = z1;
        }
    }
}

int main() {
    ifstream cin ("picture.in");
    ofstream cout ("picture.out");
    
	cin >> N; rect.resize(N);
	F0R(i,N) cin >> rect[i].f.f >> rect[i].s.f >> rect[i].f.s >> rect[i].s.s;
	solve();
	
	F0R(i,N) swap(rect[i].f,rect[i].s);
	solve();
	cout << ans << "\n";
}
