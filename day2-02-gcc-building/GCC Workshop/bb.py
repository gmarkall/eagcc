#!/usr/bin/python

import sys,os,re,getopt, itertools
from time import sleep
from collections import deque

# this will have target -> depdencies relationship
dep_dict = {}
file_index = {}

# this will have dependencies -> target relationship
# like reverse mapping
rev_dep_dict = {}
rev_file_index = {}

log_file_name = "make.log"
output_filename = ""
current_stage = 1

base_dir = ""
src_dir = ""
build_dir = ""
extn_queue = deque([])
e_flag = False

def main(argv):
	i_flag = False
	t_flag = False
	x_flag = False
	r_flag = False
	g_flag = False
	s_flag = False
	e_flag = False

	global output_filename
	global log_file_name
	global src_dir
	global build_dir
	
	try:
		opt,args = getopt.getopt(argv,"ho:s:itexrgb:c",["help","output=","source=","build="])
	except getopt.GetoptError, err:
		print str(err)
		usage()
		sys.exit(2)		
	if len(args) > 1:
		print "More than 1 argument provided"
		usage()
		sys.exit(2)
	elif len(args) == 1:
		log_file_name = args[0]

	for o,a in opt:
		if o in ("-h","--help"):
			usage()
			sys.exit(0)
		elif o in ("-o","--output"):
			output_filename = a
		elif o in ("-i"):
			i_flag = True
		elif o in ("-t"):
			t_flag = True
		elif o in ("-x"):
			x_flag = True
		elif o in ("-r"):
			r_flag = True
		elif o in ("-s","--source"):
			src_dir = a
		elif o in ("-g"):
			g_flag = True
		elif o in ("-c"):
			s_flag = True
		elif o in ("-b","--build"):
			build_dir = a
		elif o in ("-e"):
			e_flag = True;
		else:
			print "Invalid options "+o
			usage()
			sys.exit(2)

	if (i_flag and t_flag) or (i_flag and x_flag) or (t_flag and x_flag) or (g_flag and s_flag) or (e_flag and g_flag):
		print "(-i,-t and -x) and (-g and -s) and (-s and -r) and (-e and -g) are mutually exclusive"
		usage()
		sys.exit(2)
	
	if output_filename != "" and not (t_flag or x_flag):
		print "-o is valid only with -t or -x"
		usage()
		sys.exit(2)

	if build_dir == "" and (g_flag or s_flag):
		if build_dir == "":
			print "Build directory is Null" 
		print "-b <path-to-build-dir> is required for -g and -s"
		usage()
		sys.exit(2)

	if output_filename == "" and t_flag and not g_flag:
		output_filename = "cc1.txt"
	elif output_filename == "" and x_flag and not g_flag:
		output_filename = "cc1.xml"
	elif output_filename == "" and t_flag:
		output_filename = "generators.txt"
	elif output_filename == "" and x_flag:
		output_filename = "generators.xml"

	# set the default option
	if not (i_flag or t_flag or x_flag or src_dir != "" or g_flag):
		usage()
		sys.exit(0)
	#
	# lets start parsing !
	#
	parse(log_file_name)
	if i_flag and not g_flag and not s_flag and not e_flag:
		interactive(r_flag,e_flag)
	elif t_flag and not g_flag and not s_flag and not e_flag:
		f_name = raw_input("Enter file name whose tree structure need to be generated: ")
		if not r_flag:
			search_by_name(f_name,25,o_file_name=output_filename,rev=r_flag,stage_exp="1 or 2 or 3 or 4")
		else:
			search_by_name(f_name,25,o_file_name=output_filename,rev=r_flag,stage_exp="1 or 2 or 3 or 4")

	elif x_flag and not g_flag and not s_flag and not e_flag:
		xml_file = open(output_filename,"w")
		f_name = raw_input("Enter file name whose tree tructure need to be generated: ")
		r = re.compile(f_name)
		if r_flag == False:
			index = file_index
			cc1_target = filter(r.search,file_index.keys())
		else:
			index = rev_file_index
			cc1_target = filter(r.search,rev_file_index.keys())
		if len(cc1_target) != 0:
			print_tree_xml(index[cc1_target[0]][0],0,xml_file,r_flag=r_flag)
		else:
			print "NO DEPENDENCIES FOUND!!"

	elif i_flag and g_flag and not e_flag:
		interactive_generators(r_flag)

	elif t_flag and g_flag and not e_flag:
		if not r_flag:
			search_by_name("^gen[^\.]*$",25,o_file_name=output_filename,rev=r_flag,stage_exp="1 or 2 or 3 or 4")
		else:
			search_by_name("^gen[^\.]*$",25,o_file_name=output_filename,rev=r_flag,stage_exp="1 or 2 or 3 or 4")

	elif x_flag and g_flag and not e_flag:
		xml_file = open(output_filename,"w")
		r = re.compile("^gen[^\.]*$")
		if not r_flag:
			index = file_index
			cc1_target = filter(r.search,file_index.keys())
		else:
			index = rev_file_index
			cc1_target = filter(r.search,rev_file_index.keys())
		xml_file.write("<dep name='GENERATOR EXECUTABLES' >\n")
		for target in cc1_target:
			print_tree_xml(str(index[target][0]),0,xml_file,r_flag=r_flag)
		xml_file.write("</dep>\n")
	elif i_flag and e_flag:
		interactive(r_flag,e_flag)
