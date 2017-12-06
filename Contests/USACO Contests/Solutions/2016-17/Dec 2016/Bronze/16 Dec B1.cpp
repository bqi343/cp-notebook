#include <fstream>
#include<vector>
// #include<iostream>

using namespace std;
 
typedef long long ll;
typedef pair <int, int> pii;
typedef vector<int> vi;

#define mp make_pair
#define pb push_back

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define endl "\n"
 
const int MOD = 1000000007;

int main() {
    ifstream cin ("square.in");
    ofstream cout ("square.out");
    pii a,b,c,d; cin >> a.f >> a.s >> b.f >> b.s >> c.f >> c.s >> d.f >> d.s;
    int ans = max((a.f,b.f),max(c.f,d.f))-min(min(a.f,b.f),min(c.f,d.f));
    ans = max(ans,max((a.s,b.s),max(c.s,d.s))-min(min(a.s,b.s),min(c.s,d.s)));
    cout << ans*ans;
	
}