filenames = ['template.cpp', 'CppIO.h', '../number-theory (11.1)/Modular Arithmetic/Modular.h']
with open('templateLong.cpp', 'w') as outfile:
	res = []
	active = False
	def ad(line):
		global active
		if line.startswith('#include "'):
			return 
		if line.startswith('/**'):
			active = True
		if active and '*/' in line:
			active = False 
			return
		if active:
			return 
		if line.endswith("//\n"):
			line = line[:-3]+"\n"
		res.append(line)
		if not res[-1].endswith('\n'):
			res[-1] += '\n'
		while len(res) > 1 and len(res[-1]) <= 1 and len(res[-2]) <= 1:
			res.pop()

	extra = []
	for fname in filenames:
		with open(fname) as infile:
			v = []
			for line in infile:
				v.append(line)
			if fname == 'template.cpp':
				for i in range(len(v)):
					line = v[i]
					if i < len(v)-5:
						ad(line)
					elif i > len(v)-4:
						extra.append(line)
			else:
				for line in v:
					ad(line)
		ad('\n')
	for line in extra:
		ad(line)
	res.pop()
	res.append('	// you should actually read the stuff at the bottom\n')
	res.append('}\n\n')
	res.append("""/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?), slow multiset operations
	* do smth instead of nothing and stay organized
*/""")
	for line in res:
		outfile.write(line)