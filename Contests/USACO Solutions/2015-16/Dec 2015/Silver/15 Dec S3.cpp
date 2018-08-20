// #include <iostream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>

using namespace std;

ifstream cin ("bcount.in");
ofstream cout ("bcount.out");

int array1[100001][4];

int main () {
    int N, Q;
    cin >> N >> Q;
    for (int i = 1; i <= N; ++i) {
        array1[i][1] = array1[i-1][1];
        array1[i][2] = array1[i-1][2];
        array1[i][3] = array1[i-1][3];
        int a;
        cin >> a;
        array1[i][a]++;
    }
    for (int i = 0; i < Q; ++i) {
        int a,b;
        cin >> a >> b;
        cout << array1[b][1]-array1[a-1][1] << " " << array1[b][2]-array1[a-1][2] << " " << array1[b][3]-array1[a-1][3] << endl;
    }
}