#	elif i_flag and s_flag:
#		interactive_source()
				

# Removes duplicates from input	
def uniq(input):
	output = []
	for x in input:
		if x not in output:
			output.append(x)
  	return output

def add_to_dep(file_f,dep_list):

	global current_stage

	if dep_list == None:
		print "Empty dependcy "+file_f
		sys.exit(2)	

	if file_f not in dep_dict:
		dep_dict[file_f] =[]

	if isinstance(dep_list,str):
		dep_list = [dep_list]

	for dep in dep_list:
		stage_number = 0
		if any(pair[0] == dep for pair in dep_dict[file_f]):
			stage_number = [pair[1] for pair in dep_dict[file_f] if pair[0]==dep]
			stage_number = stage_number[0] 
			dep_dict[file_f].remove([dep,stage_number])

		stage_number |= (1 << (current_stage - 1))
		dep_dict[file_f].append([dep,stage_number])

def parse(make_log_f):

	#
	# Normalize the line breaks using back slash in 
	# the make file log and create a temp file 
	# for it
	#
	os.system("awk '{if($0~/ \\\\$/){printf \"%s\",substr($0,0,length($0)-1)}else{print}}' "+make_log_f+" | grep checking -v | grep ^[[:space:]]*if -v | grep ^for -v > .flat.txt")
	dir_stack = []
	global base_dir
	global current_stage
	global dep_dict

	f = open(".flat.txt","r")

	for line in f:
		split_line = line.split()

		# directory entering and leaving
		if re.match("^make\[[0-9]\]*",line):
			if split_line[1] == "Entering":
				if base_dir == "":
					base_dir = split_line[-1][1:-1]

				dir_stack.append(split_line[-1][1:-1])
			elif split_line[1] == "Leaving":
				dir_stack.pop()

		# All compilation commands: "gcc -c" or ("gcc " and "-c") or ("libtool=no gcc " and "-c") or ("prev-gcc/xgcc" and "-c")
		# or ("prev-gcc/g++" and "-c") or ("/gcc/xgcc" and "-c") or ("libtool: compile:  gcc " + "-c")
		# or ("libtool: compile: " and "/gcc/g++" and "-c")

		elif (re.search("gcc ",line) or re.search("g\+\+ ",line)) and re.search(" -c ",line):
			c_files = []
			o_file = ""
			c_count = 0
			o_count = 0

			for i in range(0,len(split_line)):
				if re.search("\.(c|cc|S|dep|Tpo)$",split_line[i]) or (re.search("\.lo$",split_line[i]) and not re.search("/bin/bash ./libtool ",line)):
					path_j = os.path.join(dir_stack[-1],split_line[i])
					c_files.append(os.path.normpath(path_j))
					c_count += 1
				elif re.search("\.(o|lo)$",split_line[i]):
					path_j = os.path.join(dir_stack[-1],split_line[i])
					o_file = (os.path.normpath(path_j))
					o_count += 1

			# it is possible that object file name is
			# implied by the c file name
			if not c_files:
