# 8/10 test cases ...

fin = open("wormsort.in","r")
lines = [line for line in fin]
N,M = map(int,lines[0].split())
p = list(map(lambda x: int(x)-1,lines[1].split()))

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

fout = open("wormsort.out","w")

fout.write(str(-1 if lo == 0 else ed[lo-1][0]))
fout.write('\n')