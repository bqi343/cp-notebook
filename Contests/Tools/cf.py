# source: https://github.com/fjzzq2002/CFBooster
# download CF sample cases, parse input

from bs4 import BeautifulSoup
import urllib.request
from termcolor import colored # print in color + bold
import sys
import time
import getopt
import random
import string
import os
import shutil

def parseUrl(url):
	page = urllib.request.urlopen(url)
	return BeautifulSoup(page,'html.parser')

TESTING=False
padding='\t'
contest="1284"
cfPrefix="https://codeforces.com/contest/"
cfTemp = r"""#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld; 
typedef double db; 
typedef string str; 

typedef pair<int, int> pi;
typedef pair<ll,ll> pl; 
typedef pair<ld,ld> pd; 
#define mp make_pair
#define f first
#define s second

typedef vector<int> vi; 
typedef vector<ll> vl; 
typedef vector<ld> vd; 
typedef vector<str> vs; 
typedef vector<pi> vpi; 
typedef vector<pl> vpl; 
typedef vector<pd> vpd; 

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend() 
#define rsz resize
#define ins insert 
#define ft front() 
#define bk back() 
#define pf push_front 
#define pb push_back
#define eb emplace_back 
#define lb lower_bound 
#define ub upper_bound 

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353; // = (119<<23)+1
const int MX = 2e5+5; 
const ll INF = 1e18; 
const ld PI = 4*atan((ld)1); 
const int xd[4] = {0,1,0,-1}, yd[4] = {1,0,-1,0}; 

template<class T> bool ckmin(T& a, const T& b) { 
	return a > b ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; }
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, 
	rb_tree_tag, tree_order_statistics_node_update>; 
// change null_type for map
#define ook order_of_key
#define fbo find_by_order

void treeExample() {
	Tree<int> t, t2; t.insert(8);
	auto it = t.insert(10).f; assert(it == t.lb(9));
	assert(t.ook(10) == 1); assert(t.ook(11) == 2);
	assert(*t.fbo(0) == 8);
	t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}

namespace input {
	template<class T> void re(complex<T>& x);
	template<class T1, class T2> void re(pair<T1,T2>& p);
	template<class T> void re(vector<T>& a);
	template<class T, size_t SZ> void re(array<T,SZ>& a);

	template<class T> void re(T& x) { cin >> x; }
	void re(double& x) { string t; re(t); x = stod(t); }
	void re(ld& x) { string t; re(t); x = stold(t); }
	template<class T, class... Ts> void re(T& t, Ts&... ts) { 
		re(t); re(ts...); 
	}

	template<class T> void re(complex<T>& x) { T a,b; re(a,b); x = cd(a,b); }
	template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.f,p.s); }
	template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
	template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
}

using namespace input;

namespace output {
	void pr(int x) { cout << x; }
	void pr(long x) { cout << x; }
	void pr(ll x) { cout << x; }
	void pr(unsigned x) { cout << x; }
	void pr(unsigned long x) { cout << x; }
	void pr(unsigned long long x) { cout << x; }
	void pr(float x) { cout << x; }
	void pr(double x) { cout << x; }
	void pr(ld x) { cout << x; }
	void pr(char x) { cout << x; }
	void pr(const char* x) { cout << x; }
	void pr(const string& x) { cout << x; }
	void pr(bool x) { pr(x ? "true" : "false"); }
	template<class T> void pr(const complex<T>& x) { cout << x; }
	
	template<class T1, class T2> void pr(const pair<T1,T2>& x);
	template<class T> void pr(const T& x);
	
	template<class T, class... Ts> void pr(const T& t, const Ts&... ts) { 
		pr(t); pr(ts...); 
	}
	template<class T1, class T2> void pr(const pair<T1,T2>& x) { 
		pr("{",x.f,", ",x.s,"}"); 
	}
	template<class T> void pr(const T& x) { 
		pr("{"); // const iterator needed for vector<bool>
		bool fst = 1; for (const auto& a: x) pr(!fst?", ":"",a), fst = 0; 
		pr("}");
	}
	
	void ps() { pr("\n"); } // print w/ spaces
	template<class T, class... Ts> void ps(const T& t, const Ts&... ts) { 
		pr(t); if (sizeof...(ts)) pr(" "); ps(ts...); 
	}
	
	void pc() { pr("]\n"); } // debug w/ commas
	template<class T, class... Ts> void pc(const T& t, const Ts&... ts) { 
		pr(t); if (sizeof...(ts)) pr(", "); pc(ts...); 
	}
	#define dbg(x...) pr("[",#x,"] = ["), pc(x);
}

using namespace output;

namespace io {
	void setIn(string s) { freopen(s.c_str(),"r",stdin); }
	void setOut(string s) { freopen(s.c_str(),"w",stdout); }
	void setIO(string s = "") {
		ios_base::sync_with_stdio(0); cin.tie(0); // fast I/O
		// cin.exceptions(cin.failbit); // ex. throws exception when you try to read letter into int
		if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
	}
}

using namespace io;

struct mi {
	typedef decay<decltype(MOD)>::type T;
	T val; 
	explicit operator T() const { return val; }
	mi() { val = 0; }
	mi(ll v) { 
		val = (-MOD <= v && v <= MOD) ? v : v % MOD;
		if (val < 0) val += MOD;
	}
	friend bool operator==(const mi& a, const mi& b) { 
		return a.val == b.val; }
	friend bool operator!=(const mi& a, const mi& b) { 
		return !(a == b); }
	friend bool operator<(const mi& a, const mi& b) { 
		return a.val < b.val; }
	friend void re(mi& a) { ll x; re(x); a = mi(x); }
	friend void pr(const mi& a) { pr(a.val); }
	friend ostream& operator<<(ostream& os, const mi& a) { 
		return os << a.val; }
   
	mi operator-() const { return mi(-val); }
	mi& operator+=(const mi& m) { 
		if ((val += m.val) >= MOD) val -= MOD; 
		return *this; }
	mi& operator-=(const mi& m) { 
		if ((val -= m.val) < 0) val += MOD; 
		return *this; }
	mi& operator++() { return *this += 1; }
	mi& operator--() { return *this -= 1; }
	friend mi operator+(mi a, const mi& b) { return a += b; }
	friend mi operator-(mi a, const mi& b) { return a -= b; }

	mi& operator*=(const mi& m) { 
		val = (ll)val*m.val%MOD; return *this; }
	friend mi pow(mi a, ll p) {
		mi ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans;
	}
	friend mi inv(const mi& a) { 
		assert(!(a == 0)); return pow(a,MOD-2); }
	mi& operator/=(const mi& m) { return (*this) *= inv(m); }
	friend mi operator*(mi a, const mi& b) { return a *= b; }
	friend mi operator/(mi a, const mi& b) { return a /= b; }
};
typedef pair<mi,mi> pmi;
typedef vector<mi> vmi;
typedef vector<pmi> vpmi;
[VARS]
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
[CODES]
	// you should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?), slow multiset operations
	* do smth instead of nothing and stay organized
*/
"""