#				f2err.write(line)
				pass
			elif o_file == "":
				for c_file in c_files:
					if re.search(".c$",c_file) or re.search(".cc$",c_file) or re.search(".S$",c_file):
						o_file = os.path.join(dir_stack[-1],c_file.split('/')[-1][:-2]+".o")
						break
				if o_file == "":
#					f2err.write(line)
					pass
				else:						
					add_to_dep(o_file,c_files)
			else:
				add_to_dep(o_file,c_files)


		# All linking commands: ("gcc " and "-o") or ("prev-gcc/xgcc" and "-o") or ("prev-gcc/g++" and "-o") or ("/gcc/xgcc" and "-o")

		elif (re.search("gcc ",line) or re.search("g\+\+ ",line)) and re.search("\-o ",line):
			e_file = ""
			oa_files = []
			for i in range(0,len(split_line)):
				if re.search("\.l?[oa]$",split_line[i]) or re.search("\.h$",split_line[i]):
					path_j = os.path.join(dir_stack[-1],split_line[i])
					oa_files.append(os.path.normpath(path_j))
				elif re.search("\-o$",split_line[i]):
					path_j = os.path.join(dir_stack[-1],split_line[i+1])
					e_file = os.path.normpath(path_j)
				elif re.search("&&",split_line[i]) or re.search(" if ",split_line[i]):
					break

			if e_file == "" or oa_files.__len__() == 0:
#				f3err.write(line)
				pass
			else:
				add_to_dep(e_file,oa_files)

		# parse archive files, contain obj files

		elif re.search("ar rc ",line) or re.search("ar cru ",line):
			a_file = ""
			o_files = []
			for i in range(0,len(split_line)):
				if re.search("\.a$",split_line[i]):
					path_j = os.path.join(dir_stack[-1],split_line[i])
					a_file = os.path.normpath(path_j)
				elif re.search("\.o$",split_line[i]):
					path_j = os.path.join(dir_stack[-1],split_line[i])
					o_files.append(os.path.normpath(path_j))

			if a_file == "" or o_files.__len__() == 0:
#				f4err.write(line)
				pass
			else:
				add_to_dep(a_file,o_files)

		# 
		# this is a special gen* comand which has move-if-change
		# with in itself , so parse this before move-if-change 
		#
	
		elif re.match("build/genchecksum ",line):
			gen_file = ""
			oa_files = []

			cksum_cmd = line.split("&&")[0]
			move_cmd = line.split("&&")[1]
		
			split_line = cksum_cmd.split()
			path_j = os.path.join(dir_stack[-1],split_line[0])
			gen_file = os.path.normpath(path_j)
			for oa in split_line[1:-2]:
				path_j = os.path.join(dir_stack[-1],oa)
				oa_files.append(os.path.normpath(path_j))
			path_j = os.path.join(dir_stack[-1],split_line[-1])
			tmp_file = os.path.normpath(path_j)

			oa_files.append(gen_file)

			add_to_dep(tmp_file,oa_files)
	
			split_line = move_cmd.split()
			path_j = os.path.join(dir_stack[-1],split_line[1])
		        src_file = os.path.normpath(path_j)
		        path_j = os.path.join(dir_stack[-1],split_line[2])
		        dst_file = os.path.normpath(path_j)
		
			add_to_dep(dst_file,src_file)		

		# parse statements copying/moving/creating links to files: "mv -f" or "mv " or "cp " or "^ln -s " or statements containing "ln -s"

		elif re.search("move\-if\-change ",line) or re.search("^mv ",line) or re.search("^cp ",line) or re.search("ln -s",line):

			src_ind = 0
			if re.match("ln",split_line[0]) or re.search("^mv -f",line):
				src_ind = 2
			elif re.match("cp",split_line[0]) or re.match("mv",split_line[0]):
				src_ind = 1
			for i in range(0,len(split_line)):
				if re.search("move\-if\-change",split_line[i]):
					src_ind = i+1
					break
				elif re.search("ln",split_line[i]):
					if re.search("^libtool: link:",line):
						path_j = os.path.join(dir_stack[-1],split_line[i+2][1:-1])
						src_file = os.path.normpath(path_j)
						path_j = os.path.join(dir_stack[-1],split_line[i+3][1:-1])
						dst_file = os.path.normpath(path_j)
