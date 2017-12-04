/*
ID: bqi3431
LANG: C++11
TASK: cowxor
*/

// #include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

#define F0R(i, a) for (int i=0; i<a; i++)

int N,a,b,c,cow[100000], z[1<<21]; 

int se (int cur, int len) {
	if (len == -1) return cur;
	cur = 2*cur+1;
	memset(z,-1,(1<<21)*sizeof(int));
	int q = 0; z[0] = 0;
	F0R(i,N) {
		q ^= (cow[i] >> len);
		if (z[cur^q] == -1) z[q] = (i+1);
		else return se(cur,len-1);
	}
	return se(cur-1,len-1);
}

int main() {
	ifstream cin ("cowxor.in");
	ofstream cout ("cowxor.out");
	
	cin >> N;
	F0R(i,N) cin >> cow[i];
	int k = se(0,20), q = 0;
	memset(z,-1,(1<<21)*sizeof(int));
	z[0] = 0;
	F0R(i,N) {
		q ^= cow[i];
		if (z[k^q] != -1) {
			cout << k << " " << (z[k^q]+1) << " " << (i+1) << endl;
			return 0;	
		} else z[q] = (i+1);
	}
}