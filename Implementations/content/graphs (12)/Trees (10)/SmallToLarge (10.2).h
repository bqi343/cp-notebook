/**
 * Description: offline subtree queries in $O(N\log^2N)$
 * Source: own
 * Verification: January Easy 2018 - Shubham & Tree 1
 */

struct SmallToLarge {
	int val[MX];
	vi child[MX];
	map<int,int> dat[MX];
	void comb(int a, int b) {
		bool swa = 0;
		if (sz(dat[a]) < sz(dat[b])) swap(a,b), swa = 1; 
		// note: swapping doesn't seem to work for indexed set
		each(x,dat[b]) dat[a][x.f] += x.s;
		dat[b].clear();
		if (swa) swap(dat[a],dat[b]);
	}
	void process(int ind) {
		dat[ind][val[ind]] ++;
		each(i,child[ind]) {
			process(i); 
			comb(ind,i);
		}
		// now do stuff with values
	}
};
