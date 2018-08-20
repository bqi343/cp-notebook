#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

ofstream fout ("paint.out");
ifstream fin ("paint.in");

int array1[101];

int main() {
    int a, b, c, d;
    fin >> a >> b >> c >> d;
    for (int i = a; i < b; ++i) array1[i] = 1;
    for (int i = c; i < d; ++i) array1[i] = 1;
    int count = 0;
    for (int i = 0; i < 100; ++i) {
        if (array1[i] == 1) count++;
    }
    fout << count;
}
