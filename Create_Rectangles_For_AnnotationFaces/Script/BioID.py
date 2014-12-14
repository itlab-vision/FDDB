
"""
Legend:
There are 20 manually placed points on each of your 1521 images.
The markup scheme is as follows:
0 = right eye pupil
1 = left eye pupil
2 = right mouth corner
3 = left mouth corner
4 = outer end of right eye brow
5 = inner end of right eye brow
6 = inner end of left eye brow
7 = outer end of left eye brow
8 = right temple
9 = outer corner of right eye
10 = inner corner of right eye
11 = inner corner of left eye
12 = outer corner of left eye
13 = left temple
14 = tip of nose
15 = right nostril
16 = left nostril
17 = centre point on outer edge of upper lip
18 = centre point on outer edge of lower lip
19 = tip of chin
"""

annot=open("D:/my-study/OpenCV/DataSet/DataSet_for_train_Faces_Detector/PositiveImage/annotation.txt",'a')
for i in range(1521):
    name = "D:/my-study/OpenCV/DataSet/BioID/points_20/bioid_"
    NameImage = "DataSet_for_train_Faces_Detector/PositiveImage/BioID/BioID_"
    if i<10:
        name+= "000" + i.__str__()
        NameImage+= "000" + i.__str__()
    if i>=10 and i<=99:
        name+="00"+i.__str__()
        NameImage+= "00" + i.__str__()
    if i>=100 and i<1000:
        name+="0" + i.__str__()
        NameImage+= "0" + i.__str__()
    if i>=1000:
        name+=i.__str__()
        NameImage+= i.__str__()

    name+=".pts"
    NameImage+=".jpg"
    file = open (name)
    xrect=0
    yrec=0
    w=0
    h=0
    count = 0
    for line in file:
        if i==50:
            print(line)
        if count>3 and count <23:
            mass = line.split()
            if count==11: #left temple
                if i==50:
                    print("left temple "+line)
                w=float(mass[0])
                xrect = float(mass[0]) - 10
                yrec = float(mass[1])
            if count==16: #right temple
                if i==50:
                    print("right temple "+line)

                w= float(mass[0]) - w + 10
            if count==20: #mouth
                h=float(mass[1])
                if i==50:
                    print("mouth  "+line)

            if count== 22: #chip
                if i==50:
                    print("chip "+line)
                h = ( float(mass[1]) - h)*2.5
                yrec = yrec - h*0.25

                if (h+yrec>286):
                    yrec = 286 - h
        count+=1
    file.close()
   # print(xrect.__str__() + " " + yrec.__str__() + " "+ w.__str__() + " "+h.__str__()+" ")
    annot.write(NameImage + " 1 "+xrect.__str__() + " " + abs(yrec).__str__() + " "+ w.__str__() + " "+h.__str__()+"\n" )

annot.close()



