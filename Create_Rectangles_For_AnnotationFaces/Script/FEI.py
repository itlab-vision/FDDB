"""
read this:
version: 1
n_points: 46
{
109.187 178.012
142.169 176.657
77.1084 207.831
113.253 204.217
124.548 206.928
136.747 204.217
171.536 207.831
143.524 233.584
107.831 234.488
49.5482 103.464
77.1084 95.7831
99.6988 106.175
76.6566 110.693
153.916 105.723
178.313 94.8795
202.259 104.367
179.115 110.234
14.3072 102.56
17.4699 154.97
22.4398 213.705
28.7651 239.006
50 261.596
75.3012 282.38
117.319 297.289
162.048 291.416
203.614 253.916
219.88 224.548
224.398 174.398
228.012 126.958
228.916 101.205
37.8012 75
56.3253 60.994
89.3072 65.512
100.151 78.1627
151.657 76.8072
157.982 65.512
199.096 59.1867
216.265 75
106.818 108.923
106.928 145.03
92.9217 155.422
94.2771 180.723
156.175 178.464
156.175 153.163
143.976 143.223
140.757 108.586
}
"""

annot = open("D:/my-study/OpenCV/DataSet/DataSet_for_train_Faces_Detector/PositiveImage/annotation.txt",'a')

for i in range(200):
    i+=1
    file = open("D:/my-study/OpenCV/DataSet/FEI/frontal/annot/" + str(i) + "a.pts")
    minX = 1000
    minY = 1000
    maxY =0
    maxX=0
    count = 0
    for line in file:
        if (count > 2 and line!="}\n"):
            line = line[0: line.__len__() - 2]
            mass= line.split()
            if ( float(mass[0]) < minX):
                minX = float(mass[0])
            if (float(mass[1])>maxY):
                maxY = float(mass[1])
            if (float(mass[0])> maxX):
                maxX = float(mass[0])
            if (float(mass[1])< minY):
                minY = float(mass[1])
        count+=1
        print(line)
    x = minX
    y = minY
    w = maxX - minX
    h = maxY - minY
    file.close()
    annot.write("DataSet_for_train_Faces_Detector/PositiveImage/FEI/frontal/" + str(i) + "a.jpg " + str(1) + " "+ str(x) + " " + str(y) + " " +
                str(w) + " " + str(h + h*0.1) + " \n")

for i in range(200):
    i+=1
    file = open("D:/my-study/OpenCV/DataSet/FEI/frontal/annot/" + str(i) + "b.pts")
    minX = 1000
    minY = 1000
    maxY =0
    maxX=0
    count = 0
    for line in file:
        if (count > 2 and line!="}\n"):
            line = line[0: line.__len__() - 2]
            mass= line.split()
            if ( float(mass[0]) < minX):
                minX = float(mass[0])
            if (float(mass[1])>maxY):
                maxY = float(mass[1])
            if (float(mass[0])> maxX):
                maxX = float(mass[0])
            if (float(mass[1])< minY):
                minY = float(mass[1])
        count+=1
        print(line)
    x = minX
    y = minY
    w = maxX - minX
    h = maxY - minY
    file.close()
    annot.write("DataSet_for_train_Faces_Detector/PositiveImage/FEI/frontal/" + str(1) + "b.jpg " + str(1) + " "+ str(x) + " " + str(y) + " " +
                str(w) + " " + str(h + h*0.1) + " \n")
annot.close()






