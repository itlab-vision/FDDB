

"""
0 - name
1 - x left eyes
2 - y left eyes
3 - x right eye
4 - y right eye
5 - x nose
6 - y nose
7 - x left corner mouth
8 - y left corner mouth
9 - x center mouth
10 - y center mouth
11 - x right corner mouth
12 - y right corner mouth
"""

file = open("D:/my-study/OpenCV/DataSet/CMU/annotTest.txt")

annotFile = open("D:/my-study/OpenCV/DataSet/CMU/annotRect.txt",'w')

for line in file:
    massLine = line.split()
    annotFile.write(massLine[0]+" ")
    h = 7.5 * (float(massLine[10]) - float(massLine[6]))
    w = 5 * ( (float(massLine[3]) - float(massLine[1]))/2 )
    x = float(massLine[1]) - 1.5 * (w/5)
    y = float(massLine[2]) - h*0.4
    print(massLine[0] + " 1" + " " + x.__str__() + " "+ y.__str__() + " "+ w.__str__() + " " + h.__str__())
    annotFile.writelines("1" + " " + x.__str__() + " "+ y.__str__() + " "+ w.__str__() + " " + h.__str__() + "\n")
    print(massLine)
annotFile.close()
"""

file = open("D:/my-study/OpenCV/DataSet/CMU/annotRect.txt")
annotFile = open("D:/my-study/OpenCV/DataSet/CMU/annotTest_Rect_OK.txt",'w')
count = 1
flag = 0
listName = []
listNameNew = []
for line in file:
    listName.append(line)
    if listName.__len__() >= 2:
        one = listName[listName.__len__()-1].split()
        two = listName[listName.__len__()-2].split()
        if one[0]!=two[0]:

            if flag==1:
                listName.remove(line)
                count=0

                annotFile.write("D:/my-study/OpenCV/DataSet/CMU/test/" + two[0]+" ")

                for str in listName:
                    count+=1

                annotFile.write(count.__str__())

                for str in listName:
                    s= str.split()
                    annotFile.write(" "+s[2]+" "+s[3]+" " + s[4]+" " + s[5])

                annotFile.write("\n")

            else:
                annotFile.write("D:/my-study/OpenCV/DataSet/CMU/test/" + two[0] + " "+two[1] + " "+two[2] + " "+two[3] + " "+two[4] + " "+two[5] + "\n")


            listName=[]
            listName.append(line)
            flag=0
        else:
            flag=1

annotFile.close()"""