def cb(text,col): # color and bold text with color col
	return colored(text,col,attrs=['bold'])

def query_yes_no(question, default="yes"):
	"""Ask a yes/no question via raw_input() and return their answer.
	"question" is a string that is presented to the user.
	"default" is the presumed answer if the user just hits <Enter>.
		It must be "yes" (the default), "no" or None (meaning
		an answer is required of the user).
	The "answer" return value is True for "yes" or False for "no".
	"""
	valid = {"yes": True, "y": True, "ye": True,
			 "no": False, "n": False}
	if default is None:
		prompt = " [y/n] "
	elif default == "yes":
		prompt = " [Y/n] "
	elif default == "no":
		prompt = " [y/N] "
	else:
		raise ValueError("invalid default answer: '%s'" % default)

	while True:
		sys.stdout.write(question + prompt)
		choice = input().lower()
		if default is not None and choice == '':
			return valid[default]
		elif choice in valid:
			return valid[choice]
		else:
			sys.stdout.write("Please respond with 'yes' or 'no' "
							 "(or 'y' or 'n').\n")
def writeFile(fn,code):
	if os.path.exists(fn):
		if not query_yes_no(' '+fn+' already exists. Overwrite?',default="no"):
			print('skipped writing '+fn+'.')
			return
	os.makedirs(os.path.dirname(fn), exist_ok=True)
	print('writing to '+fn+' ... ',end='')
	f = open(fn,"w")
	f.write(code)
	f.close()
	print('succeeded.')

