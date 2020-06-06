# 8/10 test cases ...
import os
import sys
from io import BytesIO, IOBase

_str = str
str = lambda x=b"": x if type(x) is bytes else _str(x).encode()

BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


fin = IOWrapper(open("wormsort.in"))
lines = [line for line in fin]
N,M = map(int,lines[0].split())
p = list(map(lambda x: int(x)-1,lines[1].split()))

# print("OOPS",p)

ed = []
for i in range(2,len(lines)):
	a,b,w = map(int,lines[i].split())
	a -= 1
	b -= 1
	ed.append([w,a,b])
ed.sort()
ed.reverse()

adj = [[] for i in range(N)]
vis = [0 for i in range(N)]
cnt = 0

def dfs(x):
	global cnt
	if vis[x] != 0:
		return
	vis[x] = cnt
	for i in adj[x]:
		dfs(i)

def ok(mid):
	global cnt
	for i in range(N):
		vis[i] = 0
		adj[i].clear()
	for i in range(mid):
		a,b = ed[i][1],ed[i][2]
		# print("HUH",mid,a,b)
		adj[a].append(b)
		adj[b].append(a)
	for i in range(N):
		if vis[i] == 0:
			cnt += 1
			todo = [i]
			ind = 0
			while ind < len(todo):
				x = todo[ind] 
				ind += 1
				vis[x] = cnt
				for i in adj[x]:
					if vis[i] == 0:
						vis[i] = -cnt
						todo.append(i)
			# dfs(i)
	ok = True
	for i in range(N):
		if vis[i] != vis[p[i]]:
			ok = False
	return ok

lo,hi = 0,M
while lo < hi:
	mid = (lo+hi)//2
	if ok(mid):
		hi = mid
	else:
		lo = mid+1

# print("OK",lo)

fout = IOWrapper(open("wormsort.out"))

fout.write(str(-1 if lo == 0 else ed[lo-1][0]))
fout.write('\n')