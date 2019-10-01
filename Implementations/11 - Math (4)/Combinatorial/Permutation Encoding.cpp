/**
 * Description: convert permutation of {0,1,...,n-1} to integer in [0,n!) in linear time
 * Source: http://antoinecomeau.blogspot.com/2014/07/mapping-between-permutations-and.html
 * Verification: idk if this is useful for anything but ig it's cool
 */

vi decode(int n, int a) {
	vi el(n), b; iota(all(el),0);
	F0R(i,n) {
		int z = a%sz(el);
		b.pb(el[z]); a /= sz(el);
		swap(el[z],el.back()); el.pop_back();
	}
	return b;
}

int encode(vi b) {
	int n = sz(b), a = 0, mul = 1;
	vi pos(n); iota(all(pos),0); vi el = pos;
	F0R(i,n) {
		int z = pos[b[i]]; a += mul*z; mul *= sz(el);
		swap(pos[el[z]],pos[el.back()]); 
		swap(el[z],el.back()); el.pop_back();
	}
	return a;
}

/*
int n = 5;
F0R(i,120) {
	ps(decode(n,i));
	assert(encode(decode(n,i)) == i);
}
*/