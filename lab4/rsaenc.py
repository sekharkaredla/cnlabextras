import sys
from fractions import gcd
from random import randint
argl=sys.argv
print argl

def selecterandom(p,q):
	phi=(p-1)*(q-1)
	for i in range(3,phi):
		if(gcd(i,phi)==1):
			es.append(i)
	print es	
	i=randint(0,len(es)-1)
	print es[i]
	return es[i]


file=open(argl[1],"r");
data=''
for k in file:
	if data=='':
		data=k
	else:
		data+=k
file.close()
list=[]

pub=argl[2]
pub=pub.split('-')
print pub
e=pub[0]
n=pub[1]
e=int(e)
n=int(n)
for k in data:
	list.append(ord(k))
print list

print("encryption : ")
enc=[]
#e=selecterandom(p,q)
for k in list:
	c=1
	for m in range(0,e):
		c=c*k
		c=c%n
	c=c%n
	enc.append(c)
print enc

output=''
file=open("output.txt","w")
for k in enc:
	if output!='':
		output+=str(k)+'\n'
	else:
		output=str(k)+'\n'
	
#print output
file.write(output)
file.close()


