struct cmp {
    bool operator()(const int& l, const int& r) const {
        return l > r;
    }
};

struct hsh {
    size_t operator()(const pii& k) const {
        return hash<int>()(k.f)^(hash<int>()(k.s^293849182));
    }
};

set<int,cmp> s;
map<int,int,cmp> m;
unordered_map<pii,int,hsh> u;

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	
	cout << "---\nSET\n---\n";
	s.insert(1), s.insert(2);
	for (int i: s) cout << i << "\n";
	
	cout << "---\nMAP\n---\n";
	m[1] = 5, m[2] = 10;
	for (pii i: m) cout << i.f << " " << i.s << "\n";
}

// read!
// ll vs. int!
