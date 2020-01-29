filenames = ['template.cpp', 'CppIO.h', '../number-theory (11.1)/Modular Arithmetic/Modular.h']
with open('templateShort.cpp', 'w') as outfile:
	with open('template.cpp','r') as infile:
		for line in infile:
			if not line.endswith('//\n'):
				# while len(line) >= 2 and line[-2] == ' ':
					# line = line[:-2]+'\n'
				outfile.write(line)