require 'torch'
require 'nn'
require 'image'

function loadNetModel(path)
	net = torch.load(path)
	net = net:float()
	
	neighborhood = image.gaussian1D(5)
   	normalization = nn.SpatialContrastiveNormalization(1, neighborhood, 1):float()
end

function preprocessing(img)
	img = img:float()
	img = image.rgb2yuv(img)

	local channels = {'y','u','v'}
	--pascal voc
	--local mean = {0.40559885502486, -0.019621851500929, 0.026953143125972}
   	--local std = {0.26126178026709, 0.049694558439293, 0.071862255292542}
   	--wallpapers
   	--local mean = {0.41105262607396, -0.022206692857779, 0.025196086235551}
   	--local std = {0.25762146688176, 0.071657765752595, 0.091645415727616}
   	--annot lfw
   	--local mean = {-0.000024212515815108, 0.00043179346459966, -0.00055251545393477}
   	--local std = {0.31788976333177, 0.1018027835829, 0.097225317979258}
   	--cnn-face-preproc
   	--local mean = {-0.000030917338317801, 0.00044114560185953, -0.00055240759852816}
   	--local std = {0.31813675177978, 0.10214817756977, 0.097131512356802}
   	--cnn-face-new-neg
   	local mean = {-0.00014910521235919, 0.00047613368194075, -0.00054976320288719}
   	local std = {0.3069566982661, 0.096810034332245	, 0.090332393149851	}
   	--local mean = {}
   	--local std = {}
   	for i,channel in ipairs(channels) do
        --mean[i] = img[{i,{},{} }]:mean()
        --std[i] = img[{i,{},{} }]:std()
        --print(mean[i])
      	--print(std[i])
        img[{ i,{},{} }]:add(-mean[i])
    	img[{ i,{},{} }]:div(std[i])
   	end
   	--print(mean[1], " ", mean[2], " ", mean[3])
   	--print(std[1], " ", std[2], " ", std[3])
   	
   	for c in ipairs(channels) do
        img[{ {c},{},{} }] = normalization:forward(img[{ {c},{},{} }])
   	end

	return img
end

function predict2()
	net = torch.load("/home/artem/projects/itlab/itlab-vision-faces-detection/ItlabFaceDetector/net/CNN3-face.net")
	net = net:float()
	test = torch.load("/home/artem/projects/itlab/itlab-vision-faces-detection/torchdb/train.th7")
	print(test.data[{{1}, {1}}])
	error = 0
	--print(test)
	for k = 1, 1 do

		output = net:forward(test.data[k])

		max = output:max()
		for i=1,2 do
			if output[i] == max then
				j = i
				break
			end
		end
		--print(test.labels[k].. " ".. j)
		if not test.labels[k] == j then
			error = error + 1
		end

	end	
	print("Error = ", error)
end

function predict(img)
	
	local maxVal = 255
	nClock = os.clock()
	img = torch.FloatTensor(img)
	--for i = 1, 32*32*3 do
	--	img[i] = img[i] / 255
	--end
	img = torch.reshape(img, 3, 32, 32)
	img:mul(1 / maxVal)
	--img = image.processJPG(img)
	--filename = "/home/artem/projects/itlab/itlab-vision-faces-detection/ItlabFaceDetector/imgs/Clay_Aiken_0002.jpg"
	--tmp = image.scale(image.loadJPG(filename), 32, 32, "bilinear")
	--print(tmp)
	--print(img)
	--image.saveJPG("/home/artem/projects/itlab/opencv.jpg", img)
	--image.saveJPG("/home/artem/projects/itlab/torch.jpg", tmp)

	img = preprocessing(img)
	--print("Preproc time = ", (os.clock() - nClock)*1000)
	--image.saveJPG("/home/artem/projects/itlab/opencv_preproc.jpg", img)
	--tmp = preprocessing(tmp)
	--image.saveJPG("/home/artem/projects/itlab/torch_preproc.jpg", tmp)
	nClock = os.clock()
	output = net:forward(img)
	--print("Forward time = ", (os.clock() - nClock)*1000)
	max = output:max()
	for i=1,2 do
		if output[i] == max then
			j = i
			break
		end
	end
	--print(output)
	return j, -max
end
--predict2()