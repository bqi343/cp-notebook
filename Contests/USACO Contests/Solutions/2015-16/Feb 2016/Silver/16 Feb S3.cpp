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

bool best[101][101], temp[101][101];
int MOD = 1000000007;
int ans = MOD;
int x,y,k,m;

int main() {
    ifstream cin ("pails.in");
    ofstream cout ("pails.out");
    cin >> x >> y >> k >> m;
    F0R(i,101) F0R(j,101) best[i][j] = 0;
    best[0][0] = 1;
    F0R(z,k) {
        F0R(i,101) F0R(j,101) temp[i][j] = 0;
        F0R(i,x+1) F0R(j,y+1) if (best[i][j]) {
            temp[i][j] = 1;
            temp[x][j] = temp[i][y] = 1;
            temp[0][j] = temp[i][0] = 1;
            int a = min(i,y-j), b = min(x-i,j);
            temp[i-a][j+a] = temp[i+b][j-b] = 1;
            // cout << z << " " << i << " " << j << "\n";
        }
        F0R(i,101) F0R(j,101) best[i][j] = temp[i][j];
    }
    F0R(i,101) F0R(j,101) if (best[i][j]) ans = min(ans,abs(i+j-m));
    cout << ans;
}
