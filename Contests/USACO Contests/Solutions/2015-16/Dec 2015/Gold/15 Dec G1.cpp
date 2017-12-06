// #include <iostream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>

using namespace std;

ifstream cin ("cardgame.in");
ofstream cout ("cardgame.out");

int array1[100001];

vector<int> b1;
vector<int> b2;
vector<int> e1;
vector<int> e2;

bool sub (int i,int j) { return (i>j); }

int main () {
    int N,ans;
    cin >> N;
    for (int i = 0; i < N/2; ++i) {
        int a;
        cin >> a;
        array1[a] = 1;
        e1.push_back(a);
    }
    for (int i = N/2; i < N; ++i) {
        int a;
        cin >> a;
        array1[a] = 1;
        e2.push_back(a);
    }
    
    int count = 0;
    
    for (int i = 1; i <= 2*N; ++i) {
        if (array1[i] == 0) {
            if (count < N/2) b2.push_back(i);
            if (count >= N/2) b1.push_back(i);
            count++;
        }
    }
    
    sort(b1.begin(),b1.end());
    sort(b2.begin(),b2.end(),sub);
    sort(e1.begin(),e1.end());
    sort(e2.begin(),e2.end(),sub);
    
    for (int i = N/2; i>0; --i) {
        bool x = true;
        for (int j = i-1; j >= 0; --j) {
            if (e1[j] > b1[j]) {
                x = false;
                break;
            }
        }
        if (x == false) {
            b1.erase(b1.begin());
        } else {
            ans += i;
            break;
        }
    }
    
    for (int i = N/2; i>0; --i) {
        bool x = true;
        for (int j = i-1; j >= 0; --j) {
            if (e2[j] < b2[j]) {
                x = false;
                break;
            }
        }
        if (x == false) {
            b2.erase(b2.begin());
        } else {
            ans += i;
            break;
        }
    }
    cout << ans;
}
