/**
 * Description: Evaluates mod expression with parentheses, or returns -1 if it is invalid
 * Source: Own
 * Verification: IPSC 2018 I1 
 */

namespace ExprParse {
	string expr;
	int ind; // reset to 0 every time

	int eval(char c, int x, int y) {
		switch(c) {
			case '+': return (x+y)%MOD;
			case '-': return (x-y+MOD)%MOD;
			case '*': return (ll)x*y%MOD;
			default: exit(5);
		}
	}

	int pri(char c) {
		switch (c) {
			case '+': return 0;
			case '-': return 0;
			case '*': return 1;
			default: exit(5);
		}
	}

	int process(vi& num, vector<char>& op) {
		if (sz(num) < 2 || sz(op) < 1) return -1;
		int y = num.bk; num.pop_back();
		int x = num.bk; num.pop_back();
		char c = op.bk; op.pop_back();
		num.pb(eval(c,x,y));
		return 0;
	}

	int finish(int& state, vi& num, vector<char>& op) {
		if (state != 0) return -1;
		while (sz(op)) {
			int t = process(num,op);
			if (t == -1) return -1;
		}
		if (sz(num) != 1) return -1;
		return num[0];
	}

	int eval(int cur = 0) {
		vi num;
		vector<char> op;
		
		int state = -1;
		while (ind < sz(expr)) {
			if (expr[ind] == ')') {
				ind ++;
				if (cur == 0) return -1;
				return finish(state,num,op);
			} else if (expr[ind] == '(') {
				ind ++;
				num.pb(eval(1)); if (num.bk == -1) return -1;
				if (state == 0) return -1;
				state = 0;
			} else if (isdigit(expr[ind])) {
				int val = 0;
				while (ind < sz(expr) && isdigit(expr[ind])) {
					val = (10LL*val+(expr[ind]-'0')) % MOD;
					ind ++;
				}
				num.pb(val);
				if (state == 0) return -1;
				state = 0;
			} else {
				while (sz(op) && pri(op.bk) >= pri(expr[ind])) {
					int t = process(num,op);
					if (t == -1) return -1;
				}
				op.pb(expr[ind]);
				if (state != 0) return -1;
				state = 1;
				ind ++;
			}
		}
		
		if (cur == 1) return -1; // parentheses don't match up
		if (ind != sz(expr)) return -1;
		return finish(state,num,op);
	}
}

using namespace ExprParse;
