"""
x and y in share images( 640*480)

16 - first point with annnot - circle face (left part)
23 - chin
28 - circle face (right part)
61 - mouth

"""
forannotName=""
annot = open ("D:/my-study/OpenCV/DataSet/DataSet_for_train_Faces_Detector/PositiveImage/annotation.txt",'a')
for k in range(40):
    forannotName="DataSet_for_train_Faces_Detector/PositiveImage/IMM"
    k+=1
    name = "D:/my-study/OpenCV/DataSet/IMM/"
    if k<10:
        name += "0"
        forannotName+="0"
        name +=k.__str__()
        forannotName+=k.__str__()
    else:
        name+=k.__str__()
        forannotName+=k.__str__()

    name+="-"
    forannotName+="-"

    for i in range(6):
        forAnnot = forannotName
        nameImg = name
        i+=1
        nameImg+=i.__str__()
        forAnnot+=i.__str__()
        if k==8 or k==12 or k==14 or k==15 or k==22 or k==30 or k==35:
            nameImg+="f"
            forAnnot+="f"
        else:
            nameImg+="m"
            forAnnot+="m"
        nameImg+=".asf"
        forAnnot+=".jpg"
        file = open (nameImg)
        count = 0
        xrect=0
        yrect=0
        w=0
        h=0
        for line in file:
        #print(line)
            if count>15 and count<74:
                mass = line.split()
                if count==16:
                    xrect = float(mass[2])*640
                    yrect = float(mass[3])*480
                if count==23:
                   h= float(mass[3])*480

                if count==28:
                   w = float(mass[2])*640 - xrect;

                if count==61:
                   h= 4* (h-float(mass[3])*480)
                   yrect = yrect - h*0.6
            count+=1
        file.close()
        annot.write(forAnnot + " 1" + " "+xrect.__str__()  +" " + yrect.__str__() + " "+ w.__str__() + " " + h.__str__()+"\n" )
    #print(xrect.__str__()  +" " + yrect.__str__() + " "+ w.__str__() + " " + h.__str__())
annot.close()



