# source: https://github.com/fjzzq2002/CFBooster
# download CF sample cases, parse input
# use at your own risk :P

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
from datetime import datetime, timezone
import pytz

def parseUrl(url):
	page = urllib.request.urlopen(url)
	return BeautifulSoup(page,'html.parser')

TESTING=False
DEFAULT=False
REMOVE=False
padding='\t'
contest="1284"
probs = ""
cfPrefix="https://codeforces.com/contest/"
cfTemp=""

def cb(text,col="grey"): # color and bold text with color col
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
		# print("??",l)
		a,b = getCode(l)
		print("WUT",a,b)
		DEFS = "\n"+a
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

	if '?' in isArr:
		def outputQ(b):
			if b:
				return padding+'pr("? ",sz(a));\n'+padding+'trav(t,a) pr(" ",t);\n'+padding+'ps();\n'
			else:
				return padding+'ps("?",a);\n'
		c = '?'
		DEFS += f'str query({getType(varType[c],isArr[c])} a) {{\n'
		DEFS += outputQ(isArr[c])
		DEFS += padding+'str r; re(r);\n'
		DEFS += padding+'// calculate result locally?\n'
		DEFS += padding+'return r;\n'
		DEFS += '}\n'
	if '!' in isArr:
		def outputA(b):
			if b:
				return padding+'pr("! ",sz(a));\n'+padding+'trav(t,a) pr(" ",t);\n'+padding+'ps();\n'
			else:
				return padding+'ps("!",a);\n'
		c = '!'
		DEFS += f'\nvoid fin({getType(varType[c],isArr[c])} a) {{\n'
		DEFS += outputA(isArr[c])
		DEFS += padding+'exit(0);\n'
		DEFS += '}\n'

	if len(DEFS) > 0:
		DEFS = DEFS[1:]
	if TESTING:
		print("ISARR",isArr,"VARTYPE",varType)
	print(cb('interactive template for problem '+p+'.','blue'))
	code = cfTemp.replace('[CODES]',CODES).replace('[VARS]',DEFS)
	code = code.replace('pr("\\n");','cout << endl;')
	code = ''.join(code.rsplit(padding+'setIO();\n',1))
	writeFile(cppName,code)

def writeDefault():
	code1=cfTemp.replace('[CODES]','\t').replace('[VARS]','')
	writeFile(cppName,code1)

def parse(p): # given input format make prog
	global cppName 
	cppName = p+"/"+p+".cpp"
	if DEFAULT:
		writeDefault()
		for w in range(1):
			writeFile(p+"/"+str(w+1)+".in","")
			writeFile(p+"/"+str(w+1)+".out","")
		return
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
		writeDefault()
		return
	else:
		print(cb('parsing input for problem '+p+'.','green'))
	DEFS,CODES = getCode(ps)
	code2=cfTemp.replace('[CODES]',CODES).replace('[VARS]',DEFS)
	writeFile(cppName,code2)

force = False 

def run():
	global cfTemp
	tname = "/Users/benq/Documents/USACO/Implementations/content/contest/TemplateLong.cpp"
	assert os.path.exists(tname), 'template doesn\'t exist'
	def insBefore(a,b):
		global cfTemp
		ind = cfTemp.index(a)
		if cfTemp[ind-1] == '\n' and cfTemp[ind-2] == '\n':
			ind -= 1
		else:
			b += '\n'
		cfTemp = cfTemp[:ind]+b+cfTemp[ind:]

	with open(tname,'r') as tempFile:
		cfTemp = tempFile.read()
		ind = cfTemp.find("setIO();")+len("setIO();\n")
		cfTemp = cfTemp[:ind]+cfTemp[ind+2:] # remove \t\n
		insBefore("int main()","[VARS]")
		insBefore("\t// you should actually","[CODES]")
		# print(cfTemp)
		# sys.exit(0)
	probNames = []
	if DEFAULT:
		for c in probs:
			if c.isdigit():
				assert len(probNames) > 0, 'nothing before number'
				assert len(probNames[-1]) == 1, 'multiple numbers'
				pre = probNames[-1]
				probNames[-1] += '1'
				for j in range(2,int(c)+1):
					probNames.append(pre)
					probNames[-1] += str(j)
			else:
				probNames.append(c)
		if TESTING:
			print("DEFAULT PROBNAMES",probNames)
		# sys.exit(0)
	else:
		soup = parseUrl(cfPrefix+contest+'/problems')
		l = soup.find_all(class_='problemindexholder')
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
	if REMOVE:
		rem = False
		for o in probNames:
			if os.path.exists(o+"/"):
				rem = True
				print("removed folder "+o)
				shutil.rmtree(o+"/") 
		if rem:
			print()
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