types = ['int','db','char','str']
arrTypes = ['vi','vd','vector<char>','vs']
def guess_type(si): #0: integer, 1: double, 2: char, 3: string
	try:
		int(si)
		return 0
	except:
		try:
			float(si)
			return 1
		except:
			try:
				str(si)
				if len(si) == 1:
					return 2
				return 3
			except:
				raise Exception("Unknown Type")

def getType(vType, isArr):
	if isArr:
		return arrTypes[vType]
	else:
		return types[vType]

probs={}
def lex(pn):
	isArr={} # for each variable, is it an array
	varType={}
	program=[]
	firstVar=''
	for inputs in probs[pn].find_all(class_='input-specification'):
		spec=''
		for v in inputs:
			text = v.get_text(separator="\n")
			if text != '':
				spec += text+' . '
		spec=spec.replace('\r',' . ')
		spec=spec.replace('\n',' . ')
		spec=spec.replace('...','\\cdots')
		spec=spec.replace('..','\\cdots')
		spec=spec.lower().replace(';',',').split('.')

		def clean(u):
			u=u.replace('-th ',' th ')
			while u.find(' th ')!=-1:
				c=u.find(' th ')
				u=u[:c]+u[c+3:]
				while c and u[c]==' ':
					c -= 1
				if c>=2 and u[c]=='$' and u[c-1]=='$' and u[c-2]=='$':
					c -= 2
					u=u[:c]+"##"+u[c:]
			u=u.replace('—',', i.e. ')
			u=u.replace('--',', i.e. ')
			u=u.replace(',',' , ')
			while u.find('  ')!=-1:
				u=u.replace('  ',' ')
			u=u.replace(', and ',' and ')
			u=u.split(',') # list of cleaned statements
			uu=[]
			for c_ in u:
				c=' '+c_+' '
				if c.find(' i.e')!=-1:
					c=c[:c.find(' i.e')]
				if c.find(' where')!=-1:
					c=c[:c.find(' where')]
				if c.find(' which')!=-1:
					c=c[:c.find(' which')]
				if c.find(' consisting of ')!=-1:
					c=c[:c.find(' consisting of ')]
				if c.find(' consisted of ')!=-1:
					c=c[:c.find(' consisted of ')]
				if c.find(' who')!=-1:
					c=c[:c.find(' who')]
				if c.find(' that')!=-1:
					c=c[:c.find(' that')]
				if c.find(' what')!=-1:
					c=c[:c.find(' what')]
				if c.find(' if')!=-1:
					c=c[:c.find(' if')]
				if c.find(' denoting')!=-1:
					c=c[:c.find(' denoting')]
				uu.append(c)
			u=','.join(uu)
			return u 

		def cleanParen(u):
			res = [] # deal with incorrect $ around parentheses such as 1279F
			for x in u.split(): 
				if '(' in x or ')' in x:
					x = x.replace('$$$','')
				res.append(x)
			u = ' '.join(res)

			openPar=0 # ignore stuff in parentheses
			ps=""
			for c in u:
				# print("HA",c)
				if c=='(':
					openPar+=1
				elif c==')':
					openPar-=1
				elif openPar==0:
					ps+=c
			return ps

		for u_ in spec:
			u=" "+u_+" "
			if (u.find(' line')!=-1 or u.find(' test ')!=-1 or u.find(' testcase')!=-1) and (u.find(' contain')!=-1 or u.find(' in ')!=-1):
				pass
			else:
				continue # irrelevant?
			u = clean(u)
			if TESTING:
				print()
				print("CLEANED",u)
			ps = cleanParen(u)
			if TESTING:
				print("PS",ps)
			ps=ps.split('$$$')
			pg=[]
			vis=set()
			counters=set()

			matrix = False
			stri = False
			for w in range(1,len(ps),2):
				if ps[w].find('=')==-1:
					psw=ps[w].split(',')
					for o in psw:
						if o.find('##')!=-1:
							counters.add(o.replace('##',''))
							continue
						if o.find('\\')!=-1:
							continue
						o=o.replace(' ','')
						if o.find('_')!=-1: # array elements a_1,a_2,...
							o=o[:o.find('_')]
							if o in vis:
								continue
							vis.add(o)
						if o=='':
							continue
						if len(pg)!=0 and o.isdigit():
							continue
						if w+1 < len(ps) and 'string' in ps[w+1] and 'line' in ps[w+1]:
							matrix = True
						if 'string' in ps[w-1] and (not o in isArr):
							stri = True
						pg.append(o)
			PG = []
			for x in pg:
				if not (x in counters):
					PG.append(x)
			pg = PG
			if len(pg)==0: # no vars
				continue
			isLoop=int(not(pg[0].isalpha() and not (pg[0] in isArr))) # has variable appeared before
			if isLoop and len(pg)==1:
				continue
			matrixFlag = False
			striFlag = False
			newVars = []
			for w in range(isLoop,len(pg)):
				if pg[w].isalpha() and not (pg[w] in isArr):
					if firstVar=='':
						firstVar=pg[w]
					isArr[pg[w]]=isLoop
					varType[pg[w]]=0
					newVars.append(pg[w])
				else:
					if matrix and len(pg) == 2 and isLoop:
						matrixFlag = True
					elif stri and not isLoop:
						striFlag = True
					else:
						return None # something bad happened :(
			if matrixFlag:
				program.append((pg[0],["gr"]))
				isArr["gr"] = True
				varType["gr"] = 3
				continue
			if striFlag:
				if len(newVars) != 1:
					return None
				program.append((None,newVars))
				continue
			if isLoop:
				lo=pg[0]
				while True:
					modi=0 
					for c in range(0,len(lo)-1):
						if lo[c].isdigit() and lo[c+1].isalpha():
							lo=lo[:c+1]+"*"+lo[c+1:]
							modi=1
							break
					if not modi:
						break
				program.append((lo,pg[1:]))
			else:
				program.append((None,pg[0:]))
	return (firstVar,isArr,varType,program)

