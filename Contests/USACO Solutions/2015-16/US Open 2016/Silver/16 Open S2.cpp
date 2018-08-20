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

int best[50000], c = 0, ans = 0;
vi diamond;

int main() {
    ifstream cin ("diamond.in");
    ifstream cout ("diamond.out");
    int n,k; cin >> n >> k; diamond.resize(n);
    F0R(i,n) cin >> diamond[i];
    sort(diamond.begin(),diamond.end());
    for (int i = n-1; i >= 0; --i) {
        if (i == n-1) best[i] = i;
        else best[i] = best[i+1];
        while (diamond[best[i]]-diamond[i]>k) best[i]--;
        if (i != n-1) for (int j = best[i+1]; j > best[i]; --j)
            c = max(c,best[j]-j+1);
        ans = max(ans,best[i]-i+1+c);
    }
    cout << ans;
}
