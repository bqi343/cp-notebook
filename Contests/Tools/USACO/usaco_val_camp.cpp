#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

#define GET_MACRO(_0, _1, _2, _3, NAME, ...) NAME

#define fail2(msg, line)                                                       \
  do {                                                                         \
    const char *_msg = (msg);                                                  \
    if (_msg) {                                                                \
      cout << "fail[line  " << line << "] " << _msg << endl;                   \
    } else {                                                                   \
      cout << "fail[line " << line << "]" << endl;                             \
    }                                                                          \
    exit(1);                                                                   \
  } while (0)

#define fail1(msg) fail2((msg), __LINE__)

#define fail0() fail2(NULL, __LINE__)

#define fail(...)                                                              \
  GET_MACRO(_0, _1, ##__VA_ARGS__, fail2, fail1, fail0)(__VA_ARGS__)

#define fassert3(cond, msg, line)                                              \
  do {                                                                         \
    if (!(cond)) {                                                             \
      fail((msg), (line));                                                     \
    }                                                                          \
  } while (0)

#define fassert2(cond, msg) fassert3(cond, msg, __LINE__)

#define fassert1(cond) fassert3(cond, NULL, __LINE__)

#define fassert(...)                                                           \
  GET_MACRO(_0, ##__VA_ARGS__, fassert3, fassert2, fassert1)(__VA_ARGS__)

struct input {
  input(FILE *f) : uch(-2), fin(f), sin(NULL) {}
  input(istream &in) : uch(-2), fin(NULL), sin(&in) {}

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

  void unget(int ch) { uch = ch; }

#define get_char() _get_char(__LINE__)

  char _get_char(int _line_) {
    int ch = get();
    if (ch == -1) {
      fail("expected char", _line_);
    } else if (ch != '\n' && (ch < 32 || 126 < ch)) {
      fail("expected printable ascii", _line_);
    }
    return ch;
  }

#define get_eof() _get_eof(__LINE__)

  void _get_eof(int _line_) { fassert(get() == -1, "expected eof", _line_); }

#define get_eol() _get_eol(__LINE__)

  void _get_eol(int _line_) { fassert(get() == '\n', "expected eol", _line_); }

#define get_space() _get_space(__LINE__)

  void _get_space(int _line_) {
    fassert(get() == ' ', "expected space", _line_);
  }

#define get_spaces() _get_spaces(__LINE__)

  void _get_spaces(int _line_) {
    int ch;
    _get_space(_line_);
    for (ch = get(); ch == ' '; ch = get())
      ;
    unget(ch);
  }

#define get_token() _get_token(__LINE__)

  string _get_token(int _line_) {
    int ch;
    string res;
    for (ch = get(); ch != -1 && ch != '\n' && ch != ' '; ch = get()) {
      res += (char)ch;
    }
    fassert(!res.empty(), "expected token", _line_);
    unget(ch);
    return res;
  }

#define get_int(mn, mx) _get_int((mn), (mx), __LINE__)

  long long _get_int(long long min, long long max, int _line_) {
    string tok = _get_token(_line_);
    long long res = atoll(tok.c_str());
    fassert(tok == to_string(res), "expected int", _line_);
    fassert(min <= res && res <= max, "int out of range", _line_);
    return res;
  }

#define get_line(mn, mx) _get_line((mn), (mx), __LINE__)

  string _get_line(int min_length, int max_length, int _line_) {
    int ch;
    string res;
    for (ch = get(); ch != -1 && ch != '\n'; ch = get()) {
      res += (char)ch;
      fassert((int)res.size() <= max_length, "line too long", _line_);
    }
    fassert(min_length <= (int)res.size(), "line too short", _line_);
    unget(ch);
    return res;
  }

  int uch;
  FILE *fin;
  istream *sin;
};

vector<int> get_test_case_batches(int argc, char **argv) {
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
  for (string ln; getline(fscorer_in, ln);) {
    if (ln.empty() || ln[0] == '#') {
      continue;
    }
    for (char &c : ln)
      if (c == ',')
        c = ' ';
    int sppos = ln.find(' ');
    if (sppos == string::npos) {
      continue;
    }
    istringstream sin(ln.substr(sppos + 1));

    for (string part; sin >> part;) {
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

#define gi(a, b) in.get_int(a, b)
#define gl(a, b) in.get_line(a, b)
#define gs() in.get_space()
#define ge() in.get_eol()
#define gt() in.get_token()

int main(int argc, char **argv) {
  int tc = atoi(argv[1]); // test id
  cerr << "TEST #: " << tc << endl;

  input in(cin);

  int N = in.get_int(1, 100000);
  in.get_eol();

  for (int i = 0; i < N; i++) {
    if (i)
      in.get_space();
    int c = in.get_int(0, N - 1);
  }
  in.get_eol();
  in.get_eof();

#ifndef LOCAL                // check batching
  const int NUM_BATCHES = 5; // modify
  vector<int> batches = get_test_case_batches(argc, argv);
  cerr << "BATCHES: {";
  for (int i = 0; i < (int)batches.size(); ++i) {
    if (i)
      cerr << ", ";
    fassert(0 <= batches[i] && batches[i] < NUM_BATCHES, "invalid batching");
    cerr << batches[i];
  }
  cerr << "}\n";
  for (int batch = 0; batch < NUM_BATCHES; ++batch) {
    bool contains_batch =
        find(begin(batches), end(batches), batch) != end(batches);
    bool calc_batch = 1;
    // modify calc_batch below to actually check whether test is in batch

    fassert(calc_batch == contains_batch, "wrong batching");
  }
#endif

  cerr << "VALIDATED!" << endl;
}