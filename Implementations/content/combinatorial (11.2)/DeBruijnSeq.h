/**
 * Description: Given alphabet $[0,k)$ constructs a cyclic string 
 	* of length $k^n$ that contains every length $n$ string as substr. 
 * Source: https://github.com/koosaga/DeobureoMinkyuParty/blob/master/teamnote.tex
 	* https://en.wikipedia.org/wiki/De_Bruijn_sequence
 	* pg 241 of http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.93.5967&rep=rep1&type=pdf 
 * Verification: https://codeforces.com/gym/102001/problem/C
 */ 

vi deBruijnSeq(int k, int n) { /// Recursive FKM 
	if (k == 1) return {0};
	vi seq, aux(n+1); 
	function<void(int,int)> gen = [&](int t, int p) {
		if (t > n) { // +lyndon word of len p
			if (n%p == 0) FOR(i,1,p+1) seq.pb(aux[i]); 
		} else {
			aux[t] = aux[t-p]; gen(t+1,p);
			while (++aux[t] < k) gen(t+1,t);
		}
	};
	gen(1,1); return seq;
}