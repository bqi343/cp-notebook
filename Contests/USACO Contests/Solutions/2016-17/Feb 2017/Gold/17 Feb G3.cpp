//#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define F0R(i, a) for (int i=0; i<a; i++)

#define f first
#define s second

pair<int,int> ID[50001];
int nums[100000];
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> cur;
long long ans = 0;

int main() {
	ifstream cin ("circlecross.in");
	ofstream cout  ("circlecross.out");
	int N; cin >> N;
	F0R(i,50001) ID[i] = {-1,-1};
	F0R(i,2*N) {
		int k; cin >> k; nums[i] = k;
		if (ID[k].f != -1) ID[k].s = i;
		else ID[k].f = i;
	}
	F0R(i,2*N) {
		if (i == ID[nums[i]].f) {
			ans += cur.order_of_key(ID[nums[i]].s);
			cur.insert(ID[nums[i]].s);
		} else cur.erase(ID[nums[i]].s);
	}
	cout << ans;
}