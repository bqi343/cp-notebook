/**
* Description: Demonstrates use of map
*/

void compress(vi& x) {
    map<int,int> m; for (int i: x) m[i] = 0;
    int co = 0; for (auto& a: m) a.s = co++;
    for (int& i: x) i = m[i];
}

int main() {
	vi x = {2,4,3,6}; compress(x); 
	// now x={0,2,1,3}
}