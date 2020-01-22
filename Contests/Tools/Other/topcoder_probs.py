from contextlib import closing
from bs4 import BeautifulSoup
import urllib.request
import time
import sys
import os

def parse(url):
	page = urllib.request.urlopen(url)
	return BeautifulSoup(page,'html.parser')

def topcoder_stats():
	url = "https://www.topcoder.com/tc?module=ProblemArchive&sr=1&er=400&sc=&sd=&class=&cat=&div1l=&div2l=&mind1s=&mind2s=&maxd1s=&maxd2s=&wr="
	html = parse(url)
	beg = True
	prob = []
	for a in html.find_all("tr"):
		x = a.find_all("td",{"class": "statText"})
		if len(x) != 10:
			continue # take out improperly formed columns
		number = x[5].find_all(text=True)[0].strip()
		if len(number) == 0:
			continue
		if beg:
			beg = False
			continue

		event = x[1].find_all(text=True)[1].strip()
		# if ("TCO18" not in event and "2018 TCO" not in event) or "Fun" in event:
		if "757" not in event and "758" not in event:
			continue
		title = x[0].find_all(text=True)[1].strip()
		percent = ""
		for b in x[9].findChildren():
			z = parse('https://www.topcoder.com'+b['href']).find_all("table")
			for index,Z in enumerate(z):
				if index == 3:
					percent = Z.findChildren(recursive=False)[6].findChildren()[1].text.strip()
					# print("HA",Z.findChildren()[6].text)
		prob.append([float(percent[:-1]),event,number,title])
		print(len(prob))
	prob.sort()
	for t in prob:
		for x in t:
			print(str(x)+"\t",end='')
		print()