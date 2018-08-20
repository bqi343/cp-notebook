#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

ofstream fout ("speeding.out");
ifstream fin ("speeding.in");

int array1[100];

int main() {
    int M, N, count1 = 0, max1 = 0;
    fin >> N >> M;
    for (int i = 0; i < N; ++i) {
        int a,b;
        fin >> a >> b;
        for (int j = count1; j < a+count1; ++j) {
            array1[j] = b;
        }
        count1 = count1+a;
    }
    count1 = 0;
    for (int i = 0; i < M; ++i) {
        int a,b;
        fin >> a >> b;
        for (int j = count1; j < a+count1; ++j) {
            array1[j] = b-array1[j];
            if(array1[j] > max1) max1 = array1[j];
        }
        count1 = count1+a;
    }
    fout << max1;
}
