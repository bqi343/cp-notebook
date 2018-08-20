#include <fstream>
#include<vector>
// #include<iostream>

using namespace std;
 
typedef long long ll;
typedef pair <int, int> pi;
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
    ifstream cin ("blocks.in");
    ofstream cout ("blocks.out");
    int N; cin >> N;
    vi a(26);
	F0R(i,N) {
	    vi b(26),c(26);
	    string b1, c1; cin >> b1 >> c1;
	    for (char j: b1) b[int(j-'a')]++;
	    for (char j: c1) c[int(j-'a')]++;
	    F0R(j,26) a[j] += max(b[j],c[j]);
	}
	F0R(i,26) cout << a[i] << "\n";
}
