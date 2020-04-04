filenames = ['Template.cpp', 'CppIO.h', '../number-theory (11.1)/Modular Arithmetic/Modular.h']
debug = """void DBG() { cerr << "]" << endl; }
template<class H, class... T> void DBG(H h, T... t) {
	cerr << h; if (sizeof...(t)) cerr << ", ";
	DBG(t...); }
#ifdef LOCAL // compile with -DLOCAL
	#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
	#define dbg(...) 42
#endif
"""

with open('TemplateShort.cpp', 'w') as outfile:
	with open('Template.cpp','r') as infile:
		for line in infile:
			if not line.endswith('//\n'):
				if "// 998244353" in line:
					line = line[:line.find("// 998244353")].rstrip()+"\n"
				# while len(line) >= 2 and line[-2] == ' ':
					# line = line[:-2]+'\n'
				if 'int main()' in line:
					outfile.write('mt19937 rng; // or mt19937_64\n\n')
					outfile.write(debug+"\n")
				outfile.write(line)
