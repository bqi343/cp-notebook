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

const int MOD = 1000000007;
double PI = 4*atan(1);

vi a,b;
int n;

bool need() {
    F0R(i,n) if (a[i]>b[i]) return 1;
    return 0;
}

int main() {
    ifstream cin ("cbarn.in");
    ofstream cout ("cbarn.out");
    cin >> n;
    F0R(i,n) {
        b.pb(i);
        int t; cin >> t;
        F0R(j,t) a.pb(i);
    }
    while (need()) {
        a.insert(a.begin(),a[n-1]-n);
        a.erase(a.end()-1);
    }
    int ans = 0;
    F0R(i,n) ans += (a[i]-b[i])*(a[i]-b[i]);
    cout << ans;
}
