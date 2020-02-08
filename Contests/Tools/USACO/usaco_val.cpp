#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <unordered_set>
 
using namespace std;
 
void fail(const char* msg = NULL) {
  if (msg) {
    cout << "fail: " << msg << endl;
  } else {
    cout << "fail" << endl;
  }
  exit(1);
}
 
void fassert(bool cond, const char* msg = NULL) {
  if (!cond) {
    fail(msg);
  }
}
 
struct input {
  input(FILE* f) : uch(-2), fin(f), sin(NULL) {
  }
  input(istream& in) : uch(-2), fin(NULL), sin(&in) {
  }
 
  int get() {
    if (uch != -2) {
      int ch = uch;
      uch = -2;
      return ch;
    } else if (fin) {
      return fgetc(fin);
    }
    return sin->get();
  }
 
  void unget(int ch) {
    uch = ch;
  }
 
  char get_char() {
    int ch = get();
    if (ch == -1) {
      fail("expected char");
    } else if (ch != '\n' && (ch < 32 || 126 < ch)) {
      fail("expected printable ascii");
    }
    return ch;
  }
 
  void get_eof() {
    fassert(get() == -1, "expected eof");
  }
 
  void get_eol() {
    fassert(get() == '\n', "expected eol");
  }
 
  void get_space() {
    fassert(get() == ' ', "expected space");
  }
 
  void get_spaces() {
    int ch;
    get_space();
    for (ch = get(); ch == ' '; ch = get());
    unget(ch);
  }
 
  string get_token() {
    int ch;
    string res;
    for (ch = get(); ch != -1 && ch != '\n' && ch != ' '; ch = get()) {
      res += (char)ch;
    }
    fassert(!res.empty(), "expected token");
    unget(ch);
    return res;
  }
 
  long long get_int(long long min, long long max) {
    string tok = get_token();
    long long res = atoll(tok.c_str());
    fassert(tok == to_string(res), "expected int");
    fassert(min <= res && res <= max, "int out of range");
    return res;
  }
 
  string get_line(int min_length, int max_length) {
    int ch;
    string res;
    for (ch = get(); ch != -1 && ch != '\n'; ch = get()) {
      res += (char)ch;
      fassert(res.size() <= max_length, "line too long");
    }
    fassert(min_length <= res.size(), "line too short");
    unget(ch);
    return res;
  }
 
  int uch;
  FILE* fin;
  istream* sin;
};

vector<int> get_test_case_batches(int argc, char** argv) {
  vector<int> res;
  if (argc < 3) {
    return res;
  }
  
  int test_id = atoi(argv[1]);
  if (test_id == 0) {
    return res;
  }
 
  int batch = 0;
  ifstream fscorer_in(argv[2]);
  for (string ln; getline(fscorer_in, ln); ) {
    if (ln.empty() || ln[0] == '#') {
      continue;
    }
    int sppos = ln.find(' ');
    if (sppos == string::npos) {
      continue;
    }
    istringstream sin(ln.substr(sppos + 1));
 
    for (string part; sin >> part; ) {
      int dash = part.find('-');
      if (dash == string::npos) {
        int num = atoi(part.c_str());
        if (num == test_id) {
          res.push_back(batch);
          break;
        }
      } else {
        int lo = atoi(part.substr(0, dash).c_str());
        int hi = atoi(part.substr(dash + 1).c_str());
        if (lo <= test_id && test_id <= hi) {
          res.push_back(batch);
          break;
        }
      }
    }
    batch++;
  }
  return res;
}
 
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pi;
typedef vector<int> vi; 
typedef vector<pi> vpi;

#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rsz resize
#define bk back()
#define pb push_back

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)

const int MOD = 1e9+7;

template<class T> bool ckmin(T& a, const T& b) { 
  return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
  return a < b ? a = b, 1 : 0; }

struct DSU {
  vi e; void init(int n) { e = vi(n,-1); }
  int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } 
  bool sameSet(int a, int b) { return get(a) == get(b); }
  int size(int x) { return -e[get(x)]; }
  bool unite(int x, int y) { // union-by-rank
    x = get(x), y = get(y); if (x == y) return 0;
    if (e[x] > e[y]) swap(x,y);
    e[x] += e[y]; e[y] = x;
    return 1;
  }
};
 
input in(cin);

#define gi(a,b) in.get_int(a,b)
#define gl(a,b) in.get_line(a,b)
#define gs() in.get_space()
#define ge() in.get_eol()
#define gt() in.get_token()

int main(int argc, char** argv) {
  // vector<int> batches = get_test_case_batches(argc, argv);
  // int batch = batches.empty() ? 1 : batches[0];
  // cerr << "Batch: " << batch << endl;
  int id = atoi(argv[1]); // test id
  cerr << "Test: " << id << endl;
  // write stuff here

  cerr << "OK" << endl;
  in.get_eof();
}