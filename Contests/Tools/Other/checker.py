# use with grader

import sys
from grader import splitWhite

inputF = sys.argv[1]
outputF = sys.argv[2]
o = sys.argv[3]

verdict = 1

def fassert(b):
	if not b:
		sys.exit(verdict)

x = splitWhite(outputF)
y = splitWhite(o)

fassert(len(x) == len(y))
correct = 0

for i in range(len(x)):
	fassert(len(x[i]) == len(y[i]))
	if len(x[i]) == 3:
		fassert(int(x[i][0])*int(x[i][1])*int(x[i][2]) == int(y[i][0])*int(y[i][1])*int(y[i][2]))
		fassert(y[i][0] != y[i][1] and y[i][0] != y[i][2] and y[i][1] != y[i][2])
	else:
		fassert(x[i] == y[i])
		correct += 1
		verdict = correct