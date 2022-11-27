/**
 * Description: Online Half-Plane Intersection
 * Source: retrograd
 * Verification:
   * https://infoarena.ro/job_detail/2700262?action=view-source
   * https://open.kattis.com/problems/bigbrother
 */

using T = int;
using T2 = long long;
using T4 = __int128_t;
const T2 INF = 2e9;

struct Line {
	T a, b;
	T2 c;
};

bool operator<(Line m, Line n) {
	auto half = [&](Line m) { return m.b < 0 || m.b == 0 && m.a < 0; };
	return make_tuple(half(m), (T2)m.b * n.a) <
		   make_tuple(half(n), (T2)m.a * n.b);
}
tuple<T4, T4, T2> LineIntersection(Line m, Line n) {
	T2 d = (T2)m.a * n.b - (T2)m.b * n.a; // assert(d);
	T4 x = (T4)m.c * n.b - (T4)m.b * n.c;
	T4 y = (T4)m.a * n.c - (T4)m.c * n.a;
	return {x, y, d};
}
Line LineFromPoints(T x1, T y1, T x2, T y2) {
	// everything to the right of ray {x1, y1} -> {x2, y2}
	T a = y1 - y2, b = x2 - x1;
	T2 c = (T2)a * x1 + (T2)b * y1;
	return {a, b, c}; // ax + by <= c
}
ostream &operator<<(ostream &out, Line l) {
	out << "Line " << l.a << " " << l.b << " " << -l.c;
	// out << "(" << l.a << " * x + " << l.b << " * y <= " << l.c << ")";
	return out;
}

struct HalfplaneSet : multiset<Line> {
	HalfplaneSet() {
		insert({+1, 0, INF});
		insert({0, +1, INF});
		insert({-1, 0, INF});
		insert({0, -1, INF});
	};
	auto adv(auto it, int z) { // z = {-1, +1}
		return (z == -1 ? --(it == begin() ? end() : it)
						: (++it == end() ? begin() : it));
	}
	bool chk(auto it) {
		Line l = *it, pl = *adv(it, -1), nl = *adv(it, +1);
		auto [x, y, d] = LineIntersection(pl, nl);
		T4 sat = l.a * x + l.b * y - (T4)l.c * d;
		if (d < 0 && sat < 0) return clear(), 0; // unsat
		if ((d > 0 && sat <= 0) || (d == 0 && sat < 0)) return erase(it), 1;
		return 0;
	}
	void Cut(Line l) { // add ax + by <= c
		if (empty()) return;
		auto it = insert(l);
		if (chk(it)) return;
		for (int z : {-1, +1})
			while (size() && chk(adv(it, z)))
				;
	}
	double Maximize(T a, T b) { // max ax + by (UNTESTED)
		if (empty()) return -1 / 0.;
		auto it = lower_bound({a, b});
		if (it == end()) it = begin();
		auto [x, y, d] = LineIntersection(*adv(it, -1), *it);
		return (1.0 * a * x + 1.0 * b * y) / d;
	}
	double Area() {
		double total = 0.;
		for (auto it = begin(); it != end(); ++it) {
			auto [x1, y1, d1] = LineIntersection(*adv(it, -1), *it);
			auto [x2, y2, d2] = LineIntersection(*it, *adv(it, +1));
			total += (1.0 * x1 * y2 - 1.0 * x2 * y1) / d1 / d2;
		}
		return total * 0.5;
	}
};