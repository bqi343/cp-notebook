/** 
 * Description: Generate various types of trees.
 * Source: Own + Dhruv Rohatgi
 */

int RNG(int L, int R) { assert(L <= R); // int in [L,R] inclusive
	return uniform_int_distribution<int>(L,R)(rng);  }
db RNG(db L, db R) { assert(L <= R);
	return uniform_real_distribution<db>(L,R)(rng); }
int geoRNG(db p) { assert(0 < p && p <= 1); // p large -> closer to 0
	int c = 0; while (RNG(0.0,1.0) > p) c ++; // mean 1/p-1
	return c; }
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }
vi randPerm(int N) { vi v(N); iota(all(v),0);
	shuf(v); return v; }

vpi shufTree(vpi ed) { // randomly swap endpoints, rearrange labels
	int N = sz(ed)+1; vi v = randPerm(N);
	trav(t,ed) {
		t.f = v[t.f], t.s = v[t.s];
		if (rng()&1) swap(t.f,t.s);
	}
	shuf(ed); return ed;
}
vpi randTree(int N, int back) { // smaller back -> closer to line
	assert(N >= 1 && back >= 0); vpi ed; 
	FOR(i,1,N) ed.eb(i,i-1-RNG(0,min(back,i-1)));
	return ed; }
vpi path(int N) { return randTree(N,0); }

pi geoEdge(int i, db p) { assert(i > 0); // for tall tree
	return {i,max(0,i-1-geoRNG(p))}; }
vpi tallTree(int N, db p) {
	assert(N >= 1); 
	vpi ed; FOR(i,1,N) ed.pb(geoEdge(i,p));
	return ed; }
vpi randTallTree(int N, db p) { // tall tree, then add rand 
	assert(N >= 1); int mid = (N+1)/2;
	vpi ed = tallTree(mid,p); 
	FOR(i,mid,N) ed.eb(i,RNG(0,i-1));
	return ed; }
vpi heavyTallTree(int N, db p) { // lots of stuff connected to heavy1 or heavy2
	assert(N >= 1); // + bunch of rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.pb(geoEdge(i,p));
	}	
	return ed;
}
vpi heavyTallShortTree(int N, db p) { // connected to heavy1 or heavy2
	assert(N >= 1); // + almost-path + rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i <= heavy2) ed.pb(geoEdge(i,p)); // tall -> heavy1
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.eb(i,RNG(0,i-1)); // random stuff
	}
	return ed;
}

int main(int argc, char* argv[]) {
	int tc; sscanf(argv[1],"%d",&tc); // test case #
	// sscanf(argv[2],"%d",&b); // random seed
	// sscanf(argv[3],"%d",&c); // also random seed
	// srand(b);
	
}