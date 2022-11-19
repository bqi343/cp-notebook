/**
 * Description: Hash map with similar API as unordered\_map.
 	* Initial capacity must be a power of 2 if provided.
 * Source: KACTL
 * Memory: \tilde 1.5x unordered map
 * Time: \tilde 3x faster than unordered map
 * Usage: ht<int,int> h({},{},{},{},{1<<16});
 */

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct chash { /// use most bits rather than just the lowest ones
	const uint64_t C = ll(4e18*acos(0))+71; // large odd number
	const int RANDOM = rng();
	ll operator()(ll x) const { return __builtin_bswap64((x^RANDOM)*C); }
}; /// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
/// template<class K,class V> using um = unordered_map<K,V,chash>;
template<class K,class V> using ht = gp_hash_table<K,V,chash>;
template<class K,class V> V get(ht<K,V>& u, K x) {
	auto it = u.find(x); return it == end(u) ? 0 : it->s; }