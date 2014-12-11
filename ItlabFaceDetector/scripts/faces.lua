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
	local mean = {0.41105262607396, -0.022206692857779, 0.025196086235551}
   	local std = {0.25762146688176, 0.071657765752595, 0.091645415727616}
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
	img = torch.FloatTensor(img)
	img = torch.reshape(img, 3, 32, 32)
	img = preprocessing(img)
    --print(img[1])
	output = net:forward(img)

	max = output:max()
	for i=1,2 do
		if output[i] == max then
			j = i
			break
		end
	end
	print(output)
	return j, -max
end

--predict2()