#						print "link::"
					elif re.search("^libtool: install:",line):
						path_j = os.path.join(dir_stack[-1],split_line[i+3])
						src_file = os.path.normpath(path_j)
						path_j = os.path.join(dir_stack[-1],split_line[i+4][0:-1])
						dst_file = os.path.normpath(path_j)
#						print "install::"
					elif re.search("^/bin/bash",line):
						src_ind = i+2
#						print "bash::"
					break

			if src_ind != 0:
				path_j = os.path.join(dir_stack[-1],split_line[src_ind])
				src_file = os.path.normpath(path_j)
				path_j = os.path.join(dir_stack[-1],split_line[src_ind + 1])
				dst_file = os.path.normpath(path_j)
			if src_file == "" or dst_file == "":
#				f6err.write(line)
				pass
			else:
				add_to_dep(dst_file,src_file)

		# 
		# gen* commands output parsing
		#
		# gen* > *.out
		#
		elif re.match("build/(genmodes|gencondmd|gengenrtl|gencheck) >",line):
			path_j = os.path.join(dir_stack[-1],split_line[2])
			out_file = os.path.normpath(path_j)
			add_to_dep(out_file,os.path.join(dir_stack[-1],split_line[0]))

		elif re.match("build/genmodes",line):
			path_j = os.path.join(dir_stack[-1],split_line[3])
			c_file = os.path.normpath(path_j)
			add_to_dep(c_file,os.path.join(dir_stack[-1],split_line[0]))


		elif re.match("build/genhooks",line):
			path_j = os.path.join(dir_stack[-1],split_line[-1])
			c_file = os.path.normpath(path_j)
			add_to_dep(c_file,os.path.join(dir_stack[-1],split_line[0]))

		#
		# gen* *.md > *.c
		#
		elif re.match("build/(genconditions|genenums|genpreds|genconstants|genmddeps) ",line):

			if split_line[1] == "-c" or split_line[1] == "-h":
				src_ind = 1
			else:
				src_ind = 0

			path_j = os.path.join(dir_stack[-1],split_line[src_ind + 3])
			c_file = os.path.normpath(path_j)
	
			path_j = os.path.join(dir_stack[-1],split_line[0])
			gen_file = os.path.normpath(path_j)
	
			path_j = os.path.join(dir_stack[-1],split_line[src_ind + 1])
			md_file = os.path.normpath(path_j)

			add_to_dep(c_file,[md_file,gen_file])

		# gen*  *.md *.md  > *.c/h		
		elif re.match("build/(genautomata|genattrtab|genemit|genextract|genopinit|genoutput|genpeep|genrecog|genattr|genattr-common|gencodes|genconfig|genflags) ",line):
			path_j = os.path.join(dir_stack[-1],split_line[4])
		        c_file = os.path.normpath(path_j)

		        path_j = os.path.join(dir_stack[-1],split_line[0])
		        gen_file = os.path.normpath(path_j)

		        path_j = os.path.join(dir_stack[-1],split_line[1])
		        md1_file = os.path.normpath(path_j)
		        
			path_j = os.path.join(dir_stack[-1],split_line[2])
		        md2_file = os.path.normpath(path_j)
		
			add_to_dep(c_file,[md1_file,md2_file,gen_file])

		elif re.match("libtool: install: /usr/bin/install -c",line):
			path_j = os.path.join(dir_stack[-1],split_line[-2])
			src_file = os.path.normpath(path_j)
			path_j = os.path.join(dir_stack[-1],split_line[-1])
			dst_file = os.path.normpath(path_j)
			add_to_dep(dst_file,src_file)

		elif re.match("rm -f stage_current",line):
			current_stage += 1
