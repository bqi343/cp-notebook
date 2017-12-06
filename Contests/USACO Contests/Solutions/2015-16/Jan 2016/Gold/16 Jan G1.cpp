//#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iomanip>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

vi pos;
double ans = 1000000000;
int n1[50000], n2[50000], N;

bool great(int rad) {
	int low = 0, high = N-1;
	while (low<N-1 && n1[low+1] <= rad) low++;
	while (high>0 && n2[high-1] <= rad) high--;
	double mid = double(pos[high]-pos[low])/2;
	ans = min(ans,max((double)rad+1,mid));
	if (rad+1<mid) return 0;
	return 1;
}

int main() {
	ifstream cin ("angry.in");
	ofstream cout ("angry.out");
	cin >> N; pos.resize(N);
	F0R(i,N) cin >> pos[i];
	sort(pos.begin(),pos.end());
	FOR(i,1,N) {
		if (pos[i]-pos[i-1]>n1[i-1]) {
			n1[i] = pos[i]-pos[i-1];
			continue;
		}
		auto x = lb(pos.begin(),pos.end(),pos[i]-n1[i-1]);
		int ind = distance(pos.begin(),x);
		if (n1[ind] >= n1[i-1]) n1[i] = n1[i-1]+1;
		else n1[i] = n1[i-1];
		//if (n1[i]<n1[i-1]) cout << n1[i] << "\n";
	}
	for (int i = N-2; i >= 0; --i) {
		if ((pos[i+1]-pos[i])>n2[i+1]) {
			n2[i] = pos[i+1]-pos[i];
			continue;
		}
		auto x = prev(ub(pos.begin(),pos.end(),pos[i]+n2[i+1]));
		int ind = distance(pos.begin(),x);
		if (n2[ind] >= n2[i+1]) n2[i] = n2[i+1]+1;
		else n2[i] = n2[i+1];
		//cout << n2[i] << " ";
	}
	F0R(i,N) ans = min(ans,(double)max(n1[i],n2[i]));
	int low = 0, high = 1000000000;
	while (low<high) {
		int mid = (low+high)/2;
		if (great(mid)) high = mid;
		else low = mid+1;
	}
	cout << fixed << setprecision(1) << ans;
}