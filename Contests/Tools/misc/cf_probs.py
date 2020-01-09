from contextlib import closing
from bs4 import BeautifulSoup
import urllib.request
import time
import sys
import os

def parse(url):
	page = urllib.request.urlopen(url)
	return BeautifulSoup(page,'html.parser')

def cf_stats():
	solved = get("https://codeforces.com/api/user.status?handle=Benq").json()['result']
	s = set()
	for i,t in enumerate(solved):
		if t['verdict'] == 'OK':
			p = t['problem']
			s.add((p['contestId'],p['index'],p['name']))
	contests = get("https://codeforces.com/api/contest.list").json()['result']
	badContest = set()
	for c in contests:
		if "Div. 3" in c['name'] or "Fools" in c['name'] or "Wild" in c['name']:
			badContest.add(c['id'])
	problems = get("https://codeforces.com/api/problemset.problems").json()['result']['problems']
	co = 0
	def defNot(z,s): # check if solved problem under another name
		for i in range(-50,51):
			if (z[0]+i,z[1],z[2]) in s:
				return False
		for i in range(-50,51):
			for let in range(26):
				if (z[0]+i,chr(ord('A')+let),z[2]) in s:
					return False
		return True
	for p in problems:
		if 'rating' in p:
			r = p['rating']
			z = (p['contestId'],p['index'],p['name'])
			if defNot(z,s) and p['contestId'] not in badContest and r >= 2600 and r <= 3000:
				co += 1
				if co == 20:
					sys.exit(0)
				print(p)