def parse_i(p,inputs):
	l = lex(p)
	if l == None:
		return None

	#single case?
	firstVar,isArr,varType,program=l
	if TESTING:
		print()
		print("PROGRAM FOR PROBLEM",p,"IS",program)
		print()
	varList=list(isArr.keys())
	varList.sort(key=len,reverse=True)

	def readstr(u):
		if len(u)==0:
			raise Exception("underflow!")
		return u.pop()
	def simTest(u):
		for v in varList:
			if isArr[v]:
				globals()["SIM_"+v.upper()]=[]
			else:
				globals()["SIM_"+v.upper()]=None
		for pg in program:
			if pg[0]==None: # noloop
				for c in pg[1]:
					globals()["SIM_"+c.upper()]=readstr(u)
					varType[c]=max(varType[c],guess_type(globals()["SIM_"+c.upper()]))
			else:
				pg0=pg[0]
				for c in varList:
					pg0=pg0.replace(c,'_I_N_T_(SIM_'+c.upper()+')')
				pg0=pg0.replace('_I_N_T_','int')
				pg0=eval(pg0)
				if pg0<0:
					raise Exception("negative loop!")
				for s in range(pg0):
					for c in pg[1]:
						globals()["SIM_"+c.upper()].append(readstr(u))
						varType[c]=max(varType[c],guess_type(globals()["SIM_"+c.upper()][-1]))

	def filtRev(i):
		return list(filter(None, i.replace('\n',' ').replace('\r',' ').split(' ')))[::-1]
	failed=0

	try:
		for i in inputs:
			u = filtRev(i)
			simTest(u)
			if len(u) != 0:
				raise Exception("not yet read!")
	except:
		failed = 1
		pass
	if failed == 0:
		return (None,isArr,varType,program)

	if len(program)==0 or len(program[0][1])>1: # what's program[0][1]?
		# if len(program) > 0:
			# print("WHAT's program[0][1]?",program[0][1], program)
		return None
	for v in varList:
		varType[v]=0 #reset
	p0=program[0]
	program=program[1:]

	#multiple cases?
	failed=0
	try:
		for i in inputs:
			u=filtRev(i)
			pg=p0
			if pg[0]==None: # no loop
				for c in pg[1]:
					globals()["SIM_"+c.upper()]=readstr(u)
					varType[c]=max(varType[c],guess_type(globals()["SIM_"+c.upper()]))
			num_loop=int(globals()["SIM_"+firstVar.upper()])
			if num_loop<0:
				raise Exception("negative loop!")
			for _ in range(num_loop):
				simTest(u)
			if len(u)!=0:
				raise Exception("not yet read!")
	except:
		failed=1
		pass

	if failed==0:
		return (firstVar,isArr,varType,program)
	return None

