/**
 * Description: operations with pairs / arrays (LOL is there a better way to do this)
 * Source: own
 * Verification: ?
 */

template<class A, class B> pair<A,B> operator+(const pair<A,B>& l, const pair<A,B>& r) { return {l.f+r.f,l.s+r.s}; }
template<class A, class B> pair<A,B> operator-(const pair<A,B>& l, const pair<A,B>& r) { return {l.f-r.f,l.s-r.s}; }
template<class A, class B> pair<A,B> operator*(const pair<A,B>& l, const pair<A,B>& r) { return {l.f*r.f,l.s*r.s}; }
template<class A, class B> pair<A,B> operator/(const pair<A,B>& l, const pair<A,B>& r) { return {l.f/r.f,l.s/r.s}; }
template<class A, class B> pair<A,B>& operator+=(pair<A,B>& l, const pair<A,B>& r) { return l = l+r; }
template<class A, class B> pair<A,B>& operator-=(pair<A,B>& l, const pair<A,B>& r) { return l = l-r; }
template<class A, class B> pair<A,B>& operator*=(pair<A,B>& l, const pair<A,B>& r) { return l = l*r; }
template<class A, class B> pair<A,B>& operator/=(pair<A,B>& l, const pair<A,B>& r) { return l = l/r; }

template<class A, class B, class C> pair<A,B> operator*(const pair<A,B>& l, const C& r) { return {l.f*r,l.s*r}; }
template<class A, class B, class C> pair<A,B> operator/(const pair<A,B>& l, const C& r) { return {l.f/r,l.s/r}; }
template<class A, class B, class C> pair<A,B>& operator*=(pair<A,B>& l, const C& r) { return l = l*r; }
template<class A, class B, class C> pair<A,B>& operator/=(pair<A,B>& l, const C& r) { return l = l/r; }

template<class T, size_t SZ> array<T,SZ>& operator+=(array<T,SZ>& l, const array<T,SZ>& r) {
	F0R(i,SZ) l[i] += r[i]; 
	return l; }
template<class T, size_t SZ> array<T,SZ>& operator-=(array<T,SZ>& l, const array<T,SZ>& r) {
	F0R(i,SZ) l[i] -= r[i]; 
	return l; }
template<class T, size_t SZ> array<T,SZ>& operator*=(array<T,SZ>& l, const array<T,SZ>& r) {
	F0R(i,SZ) l[i] *= r[i]; 
	return l; }
template<class T, size_t SZ> array<T,SZ>& operator/=(array<T,SZ>& l, const array<T,SZ>& r) {
	F0R(i,SZ) l[i] /= r[i]; 
	return l; }
template<class T, size_t SZ> array<T,SZ> operator+(array<T,SZ> l, const array<T,SZ>& r) { return l += r; }
template<class T, size_t SZ> array<T,SZ> operator-(array<T,SZ> l, const array<T,SZ>& r) { return l -= r; }
template<class T, size_t SZ> array<T,SZ> operator*(array<T,SZ> l, const array<T,SZ>& r) { return l *= r; }
template<class T, size_t SZ> array<T,SZ> operator/(array<T,SZ> l, const array<T,SZ>& r) { return l /= r; }

template<class T, size_t SZ> array<T,SZ>& operator*=(array<T,SZ>& l, const T& r) { 
	F0R(i,SZ) l[i] *= r;
	return l; }
template<class T, size_t SZ> array<T,SZ>& operator/=(array<T,SZ>& l, const T& r) { 
	F0R(i,SZ) l[i] /= r; 
	return l; }
template<class T, size_t SZ> array<T,SZ> operator*(array<T,SZ> l, const T& r) { return l *= r; }
template<class T, size_t SZ> array<T,SZ> operator/(array<T,SZ> l, const T& r) { return l /= r; }


// // pi a = {4,5};
// // a *= 3;
// // ps(a);
// // ps(a*4);
// // array<int,3> a = {3,4,5}, b = {1,2,1};
// // a *= 3; ps(a);
// // ps(a*(int)4);
// // ps(a);
// // ps(a/b);
// // ps(a);
// // a /= b;
// // ps(a);
// array<int,3> a = {30,40,50}, b = {1,2,3};
// ps(a);
// ps(a/b);
// a /= b;
// ps(a);
// ps(a*3);
// a *= 3;
// ps(a);