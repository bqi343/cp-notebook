from contextlib import closing
from bs4 import BeautifulSoup
import urllib.request
import time
import sys
import os

def parse(url):
	page = urllib.request.urlopen(url)
	return BeautifulSoup(page,'html.parser')

def usaco_parse(html): 
	# print(html.prettify())
	for a in html.find_all('table'):
		fst = True
		totScore = [0,0,0]
		relScore = [0,0,0]
		perfect = [0,0,0]
		lens = []
		names = []
		tot = 0
		bad = True
		for b in a.find_all('tr'):
			if fst:
				for c in b.findChildren():
					if c.has_attr('colspan'):
						lens.append(int(c['colspan'])-1)
						names.append(c.text);
			else:
				arr = []
				for c in b.find_all('tr'):
					arr.append(c.text)
				for c in b.find_all('td'):
					arr.append(c.text)
				if len(arr) == 0:
					continue 
				st = 5
				score = [0,0,0]
				for i,t in enumerate(lens):
					for j in range(t):
						if arr[st] == '*':
							score[i] += 1 
						st += 1
					st += 2
				tmpScore = 0
				for i in range(3):
					score[i] /= lens[i]
					totScore[i] += score[i]
					tmpScore += score[i]
					if score[i] == 1:
						perfect[i] += 1
				tot += 1 
				if tmpScore < 1: # less than third of points, data probably complete?
					bad = False
			fst = False
		tsum = 0
		for i in range(3):
			totScore[i] /= tot 
			tsum += totScore[i]
		for i in range(3):
			relScore[i] = totScore[i]/tsum
		if bad:
			print("INCOMPLETE DATA")

		def ro(x):
			return str(round(10000*x)/100)+"%"
		for i in range(3):
			print(names[i],ro(totScore[i]),ro(relScore[i]),perfect[i])
		break

def usaco_stats():
	prefix = "http://www.usaco.org/current/data/"
	month = ["dec","jan","feb","open"]
	offset = [0, 1, 1, 1]
	year = [15, 16, 17, 18, 19]
	for a in year:
		for j in range(len(month)):
			url = prefix+str(month[j])+str(a+offset[j])+"_platinum_results.html"
			soup = parse(url)
			print(month[j]+" "+str(a+offset[j])+": ")
			if soup == None:
				print("NO DATA")
			else:
				usaco_parse(soup)
			print()
		print("------")
		print()
