from contextlib import closing
from bs4 import BeautifulSoup
import urllib.request
import time
import sys
import os

def parse(url):
	page = urllib.request.urlopen(url)
	return BeautifulSoup(page,'html.parser')

def ioi_names(): 
	for i in range(2003,2020):
		url = f"https://ioinformatics.org/page/ioi-{i}/{29-2003+i}" 
		print("YEAR",i)
		html = parse(url)
		cool = html.find_all('a')
		co = 0
		for t in cool:
			if 'href' in t.attrs:
				tmp = t.attrs['href']
				if "/files/" in tmp and "problem" in tmp:
					name = ''.join(t.find_all(text=True))
					co += 1
					print(str(co)+" "+name)
		# sys.exit(0)

def ioi_stats(): # parses stat table
	url = "https://stats.ioinformatics.org/tasks/"
	html = parse(url)
	for a in html.find_all('tr'):
		arr = []
		for b in a.find_all('td'):
			arr.append(b.text)
		if len(arr) > 0 and len(arr[0]) == 4:
			if int(arr[0]) < 1994:
				break;
			print(arr[0])
			arr.pop(0)
		if len(arr) > 0 and len(arr[0]) == 1 and len(arr[1]) == 1:
			arr.pop(0)
		if len(arr) > 0:
			print(arr)