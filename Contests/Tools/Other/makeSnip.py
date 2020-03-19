## make snippets in sublime text based on .h files with capital first letters
import os,shutil,sys

####### CONSTANTS
USACO="/Users/benq/Documents/USACO"
SUBL="/Users/benq/Library/Application Support/Sublime Text 3/Packages/User"
LOC=SUBL+"/algos/"

if os.path.exists(LOC): # remove loc if it already exists
	shutil.rmtree(LOC)
os.makedirs(LOC)

pref = """
<snippet>
<!-- Hello, ${1:this} is a ${2:snippet}.-->
<content><![CDATA["""
mid="""
]]></content>
	<tabTrigger>"""
suf="""</tabTrigger>
	<scope>source.c++</scope>
	<!-- <description> demo description </description> -->
</snippet>"""

print("SNIPPETS LOCATION:\n\n",LOC.replace(' ','\\ '),'\n');

snippets = ""
temp = ""

def getPath(short):
	return LOC+short+".sublime-snippet"
def output(short,code):
	#print("AH",short,code)
	#sys.exit(0)

	with open(getPath(short),"w") as fout:
		fout.write(pref)
		fout.write(code)
		fout.write(mid)
		fout.write(short)
		fout.write(suf)

def getNorm(pre):
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
	while pre[-1] == '\n':
		pre = pre[:-1]
	return res

def checkNorm(root,name):
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
		if "int main()" in a: 
			main = True
		if main and a == "\t\n":
			a = "\t$0\n"
		res += a
	# print("HUH",root,name,pre,res)
	# sys.exit(0)
	return res

def tempShort(root,name):
	res = ""
	pre = checkNorm(root,name)
	main = False
	for a in pre.split('\n'):
		a += '\n'
		if "int main()" in a: 
			main = True
		if main and "ios_base" in a:
			ind = a.find("ios_base")
			res += a[:ind]+"\n"
			res += "\t"+a[ind:-2]+"\n"
			res += "\t$0\n}\n"
		else:
			res += a
	return res

def process(root,name): # prefix, file name
	global snippets,temp
	def shorten(name):
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
	if name.endswith(".cpp"):
		if "TemplateLong" in name:
			print("TEMPLATE_LONG:",name)
			temp = tempLong(root,name)
			output("Temp",temp)
		elif "TemplateShort" in name:
			print("TEMPLATE_SHORT:",name)
			output("TempShort",tempShort(root,name))
		elif "usaco" in name:
			print("INCLUDED:",name)
			output(shorten(name),checkNorm(root,name))
		elif "template" not in name.lower() and "test" not in name.lower():
			print("NOT INCLUDED:",name)
	if name == "Snippets.md":
		snippets = os.path.join(root,name)

for root, dirs, files in os.walk(USACO+"/Implementations",topdown=False):
	for name in files:
		process(root,name)
for root, dirs, files in os.walk(USACO+"/Contests/Tools",topdown=False):
	for name in files:
		process(root,name)

assert len(snippets) > 0 
assert len(temp) > 0, "snippets not found"

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
	if "TC" in names[i] or "FHC" in names[i]:
		code = temp[:ST]+code+temp[EN:]
	output(names[i],code)