def getCode(ps):
	firstVar,isArr,varType,program=ps
	ints=[]
	dbs=[]
	chrs = []
	strs=[]
	int_vecs=[]
	db_vecs=[]
	str_vecs=[]
	chr_vecs=[]
	for c in isArr.keys():
		if c == firstVar:
			continue
		if varType[c]==0:
			if isArr[c]:
				int_vecs.append(c)
			else:
				ints.append(c)
		elif varType[c]==1:
			if isArr[c]:
				db_vecs.append(c)
			else:
				dbs.append(c)
		elif varType[c]==2:
			if isArr[c]:
				chr_vecs.append(c)
			else:
				chrs.append(c)
		else:
			if isArr[c]:
				str_vecs.append(c)
			else:
				strs.append(c)
	for_var='_'
	if not 'i' in isArr.keys():
		for_var='i'

	DEFS="\n"
	CODES=""
	if True: 
		if len(ints)!=0:
			DEFS += "int "+",".join(ints)+';\n'
		if len(dbs)!=0:
			DEFS=DEFS+"db "+",".join(dbs)+';\n'
		if len(chrs)!=0:
			DEFS=DEFS+"char "+",".join(chrs)+';\n'
		if len(strs)!=0:
			DEFS=DEFS+"str "+",".join(strs)+';\n'
		if len(int_vecs)!=0:
			DEFS=DEFS+"vi "+",".join(int_vecs)+';\n'
		if len(db_vecs)!=0:
			DEFS=DEFS+"vd "+",".join(db_vecs)+';\n'
		if len(chr_vecs)!=0:
			DEFS=DEFS+"vector<char> "+",".join(chr_vecs)+';\n'
		if len(str_vecs)!=0:
			DEFS=DEFS+"vs "+",".join(str_vecs)+';\n'

	def parseVar(pad,pp):
		CODES=pad
		if pp[0]==None:
			CODES += "re("+','.join(pp[1])+');\n'
		else:
			for u in pp[1]:
				CODES += u+".rsz("+pp[0]+"); "
			if len(pp[1]) == 1:
				for u in pp[1]:
					CODES += f"re({u});"
				CODES += "\n";
			else:
				CODES += f"F0R({for_var},{pp[0]}) "+\
				"re("+','.join(list(map(lambda x:x+"["+for_var+"]",pp[1])))+");\n"
		return CODES 

	if firstVar==None:
		for pp in program:
			CODES += parseVar(padding,pp)
	else:
		CODES += padding+f"int {firstVar}; re({firstVar});\n"
		CODES += padding+f"FOR(tc,1,{firstVar}+1) {{\n"
		for pp in program:
			CODES += parseVar(padding+padding,pp)
		CODES += padding+"}\n"
	CODES = CODES[:-1]
	return DEFS,CODES