#			print "stage number is: ", current_stage
#		else:
#			f11.write(line)

	# 
	# build index for searching targets 
	#
	for k in dep_dict.keys():
		f_name = k.split('/')[-1]
		if f_name not in file_index:
			file_index[f_name] = []
		file_index[f_name].append(k)

	# 
	# build reverse mapping using the already built
	# dep_dict
	#
	for k,v in dep_dict.items():
		for value in v:
			if value[0] not in rev_dep_dict:
				rev_dep_dict[value[0]] = []
			rev_dep_dict[value[0]].append([k,value[1]])

	#
	# build index for searching dependencies
	#
	for k in rev_dep_dict.keys():
		f_name = k.split('/')[-1]
		if f_name not in rev_file_index:
			rev_file_index[f_name] = []
		rev_file_index[f_name].append(k)


def print_tree_xml(target,level,xml_file,permissible_stage_num=range(1,16),r_flag=False):
	if not r_flag:
		data_dict = dep_dict
	else:
		data_dict = rev_dep_dict

	xml_file.write("<dep name=\""+target.replace(base_dir,"$BUILD").\
			replace(src_dir,"$SOURCE/")+"\" level=\""+str(level)+"\" >\n")
	level = level+1
	if target in data_dict:
		uniq_deps = uniq( [ x[0] for x in data_dict[target] if x[1] in permissible_stage_num] )
		uniq_deps.sort()
		for dep in uniq_deps:
			print_tree_xml(dep,level,xml_file,r_flag=r_flag)
	xml_file.write("</dep>\n")

def print_tree_lvl(target,alignment,level,permissible_stage_num,stage_num,o_file=None,rev=False,extn_list=[],extn_flag=1):
	global base_dir
	global src_dir
	global extn_queue

	stage_num_list = []
	for i in range(1,5):
		if (stage_num[0] & (1 << (i-1))) == (1 << (i-1)):
			if i != 4:
				stage_num_list.append('s'+str(i))
			else:
				stage_num_list.append("post_s3")
	if stage_num_list == []:
		stage_num_list = ""

	if re.search("\.",target.split('/')[-1]):
		extn = '.' + target.split('/')[-1].split('.')[-1]
	else:
		extn='exe'

	disp_string = alignment+""+target.replace(base_dir,"$BUILD").replace(src_dir,"$SOURCE/")+" "+str(stage_num_list).replace(" ","").replace("'","")

	if len(extn_list) == 0 or (extn in extn_list) or o_file:
		if not o_file:
			if extn_flag:
				while len(extn_queue) != 0:
					print extn_queue.popleft()
			print disp_string

		else:
			o_file.write(disp_string+"\n")
	else:
		#add path string to queue
		extn_queue.append(disp_string)

	if not rev:
        	alignment = alignment+"|--"
		data_dict = dep_dict
	else:
        	alignment = alignment+"^--"
		data_dict = rev_dep_dict
	
        if target in data_dict:
		uniq_deps = uniq( [ x[0] for x in data_dict[target] if x[1] in permissible_stage_num] )
		uniq_deps.sort()
                for dep in uniq_deps:
			if level:
				stage_num = [x[1] for x in data_dict[target] if x[0] == dep]
				print_tree_lvl(dep,alignment,level-1,permissible_stage_num,stage_num,o_file=o_file,rev=rev,extn_list=extn_list, extn_flag=extn_flag)
#        elif not rev and not re.search("\.(c|md)$",target):
#               print "Warning: Non C file as leaf "+target
	if len(extn_queue) != 0:
		last = extn_queue.pop()
		if last != disp_string:
			extn_queue.append(last)

def check_perm(stage_num,or_list):
	for pair in or_list:
		if (stage_num & pair[0] == pair[0]) and (stage_num & pair[1] == 0):
			return True
	return False

