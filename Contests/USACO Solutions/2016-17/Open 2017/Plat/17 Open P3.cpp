#include<iostream>
#include<fstream>
#include<map>
#include<queue>
#include<vector>

using namespace std;
 
typedef long long ll;
typedef vector<long long> vi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define mp make_pair
#define pb push_back

const int MOD = 1000000007;

queue<string> commands;
map<string,int> getind;
vector<vi> val;
int nexind = 0;

string nex() { 
	string ret = commands.front(); commands.pop();
	return ret;
}

vi init(int ind) { 
	vi k(nexind+1);
	k[ind] = 1;
	return k;
}

char type(string t) { 
	if (t == "RETURN") return 'R';
	if ('0' <= t[0] && t[0] <= '9') return 'L';
	return 'V';
}

vi getex (bool isnest) {
	string curvar = nex();
	vi cur(nexind+1);
	
	if (curvar == "(") {
		vi i1 = getex(1);
		curvar = nex(), curvar = nex();
		vi i2 = getex(1);
		F0R(i,i1.size()) cur[i] = (i1[i] + i2[i]) % MOD;
	} else if (type(curvar) == 'L') {
		vi k(nexind+1);
		k[nexind] = stoi(curvar);
		cur = k;
	} else cur = val[getind[curvar]];
	if (isnest) curvar = nex();
	return cur;
}

vector<vi> mult (vector<vi> a, vector<vi> b){
	vector<vi> c(nexind);
	F0R(i,nexind) c[i].resize(nexind+1);
	F0R(i,nexind) {
		F0R(j,nexind) {
			F0R(k,nexind) c[i][k] = (c[i][k] + a[i][j]*b[j][k]) % MOD;
			c[i][nexind] = (c[i][nexind]+a[i][j]*b[j][nexind]) % MOD;
		}
		c[i][nexind] = (c[i][nexind]+a[i][nexind]) % MOD;
	}
	return c;
}

void execute();

vector<vi> getpo(vector<vi> a, int po) {
	vector<vi> cur = a;
	po --;
	while (po) {
		if (po & 1) a = mult(cur,a);
		po /= 2;
		cur = mult(cur,cur);
	}
	return a;
}

void rep (int tim) {
	int clevel = 1;
	queue<string> temp;
	while (1) {
		string curvar = nex();
		if (curvar == "{") clevel++;
		else if (curvar == "}") {
			clevel --;
			if (clevel == 0) break;
		}
		temp.push(curvar);
	}
	queue<string> storage = commands;
	commands = temp;
	execute();
	val = getpo(val,tim);
	commands = storage;
}

void execute() { 
	val.resize(nexind);
	F0R(i,nexind) val[i] = init(i);
	
	while (commands.size()) {
		string curvar = nex();
		char t = type(curvar);
		if (t == 'V') {
			string z = nex();
			val[getind[curvar]] = getex(0);
		} else if (t == 'L') {
			string z = nex(); z = nex();
			
			auto val1 = val;
			rep(stoi(curvar));
			val = mult(val,val1); 
		} else {
			curvar = nex();
			cout << val[getind[curvar]][nexind] << "\n";
			return;
		}
	}
}

int main() { 
	string s;
	while (cin >> s) {
		commands.push(s);
		if ('a' <= s[0] && s[0] <= 'z') 
			if (getind.find(s) == getind.end()) 
				getind[s] = nexind++;
	}
	execute();
}