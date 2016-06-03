import os
import fileinput

while True:
	command = raw_input() #input as string
	if 'create' in command:
		filename = command.split()[1]
		files = [f for f in os.listdir('.') if os.path.isfile(f)]
		if filename in files:
			print "File already exists"
			continue		
		fin = open(filename,'w')
		info = os.stat(filename)
		fin2 = open('ramesh.txt','a')
		fin2.write(filename + '\n')
		for x in info:
			fin2.write(str(x) + '\n')
		fin2.write("Lines 0\n")
		print "File successfully created"
		print "Ctrl-z to exit"
		fin.close()
		fin2.close()

	elif 'copy' in command:
		flag = 0
		file1 = command.split()[1]
		file2 = command.split()[2]
		temp = os.popen("wc -l " + file2).read().split()
		file_content = os.popen('cat ' + file2).read()
		with open("ramesh.txt", "r") as in_file:
			buf = in_file.readlines()
		with open("ramesh.txt", "w") as out_file:
			for line in buf:
				if file1 in line:
					flag = 1
				if "Lines 0\n" in line and flag == 1:
					line = "Lines " + str(temp[0]) +'\n' + file_content
					flag = 0
				out_file.write(line)
		print "File copied successfully"
		print "Ctrl-z to exit"
		in_file.close()
		out_file.close()
	
	elif 'delete' in command:
		filename = command.split()[1]
		files = [f for f in os.listdir('.') if os.path.isfile(f)]
		if filename not in files:
			print "File does not exist"
			continue
		os.system('rm -rf ' + filename)
		file_content = fileinput.input('ramesh.txt', inplace=True)
		with open("ramesh.txt", "r") as in_file:
			flag = 0
			buf = in_file.readlines()
			for line in buf:
				if filename in line:
					flag = 1
				if 'Lines' in line and flag==1:
					lines = line.split()[1]
		for line in file_content:
			if filename in line:
				for _ in range(11 + int(lines)):
					next(file_content, None)				
			else:
				print line, 
		print "File successfully deleted"
		print "Ctrl-z to exit"
		in_file.close()

	elif 'echo' in command:
		filename = command.split()[1]
		files = [f for f in os.listdir('.') if os.path.isfile(f)]
		if filename not in files:
			print "File does not exist"
			continue
		with open("ramesh.txt", "r") as in_file:
			flag = 0
			lines = 0
			buf = in_file.readlines()
			for line in buf:
				if filename in line:
					flag = 1
				if 'Lines' in line and flag == 1:
					lines = int(line.split()[1])
				if flag == 1 and lines!=0:
					print line
					lines-=1
		print "Ctrl-z to exit"
		in_file.close()

	elif 'ls' in command:
		files = [f for f in os.listdir('.') if os.path.isfile(f)]
		for filename in files:		
			print filename
		print "Ctrl-z to exit"

	else:
		print "Invalid Command"

