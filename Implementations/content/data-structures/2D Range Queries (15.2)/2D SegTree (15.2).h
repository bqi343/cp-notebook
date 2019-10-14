/**
 * Description: ?
 * Source: USACO Mowing the Field
 * Verification: ?
 * Dependency: sparse segment tree
 */

const int SZ = 1<<17;


template<class T> struct Node {
	node<T> seg;
	Node* c[2];

	void upd(int x, int y, T v, int L = 0, int R = SZ-1) { // add v
		if (L == x && R == x) {
			seg.upd(y,v);
			return;
		}

		int M = (L+R)/2;
		if (x <= M) {
			if (!c[0]) c[0] = new Node();
			c[0]->upd(x,y,v,L,M);
		} else {
			if (!c[1]) c[1] = new Node();
			c[1]->upd(x,y,v,M+1,R);
		}

		seg.UPD(y,c[0] ? &c[0]->seg : NULL,c[1] ? &c[1]->seg : NULL);
	}

	T query(int x1, int x2, int y1, int y2, int L = 0, int R = SZ-1) { // query sum of rectangle
		if (x1 <= L && R <= x2) return seg.query(y1,y2);
		if (x2 < L || R < x1) return 0;

		int M = (L+R)/2;
		T t = 0;
		if (c[0]) t += c[0]->query(x1,x2,y1,y2,L,M);
		if (c[1]) t += c[1]->query(x1,x2,y1,y2,M+1,R);
		return t;
	}
};
