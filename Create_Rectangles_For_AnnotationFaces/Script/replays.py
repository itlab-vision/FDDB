
"""
remove replay in annotation file
"""

file = open("D:/my-study/OpenCV/DataSet/GENKI-R2009a/Subsets/GENKI-SZSL/annot.txt")

#imgName = open("D:/my-study/OpenCV/DataSet/Caltech_WebFaces/annot/Caltech_Name_Image.txt",'w')

annotFile = open("D:/my-study/OpenCV/DataSet/DataSet_for_train_Faces_Detector/PositiveImage/annotation.txt",'a')

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
                annotFile.write("DataSet_for_train_Faces_Detector/PositiveImage/GENKI-R2009a/files/"+two[0]+" ")
                #imgName.write("D:/my-study/OpenCV/DataSet/Caltech_WebFaces/"+two[0]+"\n")
                for str in listName:
                    count+=1

                annotFile.write(count.__str__())

                for str in listName:
                    s= str.split()
                    annotFile.write(" "+s[2]+" "+s[3]+" " + s[4]+" " + s[5])

                annotFile.write("\n")

            else:
                annotFile.write("DataSet_for_train_Faces_Detector/PositiveImage/GENKI-R2009a/files/"+ two[0] + " "+two[1] + " "+two[2] + " "+two[3] + " "+two[4] + " "+two[5] + "\n")
                #imgName.write("D:/my-study/OpenCV/DataSet/Caltech_WebFaces/"+two[0]+"\n")

            listName=[]
            listName.append(line)
            flag=0
        else:
            flag=1

annotFile.close()
#imgName.close()