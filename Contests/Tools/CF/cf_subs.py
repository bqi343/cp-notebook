# download CF submissions
# use with 'python3 grader.py -g ok'

from bs4 import BeautifulSoup
import urllib.request
import sys
import time

def parse(url):
	page = urllib.request.urlopen(url)
	return BeautifulSoup(page,'html.parser')

sep='-'*50
prefix="https://codeforces.com/contest/"
contest="1294"
prob="C"
page="130"

def subs(page):
	url = prefix+contest+"/status/"+prob+"/page/"+page
	soup = parse(url)
	subs = soup.body.findAll('tr',attrs={'data-submission-id': True})
	L = []
	for s in subs:
		L.append(s['data-submission-id'])
	return L

L = subs(page)
for sub in L:
	url = prefix+contest+"/submission/"+sub
	soup = parse(url)
	table = soup.body.find('table')
	cpp = None
	cnt = 0
	for b in table.findAll('td'):
		cnt += 1
		if cnt == 4:
			lang = b.text.strip()
	name = ""
	if 'C++' in lang:
		name = sub+".cpp"
	elif ("Python" in lang or "PyPy" in lang) and "3" in lang:
		name = sub+".py"
	elif "Java" in lang:
		name = sub+".java"
	if len(name) > 0:
		prog = soup.body.find('pre',attrs={'id':"program-source-text"}).text
		if 'C++' in lang:
			prog = prog.replace("%I64d","%lld")
			prog = prog.replace("ONLINE_JUDGE","OJOJ")
		if 'Java' in lang: # needs to be fixed
			name = "j"+name
			clen = 1
			while clen < 100:
				des = 'public'+(' '*clen)+'class '
				ind = prog.find(des)
				if ind == -1:
					clen += 1
					continue
				L = ind+len(des)
				while prog[L].isspace():
					L += 1
				R = L
				while not prog[R].isspace() and prog[R] != '{':
					R += 1
				prog = prog[:L]+"j"+sub+prog[R:]
				break
			assert clen < 100, "public class not found"
		with open(name, "w") as f:
			f.write(prog)
		print(sub+": "+lang+", OK")
	else:
		print(sub+": "+lang+", NOT OK")
	time.sleep(0.5)