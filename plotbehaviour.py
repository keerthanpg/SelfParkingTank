import numpy
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
plt.show()


f=open('calibration', 'r')
i=0

Y1={}
Y2={}
for line in f:
	line=line.split()	
	if(len(line)!=0):
		line=line[0].split(',')
		if line[1]=='1':
			if int(line[0]) not in Y1:
				Y1[int(line[0])]=[float(line[2])]
			else:
				Y1[int(line[0])].append(float(line[2]))
		if line[1]=='2':
			if int(line[0]) not in Y2:
				Y2[int(line[0])]=[float(line[2])]
			else:
				Y2[int(line[0])].append(float(line[2]))

x1=[]
y1=[]
x2=[]
y2=[]

for k,v in Y1.items():	
	v=numpy.average(v)
	print(k,v)	
	x1.append(k)
	y1.append(v)

for k,v in Y2.items():	
	v=numpy.average(v)	
	x2.append(k)
	y2.append(v)


print(len(x1))
print(len(y1))

plt.xlabel('Value')
plt.ylabel('Pulse rate')	
plt.scatter(x2,y2)
plt.show() 