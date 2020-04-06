# based off grader.sh, kactl preprocessor

import subprocess # run terminal stuff
import os # check if file exists
import sys # to exit program
import getopt # command line
from termcolor import colored # print in color + bold

IN = "$.in" # $ is replaced with file number
OUT = "$.out"
TL = 4
EPS = 1e-6
exts = [".cpp",".cc",".java",".py",".py3"]
cppc = "g++-9 -std=c++11 -O2 -Wl,-stack_size -Wl,0x10000000 -w -o $ #" 
# -w = suppress warnings 
javac = "javac #"

sep = '-'*50
pad = '\t'
checker = None
debug = False

def cb(text,col="grey"): # color and bold text with color col
	return colored(text,col,attrs=['bold'])
def isfloat(value): 
	"""
	check if value can be float, returns boolean
	"""
	try:
		float(value)
		return True
	except ValueError:
		return False
def doubleError(a,b): # min of absolute and relative error for two doubles
	res = abs(a-b)
	if a != 0:
		res = min(res,abs(1-b/a))
	return res
def splitWhite(output): # split output by whitespace
	assert os.path.isfile(output), f'File "{output}" does not exist, cannot splitWhite'
	output = list(open(output))
	res = [i.split() for i in output]
	return [i for i in res if len(i) > 0] # ignores empty lines

def compile(file): 
	"""
	compiles file, returns True if successful
	"""
	coms = {}
	coms[".cpp"] = coms[".cc"] = cppc
	coms[".java"] = javac
	coms[".py"] = coms[".py3"] = ""

	name = file[:file.rfind('.')] # stuff before extension
	ext = file[file.rfind('.'):]
	if ext not in coms:
		print(cb(f" * Compilation failed, extension {ext} not recognized","red"))
		return False
	if coms[ext] == "":
		print(cb(" * No compilation for python."))
		return True
	com = coms[ext].replace('$',name).replace('#',file)
	print(cb(f" * Compiling {file}","cyan"))
	if subprocess.call(com,shell=True) != 0:
		print(cb(" * Compilation failed","red"))
		return False
	else:
		print(cb(" * Compilation successful!","green"))
		return True

def run(file,inputF): 
	"""
	returns tuple (output file name, exit code, time)
	"""
	coms = {}
	coms[".cpp"] = coms[".cc"] = "./$"
	coms[".java"] = "java $"
	coms[".py"] = coms[".py3"] = "python3 #"

	name = file[:file.rfind('.')] # stuff before extension
	ext = file[file.rfind('.'):]
	assert ext in coms, f"cannot run file with extension {ext}"

	outputF = f"{name}.out"
	runCom = coms[ext].replace('$',name).replace('#',file)
	runCom += f" < {inputF} > {outputF}"
	try:
		runCom = f"(time -p {runCom}) 2> .time_info;"
		ret = subprocess.call(runCom,shell=True,timeout=TL+0.5)
		if ret != 0:
			return outputF,ret,-1
		def timeInfo():
			# 'cat .time_info | grep real | cut -d " " -f 2'
			# -d sets delimiter
			# -f 2 gets second field
			proc = subprocess.Popen("cat .time_info", stdout=subprocess.PIPE, shell=True)
			res = proc.communicate()[0].rstrip().decode("utf-8").split('\n')
			real = float(res[0][len("real "):])
			user = float(res[1][len("user "):])
			sys = float(res[2][len("sys "):])
			return real,user,sys
		real,user,sys = timeInfo()
		return outputF,ret,user+sys
	except subprocess.TimeoutExpired as e:
		# template = "An exception of type {0} occurred. Arguments:\n{1!r}"
		# message = template.format(type(e).__name__, e.args)
		# print(message)
		return "",152,TL

def check(o0,o1): 
	"""
	check if output files o0,o1 match
	returns (verdict, message)
	"""
	assert o0 != o1
	O0,O1 = splitWhite(o0),splitWhite(o1)
	if len(O0) != len(O1):
		return "W", f"{o0} has {len(O0)} lines but {o1} has {len(O1)} lines"
	for i in range(len(O0)):
		if len(O0[i]) != len(O1[i]):
			return "W", f"{i+1}-th line of {o0} has {len(O0[i])} tokens but {o1} has {len(O1[i])} tokens"
		for j in range(len(O0[i])):
			z0,z1 = O0[i][j],O1[i][j]
			if z0 == z1:
				continue
			if isfloat(z0) and '.' in z0:
				if not isfloat(z1):
					return "W", f"{i+1}-th elements don't match, expected {z0} but found {z1}"
				e = doubleError(float(z0),float(z1))
				if e > EPS:
					return "W", f"{i+1}-th floats differ, error={e}. Expected {z0} but found {z1}."
				continue
			return "W", f"{i}-th elements don't match, expected {z0} but found {z1}"
	return "A", "OK"