def parse_stage_exp(stage_exp):
	or_list = []
	split_line = stage_exp.split('or')
	for i in range(0,len(split_line)):
		and_flag = 0
		not_flag = 0
		split_line2 = split_line[i].split('and')	

		for k in range(0,len(split_line2)):

			split_line2[k].strip()

			if re.search("not ",split_line2[k]):
				#process not number (reset bit corresponding to stage_number)
				not_flag |= ( 1 << (int(split_line2[k].split()[1])-1) )
			else:
				#process stage_number (set bit corresponding to stage_number)
				and_flag |= ( 1 << (int(split_line2[k])-1) )

		or_list.append([and_flag,not_flag])

	permissible_stage_num = []
	for i in range(1,16):
		if check_perm(i,or_list):
			permissible_stage_num.append(i)

	return permissible_stage_num

def search_by_name(re_pat,level,stage_exp,o_file_name=None,rev=False,extn='',extn_flag=1):
	global extn_queue
	if o_file_name:
		o_file = open(o_file_name,"w")
	else:
		o_file = None

	permissible_stage_num = parse_stage_exp(stage_exp)
	extn_list = extn.split()

	if not rev:
		index = file_index
	else:
		index = rev_file_index

	regex = re.compile(re_pat)
	matched_keys = filter(regex.search,index.keys())

	for k in matched_keys:
		for d in index[k]:
			print " **************** "+d+" ********************\n"
			extn_queue=deque([])
			print_tree_lvl(d,"",level,permissible_stage_num,[0],o_file=o_file,rev=rev,extn_list=extn_list,extn_flag=extn_flag)
			print ""

def interactive_source():
#	os.system("cd "+build_dir+"; ls -R1 | grep \"\.[ch]$\" > /tmp/.lsbuild.txt; cd "+src_dir+"; ls -R1 | grep \"\.[ch]$\" > /tmp/.lssource.txt; grep -F -x -v -f /tmp/.lssource.txt /tmp/.lsbuild.txt > /tmp/.lsall.txt")

	os.system("cd "+build_dir+"; ls -R1 > /tmp/.lsall.txt")

	f=open("/tmp/.lsall.txt",'r')

	matched_files = []

	for line in f:
		if re.match("^\.",line):
			parent=line
		elif re.search("\.(c|h)$",line):
			path=build_dir + parent[:-2] + "/" + line[:-1]
			matched_files.append(os.path.normpath(path))

	src_files = [x for x in matched_files if x in dep_dict]

#	err_src_files = [x for x in src_files if x not in rev_dep_dict]

	while True:
		try:
			print "Ctrl + D to exit"
			print("\n************** Source Files Dependency ***************")
			level_str = raw_input("\nEnter the level [1]:")
			if level_str == "":
				level = 1
			else:
				level = int(level_str)

			while True:
				stage_exp = raw_input("\nExpression for stages for selective view \n   Possible stage options for three stages and post stage3: 1 2 3 4/p \n   Possible connectors (in priority): not and or \n   Ex: 1 and not 2 and not 3 or p \n (Default is any stage) [1 or 2 or 3 or p] \nEnter the expression: ")

				if stage_exp == "":
					stage_exp = "1 or 2 or 3 or 4"
					break
				else:
					if not re.match("(\W*(not)?\W*(1|2|3|4|p)\W*)(\W*(and|or)\W*(not)?\W*(1|2|3|4|p)\W*)*",stage_exp, re.IGNORECASE):
						print "Incorrect stage expression!! Please try again."
					else:
						stage_exp = stage_exp.lower().replace("p","4")
						break

			while True:
				extn = raw_input("\nEnter the file extensions for selective browsing (Default: all extensions) [.c .h .o exe (no extension) .S .cc .tmp etc]: ")
				if not re.match("^((\W*\.[^\. ]*(\W|$))|(\W*exe\W*))*$",extn, re.IGNORECASE):
					print "Incorrect extensions!! Please try again. Ex: .h .c .o exe .S .extn"
				else:
					extn = re.sub(r"exe","exe",extn,flags=re.IGNORECASE)
					if len(extn) != 0:
						while True:
							extn_flag = raw_input("\nDo you want to display intermediate dependencies of files with non-specified extensions (y/n) [Default y]:")
							if re.match("\W*y.*",extn_flag,re.IGNORECASE) or extn_flag == "":
								extn_flag = 1
							elif re.match("\W*n.*",extn_flag,re.IGNORECASE):
								extn_flag = 0
							else:
								print "Incorrect choice (y/n)!! Please try again."
								continue
							break
					else:
						extn_flag = 1
					break
				
			permissible_stage_num = parse_stage_exp(stage_exp)
			extn_list = extn.split()

			for src_file in src_files:
				if src_file in rev_dep_dict:
					print " **************** "+src_file+" ********************\n"
					extn_queue=deque([])

					print_tree_lvl(src_file,"",level,permissible_stage_num=permissible_stage_num,stage_num=[0],o_file=None, rev=True,extn_list=extn_list,extn_flag=extn_flag)
					print ""
				else:
					print " **************** "+src_file+" ********************\nDependency information not available!!\n"

		except EOFError:
			print "\nExiting"
			sys.exit(0)

