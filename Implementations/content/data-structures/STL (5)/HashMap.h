/**
 * Description: Hash map with the same API as unordered\_map, but \tilde 3x faster.
 	* Initial capacity must be a power of 2 (if provided).
 * Source: KACTL
 * Usage: ht<int,int> h({},{},{},{},{1<<16}); // reserve memory for 1<<16 elements
 */

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash { // use most bits rather than just the lowest ones
	const uint64_t C = ll(2e18*PI)+71; // large odd number
	const int RANDOM = rng();
	ll operator()(ll x) const { 
		return __builtin_bswap64((x^RANDOM)*C); }
};
template<class K,class V> using ht = gp_hash_table<K,V,chash>;
template<class K,class V> V get(ht<K,V>& u, K x) {
	return u.find(x) == end(u) ? 0 : u[x]; }