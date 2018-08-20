#include <fstream>
#include<vector>
// #include<iostream>
#include<algorithm>

using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)

ifstream cin ("tallbarn.in");
ofstream cout ("tallbarn.out");

vector<ll> a;
ld low = 0, high = 1e12+1;

int main() {
    ll N,K; cin >> N >> K;
    a.resize(N);
    F0R(i,N) cin >> a[i];
    int z = 0;
    while (high-low>0.00000001) {
    	ld mid = (low+high)/2;
    	z++;
    	// cout << high-low << "\n";
    	ll count = 0;
    	for (ll A: a) {
    		count += ceil((-1+sqrt(1+4*A/mid))/2);
    		if (count>K) break;
    	}
    	if (count <= K) high = mid;
    	else low = mid;
    }
    ll count = 0;
    ld ans = 0;
    for (ll A: a) {
    	ll t = ceil((-1+sqrt(1+4*(ld)A/high))/2);
    	ans += (ld)A/t;
    	count += t;
    }
    ans -= (K-count)*high;
    ll k = round(ans);
    cout << k;
}