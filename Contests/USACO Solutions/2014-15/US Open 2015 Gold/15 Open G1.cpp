#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
 
typedef vector<int> vi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define F0Rd(i, a) for (int i=a-1; i>=0; i--)
 
#define pb push_back

vi start = {1}, emp = {0};

vi add(vi a, vi b) {
	vi c(max(a.size(),b.size())+1);
	F0R(i,max(a.size(),b.size())) {
		if (i<a.size()) c[i] += a[i];
		if (i<b.size()) c[i] += b[i];
		while (c[i]>9) c[i] -= 10, c[i+1] ++;
	}
	while (c.size() > 1 && c[c.size()-1] == 0) c.erase(c.end()-1);
	return c;
} 

vi divn(vi a) {
    F0R(i,a.size()) {
        if (a[i] % 2 == 1 && i != 0) a[i-1] += 5;
        a[i] /= 2;
    }
    F0R(i,a.size()) while (a[i] >= 10) {
        a[i] -= 10;
        a[i+1] ++;
    }
    while (a.size()>1 && a[a.size()-1] == 0) a.erase(a.end()-1);
    return a;
} 

vi divf(vi a) {
    a[0] --;
    F0R(i,a.size()-1) if (a[i]<0) {
        a[i] += 10;
        a[i+1] --;
    }
    return divn(a);
} 

void pr(vi cur) {
	F0Rd(i,cur.size()) cout << cur[i];
	cout << endl;
} 

vi input() {
	string x; cin >> x;
	vi cur;
	for (char c: x) cur.pb(c-'0');
	reverse(cur.begin(),cur.end());
	return cur;
} 

vi test (vi node, vi given) { 
	pr(node); vi left = input(), right = input();
	if (left == emp) return {1};
	if (right == emp) return {2};
	
	if (given[0] % 2 == 1) return add(add(test(left,divn(given)),divn(given)),{1});
	return add(add(test(right,divf(given)),divn(given)),{1});
} 

vi getnum(vi cur) {
	pr(cur); vi left = input(), right = input();
	if (left == emp) return {1};
	if (right == emp) return {2};
	vi x = getnum(right);
	return add(add(test(left,x),x),{1});
}

int main() {
	vi end = getnum(start);
	cout << "Answer ";
	pr(end);
} 