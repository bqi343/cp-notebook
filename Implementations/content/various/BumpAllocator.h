/**
 * Description: When you need to dynamically allocate many objects and don't care about freeing them.
 	* "new X" otherwise has an overhead of something like 0.05us + 16 bytes per allocation.
 * Source: Simon Lindholm 
 * Status: tested
 */

// Either globally or in a single class:
static char buf[450 << 20];
void* operator new(size_t s) {
	static size_t i = sizeof buf; assert(s < i);
	return (void*)&buf[i -= s];
}
void operator delete(void*) {}
