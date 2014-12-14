

"""
0 - name
1 - x left eyes
2 - y left eyes
3 - x right eye
4 - y right eye
5 - x nose
6 - y nose
7 - x mouth
8 - y mouth
"""

file = open("D:/my-study/OpenCV/DataSet/Caltech_WebFaces/annot/WebFaces_GroundThruth_Windows.txt")
annotFile = open("D:/my-study/OpenCV/DataSet/Caltech_WebFaces/annot/WebFaces_GroundThruth_Rectangles.txt",'w')

for line in file:
    massLine = line.split()
    annotFile.write(massLine[0]+" ")
    h = 9 * (float(massLine[8]) - float(massLine[6]))
    w = 5 * ( (float(massLine[3]) - float(massLine[1]))/2 )
    x = float(massLine[1]) - w*0.3
    y = float(massLine[2]) - h*0.3
    print(massLine[0] + " 1" + " " + x.__str__() + " "+ y.__str__() + " "+ w.__str__() + " " + h.__str__())
    annotFile.writelines("1" + " " + x.__str__() + " "+ y.__str__() + " "+ w.__str__() + " " + h.__str__() + "\n")

annotFile.close()















