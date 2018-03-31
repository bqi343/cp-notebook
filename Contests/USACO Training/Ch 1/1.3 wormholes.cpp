#include <fstream>
#include <vector>
#include<map>
using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back
#define pi pair <int, int>
#define vi vector<int>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)

#define f first
#define s second

const int MOD = 1000000007;

int n, nex[13], ans=0;
vi all;
map<int,vi> k;

void d(vi used, int ind) {
    if (ind == n) {
        // test if there is a cycle
        vi all1 = all;
        int pa[13];
        F0R(i,n/2) {
            int y = all1[0], z = all1[used[i]+1];
            pa[y] = z, pa[z] = y;
            all1.erase(all1.begin());
            all1.erase(all1.begin()+used[i]);
        }
        int visit[13];
        FOR(i,1,n+1) visit[i] = 0;
        FOR(i,1,n+1) {
            if (visit[i] == 0) {
                int i1 = i;
                while (visit[i1] == 0) {
                    visit[i1] = i;
                    i1 = nex[i1];
                    if (i1 == MOD) break;
                    i1 = pa[i1];
                }
                if (i1 != MOD && visit[i1] == i) {
                    ans ++;
                    return;
                }
            }
        }
    } else {
        F0R(i,n-1-ind) {
            vi used1 = used;
            used1.pb(i);
            d(used1,ind+2);
        }
    }
}

int main() {
    ifstream cin ("wormholes.in");
    ofstream cout ("wormholes.out");
	cin >> n;
	F0R(i,n) {
        int x,y; cin >> x >> y;
        k[y].pb(i+1);
        all.pb(i+1);
	}
	for (pair<int,vi> a: k) {
        F0R(i,a.s.size()) {
            if (a.s.size()-i == 1) nex[a.s[i]] = MOD;
            else nex[a.s[i]] = a.s[i+1];
        }
	}
	d({},0);
	cout << ans;
}
