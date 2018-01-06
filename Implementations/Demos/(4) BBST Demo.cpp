/**
* Link: http://www.spoj.com/problems/ORDERSET/
* Description: Use with treap, splay tree
*/

int main() {
	int Q; cin >> Q;
	F0R(i,Q) {
	    char c; int d; cin >> c >> d;
		if (c == 'I') root = ins(root,d);
		else if (c == 'D') root = del(root,d);
		else if (c == 'K') {
			if (!root || root->sz < d) cout << "invalid\n";
			else cout << find_by_order(d) << "\n";
		} else cout << order_of_key(d) << "\n";
	}
}