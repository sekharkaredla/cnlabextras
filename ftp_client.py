import socket
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect(('127.0.0.1',6660))
commands={1:"get",2:"put",3:"pwd",4:"ls",5:"cd",6:"quit"}
while True:
	print "menu:"
	for k in commands.keys():
		print str(k)+" "+commands[k]

	ip=input()
	if(ip<1 or ip>6):
		print "enter a proper input"
		continue
	if(ip==1):
		s.send(commands[ip])
		name=raw_input("enter file name:")
		s.send(name)
		op=s.recv(8196)
		print op
		print "--------------------------------------"
	if(ip==2):
		s.send(commands[ip])
		name=raw_input("enter file name:")
		s.send(name)
		out=' '
		for l in open(name,'r'):
			out+=l
		s.send(out)
		print 'put successful'
		print '--------------------------------------'
	if(ip==3):
		s.send(commands[ip])
		op=s.recv(1024)
		print "present working directory is "+op
		print '---------------------------------------'
	if(ip==4):
		s.send(commands[ip])
		op=s.recv(1024)
		print op
		print '----------------------------------------'
	if(ip==5):
		s.send(commands[ip])
		path=raw_input("enter the path :")
		s.send(path)
		print "path successfully changed"
		print '----------------------------------------'
	if(ip==6):
		s.send(commands[ip])
		print 'bye'
		break



