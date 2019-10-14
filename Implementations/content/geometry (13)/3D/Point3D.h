/**
 * Description: Basic 3D Geometry
 * Source: Own
 * Verification: 
	* AMPPZ 2011 Cross Spider
	* https://atcoder.jp/contests/JAG2013Spring/tasks/icpc2013spring_h
 */

typedef ld T;

namespace Point3D {
	typedef array<T,3> P3;
	typedef vector<P3> vP3;
	
	T norm(const P3& x) { 
		T sum = 0; F0R(i,sz(x)) sum += x[i]*x[i];
		return sum;
	}
	T abs(const P3& x) { return sqrt(norm(x)); }
	
	P3& operator+=(P3& l, const P3& r) { F0R(i,3) l[i] += r[i]; return l; }
	P3& operator-=(P3& l, const P3& r) { F0R(i,3) l[i] -= r[i]; return l; }
	P3& operator*=(P3& l, const T& r) { F0R(i,3) l[i] *= r; return l; }
	P3& operator/=(P3& l, const T& r) { F0R(i,3) l[i] /= r; return l; }
	
	P3 operator+(P3 l, const P3& r) { return l += r; }
	P3 operator-(P3 l, const P3& r) { return l -= r; }
	P3 operator*(P3 l, const T& r) { return l *= r; }
	P3 operator*(const T& r, const P3& l) { return l*r; }
	P3 operator/(P3 l, const T& r) { return l /= r; }
	
	T dot(const P3& a, const P3& b) { 
		T sum = 0; F0R(i,3) sum += a[i]*b[i];
		return sum;
	}
	P3 cross(const P3& a, const P3& b) {
		return {a[1]*b[2]-a[2]*b[1],
				a[2]*b[0]-a[0]*b[2],
				a[0]*b[1]-a[1]*b[0]};
	}
	
	bool isMult(const P3& a, const P3& b) {
		auto c = cross(a,b); 
		F0R(i,sz(c)) if (c[i] != 0) return 0; 
		return 1;
	}
	bool collinear(const P3& a, const P3& b, const P3& c) { return isMult(b-a,c-a); }
	bool coplanar(const P3& a, const P3& b, const P3& c, const P3& d) { 
		return isMult(cross(b-a,c-a),cross(b-a,d-a)); 
	}
}

using namespace Point3D;