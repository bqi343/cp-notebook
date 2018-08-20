#include <iostream>
#include <fstream>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef pair<int,int> pi;
typedef long long ll;

#define F0R(i, a) for (int i=0; i<a; i++)
#define f first
#define s second

int N,K;
pi x[100001];
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> s[100001];
ll ans = 0;

void updb (int num, int pos) {
	while (num <= N) {
		s[num].insert(pos);
		num += (num & -num);
	}
}

ll queryb(int mnum, int mpo) {
	ll z = 0;
	while (mnum) {
		z += s[mnum].order_of_key(mpo+1);
		mnum -= (mnum & -mnum);
	}
	return z;
}

void init() {
	//ifstream cin ("friendcross.in");
	cin >> N >> K;
	F0R(i,N) {
		int a; cin >> a;
		x[a].f = i+1;
	}
	F0R(i,N) {
		int b; cin >> b;
		x[b].s = i+1;
	}
}

int main() {
	//ofstream cout ("friendcross.out");
	init();
	for (int i = N; i > 0; --i) {
		int j = i+K+1;
		if (j > N) continue;
		updb(x[j].f,x[j].s);
		ans += queryb(N,x[i].s);
		ans += queryb(x[i].f,N);
		ans -= 2*queryb(x[i].f,x[i].s);
	}
	cout << ans;
}
