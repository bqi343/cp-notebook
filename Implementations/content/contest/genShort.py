filenames = ['Template.cpp', 'CppIO.h', '../number-theory (11.1)/Modular Arithmetic/Modular.h']
with open('TemplateShort.cpp', 'w') as outfile:
	with open('Template.cpp','r') as infile:
		for line in infile:
			if not line.endswith('//\n'):
				if "// 998244353" in line:
					line = line[:line.find("// 998244353")].rstrip()+"\n"
				# while len(line) >= 2 and line[-2] == ' ':
					# line = line[:-2]+'\n'
				outfile.write(line)
