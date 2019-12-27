package bc19;

import java.util.*;
import java.math.*;

import static bc19.Consts.*;

public class pi {
	public int f, s;
	pi(int _f, int _s) {
		f = _f; s = _s;
	}
	int norm() {
		return f*f+s*s;
	}
	int euclidDist(pi b) {
		if (b == null || f == -1 || b.f == -1) return MOD;
		return (f-b.f)*(f-b.f)+(s-b.s)*(s-b.s);
	}
	public boolean equals(pi x) {
		if (x == null) return false;
		return f == x.f && s == x.s;
	}
	public String toString() {
		return "("+f+", "+s+")";
	}
	/*public int compareTo(pi x) {
		if (f != x.f) return Integer.valueOf(f).compareTo(x.f);
		return Integer.valueOf(s).compareTo(x.s);
	}*/
};