def interactive_generators(rev=False):

	os.system("cd "+build_dir+"; ls -R | grep ^gen[^\.]*$ | sort -u > /tmp/.gen.txt")
	gen_list = [i.strip() for i in open("/tmp/.gen.txt").readlines()]

	while True:
		try:
			print "\n******************** Generator Executables ********************"
			os.system("cd "+build_dir+"; ls -R | grep ^gen[^\.]*$ | sort -u | while read line; do printf \"%-8s\n\" \"$line\" ; done | column;  echo -n \"\nGenerator Executables count:\"; cd "+build_dir+"; ls -R | grep ^gen[^\.]*$ | sort -u | wc -l")

			print "\nCtrl + D to exit"
			regex = raw_input("Enter the generator executable name (Default: All) [^gen[^\.]*$]:")
			if regex == "":
				regex = "^gen[^\.]*$"

			matched_gen = [x for x in gen_list if re.match(regex,x)]

			if not matched_gen:
				print "Regex not matching any generator!!"
				sleep(1.5)
				continue

			print "\t\t***Matched Generators: " + str(matched_gen) + "***"
			level_str = raw_input("Enter the level [1]:")
			if level_str == "":
				level = 1
			else:
				level = int(level_str)

			while True:
				stage_exp = raw_input("\nExpression for stages for selective view \n   Possible stage options for three stages and post stage3: 1 2 3 4/p \n   Possible connectors (in priority): not and or \n   Ex: 1 and not 2 and not 3 or p \n (Default is any stage) [1 or 2 or 3 or p] \nEnter the expression: ")
				if stage_exp == "":
					stage_exp = "1 or 2 or 3 or 4"
					break
				else:
					if not re.match("(\W*(not)?\W*(1|2|3|4|p)\W*)(\W*(and|or)\W*(not)?\W*(1|2|3|4|p)\W*)*",stage_exp, re.IGNORECASE):
						print "Incorrect stage expression!! Please try again."
					else:
						stage_exp = stage_exp.lower().replace("p","4")
						break
			while True:
				extn = raw_input("\nEnter the file extensions for selective browsing (Default: all extensions) [.c .h .o exe (no extension) .S .cc .tmp etc]: ")
				if not re.match("^((\W*\.[^\. ]*(\W|$))|(\W*exe\W*))*$",extn, re.IGNORECASE):
					print "Incorrect extensions!! Please try again. Ex: .h .c .o exe .S .extn"
				else:
					extn = re.sub(r"exe","exe",extn,flags=re.IGNORECASE)
					if len(extn) != 0:
						while True:
							extn_flag = raw_input("\nDo you want to display intermediate dependencies of files with non-specified extensions (y/n) [Default y]:")
							if re.match("\W*y.*",extn_flag,re.IGNORECASE) or extn_flag == "":
								extn_flag = 1
							elif re.match("\W*n.*",extn_flag,re.IGNORECASE):
								extn_flag = 0
							else:
								print "Incorrect choice (y/n)!! Please try again."
								continue
							break
					else:
						extn_flag = 1
					break
				
			for gen in matched_gen:
				search_by_name('^'+gen+'$',level,stage_exp,o_file_name=None,rev=rev,extn=extn,extn_flag=extn_flag)

		except EOFError:
			print "\nExiting"
			sys.exit(0)

