import pylab
import matplotlib.pyplot as plt
import math

'''file = open("Precision_and_Recall.txt",'r')
plt.ylabel('precision')
plt.xlabel('recall')

Np=0
Nn=0

FP=0
FN=0

h=1
listX=[]
listY =[]
for line in file:

    if (h):
       mass = line.split(" ")
       Np=mass[0]
       Nn=mass[1]
       h=0
    else:
        mass = line.split(" ")
        FP = mass[0]
        FN = mass[1]
       # print(FP+ " " + FN)
        TP = float(Np) - float(FN)
        Precision = TP/(TP+ float(FP))
        Recall = TP/(TP+ float(FN))
        listY.append(Precision)
        listX.append(Recall)

print(listX)
listX.sort()
listY.sort()
print(listY)

plt.plot(listX,listY)
plt.savefig('roc.png',format='png')
plt.show()'''

file = open("RocDisc.txt")

plt.figure("DiscRoc")
plt.xlabel("False Positive")
plt.ylabel("True positive rate")
plt.grid()

listX=[]
listY=[]
for line in file:
    name = line.split()
    for pointName in name:
        points_file = open(pointName)
        for point in points_file:
            xy = point.split()

            if (float(xy[1]) < 50000):
                listX.append(xy[1])
                listY.append(xy[0])

        plt.plot(listX,listY)
        listY=[]
        listX=[]
plt.legend(name, prop={'size':9})


file = open("RocCont.txt")
plt.figure("ContRoc")
plt.xlabel("False Positive")
plt.ylabel("True positive rate")
plt.grid()


for line in file:
    name = line.split()
    for pointName in name:
        points_file = open(pointName)
        for point in points_file:
            xy = point.split()

            if (float(xy[1]) < 50000):
                listX.append(xy[1])
                listY.append(xy[0])

        plt.plot(listX,listY)
        listY=[]
        listX=[]
plt.legend(name,prop={'size':9})
plt.show()


