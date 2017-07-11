#include <bits/stdc++.h>
 
using namespace std;
 
const int SZ = 100000;
 
int bit[SZ+1];
 
void update(int k, int val) {
	for( ;k <= SZ; k += (k & -k)) bit[k] += val;
}
 
int query(int k) {
	int temp = 0;
	for (;k>0;k -= (k & -k)) temp += bit[k];
	return temp;
}
 
int main() {
	update(5,2);
	update(4,1);
	cout << query(5)-query(3);
}
 
