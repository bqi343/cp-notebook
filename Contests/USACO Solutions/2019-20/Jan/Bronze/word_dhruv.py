import sys
with open("word.in","r") as fin:
	L = list(fin)
	N,W = map(int,L[0].split())
	with open("word.out","w") as fout:
		w = 0
		for c in L[1].split():
			if w+len(c) > W:
				fout.write("\n"+c)
				w = len(c)
			else:
				if w > 0:
					fout.write(" ")
				fout.write(c)
				w += len(c)
		fout.write("\n")