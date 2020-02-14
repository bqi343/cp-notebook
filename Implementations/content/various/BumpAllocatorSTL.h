/**
 * Description: Unused. BumpAllocator for STL containers.
 * Source: Simon Lindholm
 * Usage: vector<vector<int, small<int>>> ed(N);
 * Status: tested
 */

char buf[450 << 20] alignas(16);
size_t buf_ind = sizeof buf;
template<class T> struct small {
	typedef T value_type;
	small() {}
	template<class U> small(const U&) {}
	T* allocate(size_t n) {
		buf_ind -= n * sizeof(T);
		buf_ind &= 0 - alignof(T);
		return (T*)(buf + buf_ind);
	}
	void deallocate(T*, size_t) {}
};
