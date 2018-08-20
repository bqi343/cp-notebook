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
double PI = 4*atan(1);

int N,K,B[100000];
map<int,int> times;
map<int,set<int>> rec;

void ins(int num) {
	rec[times[num]].erase(num);
	if (rec[times[num]].size() == 0) rec.erase(times[num]);
	times[num] ++;
	rec[times[num]].insert(num);
}

void del(int num) {
	rec[times[num]].erase(num);
	if (rec[times[num]].size() == 0) rec.erase(times[num]);
	times[num] --;
	rec[times[num]].insert(num);
	if (times[num] == 0) times.erase(num);
}

int main() {
	ifstream cin ("lineup.in");
	ofstream cout ("lineup.out");
	cin >> N >> K; F0R(i,N) cin >> B[i];
	
	int lo = 0, hi = -1, ans = 0;
	F0R(i,N) {
		while (hi<i) ins(B[++hi]);
		while (lo<i) del(B[lo++]);
		while (hi<N-1 && (times.size() <= K || (times.size() == K+1 && times.find(B[hi+1]) != times.end()))) 
			ins(B[++hi]);
		ans = max(ans,rec.rbegin() -> f);
	}
	cout << ans;
}
