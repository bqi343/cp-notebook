import os
import subprocess

for root, dirs, files in os.walk("/Users/benq/Documents/USACO/Implementations",topdown=False):
	# print("?",root,dirs,files)
	for name in files:
		if name.endswith(".h") and name[0].isupper():
			path = root+"/"+name
			path = path[path.find("content/")+len("content/"):]
			if "CppIO" in path or "BigInt" in path:
				continue
			p = subprocess.Popen(['sh', 'test-compiles.sh',path], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
			res, _ = p.communicate()
			print(res.decode("utf-8").rstrip())