def printTable(table):
	maxLen = []
	for i in range(len(table)):
		if len(table[i]) != len(table[0]):
			# print("OOPS",i,len(table[0]),len(table[i]))
			print(table[0],table[i])
			sys.exit(0)
	for i in range(len(table[0])):
		maxLen.append(0)
		for j in range(len(table)):
			maxLen[-1] = max(maxLen[-1],len(table[j][i]))

	for j in range(len(table)):
		print('|',end='')
		for i in range(len(table[0])):
			print(table[j][i].center(maxLen[i]+2),end='')
			print('|',end='')
		print()
		if j == 0:
			print('|',end='')
			for i in range(len(table[0])):
				print('-'*(maxLen[i]+2),end='')
				print('|',end='')
			print()
	print()

def getStats():
	print(cb(f"STATS FOR CONTEST {contest}:\n"))
	page = parseUrl(cfPrefix+contest)
	# print(page)
	probs = page.find_all(class_="problems")
	name = []
	mem = []
	for a in probs:
		for b in a.find_all("td"):
			for c in b.find_all("div"):
				if "standard" in c.text and "s" in c.text:
					name.append(c.find_all('a')[0].text)
					text = c.text.rstrip()
					pos = -11
					assert text[pos].isdigit()
					while text[pos-1].isdigit():
						pos -= 1
					mem.append(text[pos:])
					break
	totTable = [['#','Problem','Limits','Solves']]
	solves = []
	co = 0
	for a in page.find_all(title="Participants solved the problem"):
		label = a['href'][-1]
		text = a.text
		solves.append(text[text.find('x')+1:])
		if len(solves[-1]) == 0:
			solves[-1] = "0"
		totTable.append([label,name[co],mem[co],solves[co]])
		co += 1
	printTable(totTable)
	sortSolves = []
	for _a in solves:
		a = int(_a)
		if a > 0:
			sortSolves.append(a)
	sortSolves.sort()
	for j in range(1,len(totTable)):
		label = totTable[j][0]
		link = f"https://codeforces.com/contest/{contest}/status/{label}?order=BY_ARRIVED_ASC"
		#print(link)
		s = int(solves[j-1])
		if s != 0 and (s <= 10 or s <= sortSolves[min(1,len(sortSolves)-1)]): # print submissions for that problem
			print("PROBLEM",label,"SOLVES:")
			print()
			page = parseUrl(link)
			# print("WUT",page)
			table = [["When","Who","Lang","Time","Mem"]]
			for t in page.find_all("tr"):
				if t.has_attr("data-a"):
					lang = ""
					for z in t.find_all("td"):
						if len(z.attrs) == 0:
							lang = z.text.strip()
					exeTime = t.find(class_="time-consumed-cell").text.strip()
					mem = t.find(class_="memory-consumed-cell").text.strip()
					who = ""
					sub = ""
					for z in t.find_all(class_="rated-user"):
						# print(z['href'][len("/profile/"):])
						who = z['title']
					for z in t.find_all(class_="format-time"):
						sub = z.text
					subTime = pytz.timezone("Europe/Moscow").localize(datetime.strptime(sub,"%b/%d/%Y %H:%M"))
					# https://stackoverflow.com/questions/6410971/python-datetime-object-show-wrong-timezone-offset
					st = subTime.astimezone(pytz.timezone('US/Eastern'))
					en = datetime.now(pytz.timezone('US/Eastern'))
					def make2(x):
						x = str(x)
						while len(x) < 2: 
							x = "0"+x 
						return x
					def formTime(x):
						x = int(x)
						if x < 60:
							return str(x)+" min"
						if x < 24*60:
							return str(x//60)+":"+make2(str(x%60))
						return str(x//1440)+" days"
						# mn = str(x%60)
						# while len(mn) < 2:
						# 	mn = "0"+mn
						# return str(x//60)+":"+mn
						# if x < 60:
						# 	return ""
					when = formTime((en-st).total_seconds()/60)+" ago"
					table.append([when,who,lang,exeTime,mem])
					# print(current_time)
			while len(table) > 7:
				table.pop()
			if len(table) == 7:
				table[-1] = ["..." for i in range(len(table[-1]))]
			printTable(table)

def getStands():
	print(cb(f"STANDINGS FOR CONTEST {contest}:\n"))
	link = f"https://codeforces.com/contest/{contest}/standings"
	page = parseUrl(link)
	fst = page.find('table').find('tr')
	standings = [[]]
	for b in fst.find_all(recursive=False):
		if len(b.find_all('a')):
			standings[0].append(b.find_all('a')[0].text)
		else:
			standings[0].append(b.text)
	for a in page.find_all('tr'):
		if 'participantid' in a.attrs:
			# print("WHOOPS",a)
			standings.append([])
			cells = a.find_all('td')
			for j in cells:
				def simp(x):
					x = x.strip().replace(" ","").replace("\r",", ").replace("\n","")
					x = x.replace("\xa0"," ").replace(" : ",":")
					return x
				standings[-1].append(simp(j.text))
			while len(standings[-1]) > len(standings[0]):
				standings[-1].pop()
			assert len(standings[-1]) == len(standings[0])
			if len(standings) >= 12:
				if '+' not in standings[-1][3]:
					standings.pop()
				elif len(standings) == 12:
					standings.insert(-1,["..."]*len(standings[0]))
	# for t in standings:
		# print(t)
	printTable(standings)


def main():
	try:
		global contest, probs, TESTING, DEFAULT, REMOVE
		opts, args = getopt.getopt(sys.argv[1:], "tdhrsS",["test","default","help","rem","stats","stands"])
		STATS = False
		STANDS = False
		for option, value in opts:
			if option in ("-h","--help"):
				print("This is the help section for "+cb("cf.py")+".")
				print()
				print("Available options are:")
				print("\t -h --help: display help")
				print("\t -r --rem: remove folders if they exist, does not need argument")
				print("\t -t --test: displays debug information, enables -r")
				print("\t -d --default: initialize folders given names")
				print("\t -s --stats: print solve stats and info about first solves")
				print("\t -S --stands: print top 10 + hacks")
				print()
				print("Available commands are:")
				print("\t 'python3 cf.py 1295': parse contest 1295")
				print("\t 'python3 cf.py -d AB2': initialize folders for problems A, B1, B2")
				return
			if option in ("-r","--rem"):
				REMOVE = True
			if option in ("-t","--test"):
				TESTING = True
				REMOVE = True
			if option in ("-d","--default"):
				DEFAULT = True
			if option in ("-s","--stats"):
				STATS = True
			if option in ("-S","--stands"):
				STANDS = True
		if len(args) == 0:
			assert REMOVE
			for o in "ABCDEFGHIJ":
				if os.path.exists(o+"/"):
					rem = True
					print("removed folder "+o)
					shutil.rmtree(o+"/") 
			if rem:
				print()
		elif STATS:
			contest = args[0]
			getStats()
		elif STANDS:
			contest = args[0]
			getStands()
		else:
			if DEFAULT:
				probs = args[0]
			else:
				contest = args[0]
			run()
	except (ValueError, getopt.GetoptError, IOError) as err:
		print(str(err), file=sys.stderr)
		print("\t for help use --help", file=sys.stderr)
		return 2

if __name__ == "__main__":
	exit(main())