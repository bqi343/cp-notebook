//#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define pb push_back

vi a,b;
int n;

int main() {
    ifstream cin ("cbarn.in");
    ofstream cout ("cbarn.out");
    cin >> n;
    int dif = 0;
    F0R(i,n) {
        b.pb(i);
        int t; cin >> t;
        F0R(j,t) a.pb(i);
    }
    F0R(i,n) dif = max(dif,a[i]-b[i]);
    F0R(i,n) b[i] += dif;
    ll ans = 0;
    F0R(i,n) ans += (a[i]-b[i])*(a[i]-b[i]);
    cout << ans;
}
