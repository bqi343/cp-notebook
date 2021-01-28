/**
 * Description: Operations on quaternions, useful for totations in 3D
 * Source: https://codeforces.com/blog/entry/46744
 * Verification:
 	* https://codeforces.com/gym/102354/problem/F
	* https://codeforces.com/contest/1375/problem/I
 */

using T = ld; const T EPS = 1e-9;
int sgn(T x) { return (x>0)-(x<0); }
T sq(T x) { return x*x; }
 
/////// DEFINING QUATER
using Q = array<T,4>; using vQ = vector<Q>; // represent quater as (x,y,z,s)
Q vec(T x, T y, T z) { return {x,y,z,0}; } // vector to quater
Q vec(Q a) { a[3] = 0; return a; } // quater to vector
void isVec(const Q& q) { assert(q[3] == 0); } // assert that quater is vector
const Q ex = vec(1,0,0), ey = vec(0,1,0), ez = vec(0,0,1); // unit vectors for each of three axes
Q conj(Q x) { F0R(i,3) x[i] *= -1; // conjugate
	return x; }
Q ortho(const Q& x) { isVec(x); // return any nonzero vector perpendicular to q
	return abs(x[1]) > EPS ? vec(x[1],-x[0],0) : vec(x[2],0,-x[0]); }
Q vrand() { // random vector
	Q q = Q(); F0R(i,3) q[i] = rng()%(2*MOD)-MOD;
	return q; }
T norm(const Q& x) { // sum of squares
	T sum = 0; each(t,x) sum += t*t;
	return sum; }
T abs(const Q& x) { return sqrt(norm(x)); }

/////// BASIC ARITHMETIC
Q& operator+=(Q& l, const Q& r) { F0R(i,4) l[i] += r[i]; 
	return l; }
Q& operator-=(Q& l, const Q& r) { F0R(i,4) l[i] -= r[i]; 
	return l; }
Q& operator*=(Q& l, const T& r) { F0R(i,4) l[i] *= r; 
	return l; }
Q& operator/=(Q& l, const T& r) { F0R(i,4) l[i] /= r; 
	return l; }
Q operator-(Q l) { return l *= -1; }
Q operator+(Q l, const Q& r) { return l += r; }
Q operator-(Q l, const Q& r) { return l -= r; }
Q operator*(Q l, const T& r) { return l *= r; }
Q operator*(const T& r, const Q& l) { return l*r; }
Q operator/(Q l, const T& r) { return l /= r; }
Q unit(Q x) { return x/abs(x); }
Q inv(const Q& x) { return conj(x)/norm(x); }
bool eq(Q a, Q b) { return abs(a-b) < EPS; }

Q operator*(const Q& x, const Q& y) { Q z = Q(); // multiply quaters
	F0R(i,4) F0R(j,4) // i=3 or j=3 -> multiplying by constant, just add product
		z[i^j^3] += ((i==3||j==3||(i+1)%3 == j)?1:-1)*x[i]*y[j];
	return z; }
Q operator/(const Q& l, const Q& r) { return l*inv(r); }
Q& operator*=(Q& l, const Q& r) { return l = l*r; }
Q& operator/=(Q& l, const Q& r) { return l = l/r; }

T dot(const Q& l, const Q& r) { isVec(l), isVec(r); // dot product of vectors
	T res = 0; F0R(i,3) res += l[i]*r[i];
	return res; }
Q cross(const Q& l, const Q& r) { isVec(l), isVec(r); // cross product of vectors
	return vec(l*r); }
T mix(const Q& a, const Q& b, const Q& c) { isVec(a), isVec(b), isVec(c);
	return dot(a,cross(b,c)); } // mixed product

// rotating phi about axis i -> rotation quater is in the form rot=cos(phi/2)+i*sin(phi/2)
Q rotate(const Q& rot, const Q& x) { isVec(x); 
	return vec(rot*x/rot); } // rot doesn't have to be normalized
Q minRotation(const Q& a, const Q& b) { isVec(a), isVec(b); // min rotation from a to b
	return eq(a,-b) ? ortho(b) : (a+b)*a; } // if a == -b then infinitely many possible ...
T getAngle(const Q& a) { return remainder(2*acos(a[3]/abs(a)),2*PI); }  // get phi
Q basisRotation(const Q& a, const Q& b) { isVec(a), isVec(b); // bring ex to a and ey to b
	Q ra = minRotation(ex,a); Q EY = rotate(ra,ey); // first rotate ex to a
	Q rb = eq(EY,-b) ? a : minRotation(EY,b); // then rotate ey to b
	return rb*ra; }
Q basisRotation(const Q& a, const Q& b, const Q& A, const Q& B) { // rotation that brings a to A and b to B
	return basisRotation(A,B)/basisRotation(a,b); } // a -> ex -> A, b -> ey -> B

/////// EIGENBASIS of positive semidefinite matrix, use for PCA
// eigenvectors for different eigenvalues are orthogonal
// https://en.wikipedia.org/wiki/Definite_symmetric_matrix
// https://en.wikipedia.org/wiki/Principal_component_analysis
typedef array<array<T,3>,3> Mat;
Q operator*(const Mat& l, const Q& r) { isVec(r); // multiply matrix by vector
	Q res = Q(); F0R(i,3) F0R(j,3) res[i] += l[i][j]*r[j];
	return res; }
Q flatten(const vQ& basis, Q x) { isVec(x); // reduce x given orthonormal basis
	each(t,basis) x -= t*dot(t,x);
	return unit(x); }
Q findEigenvec(const vQ& basis, const Mat& A) { // if we keep applying it will converge to vector corresponding to largest eigenvalue
	Q x = flatten(basis,vrand());
	F0R(_,1e5) {
		Q X = A*x; if (abs(X) < EPS) return x; // eigenvalue 0?
		x = flatten(basis,X);
	}
	return x;
}
vQ eigenBasis(const Mat& A) { 
	vQ basis; F0R(z,3) basis.pb(findEigenvec(basis,A));
	return basis; }

/////// GCD of Hurwitz Quaternions
// https://en.wikipedia.org/wiki/Hurwitz_quaternion
// all coordinates are integer or all coordinates are half-integer
// multiples of Hurwitz quater a are in the form a*v
Q round(const Q& q) { Q a, b; // get closest Hurwitz quaternion
	F0R(i,4) a[i] = round(q[i]); // try int
	F0R(i,4) b[i] = round(q[i]-0.5)+0.5; // and half-int
	return norm(a-q) < norm(b-q) ? a : b; }
Q operator%(const Q& a, const Q& b) { return a-b*round(inv(b)*a); }
Q gcd(Q a, Q b) { if (norm(a) > norm(b)) swap(a,b);
	return norm(a) == 0 ? b : gcd(b%a,a); }
