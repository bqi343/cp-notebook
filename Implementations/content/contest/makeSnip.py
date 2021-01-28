## make snippets in sublime text based on .h files with capital first letters and some .cpp files

import os,shutil,sys

####### snippets

# <!-- Hello, ${1:this} is a ${2:snippet}.-->

pref = """
<snippet>
<content><![CDATA["""
mid="""
]]></content>
	<tabTrigger>"""
suf="""</tabTrigger>
	<scope>source.c++</scope>
	<!-- <description> demo description </description> -->
</snippet>"""


####### file paths

USACO="/Users/benq/Documents/USACO" # location of github repository
SUBL="/Users/benq/Library/Application Support/Sublime Text 3/Packages/User"
LOC=SUBL+"/algos/" # location where you want to place snippets

if os.path.exists(LOC): # remove LOC if it already exists
	shutil.rmtree(LOC)
os.makedirs(LOC) # make LOC

print("SNIPPETS LOCATION:\n\n",LOC.replace(' ','\\ '),'\n');

snippets = ""
temp = ""

def getPath(short):
	return LOC+short+".sublime-snippet"
def output(short,code): # write "code" to sublime snippet with trigger "short"
	with open(getPath(short),"w") as fout:
		fout.write(pref)
		fout.write(code)
		fout.write(mid)
		fout.write(short)
		fout.write(suf)

def getNorm(pre): # format code
	blank = False
	res = ""
	for a in pre.split('\n'):
		if not a.endswith('\n'): 
			a += '\n'
		if '#pragma once' in a:
			continue
		if len(a) <= 1:
			if not blank:
				res += a
			blank = True
		else:
			blank = False
			res += a.replace('$','\\$')
	while res[-1] == '\n': # remove trailing blank lines
		res = res[:-1]
	return res

def checkNorm(root,name): # read file into string and format it
	res = ""
	with open(os.path.join(root, name),"r") as fin:
		for a in fin:
			res += a
	return getNorm(res)

def tempLong(root,name):
	pre = checkNorm(root,name)
	res = ""
	main = False
	for a in pre.split('\n'):
		a += '\n'
		if "int main(" in a: 
			main = True
		if main and a == "\t\n": # start at blank line
			a = "\t$0\n"
		res += a
	return res

def tempShort(root,name):
	res = ""
	pre = checkNorm(root,name)
	main = False
	for a in pre.split('\n'):
		a += '\n'
		if "int main()" in a: 
			main = True
		if main and "cin.tie(0)" in a:
			ind = a.find("cin.tie(0)")
			res += a[:ind]+"\n"
			res += "\t"+a[ind:-2]+"\n"
			res += "\t$0\n}\n"
		else:
			res += a
	return res

modint_template = ""
modfact_template = ""

def process(root,name): # prefix, file name
	global snippets,temp,modint_template, modfact_template
	def shorten(name): # convert to snippet name
		short = name[:name.rfind('.')] # strip suffix
		if '(' in short:
			short = short[:short.find('(')] # remove parentheses
		short = short.rstrip()
		return short
	if name.endswith(".h"):
		if name[0].isupper():
			print("INCLUDED:",name)
			output(shorten(name),checkNorm(root,name))
		elif "old" not in name.lower() and "kactl" not in name.lower():
			print("NOT INCLUDED:",name)
	if name.endswith("ModInt.h"):
		modint_template = checkNorm(root,name)
	if name.endswith("ModFact.h"):
		modfact_template = checkNorm(root,name)
	if name.endswith(".cpp"):
		if "TemplateLong" in name:
			print("TEMPLATE_LONG:",name)
			temp = tempLong(root,name)
			output("Temp",temp)
		elif "TemplateShort" in name:
			print("TEMPLATE_SHORT:",name)
			output("TempShort",tempShort(root,name))
		elif "usaco" in name or "Template" in name:
			print("INCLUDED:",name)
			output(shorten(name).replace("Template","Temp"),tempLong(root,name))
		elif "template" not in name.lower() and "test" not in name.lower():
			print("NOT INCLUDED:",name)
	if name == "Snippets.md":
		snippets = os.path.join(root,name)
	if name == "stress.sh":
		global suf
		_suf = suf
		suf = suf.replace('.c++','.shell') # https://gist.github.com/J2TeaM/a54bafb082f90c0f20c9
		print("INCLUDED","stress.sh")
		output("stress",checkNorm(root,name))
		suf = _suf


for root, dirs, files in os.walk(USACO+"/Implementations",topdown=False):
	for name in files:
		process(root,name)
for root, dirs, files in os.walk(USACO+"/Contests/Tools",topdown=False):
	for name in files:
		process(root,name)

assert len(snippets) > 0, "snippets not found"
assert len(temp) > 0, "long template not found"

codes = []
names = []
with open(snippets,"r") as fin:
	lines = list(fin)
	flag = 0
	for i in range(len(lines)):
		if "```" in lines[i]: # entered or exited code
			flag ^= 1
			if flag == 1:
				codes.append("")
				ind = i-2
				while not lines[ind].startswith('##'):
					ind -= 1
				names.append(lines[ind][3:].strip())
		elif flag == 1:
			codes[-1] += lines[i]

ST = temp.find("int main()")
EN = ST
while temp[EN] != '}':
	EN += 1
EN += 2

for i in range(len(names)):
	code = codes[i]
	if names[i] == "TC":
		# print("NAME",names[i])
		code = temp[:ST]+modint_template+"\n\n"+modfact_template+"\n\n"+code+temp[EN:]
	elif "FHC" in names[i] or "GCJ" in names[i] or "TS" == names[i]:
		code = temp[:ST]+code+temp[EN:]
	output(names[i],code)