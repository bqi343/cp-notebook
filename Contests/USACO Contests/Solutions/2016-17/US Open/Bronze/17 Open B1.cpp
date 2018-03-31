#include<fstream>
#include<vector>

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

ifstream cin ("lostcow.in");
ofstream cout ("lostcow.out");

int dist = 1;

int main() {
	int x,y; cin >> x >> y;
	int x1 = x+1;
	while (1) {
		int x2 = 2*(x-x1)+x;
		if (min(x1,x2) <= y && y <= max(x1,x2)) {
			dist += abs(x1-y);
			break;
		} else dist += 3*abs(x-x1);
		x1 = x2;
	}
	cout << dist;
}
