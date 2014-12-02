

annot = open ("D:/my-study/OpenCV/DataSet/DataSet_for_train_Faces_Detector/PositiveImage/annotation.txt",'a')

file = open("D:/my-study/OpenCV/DataSet/CIE_Biomatrics/annot/L001/00011001.yml")

for line in file:
    print(line)
file.close()



for i in range(100):
    name = "D:/my-study/OpenCV/DataSet/CIE_Biomatrics/annot/"
    nameImage = "DataSet_for_train_Faces_Detector/PositiveImage/CIE_Biomatrics/"
    i+=1
    if i<10:
        name+="L00" + i.__str__() + "/"
        nameImage+="000" + i.__str__() + "/"
    else:
        if i<100:
            name+="L0"+i.__str__()+"/"
            nameImage+= "00" + i.__str__() + "/"
        else:
            name+="L"+ i.__str__()+"/"
            nameImage+= "0" + i.__str__() + "/"
    file = open(name + "allNameFile.txt")
    count=0
    for line in file:
        if count>6 and line.split()[3]!="allNameFile.txt":
            mass = line.split()
            yml = mass[3] #name yml file in dir
            annot.write(nameImage + yml[0:yml.__len__() - 4] + ".jpg")
            ymlFile = open(name + yml )
            flagX=0
            flagY=0
            listPoint = []

            for ymlLine in ymlFile:
                ymlLine = ymlLine.split()
                if ymlLine.__len__()>1:
                    listPoint.append(float(ymlLine[1]))
            ymlFile.close()

            if listPoint[30]!=0.0 and listPoint[26]!=0.0:
                w = (listPoint[30] - listPoint[26])*4.5
            if listPoint[42]!=0.0 and listPoint[40]!=0.0:
                w = (listPoint[42] - listPoint[40])*3
            if listPoint[54]!=0.0 and listPoint[52]!=0.0:
                w = (listPoint[54] - listPoint[52]) + 5
            if listPoint[28]!=0.0 and listPoint[24]!=0.0:
                w = (listPoint[28] - listPoint[24])*1.5
            if listPoint[16]!=0.0 and listPoint[8]!=0.0:
                w = (listPoint[16] - listPoint[8])*4.5
            if listPoint[38]!=0.0 and listPoint[34]!=0.0:
                w = (listPoint[38] - listPoint[34])*4.5
            if listPoint[18]!=0.0 and listPoint[10]!=0.0:
                w = (listPoint[18] - listPoint[10])*4.5
            if listPoint[2]!=0.0 and listPoint[0]!=0.0:
                w = (listPoint[2] - listPoint[0])*3


            if listPoint[45]!=0.0 and listPoint[5]!=0.0:
                h = (listPoint[45] - listPoint[5])*7
            if listPoint[51]!=0.0 and listPoint[5]!=0.0:
                h = (listPoint[51] - listPoint[5])*7
            if listPoint[45]!=0.0 and listPoint[35]!=0.0:
                h = (listPoint[45] - listPoint[35])*7
            if listPoint[45]!=0.0 and listPoint[39]!=0.0:
                h = (listPoint[45] - listPoint[39])*7
            if listPoint[51]!=0.0 and listPoint[35]!=0.0:
                h = (listPoint[51] - listPoint[35])*7
            if listPoint[51]!=0.0 and listPoint[39]!=0.0:
                h = (listPoint[51] - listPoint[39])*7
            if listPoint[5]!=0.0 and listPoint[1]!=0.0:
                h = (listPoint[5] - listPoint[1])*2.5
            if listPoint[5]!=0.0 and listPoint[3]!=0.0:
                h = (listPoint[5] - listPoint[3])*2.5
            if listPoint[5]!=0.0 and listPoint[7]!=0.0:
                h = (listPoint[7] - listPoint[5])*2.5



            if listPoint[53]!=0.0:
                x = listPoint[53] - 5
            if listPoint[27]!=0.0:
                x = listPoint[27] - w*0.3
            if listPoint[35]!=0.0:
                x = listPoint[35] - w*0.3
            if listPoint[41]!=0.0:
                x = listPoint[41] - w*0.2
            if listPoint[45]!=0.0:
                x = listPoint[45] - w*0.4
            if listPoint[51]!=0.0:
                x = listPoint[51] - w*0.4
            if listPoint[5]!=0.0:
                x = listPoint[5] - w*0.4
            if listPoint[0]!=0.0:
                x = listPoint[0] - w*0.3


            if listPoint[25]!=0.0:
                y = listPoint[25] - h*0.1
            if listPoint[53]!=0.0:
                y = listPoint[53] - h*0.4
            if listPoint[55]!=0.0:
                y = listPoint[55] - h*0.4
            if listPoint[7]!=0.0:
                y = listPoint[7] - h*0.65
            if listPoint[27]!=0.0:
                y = listPoint[27] - h*0.05
            if listPoint[31]!=0.0:
                y = listPoint[31] - h*0.05
            if listPoint[51]!=0.0:
                y = listPoint[51] - h*0.45
            if listPoint[35]!=0.0:
                y = listPoint[35] - h*0.4
            if listPoint[39]!=0.0:
                y = listPoint[39] - h*0.4
            if listPoint[5]!=0.0:
                y = listPoint[5] - h*0.4
            if listPoint[1]!=0.0:
                y = listPoint[1] - h*0.3

            """
            if listPoint[7]==0.0:
                if listPoint[5]!=0.0 and listPoint[12]!=0.0:
                    h =(listPoint[12] - listPoint[5] ) * 9
                    if listPoint[0]==0.0 and listPoint[9]!=0.0:
                        y = listPoint[9] - h * 0.6
                    else:
                        y = listPoint[1] - h * 0.3
            else:
                if listPoint[5]==0.0 and listPoint[7]!=0.0 and listPoint[13]!=0.0:
                    h = (listPoint[7] - listPoint[13]) * 5
                    if listPoint[0]==0.0 and listPoint[9]!=0.0:
                        y = listPoint[9] - h * 0.5
                    else:
                        y = listPoint[1] - h * 0.3
                else:
                    if listPoint[9]!=0:
                        h = (listPoint[9] - listPoint[5]) * 3.5
                    if listPoint[0]==0.0 and listPoint[9]!=0.0:
                        y = listPoint[9] - h * 0.6
                    else:
                        y = listPoint[1] - h * 0.3

            if listPoint[0]==0.0 or listPoint[2]==0.0:

                if listPoint[10]==0.0 and listPoint[8]!=0.0 and listPoint[12]!=0.0:
                    w = (listPoint[12] - listPoint[8])*5
                    x = listPoint[8] - w*0.3
                else:
                    if listPoint[8]!=0.0:
                        w = (listPoint[10] - listPoint[8])*2
                        x = listPoint[8]  - w*0.3
            else:
                w = (listPoint[2] - listPoint[0]) * 2
                x = listPoint[0]  - w*0.3
            """
            annot.write(" 1 "+ x.__str__() + " " + y.__str__() + " " + w.__str__() + " "+ h.__str__() + "\n")


        else:
            line = line.split()
            if line.__len__()>3:
                if line[3]=="allNameFile.txt":
                    break

        count+=1

annot.close()

