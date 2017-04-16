import os,socket
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(('127.0.0.1',6660))
s.listen(5)
client,address=s.accept()
while True:
	k=client.recv(1024)
	if k=='get':
		name=client.recv(1024)
		os.system('cat '+name+'>out.txt')
		file=open('out.txt','r')
		out=' '
		for l in file:
			out+=l
		client.send(out)
		file.close()
	if k=='put':
		name=client.recv(1024)
		file=open(name,"w")
		file.write(client.recv(8192))
		file.close()
	if k=='pwd':
		os.system("pwd>out.txt")
		file=open('out.txt','r')
		out=' '
		for l in file:
			out+=l
		client.send(out)
		file.close()
	if k=='ls':
		os.system("ls>out.txt")
		file=open('out.txt','r')
		out=' '
		for l in file:
			out+=l
		client.send(out)
		file.close()
	if k=='cd':
		path=client.recv(1024)
		os.chdir(path)
	if k=='quit':
		s.close();
		print 'exiting server mode'
		break



