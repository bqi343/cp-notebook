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
contest="1279"
prob="B"

def subs(page):
	url = prefix+contest+"/status/"+prob+"/page/"+page
	soup = parse(url)
	subs = soup.body.findAll('tr',attrs={'data-submission-id': True})
	L = []
	for s in subs:
		L.append(s['data-submission-id'])
	return L

L = subs("1")
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
	if 'C++' in lang:
		prog = soup.body.find('pre',attrs={'id':"program-source-text"})
		name = sub+".cpp"
		f = open(name, "w")
		f.write(prog.text)
		f.close()
		print(sub+": "+lang+", OK")
		if "%I64d" in open(name).read():
			print("warning: %I64d\n")
	else:
		print(sub+": "+lang+", NOT OK")
	time.sleep(0.5)