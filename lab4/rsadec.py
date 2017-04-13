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
#print data
list1=data.split('\n')
list1=list1[0:-2];
print list1
list=[]
for k in list1:
	list.append(int(k))

print list
pub=argl[2]
pub=pub.split('-')
print pub
d=pub[0]
n=pub[1]
d=int(d)
n=int(n)


print("decryption : ")
dec=[]
for k in list:
	c=1
	for m in range(0,d):
		c=c*k
		c=c%n
	c=c%n
	dec.append(c)
print dec


output=''
file=open("outputcli.txt","w")
for k in dec:
	if output!='':
		output+=chr(k)
	else:
		output=chr(k)
	
print output
file.write(output)
file.close()