def interpretExit(e): 
	"""
	interpret exit code
	returns (verdict, message)
	"""
	assert e != 0, "e should not be 0"
	if e == 139:
		return "R", "runtime error"
	if e == 152:
		return "T", "time limit exceeded"
	return "R", f"exit code {e}"

def checkTL(res,t):
	if float(t) > TL: # verdict A -> AT
		res = (res[0]+"T",)+res[1:]
	return res

def runChecker(inputF,outputF,o):
	"""
	returns verdict, message
	"""
	assert checker.endswith(".py") or checker.endswith(".py3")
	res = subprocess.call(f"python3 {checker} {inputF} {outputF} {o}",shell=True)
	if res == 0:
		return "A", "OK"
	return "W", "checker failed with exit code "+str(res)

def grade(prog,inputF,outputF): # verdict, message, time, report
	global TL,grader
	report = ""
	if debug:
		def getText(file):
			res = ""
			for line in open(file):
				res += pad+line
			if res == "":
				res += pad+"(empty file)\n"
			return res
		report += pad+sep+"\n"
		report += pad+"INPUT:\n"
		report += pad+sep+"\n"
		report += getText(inputF)
		report += pad+sep+"\n"
		report += pad+"CORRECT OUTPUT:\n"
		report += pad+sep+"\n"
		report += getText(outputF)
		report += pad+sep+"\n"
	o,e,t = run(prog,inputF)
	if e != 0:
		return interpretExit(e)+(t,report)
	if debug:
		report += pad+"YOUR OUTPUT:\n"
		report += pad+sep+"\n"
		for line in open(o):
			report += pad+line
		if not report.endswith("\n"):
			report += "\n"
		report += pad+sep+"\n"
	if checker:
		res = runChecker(inputF,outputF,o)+(t,report)
	else:
		res = check(outputF,o)+(t,report)
	return checkTL(res,t)

def getOutput(prog,inputF): # verdict, message, time
	o,e,t = run(prog,inputF)
	if e != 0:
		return interpret(e)+(t,)
	res = 'A',splitWhite(o),t
	return checkTL(res,t)

def compare(f0,f1,inputF): # verdict, message, time
	o0,e0,t0 = run(f0,inputF)
	o1,e1,t1 = run(f1,inputF)
	if e0 != 0:
		return "E", "supposedly correct code gave "+interpretExit(e0)[1], (t0,)
	if e1 != 0:
		return interpretExit(e1)+(t1,)
	if checker:
		return runChecker(inputF,o0,o1)+((t0,t1),)
	return check(o0,o1)+((t0,t1),)

def output(i,res,message,t):
	print(f" * Test {i}: ",end="")
	if res == 'A':
		print(cb(res,"green"),end="")
	else:
		print(cb(res,"red"),end="")
	print(f" - {message}",end="")
	# print("??",t)
	if ('A' in res) or ('W' in res):
		if isinstance(t,float):
			T = "{:.2f}".format(t)
			print(f" [{T}]",end="")
		else:
			T0,T1 = "{:.2f}".format(t[0]), "{:.2f}".format(t[1])
			print(f" [{T0}, {T1}]",end="")
	print()

def outputRes(correct,total):
	if total == 0:
		print(cb("ERROR:")+" No tests found! D:")
	else:
		print(cb("RESULT:","blue"),correct,"/",total)
		if correct == total:
			print("Good job! :D")

def getTests(): # $ can be any sequence of digits
	assert IN.count('$') == 1, "IN is invalid"
	ind = IN.find('$')
	after = len(IN)-1-ind
	L = []
	LL = []
	files = [f for f in os.listdir('.') if os.path.isfile(f)]
	def makeKey(x):
		x = x[:x.rfind('.')]
		return [len(x),x]
	for file in files:
		if len(file) >= len(IN):
			if IN[:ind] != file[:ind]: 
				continue 
			if after != 0:
				if IN[-after:] != file[-after:]:
					continue
			if after != 0:
				dig = file[ind:-after]
			else:
				dig = file[ind:]
			if dig.isdigit():
				L.append(dig)
				LL.append(file)
	L.sort(key=lambda x: [len(x),x]);
	LL.sort(key=makeKey)
	if debug:
		if len(LL) == 0:
			print("NO TESTS FOUND")
		else:
			print("FOUND TESTS",end='')
			fst = True
			for name in LL:
				if fst:
					print(' ',end='')
					fst = False
				else:
					print(', ',end='')
				print(name,end='')
			print()
	return L 

def GETOUTPUT(f):
	print(cb(f"GET OUTPUT FOR {f}","blue"))
	if not compile(f):
		return
	print(cb("RUNNING TESTS","blue"))
	total,correct = 0,0
	for label in getTests():
		inputF = IN.replace('$',label)
		res,message,t = getOutput(f,inputF)
		output(label,res,message,t)
		total += 1
		if res == 'A':
			correct += 1
	print()
	outputRes(correct,total)

