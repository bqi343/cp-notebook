/**
 * Description: Avoid hacks with custom hash.
 	* \texttt{gp\_hash\_table} is faster than \texttt{unordered\_map}
 	* but uses more memory.
 * Source: 
	* http://codeforces.com/blog/entry/62393
	* KACTL
 * Verification: http://codeforces.com/contest/966/problem/E 
	* normal unordered map gets TLE
 */

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x^(x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x^(x >> 27)) * 0x94d049bb133111eb;
		return x^(x >> 31);
	}
	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = 
			chrono::steady_clock::now()
			.time_since_epoch().count();
		return splitmix64(x+FIXED_RANDOM);
	}
};
template<class K, class V> using um = unordered_map<K,V,chash>;
template<class K, class V> using ht = gp_hash_table<K,V,chash>;
template<class K, class V> V get(ht<K,V>& u, K x) {
	return u.find(x) == end(u) ? 0 : u[x]; }
