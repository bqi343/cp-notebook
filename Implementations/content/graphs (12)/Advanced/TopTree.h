/**
 * Source: Andrew He (https://github.com/ecnerwala/cp-book/blob/4ac19d5a3ded84adb4bb5a1aebff9d8153ac70ee/src/top_tree.hpp)
 * Description: Top tree (generalization of LCT to support path \& subtree updates \& queries)
 * Verification: 
   * https://codeforces.com/blog/entry/84056#comment-715550 (code below solves this problem, also see link to paper)
   * https://www.facebook.com/codingcompetitions/hacker-cup/2021/round-1/problems/C
   * https://codeforces.com/blog/entry/87916#comment-764429 (GP of Suwon)
   * https://dmoj.ca/problem/ds5 (Dynamic Tree Test)
 */
 
/*
 * Usage:
 *   Implement
 *     void update()
 *     void downdate()
 *     void do_flip_path()
 *     void do_other_operation() ...
 *   When update() is called, you can assume downdate() has already been called.
 *
 *   In general, do_op() should eagerly apply the operation but not touch the
 *   children. In downdate(), you can push down to the children with ch->do_op().
 *   WARNING : if different operations do not trivially commute, you *must*
 *   implement a way to swap/alter them to compose in a consistent order, and you
 *   must use that order when implementing downdate(). This can be nontrivial!
 *
 *   Creating vertices:
 *     n->is_path = n->is_vert = true;
 *     n->update();
 *
 *   Creating edges: no setup/update() needed, just call
 *     link(e, va, vb);
 *
 *   Updates:
 *     auto cur = get_path(va, vb); // or get_subtree(va, vb)
 *     cur->do_stuff();
 *     cur->downdate();
 *     cur->update_all();
 *
 * Node types:
 *   path edges: compress(c[0], self, c[1])
 *     assert(is_path && !is_vert);
 *     assert(c[0] && c[1]);
 *     assert(c[0]->is_path && c[1]->is_path);
 *     assert(!c[2]);
 *   (path) vertices: self + rake(c[0], c[1])
 *     assert(is_path && is_vert);
 *     assert(!c[2]);
 *     if (c[0]) assert(!c[0]->is_path);
 *     if (c[1]) assert(!c[1]->is_path);
 *   non-path edges: rake(c[0], self + c[2], c[1])
 *     assert(!is_path && !is_vert);
 *     assert(c[2]);
 *     assert(c[2]->is_path);
 *     if (c[0]) assert(!c[0]->is_path);
 *     if (c[1]) assert(!c[1]->is_path);
 */

using pt = struct top_tree_node*;
struct top_tree_node {
private:
	mutable pt p = nullptr;
	AR<pt, 3> c{nullptr, nullptr, nullptr};
	// \return direction in which parent points to you
	int d() const {
		if (!p) return -1;
		F0R(i,3) if (this == p->c[i]) return i;
		assert(false);
	}
	// \return true if this is root of rake or compress tree
	bool r() const { return !p || p->is_path != is_path; } 
 
public:
	// 3 types of verts: path edges, path verts, non-path edges
	bool is_path, is_vert;
	bool flip_path = false;
 
