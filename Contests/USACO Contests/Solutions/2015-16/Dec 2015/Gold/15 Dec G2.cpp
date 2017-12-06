// #include <iostream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>

using namespace std;

ifstream cin ("feast.in");
ofstream cout ("feast.out");

int array1[5000001];

int findmax(int x) {
    for (int i = x; i >= 0; --i) {
        if (array1[i]) {
            return i;
        }
    }
    return 0;
}

int main() {
    int T,A,B, ans=0;
    cin >> T >> A >> B;
    array1[0] = 1;
    for (int i = 1; i <= T; ++i) {
        if (i-A>=0 && array1[i-A] == 1) {
            array1[i] = 1;
        }
        if (i-B>=0 && array1[i-B] == 1) {
            array1[i] = 1;
        }
    }
    
    for (int i = 0; i <= T; ++i) {
        if (array1[i]) {
            int j = i/2;
            int max = j+findmax(T-j);
            if (max > ans) ans = max;
        }
    }
    cout << ans;
}
