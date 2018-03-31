// #include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define ll long long
#define mp make_pair
#define pb push_back
#define pi pair <int, int>
#define vi vector<int>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
 
using namespace std;

ifstream cin ("angry.in");
ofstream cout ("angry.out");

int N, K;
vi nums;

main() {
    cin >> N >> K;
    F0R(i,N) {
        int n;
        cin >> n, nums.pb(n);
    }
    sort(nums.begin(), nums.end());
    
    for (int R = 0; ; ++R) {
        int count = 0, index = 0;
        while (count < K && index < N) {
            int temp = nums[index]+2*R;
            while (nums[index] <= temp && index < N) index++;
            count++;
        }
        if (index == N) {
            cout << R;
            return 0;
        }
    }
}
