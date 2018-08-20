#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// ifstream cin ("div7.in");
// ofstream cout ("div7.out");

int N, pre[50001], ans=0;

int main() {
    cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> pre[i];
		pre[i] += pre[i-1];
		pre[i] %= 7;
	}
	for (int r = 0; r < 7; ++r) {
		int a=N,b=0;
		for (int i = 0; i <= N; ++i) {
			if (pre[i] == r) {
				a = i;
				break;
			}
		}
		for (int i = N; i >= 0; --i) {
			if (pre[i] == r) {
				b = i;
				break;
			}
		}
		if (b-a>ans)ans=b-a;
	}
	cout << ans;
}