def print_executables():
	print "Executables are:"
	for g_file in file_index.keys():
		if not re.search("\.",g_file) and not re.search("^gen[^\.]*$",g_file) and not re.search("\_",g_file):
			if g_file not in ("specs","optionlist","tmp-mddeps","README","checksum-options","mkheaders"):
				print "\t\t",g_file
		

def interactive(rev=False,exe=False):
	while True:
		try:
			print "Ctrl + D to exit"
			if exe:
				print_executables()
			regex = raw_input("Enter the file name [^cc1$]:")
			if regex == "":
				regex = "^cc1$"
	
			level_str = raw_input("Enter the level [1]:")
			if level_str == "":
				level = 1
			else:
				level = int(level_str)

			while True:
				stage_exp = raw_input("\nExpression for stages for selective view \n   Possible stage options for three stages and post stage3: 1 2 3 4/p \n   Possible connectors (in priority): not and or \n   Ex: 1 and not 2 and not 3 or p \n (Default is any stage) [1 or 2 or 3 or p] \nEnter the expression: ")
				if stage_exp == "":
					stage_exp = "1 or 2 or 3 or 4"
					break
				else:
					if not re.match("(\W*(not)?\W*(1|2|3|4|p)\W*)(\W*(and|or)\W*(not)?\W*(1|2|3|4|p)\W*)*",stage_exp, re.IGNORECASE):
						print "Incorrect stage expression!! Please try again."
					else:
						stage_exp = stage_exp.lower().replace("p","4")
						break

			while True:
				extn = raw_input("\nEnter the file extensions for selective browsing (Default: all extensions) [.c .h .o exe (no extension) .S .cc .tmp etc]: ")
				if not re.match("^((\W*\.[^\. ]*(\W|$))|(\W*exe\W*))*$",extn, re.IGNORECASE):
					print "Incorrect extensions!! Please try again. Ex: .h .c .o exe .S .extn"
				else:
					extn = re.sub(r"exe","exe",extn,flags=re.IGNORECASE)
					if len(extn) != 0:
						while True:
							extn_flag = raw_input("\nDo you want to display intermediate dependencies of files with non-specified extensions (y/n) [Default y]:")
							if re.match("\W*y.*",extn_flag,re.IGNORECASE) or extn_flag == "":
								extn_flag = 1
							elif re.match("\W*n.*",extn_flag,re.IGNORECASE):
								extn_flag = 0
							else:
								print "Incorrect choice (y/n)!! Please try again."
								continue
							break
					else:
						extn_flag = 1
					break
				
			search_by_name(regex,level,stage_exp,o_file_name=None,rev=rev,extn=extn,extn_flag=extn_flag)

		except EOFError:
			print "\nExiting"
			sys.exit(0)

def usage():
	print "Usage: "+sys.argv[0]+" [options] -s src_dir <log_filename>"
	print "options"
	print "\t-h, --help		show this help message"
	print "\t-s, --source=src_dir	dir which will apprear as $SOURCE"
	print "\t-r 			uses reverse mapping "
	print "\t			from source -> target"
	print "\t-i			enter interactive search"
	print "\t-o, --output=filename	output file name for -x and -t"
	print "\t-t 			store the tree in output file"
	print "\t-x			store the XML format in a output file"
	print "\t-x,-i and -t are mutually exclusive options\n"
	print "default file name for -x is cc1.xml"
	print "default file name for -t is cc1.txt"
	print "log_filename is optional and by default it is make.log\n"

	print "\t New Options:"
	print "\t-e         View executable supports -r,-i/-t/-x"
	print "\t-g			view generator executables (Requires build directory to search for generators) Supports -r, -i/-t/-x"
	print "\t-b --build=build_dir	path to build directory which will be searched for generators and source files"


if __name__ == "__main__":
	main(sys.argv[1:])