	// MODIFY STUFF BELOW
	int path_len,  best_path;
	bool own_parity, path_parity;
	AR<int,2> best_down, best_up;
	void do_flip_path() {
		assert(is_path); flip_path ^= 1;
		swap(best_down, best_up);
	}
	void downdate() {
		if (flip_path) {
			assert(is_path);
			if (!is_vert) F0R(i,2) if (c[i]) c[i]->do_flip_path(); // if vert, then you're at a leaf so don't propagate
			swap(c[0], c[1]);
			flip_path = false;
		}
	}
	void update() { // TODO: find longest path of each parity
		assert(!flip_path);
		if (is_path && !is_vert) {
			assert(c[0] && c[1] && !c[2]);
			path_len = 1+c[0]->path_len+c[1]->path_len;
			path_parity = own_parity^c[0]->path_parity^c[1]->path_parity;
 
			best_up = c[0]->best_up;
			F0R(z,2)
				ckmax(best_up[c[0]->path_parity^own_parity^z],c[0]->path_len+1+c[1]->best_up[z]);
 
			best_down = c[1]->best_down;
			F0R(z,2)
				ckmax(best_down[c[1]->path_parity^own_parity^z],c[1]->path_len+1+c[0]->best_down[z]);
			
			best_path = max(c[0]->best_path,c[1]->best_path);
			F0R(z,2) ckmax(best_path,c[0]->best_down[z]+1+c[1]->best_up[z^own_parity]);
		} else { 
			path_len = 0;
			path_parity = 0;
			best_up = {0,-MOD};
			best_path = 0;
			if (!is_vert) {
				best_path = c[2]->best_path;
				AR<int,2> tmp_up = c[2]->best_up;
				F0R(i,2) ++tmp_up[i];
				if (own_parity) swap(tmp_up[0],tmp_up[1]);
				F0R(i,2) {
					ckmax(best_up[i],tmp_up[i]);
					if (i == 0) ckmax(best_path,best_up[i]);
				}
			}
			F0R(d,2) {
				if (!c[d]) continue;
				ckmax(best_path,c[d]->best_path);
				F0R(z,2) {
					ckmax(best_path,c[d]->best_up[z]+best_up[z]);
					ckmax(best_up[z],c[d]->best_up[z]);
				}
			}
			// rake(c[0],c[1],self+c[2])
			best_down = best_up;
		}
	}
	void downdate_all() {
		if (p) p->downdate_all();
		downdate();
	}
	// Returns the root
	pt update_all() {
		pt cur = this; cur->update();
		while (cur->p) { cur = cur->p; cur->update(); }
		return cur;
	}
private:
	// sets y to be the d'th child of x
	friend void setLink(pt x, pt y, int d) {
		if (y) y->p = x;
		if (d != -1) x->c[d] = y; 
	}
	void rot() { // rotate this up, parent down
		assert(!is_vert && !r());
		pt pa = p;
		int x = d(); assert(x == 0 || x == 1);
		pt ch = c[!x];
		setLink(pa->p,this,pa->d());
		setLink(pa,ch,x);
		setLink(this,pa,!x);
		pa->update();
	}
	void rot_2(int c_d) { // rotate this up (along with c_d'th child), parent down
		assert(!is_vert && !r());
		assert(c[c_d] && !c[c_d]->is_vert);
		if (d() == c_d) { rot(); return; }
		pt pa = p;
		int x = d(); assert(x == 0 || x == 1);
		assert(c_d == !x);
		pt ch = c[c_d]->c[!x];
		setLink(pa->p,this,pa->d());
		setLink(pa,ch,x);
		setLink(this->c[c_d],pa,!x);
		pa->update();
	}
	void splay_dir(int x) { // splay while direction is x
		while (!r() && d() == x) {
			if (!p->r() && p->d() == x) p->rot();
			rot();
		}
	}
	// splay path edge along with child path edge
	void splay_2(int c_d) {
		assert(!is_vert && is_path);
		assert(c[c_d] && !c[c_d]->is_vert);
		while (!r()) {
			if (!p->r()) {
				if (p->d() == d()) p->rot();
				else rot_2(c_d);
			}
			rot_2(c_d);
		}
	}
	// splay parent edge to top of tree, bringing this along for the ride
	void splay_2() {
		assert(!is_vert && is_path && !r());
		p->splay_2(d());
	}
	// splay vertex as close to top of tree as possible
	void splay_vert() {
		assert(is_vert && is_path); if (r()) return; // if path is single vertex, done
		p->splay_dir(d()); if (p->r()) return; // if parent is already at top, done
		// otherwise vertex is in between two edges
		assert(p->d() != d());
		if (d() == 1) p->rot();
		assert(d() == 0);
		p->splay_2(); // splay parent of parent to the top
		assert(d() == 0 && p->d() == 1 && p->p->r());
	}
	void splay() { // normal splay of an edge
		assert(!is_vert);
		while (!r()) {
			if (!p->r()) {
				if (p->d() == d()) p->rot();
				else rot();
			}
			rot();
		}
	}
	// either brings root to top of splay tree, or to right child of top of splay tree
	// cuts part of compress tree to the right of this
	pt cut_right() {
		assert(is_vert && is_path);
		splay_vert();
		if (r() || d() == 1) { // if last vertex on path, do nothing
			assert(r() || (d() == 1 && p->r()));
			assert(c[0] == nullptr); // why?
			return nullptr; // don't need to cut anything
		}
		// goal: cut pa and everything to the right of it
		// make it a rake
 
		// before:
		// pa->p
		//   \
		//    \
		//     pa
		//    /
		//   /
		// this (vertex, children are rake trees)
 
		// after:
		// pa->p
		//   \
		//    \
		//     this (pa as foster child)
 
		// or -> single vertex
		pt pa = p;
		assert(pa->r() || (pa->d() == 1 && pa->p->r()));
		assert(!pa->is_vert && pa->is_path);
		assert(pa->c[0] == this && pa->c[2] == nullptr); // pa is path edge
		setLink(pa->p,this,pa->d()); // now this or this->p is root
		pa->is_path = false; pa->c[2] = pa->c[1]; // pa is now a rake tree
		F0R(i,2) setLink(pa,c[i],i); // pa inherits rake children of this
		c[0] = nullptr; setLink(this,pa,1); // set pa to be a rake
		assert(c[2] == nullptr);
		pa->update(); return pa;
	}
	pt splice_non_path() { // cut some previous path, replace with new path
		assert(!is_path && !is_vert); splay(); // bring to top of rake tree
		assert(p && p->is_vert && p->is_path); // parent is a vertex
		p->cut_right(); // cut part to right of vertex
		if (!p->is_path) rot(); // rotate this to top of rake tree again
		assert(p && p->is_vert && p->is_path); // same parent
		assert(p->r() || (p->d() == 1 && p->p->r()));
		assert(p->c[d()] == this && p->c[!d()] == nullptr); // parent vertex only has one rake child? why?
		pt pa = p;
		setLink(pa->p,this,pa->d());
		F0R(i,2) setLink(pa,c[i],i);
		assert(c[2] && c[2]->is_path);
		c[1] = c[2]; // don't need to change parent
		setLink(this,pa,0);
		c[2] = nullptr;
		is_path = true;
		assert(d() != 0);
		pa->update(); return pa;
	}
 
