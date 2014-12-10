import pylab
import matplotlib.pyplot as plt
import math

file = open("RocDisc.txt")
plt.figure("DiscRoc")
plt.xlabel("False Positive Per Frame")
plt.ylabel("True Positive Rate")
plt.grid()

n=0
listX=[]
listY=[]
listLeg=[]
for line in file:
    name = line.split()
    for pointName in name:
        points_file = open(pointName)
        for point in points_file:
            xy = point.split()
            if (float(xy[1]) < 8000):
                listX.append(int(xy[1])/float(2844))
                listY.append(xy[0])

        plt.plot(listX,listY)
        listY=[]
        listX=[]
        listLeg.append( pointName[0:len(pointName)-6])
plt.legend(listLeg, prop={'size':9})
listLeg=[]



#======================================


file = open("RocCont.txt")
plt.figure("ContRoc")
plt.xlabel("False Positive Per Frame")
plt.ylabel("True Positive Rate")
plt.grid()


for line in file:
    name = line.split()
    for pointName in name:
        listLeg.append(pointName[0:len(pointName)-6])
        points_file = open(pointName)
        for point in points_file:
            xy = point.split()

            if (float(xy[1]) < 3000):
                listX.append(int(xy[1])/float(2844))
                listY.append(xy[0])

        plt.plot(listX,listY)
        listY=[]
        listX=[]
plt.legend(listLeg,prop={'size':10})

plt.show()

