from fractions import gcd
from random import randint
es=[]
def selecterandom(p,q):
	phi=(p-1)*(q-1)
	for i in range(3,phi):
		if(gcd(i,phi)==1):
			es.append(i)
	print es	
	i=randint(0,len(es)-1)
	print es[i]
	return es[i]



p=input("enter p :")
q=input("enter q :")
n=p*q
phi=(p-1)*(q-1)
e=selecterandom(p,q)
#e=input("enter e :")
d=1
s=0
while(s!=1):
	s=(d*e)%phi
	d+=1;
d-=1
print("public key "+str(e)+" "+str(n))
print("private key "+str(d)+" "+str(n))

#data=raw_input("enter the data to be encrypted : ")
file=open("temp.txt","r");
data=''
for k in file:
	if data=='':
		data=k
	else:
		data+=k
file.close()
list=[]
for k in data:
	list.append(ord(k))
print list

print("encryption : ")
enc=[]
for k in list:
	c=1
	for m in range(0,e):
		c=c*k
		c=c%n
	c=c%n
	enc.append(c)
print enc
#output=''
#for k in enc:
 #       if output!='':
  #              output+=chr(k)
   #     else:
    #            output=chr(k)
#print output
print("decryption : ")
dec=[]
for k in enc:
	c=1
	for m in range(0,d):
		c=c*k
		c=c%n
	c=c%n
	dec.append(c)
print dec

output=''
file=open("output.txt","w")
for k in dec:
	if output!='':
		output+=chr(k)
	else:
		output=chr(k)
	
print output
file.write(output)
file.close()