	// Return the topmost vertex which was spliced into
	pt splice_all() { // make this part of topmost path
		pt res = nullptr;
		for (pt cur = this; cur; cur = cur->p) {
			if (!cur->is_path) res = cur->splice_non_path();
			assert(cur->is_path);
		}
		return res;
	}
 
public:
	pt getRoot() {
		expose(); 
		pt v = this; while (v->p) v = v->p;
		assert(v);
		v->downdate();
		while (!v->is_vert) { 
			assert(v->c[0]);
			v = v->c[0]; v->downdate(); 
		}
		v->expose();
		return v;
	}
	friend bool connected(pt a, pt b) {
		return a->getRoot() == b->getRoot();
	}
	// Return the topmost vertex which was spliced into
	pt expose() { // yay makes sense!
		assert(is_vert); 
		downdate_all(); // make sure to propagate everything above
		pt res = splice_all(); cut_right(); update_all();
		return res;
	}
	// Brings edge to the top
	// Return the topmost vertex which was spliced into
	pt expose_edge() {
		assert(!is_vert); downdate_all();
		pt v = is_path ? c[1] : c[2]; v->downdate();
		// if is_path: path to right of edge
		// otherwise: compress tree under edge
		while (!v->is_vert) { v = v->c[0]; v->downdate(); }
		pt res = v->splice_all(); v->cut_right(); v->update_all(); // same as expose
		assert(!p && v == c[1]);
		return res;
	}
	// make sure path end only has one child
	// Return the new root
	pt meld_path_end() {
		assert(!p);
		pt rt = this;
		while (true) {
			rt->downdate();
			if (rt->is_vert) break;
			rt = rt->c[1];
		}
		assert(rt->is_vert);
		rt->splay_vert();
		if (rt->c[0] && rt->c[1]) { // make sure path end has only one rake child ...
			pt ch = rt->c[1];
			while (true) {
				ch->downdate();
				if (!ch->c[0]) break;
				ch = ch->c[0];
			}
			ch->splay();
			assert(ch->c[0] == nullptr);
			setLink(ch,rt->c[0],0); rt->c[0] = nullptr;
			ch->update();
		} else if (rt->c[0]) {
			rt->c[1] = rt->c[0];
			rt->c[0] = nullptr;
		}
		assert(rt->c[0] == nullptr);
		return rt->update_all();
	}
	void make_root() {
		expose();
		pt rt = this;
		while (rt->p) {
			assert(rt->d() == 1);
			rt = rt->p;
		}
		rt->do_flip_path(); rt->meld_path_end();
		expose(); assert(!p); // root path is now single node
	}
	// link v2 as a child of v1 with edge e
	friend void link(pt e, pt v1, pt v2) {
		assert(e && v1 && v2); F0R(i,3) assert(!e->c[i]);
		e->is_path = true, e->is_vert = false;
		v1->expose(); while (v1->p) v1 = v1->p;
		v2->make_root();
		assert(!v1->p && !v2->p); // should both be at top
		setLink(e,v1,0); setLink(e,v2,1);
		e->update();
	}
	// Cuts the edge e
	// Returns the top-tree-root of the two halves; they are not necessarily the split vertices.
	friend pair<pt, pt> cut(pt e) {
		assert(!e->is_vert); e->expose_edge();
		assert(!e->p && e->is_path && e->c[2] == nullptr);
		pt l = e->c[0], r = e->c[1]; assert(l && r);
		e->c[0] = e->c[1] = nullptr; l->p = r->p = nullptr; // disconnect
		l = l->meld_path_end();
		return {l, r};
	}
	// bring path to the top
	friend pt get_path(pt a, pt b) {
		assert(a->is_vert && b->is_vert);
		a->make_root(); b->expose();
		if (a == b) { assert(!b->p); return b; } // top path is single node
		assert(!b->p->p); return b->p; // b is at end of path
	}
	// root at rt, get subtree at n
	friend pt get_subtree(pt rt, pt n) {
		assert(rt->is_vert && n->is_vert);
		rt->make_root(); n->expose(); return n;
	}
	// easy: just expose one and then the other
	friend pt lca(pt a, pt b) {
		assert(a->is_vert && b->is_vert);
		assert(connected(a,b));
		a->expose(); return b->expose() ?: b;
	}
};
 
int main() {
	cin.tie(0)->sync_with_stdio(0);
	ints(N);
	V<top_tree_node> nodes(N);
	F0R(i,N) {
		pt n = &nodes[i];
		n->is_path = n->is_vert = true;
		n->update();
	}
	V<top_tree_node> edges(N-1);
	F0R(i,N-1) {
		ints(u,v,t); --u,--v;
		edges[i].own_parity = t;
		link(&edges[i],&nodes[u],&nodes[v]);
	}
	ints(M);
	rep(M) {
		ints(id); --id;
		edges[id].expose_edge();
		edges[id].own_parity ^= 1; edges[id].update();
		ps(edges[id].best_path);
	}
}