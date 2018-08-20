#include <fstream>
#include<vector>
// #include<iostream>
#include<algorithm>

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

vi haybales;
int N,Q;

    // first one greater or equal
int b1(int x) {
    if (haybales[N-1]<x) return N;
    int lb = 0, ub = N-1;
    while (lb<ub) {
        int mid = (lb+ub)/2;
        if (haybales[mid] < x) lb = mid+1;
        else ub = mid;
    }
    return lb;
}

    // last one less than or equal
int b2(int x) {
    if (haybales[0]>x) return -1;
    int lb = 0, ub = N-1;
    while (lb<ub) {
        int mid = (lb+ub+1)/2;
        if (haybales[mid] <= x) lb = mid;
        else ub = mid-1;
    }
    return lb;
}

int main() {
    ifstream cin ("haybales.in");
    ofstream cout ("haybales.out");
    cin >> N >> Q; haybales.resize(N);
    F0R(i,N) cin >> haybales[i];
    sort(haybales.begin(),haybales.end());
    F0R(i,Q) {
        int A,B; cin >> A >> B;
        cout << b2(B)-b1(A)+1 << "\n";
    }
}
