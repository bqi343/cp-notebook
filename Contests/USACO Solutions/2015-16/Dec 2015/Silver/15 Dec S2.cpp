// #include <iostream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>

using namespace std;

ifstream cin ("highcard.in");
ofstream cout ("highcard.out");

int array1[100001];
vector<int> v1,v2;

int main () {
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        array1[a] = 1;
    }
    
    for (int i = 1; i <= 2*N; ++i) {
        if (array1[i] == 0) v1.push_back(i);
        if (array1[i] == 1) v2.push_back(i);
    }
    
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());
    for (int i = N; i > 0; --i) {
        bool x = true;
        for (int j = i-1; j >= 0; --j) {
            if (v1[j] < v2[j]) {
                x = false;
                break;
            }
        }
        if (x == true) {
            cout << i;
            return 0;
        }
        v1.erase(v1.begin());
    }
    cout << 0;
}