def GRADE(f):
	print(cb(f"GRADING {f}","blue"))
	if not compile(f):
		return
	print(cb("RUNNING TESTS","blue"))
	total,correct = 0,0
	for label in getTests():
		inputF = IN.replace('$',label)
		outputF = OUT.replace('$',label)
		if not os.path.isfile(outputF):
			print(cb("ERROR:")+" Output file '"+outputF+"' missing!")
			sys.exit(0)
		res,message,t,report = grade(f,inputF,outputF)
		output(label,res,message,t)
		if 'W' in res and debug:
			print('\n'+report)
		total += 1
		if res == 'A':
			correct += 1
	print()
	outputRes(correct,total)

def COMPARE(f0,f1,wrong):
	print(cb(f"COMPARING CORRECT {f0} AGAINST {f1}","blue"))
	print()
	if not compile(f0) or not compile(f1):
		return
	print(cb("RUNNING TESTS","blue"))
	total,correct = 0,0
	for label in getTests():
		inputF = IN.replace('$',label)
		res,message,t = compare(f0,f1,inputF)
		if not wrong or res != 'A':
			output(label,res,message,t)
		total += 1
		if res == 'A':
			correct += 1
	print()
	outputRes(correct,total)

def progs():
	res = []
	for root, dirs, files in os.walk("."):
		for file in files:
			for ext in exts:
				if file.endswith(ext):
					res.append(file)
	return res

def main():
	global debug,checker,cppc,TL,IN,OUT
	def makeFile(file): # add extension to file if doesn't exist
		if file[file.rfind('.'):] not in exts:
			done = False
			for t in exts: 
				if os.path.isfile(file+t):
					file += t
					done = True
					print(cb(" * file extension "+t+" determined","green"))
					break
			assert done, "no extension found"
		assert os.path.isfile(file), "file not found"
		return file
	try:
		correct = None
		start = None
		output = False
		grade = False
		opts, args = getopt.getopt(sys.argv[1:], "ohc:t:gs:dC:I:O:", ["output","help","correct","time","grade","start","debug","checker","infile","outfile"])
		print(cb("STARTING PROGRAM","blue"))
		for option, value in opts:
			if option in ("-h", "--help"):
				print("This is the help section for "+cb("grader.py")+".")
				print()
				print("Available options are:")
				print("\t -h --help: display help")
				print("\t -t --time: set time limit")
				print("\t -d --debug: give input/output for WAs")
				print("\t -s --start: set starting submission (for grade)")
				print("\t -C --checker: provide python checker")
				print("\t -I --infile: format of input file names ($ will be replaced by the testcase number)")
				print("\t -O --outfile: format of output file names")
				print()
				print("Available commands are:")
				print("\t 'python3 grader.py A': test if A.cpp produces correct output file for every input file")
				print("\t 'python3 grader.py -o A': display output of A.cpp for every input file")
				print("\t 'python3 grader.py -c B A': compare A.cpp against correct B.cpp for every input file")
				print("\t 'python3 grader.py -g A': compare A.cpp against all submissions in folder")
				return
			if option in ("-I", "--infile"):
				IN = str(value)
				print(cb(f" * Input file format set to '{IN}'"))
			if option in ("-O", "--outfile"):
				OUT = str(value)
				print(cb(f" * Output file format set to '{OUT}'"))
			if option in ("-t", "--time"):
				TL = float(value)
				print(cb(f" * Time limit set to {TL} seconds."))
			if option in ("-c", "--correct"):
				correct = makeFile(value) 
			if option in ("-o","--output"):
				output = True
			if option in ("-g","--grade"):
				grade = True
			if option in ("-d","--debug"):
				debug = True
				cppc = cppc.replace("-w","-Wall -Wextra")
			if option in ("-s","--start"):
				start = value
			if option in ("-C","--checker"):
				checker = makeFile(value)
				assert compile(checker), "checker compilation failed"
				print(cb(f" * Checker succesfully set to {checker}"))
		assert len(args) == 1, "must have exactly one argument"
		cnt = 0
		if grade:
			cnt += 1
		if correct:
			cnt += 1
		if output:
			cnt += 1
		assert cnt <= 1, "too many options"
		file = makeFile(args[0])
		if grade:
			subs = []
			for filename in progs(): # files starting with numbers
				#if len(filename) >= 8 and filename[0:8].isdigit():
				#	subs.append(filename)
				if len(filename) >= 9 and filename[1:9].isdigit() and filename[0] == 'j':
					subs.append(filename)
			subs.sort()
			for sub in subs:
				if start and sub < start:
					continue
				COMPARE(file,sub,True)
		elif correct:
			correct = makeFile(correct)
			assert correct != file, "can't compare same prog against itself"
			COMPARE(correct,file,False)
		elif output:
			GETOUTPUT(file)
		else:
			GRADE(file)
	except (ValueError, getopt.GetoptError, IOError) as err:
		print(str(err), file=sys.stderr)
		print("\t for help use --help", file=sys.stderr)
		return 2

if __name__ == "__main__":
	exit(main())