def interactive(p):
	global cppName
	DEFS = ""
	CODES = padding+"// INTERACTIVE"
	l = lex(p)
	if l != None:
		l = (None,)+l[1:]
		a,b = getCode(l)
		DEFS = a 
		CODES += "\n"+b

	# for d in probs[p].find_all(class_='problem-statement'):
	# 	for e in d:
	# 		if "Interaction" in e.text:
	# 			for f in e:
	# 				print("HA")
	# 				print(f.text)

	tt = probs[p].find(class_='output')
	strr=tt.find('pre').get_text(separator="\n").split('\n')

	isArr = {}
	varType = {}
	for x in strr:
		if len(x) == 0: continue
		X = x.split()
		c = X[0]
		if c == '?' or c == '!':
			if not (c in isArr):
				isArr[c] = False 
				varType[c] = 0
			if len(X) > 2:
				isArr[c] = True
			for i in range(1,len(X)):
				varType[c] = max(varType[c],guess_type(X[i]))

	def output(b):
		if b:
			return padding+'trav(t,a) pr(t,\' \')\n'+padding+'ps();\n'
		else:
			return padding+'ps(a);\n'

	if '?' in isArr:
		c = '?'
		DEFS += f'\nvoid query({getType(varType[c],isArr[c])} a) {{\n'
		DEFS += output(isArr[c])
		DEFS += padding+'re(?);\n'
		DEFS += padding+'return ?;\n'
		DEFS += '}\n'
	if '!' in isArr:
		c = '!'
		DEFS += f'\nvoid fin({getType(varType[c],isArr[c])} a) {{\n'
		DEFS += output(isArr[c])
		DEFS += padding+'exit(0);\n'
		DEFS += '}\n'

	print(isArr,varType)
	print(cb('interactive template for problem '+p+'.','blue'))
	code = cfTemp.replace('[CODES]',CODES).replace('[VARS]',DEFS)
	code = code.replace('pr("\\n");','cout << endl;')
	code = ''.join(code.rsplit(padding+'ios_base::sync_with_stdio(0); cin.tie(0);\n',1))
	writeFile(cppName,code)

def parse(p): # given input format make prog
	global cppName 
	cppName = p+"/"+p+".cpp"
	if 'interactive' in probs[p].text:
		interactive(p)
		return
	inputs=[] # sample inputs
	outputs=[]

	def clean(strr):
		strr=strr.replace('\r\n','\n')
		strr=strr.replace('\r','\n')
		while strr[0]=='\n':
			strr=strr[1:]
		if strr[-1]!='\n':
			strr=strr+'\n'
		return strr
	for tt in probs[p].find_all(class_='input'):
		strr=tt.find('pre').get_text(separator="\n")
		inputs.append(clean(strr))
	for tt in probs[p].find_all(class_='output'):
		strr=tt.find('pre').get_text(separator="\n")
		outputs.append(clean(strr))

	for w in range(len(inputs)):
		writeFile(p+"/"+str(w+1)+".in",inputs[w])
		writeFile(p+"/"+str(w+1)+".out",outputs[w])
	ps=parse_i(p,inputs)
	if ps==None:
		print(cb('could not parse input for problem '+p+'.','red'))
		code1=cfTemp.replace('[CODES]','').replace('[VARS]','')
		writeFile(cppName,code1)
		return
	else:
		print(cb('parsing input for problem '+p+'.','green'))
	DEFS,CODES = getCode(ps)
	code2=cfTemp.replace('[CODES]',CODES).replace('[VARS]',DEFS)
	writeFile(cppName,code2)

force = False 

def run():
	soup = parseUrl(cfPrefix+contest+'/problems')
	l=soup.find_all(class_='problemindexholder')
	for c in l:
		pname = c['problemindex']
		probs[pname]=c
	probNames=sorted(list(probs.keys()))
	if len(probNames) == 0:
		print('no problems found')
		return
	print('fetched full problemset, length='+str(len(soup.text)))
	print('found problems: '+','.join(probNames))
	print()
	if TESTING:
		for o in probNames:
			if os.path.exists(o+"/"):
				shutil.rmtree(o+"/") 
	else:
		for o in probNames:
			if os.path.exists(o+"/"):
				print(f"folder for {o} already exists, terminating.")
				return
	for o in probNames:
		parse(o)
		# if os.path.exists('grader.py'):
		# 	shutil.copyfile('grader.py',o+'/grader.py')
		print()
	print('all done.')

def main():
	try:
		global contest, TESTING
		opts, args = getopt.getopt(sys.argv[1:], "t")
		for option, value in opts:
			if option in ("-t"):
				TESTING = True
		contest = args[0]
		run()
	except (ValueError, getopt.GetoptError, IOError) as err:
		print(str(err), file=sys.stderr)
		# print("\t for help use --help", file=sys.stderr)
		return 2

if __name__ == "__main__":
	exit(main())