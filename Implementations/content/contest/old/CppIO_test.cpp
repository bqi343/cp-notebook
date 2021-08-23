int main() {
	// setIO();
	{
		vector<bool> v = {0,1,1,0,1};
		ps(v);
		bitset<5> b; b[3] = 1;
		ps(b);
	}
	{
		int a = 1; 
		ll b = 2; 
		db c = 3; 
		char d = '4'; 
		str e = "5"; 
		bool f = true; 
		complex<double> g(1,2);
		ps("OK",a,b,c,d,e,f,g);
	}
	{
		pair<int, int> a = {1, 2};
		pair<string, bool> b = {"abcd", false};
		pair<char, float> c = {'x', 0.5};
		string d = "This is a string";
		pair<int, pair<int, int> > e = {1, {2, 3}};
		dbg(a, b, c, d, e);
		dbg();
	}
	{
		vector<int> a = {1, 2, 3, 4};
		set<int> b = {1, 2, 2, 3, 3, 4, 4, 5};
		map<string, int> c;
		c["string 1"] = 1;
		c["string 2"] = 2;
		dbg(a, b, c);

		unordered_map<string, int> d;
		d["string 3"] = 3;
		d["string 4"] = 4;
		multiset<int> e = {5, 5, 4, 3, 1, 1, 2};
		vector<vector<int> > f = {{1, 2, 3}};
		dbg(d, e, f);
	}
	{
		int a = 1;
		int b = 2;
		dbg(a + b, a * b, a / b, a - b, a / (float)b, 2019, 2019 - 1);
	}
}